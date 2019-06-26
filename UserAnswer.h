#ifndef USERANSWER_H
#define USERANSWER_H
#include <iostream>
#include <string>
using std::istream;
using std::string;

class UserAnswer
{
	friend class Permutation;
	friend istream &operator>>(istream &input, UserAnswer &X);

public:
	UserAnswer(string s = "") :answer(s), nA(0), mB(0) {}
	void setA(const char a) { nA = a - '0'; }
	void setB(const char b) { mB = b - '0'; }
	int getA() const { return nA; }
	int getB() const { return mB; }
	string getAnswer() const { return answer; }

private:
	string answer;		//Store user input nAmb
	int nA, mB;

	//Utility function
	void setHelper();
};

#endif // !USERANSWER_H
