// This file is part of the course TPV2@UCM - Samir Genaim

#include "transform_system.h"
#include "entity_manager.h"
#include "Transform.h"
//#include "../sdlutils/SDLUtils.h"

TransformSystem::TransformSystem() /*:*/
	/*ballTr_(nullptr)*/ {
}

TransformSystem::~TransformSystem() {
}

void TransformSystem::initSystem() {
	// create the ball entity
	//
	//auto ball = mngr_->addEntity();
	//mngr_->setHandler<_hdlr_BALL>(ball);

	//ballTr_ = mngr_->addComponent<Transform>(ball);
	//auto ballSize = 15.0f;
	//auto ballX = (sdlutils().width() - ballSize) / 2.0f;
	//auto ballY = (sdlutils().height() - ballSize) / 2.0f;
	//ballTr_->init(Vector2D(ballX, ballY), Vector2D(), ballSize, ballSize, 0.0f);

	//mngr_->addComponent<Image>(ball, &sdlutils().images().at("tennis_ball"));
}

void TransformSystem::update() {


	if ()
	{
		componentTrans.actualiza
	}
	//ballTr_->move();

	//// check upper/lower borders
	//if (ballTr_->pos_.getY() < 0) 
	//	ballTr_->pos_.setY(0.0f);
	//	ballTr_->vel_.setY(-ballTr_->vel_.getY());
	//	// play some sound
	//	sdlutils().soundEffects().at("wall_hit").play();
	//}
	//else if (ballTr_->pos_.getY() + ballTr_->width_ > sdlutils().height()) {
	//	ballTr_->pos_.setY(sdlutils().height() - ballTr_->height_);
	//	ballTr_->vel_.setY(-ballTr_->vel_.getY());
	//	sdlutils().soundEffects().at("wall_hit").play();
	//}

}
//
//void TransformSystem::resetBall() {
//	ballTr_->pos_.set(sdlutils().width() / 2 - 5,
//		sdlutils().height() / 2 - 5);
//	ballTr_->vel_.set(0, 0);
//}
//
//void TransformSystem::moveBall() {
//	auto& r = sdlutils().rand();
//
//	int dx = 1 - 2 * r.nextInt(0, 2); // 1 or -1
//	int dy = 1 - 2 * r.nextInt(0, 2); // 1 or -1
//
//	Vector2D v(dx * r.nextInt(2, 7), dy * r.nextInt(2, 7));
//	ballTr_->vel_.set(v.normalize() * 2);
//}

void TransformSystem::recieve(const Message& m) {
	/*switch (m.id) {
	case _m_ROUND_START:
		moveBall();
		break;
	case _m_ROUND_OVER:
		resetBall();
		break;
	case _m_BALL_HIT_PADDLE:
		changeDirection();
		break;
	default:
		break;
	}*/
}

//void BallSystem::changeDirection() {
//	auto& vel = ballTr_->vel_; // the use of & is important, so the changes goes directly to the ball
//	vel.setX(-vel.getX());
//	vel = vel * 1.2f;
//	// play some sound
//	sdlutils().soundEffects().at("paddle_hit").play();
//
//}
