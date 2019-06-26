#include <sstream>	//for ostringstream
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstdlib>		//for rand, srand
#include <time.h>		//for time
#include "Permutation.h"
#include "exception.h"
#define FOURDIGITS 4
//#define DEBUG
using std::ostringstream;
using std::cin;
using std::cout;
using std::endl;
using std::remove_if;
using std::iterator;
using std::string;

//Removie_if lambda
string compareNAMB(string reference, string element)
{
	int countA = 0, countB = 0;
	ostringstream oss;
	for (int i = 0; i < FOURDIGITS; ++i)
	{
		for (int j = 0; j < FOURDIGITS; ++j)
		{
			//Position and number are both correct
			if (i == j && reference.at(i) == element.at(j))
				++countA;
			//Position is wrong but number is right
			else if (i != j && reference.at(i) == element.at(j))
				++countB;
		}	//end inside for
	}	//end outside for

	oss << countA << "A" << countB << "B";	//Creat a string
	return oss.str();
}
//Constructor
Permutation::Permutation()
{
	resetHelper();
}
void
Permutation::printChoice(vector<string>::iterator &position) const
{
	//Format output
	cout << "(" << position->at(0) << "," << position->at(1)
		<< "," << position->at(2) << "," << position->at(3) << ")"
		<< " -- ";
}

void
Permutation::printChoice(const string &S)
{
	cout << "(" << S.at(0) << "," << S.at(1)
		<< "," << S.at(2) << "," << S.at(3) << ")";
}

void 
Permutation::removeChoice(UserAnswer &userInput, vector<string>::iterator &value)
{
	string tempCmp = *value;		//Hold the value to compare
	string user = userInput.answer; //Hold the user input answer to compare

	setRecord(*value, userInput.answer);

	//Delete the impossiable permutation
	password.erase
	(
		remove_if
		(password.begin(), password.end(), [userInput, value](string x)
	{ return userInput.answer.compare(compareNAMB(*value, x)) != 0; }
		)	//end remove_if
		, password.end()
	);	//end erase
}

void 
Permutation::reset()
{
	resetHelper();
}

vector<string>::iterator 
Permutation::getRandom()
{
	vector<string>::iterator randomAccess = this->password.begin();	//Point to begin

	try {
		if (!password.size())
			throw GuessError();

		srand(static_cast<unsigned>(time(NULL)));
		int range = rand() % password.size();
		randomAccess += range;

		return randomAccess;
	}
	catch (GuessError &guessError)
	{
		
		string check_answer;

		cout << guessError.what() << endl;
		cout << "I can find the error input. Please tell me your real answer: ";
		cin >> check_answer;

		historyCheck(check_answer);

		throw;
	}
	
}

void
Permutation::historyCheck(const string &check_answer)
{
	multimap<string, string>::iterator reviewIte;

	for (reviewIte = record.begin(); reviewIte != record.end(); ++reviewIte)
	{
		string realAnswer;
		realAnswer = compareNAMB(reviewIte->first, check_answer);
#ifdef DEBUG
		cout << realAnswer << endl;
#endif // DEBUG
		if (reviewIte->second.compare(realAnswer) != 0)
		{
			cout << "When I guess ";
			printChoice(reviewIte->first);
			cout << ". You answer " << reviewIte->second;
			cout << ". But you should answer " << realAnswer << endl;
		}	//end if
	}	//end for
}

//Utility Function
void 
Permutation::resetHelper()
{
	ostringstream oss;
	string temp;

	//Reset password and record
	password.clear();
	record.clear();

	for (int i = 0; i < TEN; ++i)
	{
		for (int j = 0; j < TEN; ++j)
		{
			//No duplicate number
			if (i == j)	continue;

			for (int k = 0; k < TEN; ++k)
			{
				//No duplicate number
				if (i == k || j == k) continue;

				for (int l = 0; l < TEN; ++l)
				{
					//No duplicate number
					if (i == l || j == l || k == l) continue;
					//Create password
					oss << i << j << k << l;
					temp = oss.str();
					password.push_back(temp);
					//Reset ostringstream
					oss.str("");
				}
			}
		}
	}
#ifdef DEBUG
	cout << password.size() << endl;
#endif // DEBUG

}

void
Permutation::setRecord(string number, string answer)
{
	record.insert(std::pair<string, string>(number, answer));

#ifdef DEBUG
	multimap<string, string>::iterator Ite = record.begin();
	for (; Ite != record.end(); ++Ite)
	{
		cout << "DEBUG" << " first: " << Ite->first << " second: " << Ite->second << endl;
	}
#endif
}
