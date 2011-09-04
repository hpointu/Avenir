#ifndef ABSTRACTCLASS_HPP
#define ABSTRACTCLASS_HPP

#include "Logger.hpp"

class AbstractClass
{
public:
    AbstractClass();

	Logger* baseLogger();

private:
	Logger *mBaseLogger;
};

#endif // ABSTRACTCLASS_HPP
