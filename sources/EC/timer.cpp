#include <EC/timer.h>

#include <Render/text.h>

#include <SDL_timer.h>

namespace magma_engine
{
	Timer::Timer() : Component() 
	{
		time = 0; 
		timeStop = 0;

		timerPause = false; 

		textTime = nullptr; 
	}

	Timer::~Timer() {}

	bool Timer::initComponent() { return true; }

	void Timer::start() 
	{
		reset(); 
	}

	void Timer::onEnable() 
	{
		if (textTime != nullptr)
			textTime->onEnable(); 
	}

	void Timer::onDisable() 
	{
		if (textTime != nullptr)
			textTime->onDisable();
	}

	int Timer::getTimer()
	{
		if (timerPause)
			return (timeStop - time);
		else
			return (SDL_GetTicks() - time); 
	}

	void Timer::assignText(Text* text)
	{
		textTime = text; 
	}

	void Timer::update(float deltaTime) 
	{
		if (textTime != nullptr)
			textTime->changeText(std::to_string(getTimer()));
	}

	void Timer::reset()
	{
		timerPause = false;
		time = 0; 
	}

	void Timer::pause()
	{
		if (!timerPause)
		{
			timerPause = true;
			timeStop = SDL_GetTicks();
		}
	}

	void Timer::resume()
	{
		if (timerPause)
		{
			timerPause = false;
			time += (SDL_GetTicks() - timeStop);
		}
	}
}

