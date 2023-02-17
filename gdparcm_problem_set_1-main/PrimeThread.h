#pragma once
#include "IETThread.h"
#include <string>

class PrimeThread : public IETThread
{
public:
	PrimeThread();
	PrimeThread(int threadId, long primeNumberUnderTest, long startingDivisor, int stepValue);
	~PrimeThread();

	bool	isRunning;
	bool	isAValidPrimeNumber = true;

private:
	typedef std::string String;
	
	void run() override;
	void dismiss();

	int		threadId;
	long	primeNumberUnderTest;
	long	startingDivisor;
	int		stepValue;
};