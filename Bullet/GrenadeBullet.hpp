#ifndef GRENADEBULLET_HPP
#define GRENADEBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class GrenadeBullet : public Bullet {
public:
	explicit GrenadeBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void Update(float deltaTime) override;
	void OnExplode(Enemy* enemy) override;
};
#endif // GRENADEBULLET_HPP
