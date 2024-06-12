#ifndef TANKBULLET_HPP
#define TANKBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class TankBullet : public Bullet {
public:
	explicit TankBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void Update(float deltaTime) override;
	void OnExplode(Turret* turret);
};
#endif // TANKBULLET_HPP
