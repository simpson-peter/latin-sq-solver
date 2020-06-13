#include "latinsquare.h"
#include <set>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

/* NTS: EDGE CASES TO CHECK:
* -Excessively large contents set
* -Too small contents set
* -Unordered int contents passed in
* -Non-int LSqaure made with the minimal constructor
* -See if this can work with a class that doesn't support << if I don't call print()
*/
//this is a default testing suite to demo some of the basic possibilites of the Latin Square Solver
int main(int argc, char* argv[]){

	test3x3Integer();

	//create a contents for a hex-dec Latin Square
	std::set<std::string> hex_colors;

	hex_colors.insert("#d50000"); //Red
	hex_colors.insert("#00c853"); //Green
	hex_colors.insert("#2962ff"); //Blue
	hex_colors.insert("#6200ea"); //Deep Purple
	hex_colors.insert("#ffd600"); //Yellow
	hex_colors.insert("#f7f7e1"); //Off-White

	LatinSquare<std::string> lsqaure_hex(hex_colors.size(), hex_colors);

	std::cout<<"The Second Latin Square: "<<std::endl;
	lsqaure_hex.print(std::cout);

	return 0;
}

//generates and prints a 3x3 Latin Square, populating it with numbers [0, 2] 
void test3x3Integer(){
	std::set<int> int_contents;
	int_contents.insert(0);
	int_contents.insert(1);
	int_contents.insert(2);

	//constructs a 3 x 3 Latin Square with integers
	LatinSquare<int> lsqaure_int(3, int_contents); 

	std::cout<<"3 x 3 Integer Latin Square: "<<std::endl;
	std::cout<<lsqaure_int<<std::endl;
}

//generates and prints a n x n Latin Square, populating it with a set of n random numbers
void testNxNInteger(int n){

	//seed random number generator
	srand (time(NULL));

	std::set<int> int_contents;

	for(int i = 0; i < n; i++){
		int_contents.insert(rand());
	}

	LatinSquare<int> lsqaure_nxn_int(3, int_contents);

	std::cout<< n <<" x "<< n <<" Integer Latin Square: "<<std::endl;
	std::cout<<lsqaure_nxn_int<<std::endl;
}




