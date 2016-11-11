#include "MyMap.h"
#include <iostream>
#include <string>
using namespace std;

void foo()
{
	MyMap<string,double> nameToGPA; // maps student name to GPA

	// add new items to the binary search tree-based map
	nameToGPA.associate("Carey", 3.5); // Carey has a 3.5 GPA
	nameToGPA.associate("David", 3.99); // David beat Carey
	nameToGPA.associate("Abe", 3.2); // Abe has a 3.2 GPA

	double* davidsGPA = nameToGPA.find("David");
	if (davidsGPA != NULL)
		*davidsGPA = 1.5; // after a re-grade of David’s exam

	nameToGPA.associate("Carey", 4.0); // Carey deserves a 4.0
	// replaces old 3.5 GPA

	double* lindasGPA = nameToGPA.find("Linda");
	if (lindasGPA == NULL)
		cout << "Linda is not in the roster!" << endl;
	else
		cout << "Linda’s GPA is: " << *lindasGPA << endl;

	// now let’s print all associations out in a level-order ordering
	cout << "Here are the " << nameToGPA.size() << " associations: "
	<< endl;

	string name;
	for (double* GPAptr = nameToGPA.getFirst(name); GPAptr != NULL;
	GPAptr = nameToGPA.getNext(name))
	{
		 cout << name << " has a GPA of " << *GPAptr << endl;
	}
	// The above loop would print:
	// Student Carey has a GPA of 4.0
	// Student Abe has a GPA of 3.2
	// Student David has a GPA of 1.5
}

int main()
{
	foo();
}