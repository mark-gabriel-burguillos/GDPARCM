#include "StreamAssetLoader.h"
#include "StringUtils.h"
#include "TextureManager.h"
#include "IExecutionEvent.h"
#include <iostream>

StreamAssetLoader::StreamAssetLoader(String path, IExecutionEvent* executionEvent)
{
	this->path = path;
	this->executionEvent = executionEvent;
};

StreamAssetLoader::~StreamAssetLoader()
{
	std::cout << "Destroying stream asset loader thread" << std::endl;
}

void StreamAssetLoader::run()
{
	std::cout << "Running stream asset loader thread" << std::endl;

	std::vector<String> tokens = StringUtils::split(path, '/');
	String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
	TextureManager::getInstance()->instantiateAsTexture(path, assetName, true);

	std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;

	// Delay
	const float SLEEP_TIMER = 200;
	//std::cout << "[SAL Thread] Sleeping for... " << SLEEP_TIMER / 1000 << " seconds \n";
	IETThread::sleep(SLEEP_TIMER);
	// std::cout << "[SAL Thread] Woke up from slumber!\n";

	this->executionEvent->onFinishedExecution();

	// Clean-up
	delete this;
}