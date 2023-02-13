#include "BaseRunner.h"
#include  "GameObjectManager.h"
#include "BGObject.h"
#include "TextureManager.h"
#include "TextureDisplay.h"
#include "FPSCounter.h"

/// <summary>
/// This demonstrates a running parallax background where after X seconds, a batch of assets will be streamed and loaded.
/// </summary>
const float EXPECTED_FRAME = 60.f;
const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.f / EXPECTED_FRAME);

BaseRunner::BaseRunner() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "HO: Entity Component", sf::Style::Close) {
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
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	bool isFirstLoop = true;

	while (this->window.isOpen())
	{
		// Calculating the frame rate
		sf::Time elapsedTime = isFirstLoop ? sf::Time::Zero : clock.restart();
		timeSinceLastUpdate += elapsedTime;

		// Force constrict from updating the frame until timer hits 16.66 ms
		while (timeSinceLastUpdate >= TIME_PER_FRAME)
		{
			// Remove timer constriction for frame rate calculation
			timeSinceLastUpdate -= TIME_PER_FRAME; 

			processEvents();
			update(elapsedTime);
		}

		render();

		isFirstLoop = false;
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

void BaseRunner::update(sf::Time elapsedTime) {
	GameObjectManager::getInstance()->update(elapsedTime);
}

void BaseRunner::render() {
	this->window.clear();
	GameObjectManager::getInstance()->draw(&this->window);
	this->window.display();
}