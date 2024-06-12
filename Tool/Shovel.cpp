#include <allegro5/base.h>
#include <string>

#include "Engine/Group.hpp"
#include "Shovel.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

Shovel::Shovel(float x, float y) : Tool("play/shovel.png", x, y) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
