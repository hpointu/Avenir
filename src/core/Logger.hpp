#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <iostream>

using namespace std;

class Logger
{
public:
    Logger();

	void debugLine(string msg);
	void errorLine(string msg);
	void infoLine(string msg);
};

#endif // LOGGER_HPP
