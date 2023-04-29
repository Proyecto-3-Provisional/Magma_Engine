#include <EC/progress_bar.h>

#include <Render/ui_progress_bar.h>
#include <Render/ui_manager.h>

namespace magma_engine
{
	Progress_Bar::Progress_Bar() : Component(), progressBar(nullptr), interactive(true), screenHeight(1.0f), screenWidth(1.0f), imageName(), normalName(), tamX(), tamY(), posX(), posY(), progress(), limit()
	{

	}

	Progress_Bar::~Progress_Bar() {}

	std::string Progress_Bar::GetName()
	{
		return imageName;
	}

	bool Progress_Bar::initComponent(std::string overlayName, std::string name,
		float width, float height, float x, float y, float pro, float proLimit) 
	{ 
		imageName = overlayName;
		normalName = name;

		tamX = width;
		tamY = height;

		posX = x;
		posY = y;

		progress = pro;
		limit = proLimit;

		screenWidth = (float)Singleton<RenderManager>::instance()->getWinWidth();
		screenHeight = (float)Singleton<RenderManager>::instance()->getWinHeight();
		return true; 
	}

	void Progress_Bar::start()
	{
		progressBar = Singleton<UI_Manager>::instance()->createElement<UI_Progress_Bar>(imageName, normalName, posX, posY, tamX, tamY);

		progressBar->setPanelPosition(posX, posY);
		progressBar->setPanelSize(tamX, tamY);
		progressBar->setInteractive(interactive);
	}

	void Progress_Bar::onEnable()
	{
		if (progressBar != nullptr)
			progressBar->showElement();
	}

	void Progress_Bar::onDisable()
	{
		progressBar->hideElement();
	}

	void Progress_Bar::update(float deltaTime)
	{
		float newWidth = (float)Singleton<RenderManager>::instance()->getWinWidth();
		float newHeight = (float)Singleton<RenderManager>::instance()->getWinHeight();

		if (newWidth != 0 && newHeight != 0 && screenWidth != 0 && screenHeight != 0)
			progressBar->setPanelPosition(posX * (newWidth / screenWidth), posY * (newHeight / screenHeight));

		progressBar->setPanelSize(tamX * (progress / limit) * (newWidth / screenWidth), (newHeight / screenHeight) * tamY);
	}

	void Progress_Bar::setInteractive(bool interact)
	{
		interactive = interact;
	}

	void Progress_Bar::setProgress(float pro)
	{
		float maxLimit = limit * 10; 

		if (pro <= maxLimit)
			progress = pro;
		else
			progress = maxLimit; 
	}

	void Progress_Bar::setProgressLimit(float proLimit)
	{
		limit = proLimit; 
	}
}

