#include "ScalarConverter.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <climits>
#include <cctype>

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
	(void)other;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
	(void)other;
	return *this;
}

ScalarConverter::~ScalarConverter()
{
}

static bool	isCharLiteral(const std::string &s)
{
	if (s.length() == 1 && !std::isdigit(static_cast<unsigned char>(s[0])))
	{
		return true;
	}
	return false;
}

static bool	isIntLiteral(const std::string &s)
{
	size_t	i = 0;

	if (s.empty())
	{
		return false;
	}
	if (s[i] == '+' || s[i] == '-')
	{
		i++;
	}
	if (i == s.length())
	{
		return false;
	}
	while (i < s.length())
	{
		if (!std::isdigit(static_cast<unsigned char>(s[i])))
		{
			return false;
		}
		i++;
	}
	return true;
}

static bool	isValidDecimal(const std::string &s)
{
	const char	*str = s.c_str();
	char		*end = NULL;

	if (s.empty())
	{
		return false;
	}
	std::strtod(str, &end);
	if (*end != '\0')
	{
		return false;
	}
	if (s.find('.') == std::string::npos)
	{
		return false;
	}
	return true;
}

static bool	isFloatLiteral(const std::string &s)
{
	if (s == "nanf" || s == "+inff" || s == "-inff" || s == "inff")
	{
		return true;
	}
	if (s.length() < 2 || s[s.length() - 1] != 'f')
	{
		return false;
	}
	return isValidDecimal(s.substr(0, s.length() - 1));
}

static bool	isDoubleLiteral(const std::string &s)
{
	if (s == "nan" || s == "+inf" || s == "-inf" || s == "inf")
	{
		return true;
	}
	return isValidDecimal(s);
}

static void	printChar(double value, bool special)
{
	std::cout << "char: ";
	if (special || value < 0.0 || value > 127.0)
	{
		std::cout << "impossible" << std::endl;
		return;
	}
	char	c = static_cast<char>(value);
	if (!std::isprint(static_cast<unsigned char>(c)))
	{
		std::cout << "Non displayable" << std::endl;
		return;
	}
	std::cout << "'" << c << "'" << std::endl;
}

static void	printInt(double value, bool special)
{
	std::cout << "int: ";
	if (special || value < static_cast<double>(INT_MIN)
		|| value > static_cast<double>(INT_MAX))
	{
		std::cout << "impossible" << std::endl;
		return;
	}
	std::cout << static_cast<int>(value) << std::endl;
}

static void	printFloating(const std::string &label, double value, char suffix)
{
	std::ostringstream	oss;

	oss << value;
	std::string	repr = oss.str();
	if (repr.find('.') == std::string::npos
		&& repr.find('e') == std::string::npos)
	{
		repr += ".0";
	}
	std::cout << label << ": " << repr;
	if (suffix == 'f')
	{
		std::cout << "f";
	}
	std::cout << std::endl;
}

void ScalarConverter::convert(const std::string &literal)
{
	bool	special = false;
	double	value = 0.0;
	std::string	floatRepr;
	std::string	doubleRepr;

	if (literal == "nan" || literal == "nanf")
	{
		special = true;
		floatRepr = "nanf";
		doubleRepr = "nan";
	}
	else if (literal == "+inf" || literal == "+inff"
		|| literal == "inf" || literal == "inff")
	{
		special = true;
		floatRepr = "+inff";
		doubleRepr = "+inf";
	}
	else if (literal == "-inf" || literal == "-inff")
	{
		special = true;
		floatRepr = "-inff";
		doubleRepr = "-inf";
	}
	else if (isCharLiteral(literal))
	{
		value = static_cast<double>(literal[0]);
	}
	else if (isIntLiteral(literal))
	{
		value = static_cast<double>(std::strtol(literal.c_str(), NULL, 10));
	}
	else if (isFloatLiteral(literal))
	{
		value = std::strtod(literal.c_str(), NULL);
	}
	else if (isDoubleLiteral(literal))
	{
		value = std::strtod(literal.c_str(), NULL);
	}
	else
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}

	printChar(value, special);
	printInt(value, special);
	if (special)
	{
		std::cout << "float: " << floatRepr << std::endl;
		std::cout << "double: " << doubleRepr << std::endl;
		return;
	}
	printFloating("float", static_cast<float>(value), 'f');
	printFloating("double", value, 'd');
}
