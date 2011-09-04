#include "AbstractClass.hpp"

AbstractClass::AbstractClass()
{
	mBaseLogger = new Logger();
}

Logger* AbstractClass::baseLogger()
{
	return mBaseLogger;
}
