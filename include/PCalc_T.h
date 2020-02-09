#ifndef PCALC_T_H
#define PCALC_T_H

#include "PCalc.h"
#include <vector>

/********************************************************************************************
 * PCalc_T : Prime number calculation class. Inherits from base class PCalc. This class works
 * with multiple threads. 
 *
 *	PCalc_T(Const): takes the array size (max number to count up to) and numThreads and
 *	initializes
 *	markNonPrimes() : sets all composite numbers in range 0->arraySize to false in 
 *	PCalc::primelist
 *
 *	~PCalc_T(Dest): cleans up memory
 *******************************************************************************************/
class PCalc_T : public PCalc
{
	public:
		PCalc_T(const unsigned int& arraySize, unsigned int numThreads);
		~PCalc_T();
		void markNonPrimes();

		bool checkIfThreadProcessingIdx(unsigned int idx);
	private:
		unsigned int arraySize = 0; // number to count up to
		unsigned int numThreads; // number of threads to use in sieve
		unsigned int *threadMins; // for each thread, tracks the minimum number being processed by a given thread (not used; poor performance metrics observed)
};

#endif
