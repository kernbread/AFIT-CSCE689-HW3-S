#ifndef PCALC_SP_H
#define PCALC_SP_H

#include "PCalc.h"

/*********************************************************************************************
 * PCalc_SP : Prime number calculation class. Inherits from base class PCalc. This class works
 * serially (i.e. one thread). 
 *
 * 	PCalc_SP(Const): takes the array size (max number to count up to) and initializes
 * 	markNonPrimes(): sets all composite numbers in range 0->arraySize to false in
 * 	PCalc::primelist.
 *
 * 	~PCalc_SP(Dest): cleans up memory
 *********************************************************************************************/
class PCalc_SP : public PCalc
{
	public:
		PCalc_SP(const unsigned int& arraySize);
		~PCalc_SP();
		void markNonPrimes();
	private:
		unsigned int arraySize = 0; // max number to count up to
};

#endif
