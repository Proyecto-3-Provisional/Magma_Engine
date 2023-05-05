#include <Physics/rigidbody.h>
#include <EC/transform.h>
#include <TheRiseOfSuxalote/progress_bar.h>
#include <TheRiseOfSuxalote/player_controller.h>
#include <TheRiseOfSuxalote/size_temp.h>
#include <TheRiseOfSuxalote/endgame.h>

magma_game::Size_Temp::Size_Temp() : tam(1.0f), maxTam(2.0f), isAPlayer(false)
{
}

magma_game::Size_Temp::~Size_Temp()
{
}

bool magma_game::Size_Temp::initComponent(std::map<std::string, std::string> args)
{
	try {
		tam = stof(args["size"]);
	}
	catch (std::exception& e) {
		std::cout << "WARNING! - error en un componente size_temp:\n\n     " << e.what() << "\n\n";
		return false;
	}
	return true;
}

bool magma_game::Size_Temp::start() {

	trPtr = ent->getComponent<magma_engine::Transform>();
	rbPtr = ent->getComponent<magma_engine::Rigidbody>();

	if (trPtr == nullptr || rbPtr == nullptr)
		return false;

	if (ent->hasComponent<Progress_Bar>()) {
		prBarPtr = ent->getComponent<Progress_Bar>();
		if (prBarPtr != nullptr)
		{
			prBarPtr->setProgress(tam);
			// establecer maxTam en barra progreso
		}
		else
		{
			std::cout << "WARNING! No hay progress bar en Size_temp \n\n";
			return false;
		}
	}

	
	originalScale = trPtr->getScale();
	isAPlayer = ent->hasComponent<PlayerController>();

	trPtr->setScale(originalScale * tam);

	return true;
}

void magma_game::Size_Temp::update(float deltaTime)
{
	if (isAPlayer && rbPtr->isOnCollision()) {
		auto colEnts = rbPtr->getCollisionObjs();
		for (int i = 0; i < colEnts.size(); i++) {
			if (colEnts[i]->hasComponent<Size_Temp>()) {
				float otherS = colEnts[i]->getComponent<Size_Temp>()->getTam();
				if (otherS > tam) {

					if (ent->hasComponent<Endgame>())
						ent->getComponent<Endgame>()->winOrLose(false);
				}
				else
				{
					colEnts[i]->setAlive(false);

					tam += 2.0f;

					if (tam >= maxTam)
					{
						if (ent->hasComponent<Endgame>())
							ent->getComponent<Endgame>()->winOrLose(true);
					}

					trPtr->setScale(originalScale * tam);
				}
			}
		}
	}
}

float magma_game::Size_Temp::getTam()
{
	return tam;
}

void magma_game::Size_Temp::setTam(float ntam)
{
	tam = tam + ntam;
	trPtr->setScale(originalScale * tam);
}