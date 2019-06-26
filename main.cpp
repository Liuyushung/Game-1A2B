//Program 1A2B
//Using lambda function
#include <iostream>		//for normal I/O
#include <cstdlib>
#include "ImportantFunction.h"
//#define	DEBUG


int main()
{
	char choice;

	srand(static_cast<unsigned>(time(NULL)));

	cout << "If you want to guess the answer, please input \"1\" " << endl
		<< "If you want the computer guess your answer, input \"2\"" << endl;
	cout << "If you wnat to leave. input \"Q\" to leave the game" << endl;

	while(1) {
		cout << ">>";
		cin >> choice;
		
		switch (choice)
		{
		case '1':
			menGuess();
			break;
		case '2':
			computerGuess();
			break;
		case'Q':
		case'q':
			exit(0);
		default:
			cout << "Bad answer. Please answer seriously." << endl;
		}
	}	//end while

	system("pause");

	return 0;
}