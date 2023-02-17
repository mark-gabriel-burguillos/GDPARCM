#include "PrimeThread.h"
#include <utility>
#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>

static void calculateParameters(float& mean, float& standardDeviation, std::vector<float> timeList)
{
	float sum = 0.0f;

	for (int i = 0; i < timeList.size(); i++)
	{
		sum += timeList[i];
	}

	mean = sum / timeList.size();

	for (int i = 0; i < timeList.size(); i++)
	{
		standardDeviation += std::pow(timeList[i] - mean, 2);
	}

	standardDeviation = std::sqrt(standardDeviation / timeList.size());
}

int main()
{
	const long PRIME_NUMBER = 2147483647;
	const int MAX_NUMBER_OF_THREADS = 2500;
	const int NUMBER_OF_TRIALS = 15;

	PrimeThread* threadList = new PrimeThread[MAX_NUMBER_OF_THREADS];
	//std::cout << "Initialized threadList" << std::endl;

	// Used for recording the output(s)
	std::vector<std::pair<int, float>> outputRecord = std::vector<std::pair<int, float>>();
	std::vector<std::pair<float, float>> parametersRecord = std::vector<std::pair<float, float>>();

	for (int currentNumberOfThreads = 1; currentNumberOfThreads <= MAX_NUMBER_OF_THREADS; currentNumberOfThreads *= 2)
	{
		std::vector<float> timeList = std::vector<float>();

		for (int currentTrial = 0; currentTrial < NUMBER_OF_TRIALS; currentTrial++)
		{
			// Instantiation of the threads
			for (int i = 0; i < currentNumberOfThreads; i++)
			{
				PrimeThread primeThread = PrimeThread(i, PRIME_NUMBER, i, currentNumberOfThreads);
				threadList[i] = primeThread;
			}

			// Started timing
			auto TIME_OF_START = std::chrono::high_resolution_clock::now();

			// Starting the threads
			for (int i = 0; i < currentNumberOfThreads; i++)
			{
				threadList[i].start();
			}

			/*
			* Busy Waiting Implementation.
			* Postpone the Main thread until all of the PrimeThreads
			* are done with their operations.
			*/
			int finishedThreadsCount = 0;

			while (finishedThreadsCount != currentNumberOfThreads)
			{
				/*
				* Iteratively go through each thread. Only move unto
				* the next thread when the current thread being inspected
				* is finished running. And when the final thread is
				* finished running then move out of the while loop.
				*/
				if (threadList[finishedThreadsCount].isRunning == false)
				{
					finishedThreadsCount++;
				}
			}

			// Verifying the validity of PRIME_NUMBER
			bool isAValidPrimeNumber = true;

			for (int i = 0; i < currentNumberOfThreads; i++)
			{
				if (threadList[i].isAValidPrimeNumber == false)
				{
					isAValidPrimeNumber = false;
					break;
				}
			}

			// End timing
			auto TIME_OF_STOP = std::chrono::high_resolution_clock::now();
			auto DURATION_OF_RUN = std::chrono::duration_cast<std::chrono::milliseconds>(TIME_OF_STOP - TIME_OF_START);

			timeList.push_back(DURATION_OF_RUN.count());

			// Print out the results
			std::cout << "=================================================================" << std::endl;
			std::cout << "Trial Number : " << currentTrial + 1 << std::endl;
			std::cout << "Number of Threads : " << currentNumberOfThreads << std::endl;
			std::cout << "Result : " << (isAValidPrimeNumber ? "TRUE" : "FALSE") << std::endl;
			std::cout << "Duration of the program : " << DURATION_OF_RUN.count() << " ms" << std::endl;
			std::cout << "=================================================================" << std::endl;

			// Record output
			outputRecord.push_back(std::make_pair(currentNumberOfThreads, DURATION_OF_RUN.count()));
		}

		// Calculate Mean and Standard Deviation
		float mean, standardDeviation;
		mean = standardDeviation = 0.0f;

		calculateParameters(mean, standardDeviation, timeList);

		// Record parameters
		parametersRecord.push_back(std::make_pair(mean, standardDeviation));

		std::cout << "Mean : " << mean << " ms || Standard Deviation : "
			<< standardDeviation << " ms" << std::endl
			<< "================================================================="
			<< std::endl;
	}

	// Outputting record(s) to text file
	std::ofstream outputTextFile;
	outputTextFile.open("Output_Text_File.txt");

	outputTextFile << "PRIME NUMBER : " << PRIME_NUMBER << std::endl << std::endl;
	for (int batchCounter = 0; batchCounter < (outputRecord.size() / NUMBER_OF_TRIALS); batchCounter++)
	{
		outputTextFile << outputRecord[batchCounter * NUMBER_OF_TRIALS].first << " threads ============================= " << std::endl;

		for (int trialNumber = batchCounter; trialNumber < batchCounter + NUMBER_OF_TRIALS; trialNumber++)
		{
			outputTextFile << "# " << (trialNumber % NUMBER_OF_TRIALS) + 1 <<
				" -> " << outputRecord[trialNumber].second << " ms" << std::endl;
		}

		outputTextFile << "Mean : " << parametersRecord[batchCounter].first
			<< " ms || Standard Deviation : " << parametersRecord[batchCounter].second
			<< " ms" << std::endl;
	}
	
	outputTextFile.close();

	return 0;
};