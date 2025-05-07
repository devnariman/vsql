#include <iostream>
#include "Vsql.h"
#include <vector>
using namespace std;

int main() {

	Vsql a1("test1.db");


	vector<string> b = a1.get_All_TableName();


	b[0];

	a1.Add_Field(b[0] , "test", Vsql::Integer, "2");

	return 0;
}