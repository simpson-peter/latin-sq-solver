all: test-sq

test-sq: test-sq.cpp latinsquare.h
	g++ -g -Wall -std=c++11 test-sq.cpp -o test-sq

clean:
	rm -f *.o test-sq