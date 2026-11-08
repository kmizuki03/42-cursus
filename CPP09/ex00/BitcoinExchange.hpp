#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange
{
	private:
		std::map<std::string, double>	_database;

		bool	isValidDate(const std::string &date) const;
		enum ValueStatus { VALUE_VALID, VALUE_INVALID, VALUE_NEGATIVE, VALUE_TOO_LARGE };
		ValueStatus	parseValue(const std::string &str, double &value) const;
		double	getRate(const std::string &date) const;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		bool	loadDatabase(const std::string &filename);
		bool	processInput(const std::string &filename) const;
};

#endif
