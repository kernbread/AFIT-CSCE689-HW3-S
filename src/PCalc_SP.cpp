#include <PCalc_SP.h>
#include <iostream>
#include <cmath>

PCalc_SP::PCalc_SP(const unsigned int& arraySize) : PCalc(arraySize) {
	this->arraySize = arraySize;
}

void PCalc_SP::markNonPrimes() {
	// skip trivial 0 and 1, lets just call them both prime
	at(0)=true;
	at(1)=true;	

	auto idx = 2; // start sieve at 2
	unsigned int sqrtN = (int) sqrt(arraySize);

	while (idx <= sqrtN) {
		bool elem = at(idx);

		if (elem) { // start the sieve!
			for(unsigned int i=2*idx; i < arraySize; i+=idx) // start at first multiple of idx
					at(i) = false;
		} // else, we hit a multiple, therefore skip

		idx++;
	}
}

PCalc_SP::~PCalc_SP() {
	cleanup();
}
