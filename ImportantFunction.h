#ifndef IMPORTANT
#define IMPORTANT

#include <iostream>		//for normal I/O
#include <string>
#include <vector>
#include <iterator>
#include <regex>
#include <cstdlib>
#include "Permutation.h"
#include "UserAnswer.h"
#include "Exception.h"

using std::iterator;
using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::regex;
using std::regex_match;

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
	cout << "Enter your guess like 1593" << endl;
	while (1)
	{
		string compare_result;

		cout << ">";
		cin >> input;
		//BackDoor
		if (regex_match(input, regex("shit", std::regex_constants::icase))
			|| regex_match(input, regex("fuck", std::regex_constants::icase)))
		{
			cout << "你真得我心啊～～\n那我就告訴你答案吧，";
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

#endif