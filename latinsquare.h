#ifndef LATINSQUARE_H
#define LATINSQUARE_H
#include <set>
#include <exception>
#include <iostream>
//NTS: REMOVE BELOW IF I DONT END UP NEEDING SETW
#include <iomanip>
//NTS: See if this can work with a class that doesn't support << if I don't call print()
//NTS: Consider adding "reduced" bool to constructor for additional constraints
//NTS: Make sure weird stuff doesn't happen with dynamic allocation and elements passed in the set
//(should I be allocating them here???, Does the type need to support the assignment/copy constructor???)
//NTS: CONSIDER ADDING RUNTIME ANALYSIS

/*
* Definition for the LatinSquare class, which represents an n x n grid
* of n distinct Ts arranged so that each T occurs once in each row and once in each column.
*
* This is a templated class, so a latin square can be made for any class passed in as a set
* and, by default, integers.
*
* The Latin square will be "solved" and populated through a backtracking algorithim
*/
template <typename T>
class LatinSquare{
public:

	/*
	*constructor for the templated Latin square. Set contents should contain at least n
	*distinct Ts
	*/
	LatinSquare(unsigned n_dimension, std::set<T>& contents);

	//destructor
	~LatinSquare();

	//Prints the square to provided ostream (T must support the << operator)
	void print(std::ostream& outstream);

	//overload for the extraction operator, T must support the << operator
	//friend std::ostream& operator<<(ostream& outstream);

private:

	//Called upon construction. This will solve the Latin square and populate it with T objects
	void solve(std::set<T>& contents);

	/*
	* Helper function designed to be called after a new value is inserted at square[row][col]
	*
	* In order to maintain O(n) complexity, this function only compares the new value at square[row][col]
	* to values at square[row][c] where c < col and square[r][col] where r < row.
	*
	* If you desire to evaluate the validity of the entire grid, use isValid()
	*/
	bool isNewValid(unsigned row_in, unsigned col_in);

	//recursive back-tracking helper function for solve(), performs most of the work in solving
	bool solveHelp(std::set<T>& contents, unsigned row, unsigned col);

	/*
	* Checks the validity of the entire Latin square
	* Worst Case Runtime: O((n^2)logn)
	*/
	bool isValid();

	//Stores the dimensions of the n x n Latin square
	unsigned n;

	//2D array which stores Ts
	T** square;
};

//LatinSquare destructor
template <typename T>
LatinSquare<T>::~LatinSquare(){

	//deallocate square grid

	for(unsigned i = 0; i < n; i++){
		delete [] square[i];
	}

	delete [] square;
}


/*
*
* Constructor which recieves a set of contents, which must have at least n members
* Will attempt to create a std::set of Ts by assigning them numeric values
* and then call solve() to populate the square.
*/
//NTS: THIS MAY CAUSE MEMORY ALLOCATION ISSUES???
template <typename T>
LatinSquare<T>::LatinSquare(unsigned n_dimension, std::set<T>& contents) : n(n_dimension) {
	//handle zero case
	if(n == 0){
		throw std::logic_error("Cannot construct a Latin square of size 0.");
	}
	//handle cases where cotents is smaller than n
	if(contents.size() < n){
		throw std::runtime_error("Size of set contents cannot be less than n.");
	}

	//aquire space for the square

	//allocate the first column
	square = new T*[n];

	//allocate the rows
	for(unsigned i = 0; i < n; i++){
		square[i] = new T[n];
	}

	//create the contents set 
	solve(contents);
}

//NTS: Probably just have to overload this if making a reduced class
template <typename T>
void LatinSquare<T>::solve(std::set<T>& contents){
	solveHelp(contents, 0, 0);
}

/* 
* Recursive, backtracking, helper for solving the Latin square
* attempts to find a value for square[row][col], then call solveHelp for the next space in the square
*/
template <typename T>
bool LatinSquare<T>::solveHelp(std::set<T>& contents, unsigned row, unsigned col){
	//check if it's necessary to wrap down to the next row
	if(col >= n){
		col = 0;
		row += 1;
	}

	//check if we've filled the entire square, check validity if so
	//NTS: THIS IS PROBABLY AN UNECESSARY STEP (probably could just return true since we've gone off the map)
	if(row >= n){
		return isValid();
	}

	/*
	* num_tried tracks the number of values tried, so we can break early if contents.size > n, 
	* but still want to maintain efficient iteration through the set 
	*/
	unsigned num_tried = 0;

	//iterate through set, seeing if each assignment is valid, and recursing to solve the next space if so
	for(typename std::set<T>::iterator it = contents.begin();
		it != contents.end();
		++it){

		if(num_tried >= n){
			break;
		}

		square[row][col] = *it;

		//if the current assignment is valid, try solving the next square
		if(isNewValid(row, col)){

			//return true if a solution is found by subsequent solveHelp iterations
			if(solveHelp(contents, row, col+1)){
				return true;
			}
			//otherwise the loop will continue and keep trying values
		}

		num_tried++;		
	}

	/*
	* If we couldn't generate a solution from any of the attempted values, the issues lies earlier in the square
	* return false to let earlier functions this is the case
	*/
	return false;
}


//compares square[row][col] to values at square[row][c] where c < col and square[r][col] where r < row.
template <typename T>
bool LatinSquare<T>::isNewValid(unsigned row_in, unsigned col_in){

	//Convert to ints to avoid overflow issues
	int row = (int) row_in;
	int col = (int) col_in;

	bool row_is_valid = true;
	bool col_is_valid = true;

	//check row validity
	for(int r = row-1; r >= 0; r-=1){
		//immediately return false if distinctness requriement is violated
		if(square[r][col] == square[row][col]){
			row_is_valid = false;
			return row_is_valid;
		}
	}

	//checl column validity
	for(int c = col-1; c >= 0; c-=1){
		//immediately return false if distinctness requriement is violated
		if(square[row][c] == square[row][col]){
			col_is_valid = false;
			return col_is_valid;
		}
	}

	//return whether the searched row and column are valid in comparison to the value at square[row][col]
	return row_is_valid && col_is_valid;
}

//checks the validity of the entire Latin Square (assumes all values have been initialized)
template <typename T>
bool LatinSquare<T>::isValid(){
	//generate a set of elements for this row/col, which will check for repeated items
	std::set<T> seen_before;

	//check that row elements are distinct within their row
	for(unsigned r = 0; r < n; r++){
		for(unsigned c = 0; c < n; c++){

			//if we haven't seen it before, add it to the set becuase we have noe
			if(seen_before.find(square[r][c]) == seen_before.end()){
				seen_before.insert(square[r][c]);
			}
			//if we've seen it before the distinctness requirement is violated and this isn't a Latin square! return false
			else{
				return false;
			}
		}

		//clear after fully checking a row
		seen_before.clear();
	}

	//now check for distinctness in columns
	for(unsigned c = 0; c < n; c++){
		for(unsigned r = 0; r < n; r++){

			//if we haven't seen it before, add it to the set becuase we have noe
			if(seen_before.find(square[r][c]) == seen_before.end()){
				seen_before.insert(square[r][c]);
			}
			//if we've seen it before the distinctness requirement is violated and this isn't a Latin square! return false
			else{
				return false;
			}
		}

		//clear after fully checking a column
		seen_before.clear();
	}

	/*
	* if we reach here it means that the distinctness requirement hasn't been violated within any of the rows
	* or columns in the Latin square. Return true.
	*/
	return true;
}

//NTS: CONSIDER ADDING FORMATTED OUTPUT
template <typename T>
void LatinSquare<T>::print(std::ostream& outstream){
	outstream<<n<<" x "<<n<<" Latin Square" << std::endl;

    // Start printing square data
    for(unsigned ridx = 0; ridx < n; ridx++) {
        // Print values
        for(unsigned cidx = 0; cidx < n; cidx++) {
            outstream << std::setw(4) << " ";
           
            outstream << std::setw(4) << square[ridx][cidx];
        }
        outstream << std::endl;
    }

}

template <typename T>
std::ostream& operator<<(std::ostream& outstream, LatinSquare<T> lsquare){
	lsquare.print(outstream);
	return outstream;
}


#endif