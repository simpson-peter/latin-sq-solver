#  Latin Square Solver
![A visualization of a Latin square created by this program](https://petersimpson.me/img/small_hex_vis.png)

*Above: A visualization of a Latin square generated by this program from a hex code set.*

This is a templated Latin square solver written in C++.
Created by [Peter Simpson](https://petersimpson.me) under the MIT License.

## What is a Latin Square?
From [Wikipedia](https://en.wikipedia.org/wiki/Latin_square): A **Latin square** is an _n_ × _n_ array filled with _n_ different symbols, each occurring exactly once in each row and exactly once in each column.

## Repository Contents
This repository contains:
 - **README.md** (you are here!)
 - **latinsquare.h** (templated implementation of the LatinSquare class)
 - **test-sq.cpp** (a demonstrative test shell)
 - **Makefile**
 - **License txt file** (MIT)

## How to Use the LatinSqaure Class
### Declaration
LatinSquare classes must be typed using the template <type\> brackets.
There is one constructor for the class. Declaration should follow the paradigm below:

    LatinSqaure<type> name(unsigned n, std::set<type> contents)
where n <= contents.size().

The LatinSquare class will populate the Square with the first n items returned by an iterator through contents, so contents.size() may be larger than n. 
The LatinSquare.solve() function is called upon construction, so the sqaure will be populated, solved, and validated upon declaration.

### Printing
Either call the object's print(std::ostream) function, which accepts your desired outstream as a reference parameter.
Alternatively simply pass the object into a stream through the extraction operator:

    outstreamName << LatinSquareName;

## How to Compile
I have included a Makefile for compilation. In the command line, simply navigate to the LatinSqSolver repository, and type "make" for compilation into the test-sq executable using the default shell (non-interactive). 
If you would like to use a new shell, simply replace "test-sq.cpp" with your filename in the Makefile, or just #include the latinsquare.h header file to make use of the class within a larger program.

## Forthcoming Features

 - A constructor for reduced Latin Squares
 - Const constructor, const solve function

## Known Issues
None as of now, but as always submit issues or pull requests if you find any!
