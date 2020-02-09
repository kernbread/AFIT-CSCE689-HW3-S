#include <PCalc_T.h>
#include <iostream>
#include <omp.h>
#include <cstring>
#include <cmath>

/* PCalc_T : constructor; initializes class variables arraySize and numThreads. Also inherits from 
 * PCalc base class, and calls its constructor with the arraySize input. */
PCalc_T::PCalc_T(const unsigned int& arraySize, unsigned int numThreads) : PCalc(arraySize), threadMins(new unsigned int[numThreads]) {
	this->arraySize = arraySize;
	this->numThreads = numThreads;

	omp_set_num_threads(numThreads); // set number of threads for omp to use
	
	memset(threadMins, 0, sizeof(unsigned int)*numThreads);
}

/* checkIfThreadProcessingIdx : initially made this function to prevent the main loop from getting 
 * ahead of the threads marking off numbers. However, I found through its usage that it caused
 * the program to run over 2x slower on average!
 *
 * To use this, inside the parallel portion, make sure to do the following:
 * 	threadMins[omp_get_thread_num()-1] = i;
 *
 * Also, capture true/false from this f() and check for !(alreadyMarkedByThread) as well as elem.
 */
bool PCalc_T::checkIfThreadProcessingIdx(unsigned int idx) {
	for (int i=0; i < numThreads; i++) {
		if (threadMins[i] == idx)
			return true;
	}	
	return false;
}

/* markNonPrimes : iterates through the range of 0->arraySize-1 and sets PCalc::primelist[i] = false
 * if i is a composite number. It does this using the sieve of eratosthenes algorithm. 
 *
 * This implementation uses a parallel for loop to speed up execution time by splitting the inner
 * for loop into 'numThreads' threads. Then, each iteration of the inner for loop is split so that
 * each thread works on a portion of the loop. 
 */
void PCalc_T::markNonPrimes() {
	// skip trivial 0 and 1, lets just call them both prime
	at(0)=true;
	at(1)=true;	

	auto idx = 2; // start sieve at 2
	
	// only need to check up to sqrt(N) : N = arraySize
	// this is b/c we would be doing unnecessary work if we checked > sqrt(N).
	// e.g. if N = 22, (int) sqrt(22) = 4. We don't need numbers higher, like 7 for instance
	// b/c we already got that multiple with 3*7. 
	// i.o.w. : for any N, the prime factorization of n yields x*y : either x <=sqrt(N) or 
	// y <= sqrt(N).  
	auto squareRootOfN = (unsigned int) sqrt(arraySize);

	// iterate through range 2->sqrt(N) and set all multiples of primes to false
	for (unsigned int i=idx; i <= squareRootOfN; i++) {
		bool elem = at(i);

		if (elem) { // i is a prime; mark off all its multiples less than N
		        unsigned int start = 2 * i;
			
			// Using omp to parallelize for loop. 
			// omp vectorizes and splits for loop between 'numThreads' threads
			// to split work.
#pragma omp parallel for
			for(unsigned int j=start; j < arraySize; j+=i) // start at first multiple of idx
					at(j) = false;
			// I decided to go with this approach because this loop is 
			// embarrassingly parallel. As such, due to how common this problem is,
			// c/c++ come equipt with a methodology to handle it with ease.
			// If this didn't exist, I would have had to create a thread pool
			// and pass the worker threads lambdas to execute (the for loop above).
		} // else, i is a multiple of some prime, therefore skip
	}
}

/* ~PCalc_T : destructor; cleans up PCalc_T and PCalc base before destroying objects. */
PCalc_T::~PCalc_T() {
	cleanup();
}
