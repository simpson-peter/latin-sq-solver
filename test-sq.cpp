#include "latinsquare.h"
#include <set>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

void test3x3Integer();
void testNxNInteger(unsigned n);
void test6x6Hex();
void megaContents();

/* NTS: EDGE CASES TO CHECK:
* -Too small contents set
* -Unordered int contents passed in
* -Assignment Operator (use valgrind too)
* -Const contents set (with const dimension)
* -Const contesnts set and dimension
* -Copy Constructor
* -Non-int LSqaure made with the minimal constructor
* -See if this can work with a class that doesn't support << if I don't call print()
*/
//This is a default testing suite to demo some of the basic possibilites of the Latin Square Solver
int main(int argc, char* argv[]){

	test3x3Integer();
	testNxNInteger(9);
	test6x6Hex();
	megaContents();

	return 0;
}

//Generates and prints a 3x3 Latin Square, populating it with numbers [0, 2] 
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

/*
* Generates and prints a n x n Latin Square, 
* populating it with a set of n random numbers in the range [0, n*2)
*/
void testNxNInteger(unsigned n){

	//seed random number generator
	srand (time(NULL));

	std::set<int> int_contents;

	for(int i = 0; i < (int) n; i++){
		//generate random number to be added
		int new_int = rand() % (n*2);

		//if new_int's not in the set, go ahead and add it.
		if(int_contents.find(new_int) == int_contents.end()){

			int_contents.insert(new_int);

		//if new_int is in the set, we need to try again as the set does not accept duplicates
		}else{

			i = i-1;

		}
	}

	LatinSquare<int> lsqaure_nxn_int(n, int_contents);

	std::cout<< n <<" x "<< n <<" Integer Latin Square: "<<std::endl;
	std::cout<<lsqaure_nxn_int<<std::endl;
}

//Generates and prints a 6 x 6 Latin Square populated with 6 color hex codes
void test6x6Hex(){
	//create a contents for a hex-dec Latin Square
	std::set<std::string> hex_colors;

	hex_colors.insert("#d50000"); //Red
	hex_colors.insert("#00c853"); //Green
	hex_colors.insert("#2962ff"); //Blue
	hex_colors.insert("#6200ea"); //Deep Purple
	hex_colors.insert("#ffd600"); //Yellow
	hex_colors.insert("#f7f7e1"); //Off-White

	LatinSquare<std::string> lsqaure_hex(hex_colors.size(), hex_colors);

	std::cout<<"6 x 6 Hex Code Latin Square: "<<std::endl;
	lsqaure_hex.print(std::cout);
}

/*
* Generates and prints a large contents set for the Latin square, but does not use most of it.
*
* This test case is illustrative of how the Latin Square's time complexity tracks with the dimension
* of the square, rather than the size of the provided contents set.
*/
void megaContents(){
	//create and populate at 1000 element integer set
	std::set<int> int_contents;

	for(int i = 0; i < 1000; i++){
		int_contents.insert(i);
	}

	LatinSquare<int> lsqaure_int(4, int_contents);

	std::cout<<"4 x 4 Integer Latin Square from 1000 element set"<<std::endl;
	lsqaure_int.print(std::cout);
}



