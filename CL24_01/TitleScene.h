#pragma once
#include "BaseScene.h"
#include "Sound.h"

class Game;
class TitleScene : public BaseScene
{
private:
	Sound sound;
	Object* title_bg;
	Object* button;
	Object* health;
	std::vector<std::unique_ptr<Object>> scoreNum;

	int state = 0;

	int max = 30;
	int maxhp = 1;

	float time = 0.0f;
	float frequency = 0.8f;     // �U���̑��� (1.0f = 1�b��1����)
	float amplitude = 10.0f;    // �U�� (�p�x�͈̔�: �}�x)
	float offset = 0.0f;       // ��p�x (���S�ʒu)

public:
	TitleScene();
	~TitleScene();

	void Update() override;
	void Draw() override;
};