#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
class BaseRunner : private sf::NonCopyable
{
public:
	static BaseRunner* getInstance();
	static const sf::Time	TIME_PER_FRAME;
	static const int FRAME_LIMIT = 60;
	static const int WINDOW_WIDTH = 1920 / 2; // 1920;
	static const int WINDOW_HEIGHT = 1080 / 2; // 1080;

	BaseRunner();
	void run();
	float getFramesPerSecond();

private:
	
	static BaseRunner* sharedInstance;
	sf::RenderWindow		window;

	void render();
	void processEvents();
	void update(sf::Time elapsedTime);

	float framesPerSecond;
};


