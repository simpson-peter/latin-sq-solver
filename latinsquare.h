#ifndef LATINSQUARE_H
#define LATINSQUARE_H
#include <set>
#include <exception>

//NTS: WOULD BE COOL TO MAKE A VISUAL REPRESENTATION OF ONE OF THE SQUARES USING HEX
//NTS: See if this can work with a class that doesn't support << if I don't call print()
//NTS: Consider adding "reduced" bool to constructor for additional constraints
//NTS: Make sure weird stuff doesn't happen with dynamic allocation and elements passed in the set
//(should I be allocating them here???, Does the type need to support the assignment/copy constructor???)

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
	//constructor for defualt integer Latin square (no need to pass in a set of contents)
	//Note: only call this constructor if the LatinSquare instance has been templated as <int>
	LatinSquare(size_t n_dimension);

	//constructor for the templated Latin square. Set contents should contain at least n
	//distinct Ts
	LatinSquare(size_t n_dimension, std::set<T>& contents);

	//destructor
	~LatinSquare();

	//Prints the square to provided ostream (T must support the << operator)
	void print(std::ostream outstream);

	//overload for the extraction operator, T must support the << operator
	friend ostream& operator<<(ostream& outstream);

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
	bool isNewValid(size_t row, size_t col);

	// O(n^2) complexity function to check the validity of the entire Latin square
	bool isValid();

	//Stores the dimensions of the n x n Latin square
	size_t n;

	//2D array which stores Ts
	T** square;
};

/*
* NOTE: THIS CONSTRUCTOR IS INTENDED FOR USE WITH INTEGERS.
*
* Constructor which does not require a set of contents.
* Will attempt to create a std::set of Ts by assigning them numeric values
* and then call solve() to populate the square.
*/
//NTS: THIS MAY CAUSE MEMORY ALLOCATION ISSUES???
template <typename T>
LatinSquare::LatinSquare(size_t n_dimension) : n(n_dimension){
	//aquire space for the square

	//allocate the first column
	square = new T*[n];

	//allocate the rows
	for(size_t i = 0; i < n; i++){
		square[i] = new T[n];
	}

	//create the contents set, and initialize it
	std::set<T> contents;
	for(typename T q = 0; q < n; q++){
		contents.insert(q);
	}

	//create the contents set 
	solve(contents);
}

//LatinSquare destructor
template <typename T>
LatinSquare::~LatinSquare(){

	//deallocate square grid

	for(size_t i = 0; i < n; i++){
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
LatinSquare::LatinSquare(size_t n_dimension, std::set<T>& contents){
	//handle zero case
	if(n == 0){
		throw std::logic_error("Cannot construct a Latin square of size 0.")
	}
	//handle cases where cotents is smaller than n
	if(contents.size() < n){
		throw std::runtime_error("Size of set contents cannot be less than n.");
	}
	//aquire space for the square

	//allocate the first column
	square = new T*[n];

	//allocate the rows
	for(size_t i = 0; i < n; i++){
		square[i] = new T[n];
	}

	//create the contents set 
	solve(contents);
}

void LatinSquare::solve(std::set<T>& contents){

}


//compares square[row][col] to values at square[row][c] where c < col and square[r][col] where r < row.
bool isNewValid(size_t row, size_t col){

}

//checks the validity of the entire Latin Square
bool isValid(){
	
}

#endif