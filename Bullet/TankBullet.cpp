#include <allegro5/base.h>
#include <random>
#include <string>

#include "Engine/Collider.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "Enemy/Enemy.hpp"
#include "Turret/Turret.hpp"
#include "TankBullet.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

TankBullet::TankBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
	Bullet("play/grenade.png", 50, 10, 16, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
}
void TankBullet::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();

    for (auto& it : scene->TowerGroup->GetObjects()) {
		Turret* turret = dynamic_cast<Turret*>(it);
        if (!turret->Visible)
			continue;
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, turret->Position, turret->CollisionRadius)) {
			OnExplode(turret);
            getPlayScene()->TowerGroup->RemoveObject(turret->GetObjectIterator());
			getPlayScene()->BulletGroup->RemoveObject(objectIterator);
			return;
		}
	}
	// Check if out of boundary.
	if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, Engine::Point(0, 0), PlayScene::GetClientSize()))
		getPlayScene()->BulletGroup->RemoveObject(objectIterator);
	
}
void TankBullet::OnExplode(Turret* turret) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
	getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-1.png", dist(rng), turret->Position.x, turret->Position.y));
}

