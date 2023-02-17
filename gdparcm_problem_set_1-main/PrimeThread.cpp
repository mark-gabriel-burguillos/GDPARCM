#include "PrimeThread.h"
#include <iostream>

PrimeThread::PrimeThread()
{

}

PrimeThread::PrimeThread(int threadId, long primeNumberUnderTest, long startingDivisor, int stepValue)
{
	this->threadId = threadId;
	this->primeNumberUnderTest = primeNumberUnderTest;
	this->startingDivisor = startingDivisor;
	this->stepValue = stepValue;
};

PrimeThread::~PrimeThread()
{
	//std::cout << "Terminated PrimeThread # " << threadId << std::endl;
};

void PrimeThread::dismiss()
{
	this->isRunning = false;
	
	delete this;
};

void PrimeThread::run()
{
	//std::cout << "Running PrimeThread # " << threadId << std::endl;

	while (this->isRunning)
	{
		if (this->primeNumberUnderTest == 1)
		{
			this->isAValidPrimeNumber = false;
		}

		for (int divisor = 2 + this->startingDivisor;
			divisor < this->primeNumberUnderTest && divisor > 0;
			divisor += this->stepValue)
		{
			if ((this->primeNumberUnderTest % divisor) == 0)
			{
				/*
				std::cout << "[PrimeThread # " << threadId <<
					"] NOT A VALID PRIME NUMBER. Found that "  <<
					divisor << " is a valid factor!" << std::endl;
				*/
				this->isAValidPrimeNumber = false;
				//break;
			}
			else
			{
				/*
				std::cout << "[PrimeThread # " << threadId <<
					"] " << divisor << " is not a factor."
					<< std::endl;
				*/
			}

		}

		this->isRunning = false;
	};
}