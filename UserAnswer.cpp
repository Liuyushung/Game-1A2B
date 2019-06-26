#include <sstream>	//for ostringstream
#include <cctype>	//for isalpha, toupper
#include <regex>
#include "UserAnswer.h"
using std::ostringstream;
using std::regex;
using std::regex_match;
using std::regex_replace;

//UserAnswer overload operator>>
istream &operator>>(istream &input, UserAnswer &X)
{
	input >> X.answer;
	X.setHelper();

	return input;
}
//Utility function
void UserAnswer::setHelper()
{

	char tempChar;
	unsigned APos, BPos;
	ostringstream oss;

	//Format the password to uppercase
	for (unsigned i = 0; i < this->answer.size(); ++i)
	{
		if (isalpha(this->answer.at(i)))
		{
			tempChar = toupper(this->answer.at(i));
			this->answer.at(i) = tempChar;
		}
	}

	//Set nA,mB
	APos = this->answer.find("A");
	BPos = this->answer.find("B");

	if (APos == string::npos && BPos == string::npos)
	{
		this->setA('0');
		this->setB('0');
		oss << "0A0B";
		this->answer = oss.str();
	}
	else if (APos == string::npos)
	{
		this->setA('0');
		char c = this->answer.at(BPos - 1);
		this->setB(c);
		oss << "0A" << c << "B";
		this->answer = oss.str();
	}
	else if (BPos == string::npos)
	{
		this->setB('0');
		char c = this->answer.at(APos - 1);
		this->setA(c);
		oss << c << "A" << "0B";
		this->answer = oss.str();
	}
	else
	{
		char c1, c2;
		c1 = this->answer.at(APos - 1);
		this->setA(c1);
		c2 = this->answer.at(BPos - 1);
		this->setB(c2);
		oss << c1 << "A" << c2 << "B";
		this->answer = oss.str();
	}

}