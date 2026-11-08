#include "Message.hpp"

#include "Utils.hpp"

Message	parseMessage(const std::string &line)
{
	Message	msg;
	size_t	pos = 0;

	for (; pos < line.size() && line[pos] == ' '; )
		++pos;
	if (pos < line.size() && line[pos] == ':')
	{
		++pos;
		for (; pos < line.size() && line[pos] != ' '; )
			msg.prefix += line[pos++];
		for (; pos < line.size() && line[pos] == ' '; )
			++pos;
	}
	for (; pos < line.size() && line[pos] != ' '; )
		msg.command += line[pos++];
	msg.command = toUpperString(msg.command);
	for (; pos < line.size(); )
	{
		for (; pos < line.size() && line[pos] == ' '; )
			++pos;
		if (pos >= line.size())
			break ;
		if (line[pos] == ':')
		{
			msg.params.push_back(line.substr(pos + 1));
			break ;
		}
		size_t	end = line.find(' ', pos);
		if (end == std::string::npos)
			end = line.size();
		msg.params.push_back(line.substr(pos, end - pos));
		pos = end;
	}
	return (msg);
}
