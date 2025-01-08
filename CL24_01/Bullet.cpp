#include "Bullet.h"
#include <cmath>

Bullet::Bullet(int setType) : bulletType(setType), rotationOffset(0.0f), initRadius(10.0f) {
	if (setType == 2) {
		moveSpeed = 0.0001f;
	}
	else {
		moveSpeed = 0.3f;
	}
}

Bullet::~Bullet() {

}

void Bullet::Update() {
	move();
}

void Bullet::move() {
	switch (bulletType) {
	// 自分の弾
	case 0:	
		direction = { 0.0f,1.0f,0.0f };
		break;

	// 通常敵の弾
	case 1:
		direction = { 0.0f,-1.0f,0.0f };
		break;

	// 特殊敵の弾
	case 2:
		// 回転の更新（各弾ごとに異なる角度を使用）
		rotationOffset += rotationSpeed; // 角度を進めて回転

		// 半径を増加させて、弾を広げる
		initRadius += expansionSpeed; // 以前の initialRadius を initRadius に変更

		// 弾の位置を更新するために、敵の位置を基準に計算
		float offsetX = initRadius * std::cos(rotationOffset); // 回転後の x 座標
		float offsetY = initRadius * std::sin(rotationOffset); // 回転後の y 座標

		// 弾の進行方向ベクトルを更新（回転後の方向）
		direction = DirectX::SimpleMath::Vector3(offsetX, offsetY, 0.0f);

		// 新しい位置を計算（敵の位置を基準にして回転させる）
		pos = DirectX::SimpleMath::Vector3(t_pos.x + offsetX, t_pos.y + offsetY, t_pos.z);

		break;
	}
	velocity += direction * moveSpeed;
	pos += velocity;
}

bool Bullet::CheckCollision(const DirectX::XMFLOAT3& objPos, float r) {
	DirectX::XMFLOAT3 circlePos = GetPos();
	float radius = 20.0f; // 現在の円の半径

	// 中心間の距離の二乗を計算
	float dx = circlePos.x - objPos.x;
	float dy = circlePos.y - objPos.y;
	float distanceSquared = dx * dx + dy * dy;

	// 半径の和の二乗
	float radiusSum = radius + r;
	float radiusSumSquared = radiusSum * radiusSum;

	// 距離の二乗が半径の和の二乗以下であれば衝突
	return distanceSquared <= radiusSumSquared;
}

int Bullet::GetBulletDamege() {
	return bulletDamage;
}

void Bullet::SetVelocity(float x, float y, float z) {
	velocity = DirectX::SimpleMath::Vector3(x, y, z);
}

void Bullet::SetDirection(const DirectX::SimpleMath::Vector3& dir) {
	direction = dir;
}

void Bullet::SetRotationOffset(float angle) {
	rotationOffset = angle; // 回転角度を設定
}

void Bullet::SetTargetPos(DirectX::SimpleMath::Vector3 pos) {
	t_pos = pos;
}