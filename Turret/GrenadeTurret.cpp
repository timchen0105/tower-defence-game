#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/GrenadeBullet.hpp"
#include "Bullet/FireBullet.hpp"
#include "Engine/Group.hpp"
#include "GrenadeTurret.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

const int GrenadeTurret::Price = 250;
GrenadeTurret::GrenadeTurret(float x, float y) :
	Turret("play/tower-base.png", "play/turret-4.png", x, y, 500, Price, 2) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void GrenadeTurret::CreateBullet() {
	Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
	float rotation = atan2(diff.y, diff.x);
	Engine::Point normalized = diff.Normalize();
	// Change bullet position to the front of the gun barrel.
	getPlayScene()->BulletGroup->AddNewObject(new GrenadeBullet(Position + normalized * 36, diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}
