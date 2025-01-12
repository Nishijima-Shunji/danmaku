#pragma once
#include "BaseScene.h"
#include "sound.h"

class Game;
class ResultScene : public BaseScene
{
private:
    Sound sound;
    Object* result_bg;
    Object* button;
    Object* score_bg;
    std::vector<std::unique_ptr<Object>> scoreNum;

    float time = 0.0f;
    float frequency = 1.0f;     // U“®‚Ì‘¬‚³ (1.0f = 1•b‚Å1üŠú)
    float amplitude = 960.0f;    // U• (Šp“x‚Ì”ÍˆÍ: }30“x)
    float offset = 0.0f;       // Šî€Šp“x (’†SˆÊ’u)
    int score;

public:
    ResultScene(int score);
    ~ResultScene();


    void Update() override;
    void Draw() override;
};

