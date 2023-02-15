#include "FPSCounter.h"
#include <iostream>
#include "BaseRunner.h"

FPSCounter::FPSCounter(): AGameObject("FPSCounter")
{
}

FPSCounter::~FPSCounter()
{
	delete this->statsText->getFont();
	delete this->statsText;
	AGameObject::~AGameObject();
}

void FPSCounter::initialize()
{
	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Sansation.ttf");

	this->statsText = new sf::Text();
	this->statsText->setFont(*font);
	this->statsText->setPosition(BaseRunner::WINDOW_WIDTH - 150, BaseRunner::WINDOW_HEIGHT - 70);
	this->statsText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->statsText->setOutlineThickness(2.5f);
	this->statsText->setCharacterSize(35);
}

void FPSCounter::processInput(sf::Event event)
{
}

void FPSCounter::update(sf::Time elapsedTime)
{
	this->updateFPS(elapsedTime);
}

void FPSCounter::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);

	if(this->statsText != nullptr)
		targetWindow->draw(*this->statsText);
}

void FPSCounter::updateFPS(sf::Time elapsedTime)
{
	this->updateTime += elapsedTime;

	// Restrict FPS timer updates
	const sf::Time UPDATE_LIMIT = sf::seconds(0.5f);

	if (this->updateTime >= UPDATE_LIMIT)
	{
		float elapsedTimeInMilliseconds = elapsedTime.asMilliseconds();
		float fps = 1000.f / elapsedTimeInMilliseconds;

		this->updateTime = sf::Time::Zero;
		this->statsText->setString("FPS: " + std::to_string(fps) + "\n");
	}
}
