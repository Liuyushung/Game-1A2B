//Program 1A2B
//Using lambda function
/*
Step1:Generate all possiable permutation
Step2:Get user's answer
Step3:Remove the impossiable answer
Step4:If not correct, repeat Step2 to Step4 until success
*/
#include <iostream>		//for normal I/O
#include <string>
#include <vector>
#include <iterator>
#include <regex>
#include <cstdlib>
#include <sstream>
#include "Permutation.h"
#include "UserAnswer.h"
#include "Exception.h"
//#define	DEBUG

using std::iterator;
using std::vector;
using std::string;
using std::ostringstream;
using std::cin;
using std::cout;
using std::endl;
using std::regex;
using std::regex_match;
using std::regex_search;
using std::getline;

void computerGuess(void)
{
	Permutation library;
	UserAnswer AnswerInMind;
	vector<string>::iterator currentPos;
	int count = 0;

	//Prompt messange
	cout << "Enter your answer like nAmB or nA or mB, don't care uppercase or lowercase.\n\n";

	while (1)
	{
		try {
			currentPos = library.getRandom();	//Generate a random guess
			library.printChoice(currentPos);	//Show this guess
			cin >> AnswerInMind;	//Get user's answer
			++count;
			if (AnswerInMind.getAnswer().compare("4A0B") == 0)  break;	//Correct! end while
			library.removeChoice(AnswerInMind, currentPos);		//Delete the impossiable choice
		}
		catch (GuessError)
		{
			string choice;
			int counter = 0;

			do {
				cout << "\nIf you want to paly this game again, "
					<< "please enter 'y', otherwise, enter 'n' to quit the game.\n";
				cin >> choice;
				++counter;
				if (counter > 10)
				{
					cout << "Are you kidding me? "
						<< "You have already given me BAD answer ten times! "
						<< "I'm angry now.\n";
					exit(1);
				}
			} while (!regex_match(choice, regex("[yYnN]")));

			if (regex_match(choice, regex("[yY]")))
			{
				library.reset();
				count = 0;
				cout << "\nI'm ready to play another round.\n";
				continue;
			}
			else
				exit(1);
		}
	}
	cout << "\nExcellent!!   "
		<< "I make it with " << count << " guesses.\n";
}

void menGuess(void)
{
	int digit = 0, count = 0;
	string answer, input;

	//Generate Guess
	while (digit < 4)
	{
		char c;
		c = (rand() % 10) + '0';
		if (answer.find(c) == string::npos)
		{
			answer = answer + c;
			++digit;
		}
	}
#ifdef DEBUG
	cout << answer << endl;
#endif // DEBUG
	cout << "Enter your guess like 1593" << endl;
	while (1)
	{
		string compare_result;

		cout << ">";
		cin >> input;
		//BackDoor
		if (regex_match(input,regex("shit",std::regex_constants::icase))
			|| regex_match(input, regex("fuck",std::regex_constants::icase)))
		{
			cout << answer << endl;
			cout << ">";
			cin >> input;
		}
		compare_result = compareNAMB(answer, input);
		cout << compare_result << endl;
		++count;

		if (!compare_result.compare("4A0B"))
		{
			cout << "Congratulation!! " << "You guess " << count << " times to hit the answer!!" << endl;
			break;
		}
	}
}

int main()
{
	string choice;

	srand(static_cast<unsigned>(time(NULL)));

	cout << "If you want to guess the answer, please input \"I want\" " << endl
		<< "Otherwise, input \"Computer guess\"" << endl;
	cout << "If you wnat to leave. input \"Quit\" to leave the game" << endl;

	while(1) {
		cout << ">>";
		getline(cin, choice, '\n');
		
		if (regex_search(choice, regex("I want", std::regex_constants::icase)))
		{
#ifdef DEBUG
			cout << "I want" << endl;
#endif // DEBUG
			menGuess();
			cin.ignore(1);	//ignore '\n'
		}
		else if (regex_search(choice, regex("Computer guess", std::regex_constants::icase)))
		{
#ifdef DEBUG
			cout << "Computer guess" << endl;
#endif // DEBUG
			computerGuess();
			cin.ignore(1);	//ignore '\n'
		}
		else if (regex_search(choice, regex("Quit", std::regex_constants::icase)))
			break;
		else
			cout << "Bad answer. Please answer seriously." << endl;
	}	//end while

	system("pause");

	return 0;
}