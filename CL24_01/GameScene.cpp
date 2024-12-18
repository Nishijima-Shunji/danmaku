#include "GameScene.h"
#include "Game.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <sstream>

std::chrono::high_resolution_clock::time_point start;

GameScene::GameScene() {
	textureManager = new TextureManager(g_pDevice);

	// プレイヤーの生成
	player = new Player;
	player->Init(textureManager, L"asset/player.png");
	player->SetPos(0.0f, -500.0f, 0.0f);
	player->SetSize(40.0f, 40.0f, 0.0f);

	// 背景の生成
	bg = new Object;
	bg->Init(textureManager, L"asset/Gamebg.png");
	bg->SetPos(0.0f, 0.0f, 0.0f);
	bg->SetSize(560.0f, 720.0f, 0.0f);
	bg->SetColor(1.0f, 0.0f, 0.0f, 0.0f);

	bulletManager = new BulletManager(this, enemies, player, textureManager);
}

GameScene::~GameScene() {
	// TextureManagerを解放
	delete textureManager;
	delete bulletManager;
	delete player;
	delete bg;
}

// 更新
void GameScene::Update() {
	input.Update();
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
				bulletManager->ShootBullet();
				shootcount = 0;
			}
			shootcount++;
		}

		bulletManager->Update();
		// ========弾の範囲検知========
		bulletManager->OutBullet();

		// ========敵生成========
		spawnTimer += 1.0f / 60.0f;
		// 特定の時間の時だけ特殊な敵を生成
		if (elapsed.count() == 100) {
			enemyType = 1;
		}
		if (spawnTimer >= rand() % 5 + 1) {
			spawnTimer = 0.0f;
			float spawnX, spawnY;
			spawnX = rand() % MAP_WIDTH - (MAP_WIDTH / 2);  // -470 ～ 390の範囲でX位置をランダム生成
			spawnY = (MAP_HEIGHT / 2);
			SpawnEnemy(spawnX, spawnY, enemyType);
			//生成した敵の種類がノーマルでないなら
			if (enemyType != 0) {
				// 敵の種類をノーマルに設定
				enemyType = 0;
			}
		}

		// ========キャラクター更新========
		player->Update(input);

		// ダメージエフェクトを赤から徐々に透明に戻す
		if (bg->GetColor().w != 0.0f) {
			bg->SetColor(1.0f, 0.0f, 0.0f, bg->GetColor().w - 0.01f);
		}

		// ========敵の更新========
		for (auto& enemy : enemies) {
			enemy->Update();
			int state = enemy->GetState();
			if (state == 1 && enemy->CanShoot()) {
				// プレイヤーの座標に生成
				DirectX::XMFLOAT3 t_pos = enemy->GetPos();
				//弾の発射方法をエネミータイプによって
				switch (enemy->GetEnemyType()) {
				case 0:
					bulletManager->EnemyShootBullet(t_pos);
					break;
				case 1:
					break;
				}
				enemy->ResetCoolTime();
			}
		}

		// 削除フラグが立っている敵を削除
		enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const std::unique_ptr<Enemy>& enemy) {
			return enemy->GetDeadFlg();
			}),
			enemies.end());


		// ========死亡========
		if (player->GetdeadFlg()) {
			SceneManager::ChangeScene(SceneManager::RESULT);
		}

		// デバッグ
		if (input.GetKeyTrigger(VK_3)) {
			SceneManager::ChangeScene(SceneManager::RESULT);
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
	bg->Draw();
}

void GameScene::SpawnEnemy(float posX, float posY, int type) {
	// 敵の生成
	enemies.emplace_back(std::make_unique<Enemy>(type));
	// 敵の初期化
	AddEnemy(L"asset/enemy",type);
	// 指定の座標に生成
	enemies.back()->SetPos(posX, posY, 0.0f);
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
		return;  // 無効なポインタは無視
	}
	// 対象の敵をenemiesから探して削除
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
		[enemy](const std::unique_ptr<Enemy>& e) {
			return e.get() == enemy;
		}),
		enemies.end());
}

// ダメージを受けたら
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
			health.back()->SetPos(120.0f + healthval + (healthval % 10) * 15.0f, -300.0f - (healthval / 10) * 15.0f, 0.0f);
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

Player* GameScene::GetPlayer() {
	return player;
}
