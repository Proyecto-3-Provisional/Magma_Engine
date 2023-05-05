#include <TheRiseOfSuxalote/progress_bar.h>
#include <Render/render_manager.h>
#include <Render/ui_progress_bar.h>
#include <Render/ui_manager.h>

#include <Sounds/sound_manager.h>

#include <iostream>

namespace magma_game
{
	Progress_Bar::Progress_Bar() : progressBar(nullptr), interactive(true), imageName(), normalName(), tamX(), tamY(), posX(), posY(), progress(), limit()
	{

	}

	Progress_Bar::~Progress_Bar() {
		Singleton<magma_engine::UI_Manager>::instance()->deleteElement(progressBar);
	}

	std::string Progress_Bar::GetName()
	{
		return imageName;
	}

	bool Progress_Bar::initComponent(std::map<std::string, std::string> args)
	{
		try {
			imageName = args["imageName"];
			normalName = args["normalName"];

			tamX = stof(args["width"]);
			tamY = stof(args["height"]);

			posX = stof(args["x"]);
			posY = stof(args["y"]);

			progress = stof(args["progress"]);
			limit = stof(args["limit"]);
		}
		catch (std::exception& e) {
			std::cout << "WARNING! - error en un componente enemy_controller:\n\n     " << e.what() << "\n\n";

			return false;
		}
		return true;
	}

	bool Progress_Bar::start()
	{
		progressBar = Singleton<magma_engine::UI_Manager>::instance()->createElement<magma_engine::UI_Progress_Bar>(
			imageName, normalName, posX, posY, tamX, tamY);

		progressBar->setPanelPosition(posX, posY);
		progressBar->setPanelSize(tamX, tamY);
		progressBar->setInteractive(interactive);

		return true;
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
		progressBar->setPanelSize(tamX * (progress / limit), tamY);
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

