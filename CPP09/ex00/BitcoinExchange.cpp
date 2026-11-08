#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <cerrno>
#include <cfloat>

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _database(other._database)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		this->_database = other._database;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

static std::string	trim(const std::string &str)
{
	std::string::size_type	start = str.find_first_not_of(" \t\r");
	std::string::size_type	end = str.find_last_not_of(" \t\r");

	if (start == std::string::npos)
	{
		return "";
	}
	return str.substr(start, end - start + 1);
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
	{
		return false;
	}
	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
		{
			continue;
		}
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
		{
			return false;
		}
	}

	int	year = std::atoi(date.substr(0, 4).c_str());
	int	month = std::atoi(date.substr(5, 2).c_str());
	int	day = std::atoi(date.substr(8, 2).c_str());

	if (year < 1 || month < 1 || month > 12 || day < 1)
	{
		return false;
	}

	static const int	daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int					maxDay = daysInMonth[month - 1];
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
	{
		maxDay = 29;
	}
	if (day > maxDay)
	{
		return false;
	}
	return true;
}

static bool isDecimal(const std::string &str)
{
	bool seenDigit = false;
	bool seenDot = false;
	std::string::size_type i = 0;

	if (str.empty())
		return false;
	if (str[0] == '+' || str[0] == '-')
		i = 1;
	for (; i < str.length(); ++i)
	{
		if (str[i] == '.' && !seenDot)
			seenDot = true;
		else if (std::isdigit(static_cast<unsigned char>(str[i])))
			seenDigit = true;
		else
			return false;
	}
	return seenDigit;
}

static bool parseDecimal(const std::string &str, double &value)
{
	if (!isDecimal(str))
		return false;
	char *end = NULL;
	errno = 0;
	value = std::strtod(str.c_str(), &end);
	return errno != ERANGE && *end == '\0'
		&& value >= -DBL_MAX && value <= DBL_MAX;
}

BitcoinExchange::ValueStatus BitcoinExchange::parseValue(
	const std::string &str, double &value) const
{
	if (!isDecimal(str))
		return VALUE_INVALID;

	bool nonZero = false;
	for (std::string::size_type i = 0; i < str.size(); ++i)
		if (str[i] >= '1' && str[i] <= '9')
			nonZero = true;
	if (str[0] == '-' && nonZero)
		return VALUE_NEGATIVE;

	std::string::size_type start = (str[0] == '+' || str[0] == '-') ? 1 : 0;
	std::string::size_type dot = str.find('.');
	std::string::size_type end = (dot == std::string::npos) ? str.size() : dot;
	while (start < end && str[start] == '0')
		++start;
	std::string integer = str.substr(start, end - start);
	if (integer.size() > 4 || (integer.size() == 4 && integer > "1000"))
		return VALUE_TOO_LARGE;
	if (integer == "1000" && dot != std::string::npos)
		for (std::string::size_type i = dot + 1; i < str.size(); ++i)
			if (str[i] != '0')
				return VALUE_TOO_LARGE;
	if (!parseDecimal(str, value))
		return VALUE_INVALID;
	return VALUE_VALID;
}

double BitcoinExchange::getRate(const std::string &date) const
{
	std::map<std::string, double>::const_iterator	it = this->_database.lower_bound(date);

	if (it != this->_database.end() && it->first == date)
	{
		return it->second;
	}
	if (it == this->_database.begin())
	{
		return -1.0;
	}
	--it;
	return it->second;
}

static bool readLine(std::ifstream &file, std::string &line, bool &readError)
{
	errno = 0;
	if (std::getline(file, line))
		return true;
	readError = file.bad() || !file.eof() || errno != 0;
	return false;
}

bool BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open database file." << std::endl;
		return false;
	}
	std::map<std::string, double> database;
	std::string line;
	bool firstLine = true;
	bool readError = false;
	while (readLine(file, line, readError))
	{
		line = trim(line);
		if (line.empty())
			continue;
		if (firstLine)
		{
			firstLine = false;
			if (line == "date,exchange_rate")
				continue;
		}
		std::string::size_type comma = line.find(',');
		if (comma == std::string::npos)
		{
			std::cerr << "Error: bad database input => " << line << std::endl;
			return false;
		}
		std::string date = trim(line.substr(0, comma));
		std::string rateStr = trim(line.substr(comma + 1));
		double rate = 0.0;
		if (!isValidDate(date) || !parseDecimal(rateStr, rate) || rate < 0.0)
		{
			std::cerr << "Error: bad database input => " << line << std::endl;
			return false;
		}
		database[date] = rate;
	}
	if (readError || database.empty())
	{
		std::cerr << "Error: empty or unreadable database." << std::endl;
		return false;
	}
	_database.swap(database);
	return true;
}

bool BitcoinExchange::processInput(const std::string &filename) const
{
	std::ifstream	file(filename.c_str());

	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return false;
	}

	std::string	line;
	bool		firstLine = true;
	bool		readError = false;
	while (readLine(file, line, readError))
	{
		line = trim(line);
		if (line.empty())
			continue;
		if (firstLine)
		{
			firstLine = false;
			if (trim(line) == "date | value")
			{
				continue;
			}
		}

		std::string::size_type	sep = line.find('|');
		if (sep == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string	date = trim(line.substr(0, sep));
		std::string	valueStr = trim(line.substr(sep + 1));

		if (!this->isValidDate(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		double	value = 0.0;
		ValueStatus status = this->parseValue(valueStr, value);
		if (status == VALUE_INVALID)
		{
			std::cerr << "Error: bad input => " << valueStr << std::endl;
			continue;
		}
		if (status == VALUE_NEGATIVE)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (status == VALUE_TOO_LARGE)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		double	rate = this->getRate(date);
		if (rate < 0.0)
		{
			std::cerr << "Error: no earlier date in database => " << date << std::endl;
			continue;
		}
		if (value > 1.0 && rate > DBL_MAX / value)
		{
			std::cerr << "Error: result out of range." << std::endl;
			continue;
		}
		std::cout << date << " => " << value << " = " << value * rate << std::endl;
	}
	if (readError)
	{
		std::cerr << "Error: could not read file." << std::endl;
		return false;
	}
	return true;
}
