#include <EC/size_temp.h>

//#include <EC/entity.h>
#include <EC/transform.h>
//#include <Physics/rigidbody.h>
#include <EC/player_controller.h>


magma_engine::Size_Temp::Size_Temp() : tam(1.0f), player(false)
{
}

magma_engine::Size_Temp::~Size_Temp()
{
}

bool magma_engine::Size_Temp::initComponent(std::map<std::string, std::string> args)
{
	try {
		tam = stof(args["Size"]);
	}
	catch (...) {
		return false;
	}
	return true;
}

bool magma_engine::Size_Temp::start() {

	trPtr = ent->getComponent<Transform>();
	rbPtr = ent->getComponent<Rigidbody>();

	if (trPtr == nullptr || rbPtr == nullptr)
		return false;

	originalScale = trPtr->getScale();
	player = ent->hasComponent<PlayerController>();

	return true;
}

void magma_engine::Size_Temp::update(float deltaTime)
{
	if (rbPtr->isOnCollision()) {
		auto colEnts = rbPtr->getCollisionObjs();
		for (int i = 0; i < colEnts.size(); i++) {
			if (colEnts[i]->hasComponent<Size_Temp>()) {
				float otherS = colEnts[i]->getComponent<Size_Temp>()->getTam();
				if (player || colEnts[i]->getComponent<Size_Temp>()->isPlayer()) {
					if (otherS > tam) {
						ent->setAlive(false);
					}
					else if (tam > otherS) {
						//aqui se aumentara el tamaño del personaje segun la diferencia de tamaño entre ellos
						if (tam - otherS >= 0.7f) {
							tam = tam + 0.1f;
						}
						else {
							tam = tam + 0.2f;
						}
						trPtr->setScale(originalScale * tam);
					}
					else {
						//si tienen el mismo tamaño el jugador se lo come
						if (player) {
							tam = tam + 0.2f;
							trPtr->setScale(originalScale * tam);
						}
						else {
							ent->setAlive(false);
						}
					}
				}
			}
		}
	}
}

float magma_engine::Size_Temp::getTam() 
{
	return tam;
}

bool magma_engine::Size_Temp::isPlayer()
{
	return player;
}

void magma_engine::Size_Temp::setTam(float ntam)
{
	tam = tam + ntam;
	trPtr->setScale(originalScale * tam);
}