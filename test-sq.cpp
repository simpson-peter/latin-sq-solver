#include "latinsquare.h"
#include <set>
#include <string>
#include <iostream>
/* NTS: EDGE CASES TO CHECK:
* -Excessively large contents set
* -Too small contents set
* -Unordered int contents passed in
* -Non-int LSqaure made with the minimal constructor
*/
int main(int argc, char* argv[]){
	std::set<int> int_contents;
	int_contents.insert(0);
	int_contents.insert(1);
	int_contents.insert(2);
	//constructs a 9 x 9 Latin Square with integers
	LatinSquare<int> lsqaure_int(3, int_contents); 

	std::cout<<"The First Latin Square: "<<std::endl;
	lsqaure_int.print(std::cout);

	std::cout<<"Alternate Print Method for First Latin Square: "<<std::endl;
	//std::cout<<lsqaure_int<<std::endl;

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