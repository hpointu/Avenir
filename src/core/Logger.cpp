#include "Logger.hpp"

Logger::Logger()
{
}

void Logger::debugLine(string msg)
{
#ifndef AV_DEBUG
	// do nothing :)
#else
	cout << msg << endl;
#endif
}

void Logger::errorLine(string msg)
{
	cerr << msg << endl;
}

void Logger::infoLine(string msg)
{
	cout << msg << endl;
}
