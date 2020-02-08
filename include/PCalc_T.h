#ifndef PCALC_T_H
#define PCALC_T_H

#include "PCalc.h"
#include <vector>

// Your implementation of PCalc_T class should go here.
// Make sure your constructor takes in two parameters:
//
// PCalc_T::PCalc_T(unsigned int array_size, unsigned int num_threads);
//
// Call the parent constructor when initializing your constructor and pass in array_size. Then
// use num_threads to cap off how many threads you use to calculate all prime numbers

class PCalc_T : public PCalc
{
	public:
		PCalc_T(const unsigned int& arraySize, unsigned int numThreads);
		~PCalc_T();
		void markNonPrimes();

		bool checkIfThreadProcessingIdx(unsigned int idx);
	private:
		unsigned int arraySize = 0;
		unsigned int numThreads;
		//std::vector<unsigned int> *threadMins; // vector to hold current elem thread marking off	
		unsigned int *threadMins;
};

#endif
