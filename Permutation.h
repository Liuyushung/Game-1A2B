#include <string>
#include <vector>
#include <map>
#include "UserAnswer.h"
using std::string;
using std::vector;
using std::multimap;
#ifndef PERMUATAION_H
#define PERMUTATION_H

string compareNAMB(string reference, string element);

class Permutation
{
public:
	static const int TEN = 10;

	Permutation();
	void printChoice(vector<string>::iterator &) const;
	void printChoice(const string &);
	void removeChoice(UserAnswer &, vector<string>::iterator &);
	void reset();
	vector<string>::iterator getRandom();


private:
	vector<string> password;	//Store all permutation
	multimap<string, string> record;	//Store history answer, key for

	void historyCheck(const string &);
	void resetHelper();
	void setRecord(string, string);
};

#endif