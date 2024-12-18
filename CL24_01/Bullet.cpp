#include "Bullet.h"

Bullet::Bullet(int setType) : bulletType(setType) {
	moveSpeed = 0.3f;
}

Bullet::~Bullet() {

}

void Bullet::Update() {
	move();
}

void Bullet::move() {
	switch (bulletType) {
	case 0:
		direction = { 0.0f,1.0f,0.0f };
		break;
	case 1:
		direction = { 0.0f,-1.0f,0.0f };
		break;
	//case 2:

	//}
	}
	velocity += direction * moveSpeed;
		pos += velocity;
}

bool Bullet::CheckCollision(const DirectX::XMFLOAT3& objPos, float r) {
	DirectX::XMFLOAT3 circlePos = GetPos();
	float radius = 20.0f; // Œ»İ‚Ì‰~‚Ì”¼Œa

	// ’†SŠÔ‚Ì‹——£‚Ì“ñæ‚ğŒvZ
	float dx = circlePos.x - objPos.x;
	float dy = circlePos.y - objPos.y;
	float distanceSquared = dx * dx + dy * dy;

	// ”¼Œa‚Ì˜a‚Ì“ñæ
	float radiusSum = radius + r;
	float radiusSumSquared = radiusSum * radiusSum;

	// ‹——£‚Ì“ñæ‚ª”¼Œa‚Ì˜a‚Ì“ñæˆÈ‰º‚Å‚ ‚ê‚ÎÕ“Ë
	return distanceSquared <= radiusSumSquared;
}

int Bullet::GetBulletDamege() {
	return bulletDamage;
}