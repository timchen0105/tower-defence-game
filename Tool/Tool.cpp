#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <utility>

#include "Enemy/Enemy.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Tool.hpp"

PlayScene* Tool::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
Tool::Tool(std::string imgTurret, float x, float y) : Sprite(imgTurret, x, y) {
}
void Tool::Update(float deltaTime) {
	Sprite::Update(deltaTime);
}
void Tool::Draw() const {
	Sprite::Draw();
}