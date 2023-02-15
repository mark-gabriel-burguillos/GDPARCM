#include "BaseRunner.h"
#include  "GameObjectManager.h"
#include "BGObject.h"
#include "TextureManager.h"
#include "TextureDisplay.h"
#include "FPSCounter.h"

/// <summary>
/// This demonstrates a running parallax background where after X seconds, a batch of assets will be streamed and loaded.
/// </summary>
const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.f / FRAME_LIMIT);

BaseRunner* BaseRunner::sharedInstance = NULL;

BaseRunner* BaseRunner::getInstance()
{
	if (sharedInstance == NULL)
	{
		sharedInstance = new BaseRunner();
	}

	return sharedInstance;
}

BaseRunner::BaseRunner() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "HO - Background Asset Loader", sf::Style::Close) {
	//load initial textures
	TextureManager::getInstance()->loadFromAssetList();

	//load objects
	BGObject* bgObject = new BGObject("BGObject");
	GameObjectManager::getInstance()->addObject(bgObject);

	TextureDisplay* display = new TextureDisplay();
	GameObjectManager::getInstance()->addObject(display);

	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);
}

void BaseRunner::run() {
	window.setFramerateLimit(FRAME_LIMIT);

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time prevTime = clock.getElapsedTime();

	while (this->window.isOpen())
	{
		// Calculating the frame rate
		sf::Clock clock;

		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		bool isFirstLoop = true;

		// Render loop
		while (this->window.isOpen())
		{
			sf::Time elapsedTime;

			/*
			* Check if it is the first Render loop. If it is,
			* then reset clock again to disregard time gained
			* since its instantiation.
			*/
			if (isFirstLoop) {
				clock.restart();
				elapsedTime = sf::Time::Zero;
			}
			else {
				elapsedTime = clock.restart();
			}

			timeSinceLastUpdate += elapsedTime;

			/*
			* Fixed Time Step Implementation
			* Force update the window when the timer hits 16.66 ms
			*/
			while (timeSinceLastUpdate >= TIME_PER_FRAME)
			{
				// Readjust
				timeSinceLastUpdate -= TIME_PER_FRAME;

				float foo = elapsedTime.asMilliseconds();

				processEvents();
				update(elapsedTime);
			}

			isFirstLoop = false;
			render();
		}
	}
}

void BaseRunner::processEvents()
{
	sf::Event event;
	if (this->window.pollEvent(event)) {
		switch (event.type) {
		
		default: GameObjectManager::getInstance()->processInput(event); break;
		case sf::Event::Closed:
			this->window.close();
			break;

		}
	}
}

void BaseRunner::update(sf::Time elapsedTime)
{
	GameObjectManager::getInstance()->update(elapsedTime);
}

void BaseRunner::render()
{
	this->window.clear();
	GameObjectManager::getInstance()->draw(&this->window);
	this->window.display();
}

float BaseRunner::getFramesPerSecond()
{
	return this->framesPerSecond;
}