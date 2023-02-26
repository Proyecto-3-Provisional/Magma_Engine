// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

struct Transform;

class TransformSystem : public ecs::System {
public:

	void recieve(const Message&) override;
	TransformSystem();
	virtual ~TransformSystem();


	void initSystem() override;
	void update() override;
private:
	/*void resetBall();
	void moveBall();
	void changeDirection();*/

	//Transform* ballTr_;
};

