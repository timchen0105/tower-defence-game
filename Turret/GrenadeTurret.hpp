#ifndef GRENADETURRET_HPP
#define GRENADETURRET_HPP
#include "Turret.hpp"

class GrenadeTurret: public Turret {
public:
	static const int Price;
    GrenadeTurret(float x, float y);
	void CreateBullet() override;
};
#endif // GRENADETURRET_HPP
