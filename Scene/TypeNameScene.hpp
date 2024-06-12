#ifndef TypeNameScene_HPP
#define TypeNameScene_HPP

#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"

class TypeNameScene final : public Engine::IScene {
private:
    std::string name = "";
public:
    explicit TypeNameScene() = default;

    void Initialize() override;

    void Terminate() override;

    void NextOnClick();

    void Draw() const override;

    void OnKeyDown(int keyCode) override;
};

#endif // TypeNameScene_HPP
