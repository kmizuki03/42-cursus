#include "FileReplacer.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

FileReplacer::FileReplacer(const std::string &filename, const std::string &s1,const std::string &s2): _filename(filename), _s1(s1), _s2(s2) {}

std::string FileReplacer::replaceAll(const std::string &content) const
{
	if (_s1.empty())
		return (content);

	std::string result;
	std::string::size_type pos = 0;
	std::string::size_type found;
	while ((found = content.find(_s1, pos)) != std::string::npos)
	{
		result.append(content, pos, found - pos);
		result.append(_s2);
		pos = found + _s1.length();
	}

	result.append(content, pos, content.length() - pos);
	return (result);
}

bool FileReplacer::run() const
{
	std::ifstream infile(_filename.c_str());

	if (!infile.is_open())
	{
		std::cerr << "Error: Cannot open file '" << _filename << "'" << std::endl;
		return (false);
	}

	std::stringstream ss;
	ss << infile.rdbuf();
	std::string content = ss.str();

	std::ofstream outfile((_filename + ".replace").c_str());

	if (!outfile.is_open())
	{
    std::cerr << "Error: Cannot create output file" << std::endl;
    return (false);
	}

	outfile << replaceAll(content);
	return (true);
}
