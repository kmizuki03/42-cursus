#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include <vector>

std::string					toLowerString(const std::string &input);
std::string					toUpperString(const std::string &input);
std::string					numberToString(long value);
std::vector<std::string>	splitString(const std::string &input, char delimiter);
bool						isValidNickname(const std::string &nickname);
bool						isValidChannelName(const std::string &name);
bool						isChannelPrefix(char c);

#endif
