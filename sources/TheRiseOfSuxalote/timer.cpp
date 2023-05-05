#include <TheRiseOfSuxalote/timer.h>

#include <SDL_timer.h>

namespace magma_game
{
	Timer::Timer() : textTime(nullptr), timerPause(false), time(0), timeStop(0) 
	{
	}

	Timer::~Timer()
	{
	}

	bool Timer::initComponent() 
	{ 
		time = 0;
		timeStop = 0;

		timerPause = false;

		textTime = nullptr;
		return true; 
	}

	bool Timer::start()
	{
		reset();
		return true;
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

	void Timer::assignText(magma_engine::Text* text)
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

