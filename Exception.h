#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
using std::runtime_error;

class GuessError : public runtime_error
{
public:
	GuessError()
		: runtime_error("Maybe your answer is changed") {}
};

#endif // !EXCEPTION_H