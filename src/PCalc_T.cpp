#include <PCalc_T.h>
#include <iostream>
#include <omp.h>
#include <cstring>
#include <cmath>

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

void PCalc_T::markNonPrimes() {
	// skip trivial 0 and 1, lets just call them both prime
	at(0)=true;
	at(1)=true;	

	auto idx = 2; // start sieve at 2
	
	// only need to check up to sqrt(N) : N = arraySize
	auto squareRootOfN = (int) sqrt(arraySize);

	for (unsigned int i=idx; i <= squareRootOfN; i++) {
		bool elem = at(i);

		if (elem) { // start the sieve!
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
		
		} // else, we hit a multiple, therefore skip
	}
}

PCalc_T::~PCalc_T() {
	cleanup();
}
