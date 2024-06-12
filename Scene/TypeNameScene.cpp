#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <ctime>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Record.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "TypeNameScene.hpp"
#include "ScoreboardScene.hpp"
#include "PlayScene.hpp"

void TypeNameScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    AddNewObject(new Engine::Label("Type your name", "pirulen.ttf", 48, halfW, halfH / 6, 225, 255, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Your score: " + std::to_string(total_score), "pirulen.ttf", 36, halfW, halfH / 6 + 100, 225, 255, 255, 255, 0.5, 0.5));

    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 5 / 3,
                                  400, 100);
    btn->SetOnClickCallback(std::bind(&TypeNameScene::NextOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Next", "pirulen.ttf", 48, halfW, halfH * 5 / 3 + 50, 0, 0, 0, 255, 0.5, 0.5));
}

void TypeNameScene::Terminate() {
    IScene::Terminate();
}

void TypeNameScene::NextOnClick() {
    time_t t = time(NULL);
    struct tm * pt = localtime(&t);
    std::string time = std::to_string(pt->tm_year+1900) + "/" + std::to_string(pt->tm_mon+1) + "/" + std::to_string(pt->tm_mday) + "-" + std::to_string(pt->tm_hour) + ":" + std::to_string(pt->tm_min) + ":" + std::to_string(pt->tm_sec);
    Engine::Record new_record(name, total_score, time);
    scoreRecords.insert(new_record);
    WriteScoreRecords();
    name = "";
    Engine::GameEngine::GetInstance().ChangeScene("scoreboard");
}

void TypeNameScene::Draw() const {
    IScene::Draw();
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	Engine::Label nameLabel(name, "pirulen.ttf", 36, halfW, halfH, 255, 255, 255, 255, 0.5, 0.5);
    nameLabel.Draw();
}

void TypeNameScene::OnKeyDown(int keyCode) {
	IScene::OnKeyDown(keyCode);
	if (keyCode == ALLEGRO_KEY_BACKSPACE) {
		name = name.substr(0, name.length()-1);
	} else {
		if(keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z)
		name = name + char(keyCode + 64);
	}
}
