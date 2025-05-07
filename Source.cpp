#include <iostream>
#include "Vsql.h"
#include <vector>
#include <map>
using namespace std;

int main() {

	Vsql a1("test1.db");

	std::map<std::string, std::string> test={
		{"c1" , "a1"},
		{"c2" , "a2"},
		{"c3" , "a3"},
		{"c4" , "a4"},
		{"c5" , "a5"},
		{"c6" , "a6"},
	
	};

	string b1 = "b1";


	a1.add_row(b1, test);

	return 0;
}