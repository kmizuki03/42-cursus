#include "Utils.hpp"

#include <sstream>

std::string	toLowerString(const std::string &input)
{
	std::string	result(input);

	for (size_t i = 0; i < result.size(); ++i)
	{
		if (result[i] >= 'A' && result[i] <= 'Z')
			result[i] = static_cast<char>(result[i] - 'A' + 'a');
	}
	return (result);
}

std::string	toUpperString(const std::string &input)
{
	std::string	result(input);

	for (size_t i = 0; i < result.size(); ++i)
	{
		if (result[i] >= 'a' && result[i] <= 'z')
			result[i] = static_cast<char>(result[i] - 'a' + 'A');
	}
	return (result);
}

std::string	numberToString(long value)
{
	std::ostringstream	stream;

	stream << value;
	return (stream.str());
}

std::vector<std::string>	splitString(const std::string &input, char delimiter)
{
	std::vector<std::string>	result;
	std::string					token;
	std::istringstream			stream(input);

	for (; std::getline(stream, token, delimiter); )
	{
		if (!token.empty())
			result.push_back(token);
	}
	return (result);
}

static bool	isNicknameSpecial(char c)
{
	return (c == '[' || c == ']' || c == '\\' || c == '`' || c == '_'
		|| c == '^' || c == '{' || c == '|' || c == '}');
}

static bool	isLetter(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

static bool	isDigit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	isValidNickname(const std::string &nickname)
{
	if (nickname.empty() || nickname.size() > 30)
		return (false);
	if (!isLetter(nickname[0]) && !isNicknameSpecial(nickname[0]))
		return (false);
	for (size_t i = 1; i < nickname.size(); ++i)
	{
		if (!isLetter(nickname[i]) && !isDigit(nickname[i])
			&& !isNicknameSpecial(nickname[i]) && nickname[i] != '-')
			return (false);
	}
	return (true);
}

bool	isChannelPrefix(char c)
{
	return (c == '#' || c == '&');
}

bool	isValidChannelName(const std::string &name)
{
	if (name.size() < 2 || name.size() > 50)
		return (false);
	if (!isChannelPrefix(name[0]))
		return (false);
	for (size_t i = 1; i < name.size(); ++i)
	{
		char	c = name[i];

		if (c == ' ' || c == ',' || c == ':' || c == '\a'
			|| (c >= 0 && c < ' '))
			return (false);
	}
	return (true);
}
