#include <allegro5/base.h>
#include <random>
#include <string>

#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Bullet/FireBullet.hpp"
#include "Engine/Point.hpp"
#include "TankEnemy.hpp"

PlayScene* TankEnemy::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
TankEnemy::TankEnemy(int x, int y) : Enemy("play/enemy-3.png", x, y, 20, 20, 100, 50),
head("play/enemy-3-head.png", x, y), targetRotation(0) {
}
void TankEnemy::Draw() const {
	Enemy::Draw();
	head.Draw();
}
void TankEnemy::Update(float deltaTime) {
	Enemy::Update(deltaTime);
	head.Position = Position;
	// Choose arbitrary one.
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_real_distribution<> dist(0.0f, 4.0f);
	float rnd = dist(rng);
	if (rnd < deltaTime) {
		// Head arbitrary rotation.
		std::uniform_real_distribution<> distRadian(-ALLEGRO_PI, ALLEGRO_PI);
		targetRotation = distRadian(rng);
	}
	head.Rotation = (head.Rotation + deltaTime * targetRotation) / (1 + deltaTime);

	reload -= deltaTime;
	if (reload <= 0) {
		// shoot.
		reload = coolDown;
		//CreateBullet();
	}
}
void TankEnemy::CreateBullet(){
	Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
	float rotation = atan2(diff.y, diff.x);
	Engine::Point normalized = diff.Normalize();
	// Change bullet position to the front of the gun barrel.
	getPlayScene()->BulletGroup->AddNewObject(new FireBullet(Position + normalized * 36, diff, rotation, nullptr));
}
