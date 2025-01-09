#pragma once
#include "BaseScene.h"


class Game;
class ResultScene : public BaseScene
{
private:
    Object* result_bg;
    Object* button;
    Object* score_bg;
    std::vector<std::unique_ptr<Object>> scoreNum;

    float time = 0.0f;
    float frequency = 1.0f;     // �U���̑��� (1.0f = 1�b��1����)
    float amplitude = 960.0f;    // �U�� (�p�x�͈̔�: �}30�x)
    float offset = 0.0f;       // ��p�x (���S�ʒu)
    int score;

public:
    ResultScene(int score);
    ~ResultScene();


    void Update() override;
    void Draw() override;
};

