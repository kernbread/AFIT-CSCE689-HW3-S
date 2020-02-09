#include <PCalc_SP.h>
#include <iostream>
#include <cmath>

/* PCalc_SP : constructor; initializes class variable arraySize. Also inherits from PCalc base class,
 * and calls its constructor with the arraySize input. */
PCalc_SP::PCalc_SP(const unsigned int& arraySize) : PCalc(arraySize) {
	this->arraySize = arraySize;
}

/* markNonPrimes : iterates through the range 0->arraySize-1 and sets PCalc::primelist[i] = false if i
 * is a composite number. It does this using the sieve of eratosthenes algorithm (serial). */
void PCalc_SP::markNonPrimes() {
	// skip trivial 0 and 1, lets just call them both prime
	at(0)=true;
	at(1)=true;	

	auto idx = 2; // start sieve at 2

	// only need to check up to sqrt(N) : N = arraySize. Explanation in PCalc_T.cpp.
	unsigned int sqrtN = (int) sqrt(arraySize); 

	// iterates through range 2->sqrt(N) and sets all multiples of primes to false
	for (unsigned int i=idx; i <= sqrtN; i++) {
		bool elem = at(i);

		if (elem) { // i is a prime; mark off all its multiples less than N
			for(unsigned int j=2*i; j < arraySize; j+=i) // start at first multiple of idx
					at(j) = false;
		} // else, i is a multiple of some prime, therefore skip
	}
}

/* ~PCalc_SP : destructor; cleans up PCalc_T and PCalc base before destroying objects. */
PCalc_SP::~PCalc_SP() {
	cleanup();
}
