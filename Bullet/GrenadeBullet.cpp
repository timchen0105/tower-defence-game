#include <allegro5/base.h>
#include <random>
#include <string>

#include "Engine/Collider.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "Enemy/Enemy.hpp"
#include "GrenadeBullet.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

class Turret;

GrenadeBullet::GrenadeBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
	Bullet("play/grenade.png", 50, 10, 16, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
}
void GrenadeBullet::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
	
	for (auto& it : scene->EnemyGroup->GetObjects()) {
		Enemy* enemy = dynamic_cast<Enemy*>(it);
		if (!enemy->Visible)
			continue;
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, enemy->Position, enemy->CollisionRadius)) {
			for (auto& it2 : scene->EnemyGroup->GetObjects()) {
				Enemy* enemy2 = dynamic_cast<Enemy*>(it2);
				if (!enemy2->Visible)
					continue;
				if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius*4, enemy2->Position, enemy2->CollisionRadius)  && enemy2->fly == false) {
					OnExplode(enemy2);
					enemy2->Hit(damage);
				}
			}

			getPlayScene()->BulletGroup->RemoveObject(objectIterator);
			return;
		}
	}
	// Check if out of boundary.
	if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, Engine::Point(0, 0), PlayScene::GetClientSize()))
		getPlayScene()->BulletGroup->RemoveObject(objectIterator);
}
void GrenadeBullet::OnExplode(Enemy* enemy) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(4, 10);
	getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-1.png", dist(rng), enemy->Position.x, enemy->Position.y));
}

