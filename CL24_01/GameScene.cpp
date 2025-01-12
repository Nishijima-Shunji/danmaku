#include "GameScene.h"
#include "Game.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <sstream>

std::chrono::high_resolution_clock::time_point start;

GameScene::GameScene(int maxhp){
	sound.Init();
	sound.Play(SOUND_LABEL_BGM001);

	textureManager = new TextureManager(g_pDevice);

	// プレイヤーの生成
	player = new Player(maxhp);
	player->Init(textureManager, L"asset/player.png");
	player->SetPos(0.0f, -500.0f, 0.0f);
	player->SetSize(40.0f, 40.0f, 0.0f);

	// 背景の生成
	bg = new Object;
	bg->Init(textureManager, L"asset/Gamebg.png");
	bg->SetPos(0.0f, 0.0f, 0.0f);
	bg->SetSize(560.0f, 720.0f, 0.0f);
	bg->SetColor(1.0f, 0.0f, 0.0f, 0.0f);

	// スコア背景の生成
	score_bg = new Object;
	score_bg->Init(textureManager, L"asset/score_bg.png");
	score_bg->SetPos(-250.0f, -300.0f, 0.0f);
	score_bg->SetSize(50.0f, 50.0f, 0.0f);

	for (int i = 0; i < 5; i++) {
		// UIの生成
		scoreNum.emplace_back(std::make_unique<Object>());
		scoreNum.back()->Init(textureManager, L"asset/num.png", 10, 1);
		scoreNum.back()->SetPos((i * 25.0f) - 215.0f, -300.0f, 0.0f);
		scoreNum.back()->SetSize(25.0f, 25.0f, 0.0f);
		scoreNum.back()->SetUV(0, 0);
	}
	bulletManager = new BulletManager(this, enemies, player, textureManager);
}

GameScene::~GameScene() {
	// TextureManagerを解放
	delete textureManager;
	delete bulletManager;
	delete player;
	delete bg;
	delete score_bg;
}

// 更新
void GameScene::Update() {
	input.Update();

	// ダメージエフェクトを赤から徐々に透明に戻す
	if (bg->GetColor().w != 0.0f) {
		bg->SetColor(1.0f, 0.0f, 0.0f, bg->GetColor().w - 0.01f);
	}


	//=====================イントロアニメーション=====================
	if (state == 0) {
		Intro();
	}
	//=====================ゲームスタート=====================
	else if (state == 1) {
		// 現在の時間を取得
		auto now = std::chrono::high_resolution_clock::now();
		// 経過時間を計算
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);


		// ========弾発射========
		if (input.GetKeyPress(VK_SPACE)) {
			if (shootcount % shootInterval == 0) {
				if (score != 0) {
					score--;
				}
				bulletManager->ShootBullet();
				shootcount = 0;
				sound.Play(SOUND_LABEL_SEthrow);
			}
			shootcount++;
		}

		bulletManager->Update();

		// ========弾の画面外検知========
		bulletManager->OutBullet();

		// ========敵生成========
		spawnTimer += 1.0f / 60.0f;
		// 特定の時間の時だけ特殊な敵を生成
		if (elapsed.count() > 10000) {
			enemyType = 1;
			// タイマーをリセット
			start = now;
		}
		if (spawnTimer >= rand() % 5 + 1) {
			spawnTimer = 0.0f;
			if (enemies.size() < 30) {
				SpawnEnemy(enemyType);
				//生成した敵の種類がノーマルでないなら
				if (enemyType != 0) {
					// 敵の種類をノーマルに設定
					enemyType = 0;
				}
			}
		}

		// ========キャラクター更新========
		player->Update(input);

		// ========敵の更新========
		for (auto it = enemies.begin(); it != enemies.end();) {
			auto& enemy = *it;
			enemy->Update();
			int state = enemy->GetState();

			// 敵の弾発射
			if (state == 1 && enemy->CanShoot()) {
				bulletManager->EnemyShootBullet(enemy.get());
				enemy->ResetCoolTime();
			}

			// 範囲外へ行くか体力がなくなると消す
			if (enemy->GetDeadFlg() == true || enemy->GetPos().y > 500.0f) {
				// スコア増加
				score += (enemy->GetEnemyType() * 5 + 5) * 5;
				// 敵が死亡している場合削除
				it = enemies.erase(it);
				std::cout << score << std::endl;
			}
			else {
				// それ以外は次の要素に進む
				++it;
			}
		}

		// ========死亡========
		if (player->GetdeadFlg()) {
			player->SetVelocity(DirectX::SimpleMath::Vector3(0.0f,20.0f,0.0f));
			state = 2;
			sound.Play(SOUND_LABEL_SE002);
		}

		// ========スコア表示用========
		int tempScore = score;
		for (int i = static_cast<int>(scoreNum.size()) - 1; i >= 0; i--) {
			int digit = tempScore % 10;  // 右端の桁を取得
			tempScore /= 10;			 // スコアを10で割って次の桁へ進む

			// UVを桁の値に基づいて設定
			scoreNum[i]->SetUV(digit, 0);
		}
	}

	// =====================死亡アニメーション=====================
	else if (state == 2) {
		Outro();
		if (player->GetPos().y < -400.0f) {
			sound.Stop(SOUND_LABEL_BGM001);
			SceneManager::ChangeScene(SceneManager::RESULT, score);
		}
	}
	// 負荷軽減
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}


void GameScene::Draw() {
	player->Draw();
	bulletManager->Draw();
	for (auto& obj : enemies) {
		obj->Draw();
	}
	for (auto& obj : health) {
		obj->Draw();
	}
	score_bg->Draw();
	for (auto& obj : scoreNum) {
		obj->Draw();
	}
	bg->Draw();
}

void GameScene::SpawnEnemy(int type) {
	// 敵の生成
	enemies.emplace_back(std::make_unique<Enemy>(type));
	// 敵の初期化
	AddEnemy(L"asset/enemy", type);
	// 指定の座標に生成
	//enemies.back()->SetPos(posX, posY, 0.0f);
	enemies.back()->SetSize(enemies.back()->GetRadius() * 2, enemies.back()->GetRadius() * 2, 0.0f);
}

void GameScene::AddEnemy(const std::wstring& baseTexturePath, int enemyType) {
	// テクスチャパスを生成
	std::wstringstream texturePath;
	texturePath << baseTexturePath << enemyType << L".png";

	enemies.back()->Init(textureManager, texturePath.str().c_str());
}

void GameScene::RemoveEnemy(Enemy* enemy) {
	if (!enemy) {
		return;
	}
	// 対象の敵を探して削除
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
		[enemy](const std::unique_ptr<Enemy>& e) {
			return e.get() == enemy;
		}),
		enemies.end());
}

void GameScene::TakeDamege() {
	// 体力減らす
	health.erase(health.end() - 1);
	// 背景真っ赤に（ダメージエフェクト）
	bg->SetColor(1.0f, 0.0f, 0.0f, 0.7f);
}

void GameScene::Intro() {
	// ループカウント
	static int animcount;
	// 現在表示した体力
	static int healthval;
	// 体力の最大値（この数値まで体力生成する）
	int maxhealth = player->GetHealth();
	player->Intro();


	if (player->GetPos().y >= -100.0f) {
		if (animcount % 10 == 0 && healthval < maxhealth) {
			// UIの生成
			health.emplace_back(std::make_unique<Object>());
			// UIの初期化
			health.back()->Init(textureManager, L"asset/health.png");
			// 位置設定
			health.back()->SetPos(120.0f + healthval + (healthval % 10) * 14.0f, -280.0f - (healthval / 10) * 15.0f, 0.0f);
			health.back()->SetSize(15.0f, 15.0f, 0.0f);
			healthval++;
		}
		// 体力が最大になったらアニメーション終了
		else if (healthval == maxhealth) {
			state = 1;
			healthval = 0;
			animcount = 0;
			// ゲーム時間の計測開始
			start = std::chrono::high_resolution_clock::now();
		}
	}
	animcount++;
}

void GameScene::Outro() {
	player->Outro();
}
