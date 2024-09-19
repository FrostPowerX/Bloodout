#include "Utils.h"

int GetRandomValue(int minValue, int maxValue)
{
	return minValue + (rand() % (maxValue - minValue + 1));
}

bool CheckCollision(Rectangle r1, Rectangle r2)
{
	float r1X2 = r1.x + (r1.width / 2);

	float r1Y = r1.y + (r1.height / 2);

	float r2X2 = r2.x + (r2.width / 2);

	float r2Y = r2.y + (r2.height / 2);

	return	(r1X2 >= r2.x &&
		r2X2 >= r1.x &&
		r1Y >= r2.y &&
		r2Y >= r1.y);
}

bool CheckCollision(Circle c1, Circle c2)
{
	double refX = c1.x - c2.x;
	double refY = c1.y - c2.y;

	double distance = sqrt(refX * refX + refY * refY);

	return (distance < c1.radius + c2.radius);
}

bool CheckCollision(Rectangle r, Circle c)
{
	double pointX = c.x;
	double pointY = c.y;

	if (pointX < r.x - (r.width / 2))
		pointX = r.x - (r.width / 2);

	if (pointX > r.x + (r.width / 2))
		pointX = r.x + (r.width / 2);

	if (pointY < r.y - (r.height / 2))
		pointY = r.y - (r.height / 2);

	if (pointY > r.y + (r.height / 2))
		pointY = r.y + (r.height / 2);

	double refX = c.x - pointX;
	double refY = c.y - pointY;

	double distance = sqrt(refX * refX + refY * refY); // Distancia euclidiana

	return (distance < c.radius);
}

bool CheckCollision(Circle c, Rectangle r)
{
	double pointX = c.x;
	double pointY = c.y;

	if (pointX < r.x - (r.width / 2))
		pointX = r.x - (r.width / 2);

	if (pointX > r.x + (r.width / 2))
		pointX = r.x + (r.width / 2);

	if (pointY < r.y - (r.height / 2))
		pointY = r.y - (r.height / 2);

	if (pointY > r.y + (r.height / 2))
		pointY = r.y + (r.height / 2);

	double refX = c.x - pointX;
	double refY = c.y - pointY;

	double distance = sqrt(refX * refX + refY * refY); // Distancia euclidiana

	return (distance < c.radius);
}

bool CheckBorderCollision(Circle c, float maxWidth, float minWidth, float maxHeight, float minHeight)
{
	if (c.y > maxHeight - c.radius || c.y < minHeight + c.radius)
		return true;

	if (c.x > maxWidth - c.radius || c.x < minWidth + c.radius)
		return true;

	return false;
}

bool CheckBorderCollision(Rectangle rect, float maxWidth, float minWidth, float maxHeight, float minHeight)
{
	if (rect.y > maxHeight - (rect.height / 2) || rect.y < minHeight + (rect.height / 2))
		return true;

	if (rect.x > maxWidth - (rect.width / 2) || rect.x < minWidth + (rect.width / 2))
		return true;

	return false;
}

TYPE_PENETRATION SolveCollision(Rectangle& entityA, Circle& entityB)
{
	TYPE_PENETRATION typeOfPenetration = TYPE_PENETRATION::NONE;

	Vector2 separationB;
	separationB.x = 0;
	separationB.y = 0;

	float widthAGB = entityA.width / 2;
	float heightAGB = entityA.height / 2;

	float widthBGB = entityB.radius;
	float heightBGB = entityB.radius;

	Vector2 entityACenteredPos;
	entityACenteredPos.x = entityA.x;
	entityACenteredPos.y = entityA.y;

	Vector2 entityBCenteredPos;
	entityBCenteredPos.x = entityB.x;
	entityBCenteredPos.y = entityB.y;

	Vector2 diff;

	diff.x = entityBCenteredPos.x - entityACenteredPos.x;
	diff.y = entityBCenteredPos.y - entityACenteredPos.y;

	float minHorDistance = widthAGB + widthBGB;
	float minVerDistance = heightAGB + heightBGB;

	float horPenetration = minHorDistance - abs(diff.x);
	float verPenetration = minVerDistance - abs(diff.y);

	bool isPositiveDiff;
	float displacementB = 0;
	float displacementBSign;

	if (horPenetration > verPenetration) // Colisionan verticalmente
	{
		isPositiveDiff = (diff.y > 0.f);
		displacementBSign = (isPositiveDiff) ? 1.f : -1.f;

		displacementB = verPenetration * displacementBSign;

		separationB.y = displacementB;

		typeOfPenetration = TYPE_PENETRATION::VERTICAL;
	}
	else // Colisionan horizontalmente
	{
		isPositiveDiff = (diff.x > 0.f);
		displacementBSign = (isPositiveDiff) ? 1.f : -1.f;

		displacementB = horPenetration * displacementBSign;

		separationB.x = displacementB;

		typeOfPenetration = TYPE_PENETRATION::HORIZONTAL;
	}

	entityB.x += separationB.x;
	entityB.y += separationB.y;

	return typeOfPenetration;
}

TYPE_PENETRATION SolveCollision(Circle& entityA, Circle& entityB)
{
	TYPE_PENETRATION typeOfPenetration = TYPE_PENETRATION::NONE;

	Vector2 separationA;
	separationA.x = 0;
	separationA.y = 0;
	Vector2 separationB;
	separationB.x = 0;
	separationB.y = 0;

	float widthAGB = entityA.radius;
	float heightAGB = entityA.radius;

	float widthBGB = entityB.radius;
	float heightBGB = entityB.radius;

	Vector2 entityACenteredPos;
	entityACenteredPos.x = entityA.x;
	entityACenteredPos.y = entityA.y;

	Vector2 entityBCenteredPos;
	entityBCenteredPos.x = entityB.x;
	entityBCenteredPos.y = entityB.y;

	Vector2 diff;

	diff.x = entityBCenteredPos.x - entityACenteredPos.x;
	diff.y = entityBCenteredPos.y - entityACenteredPos.y;

	float minHorDistance = widthAGB + widthBGB;
	float minVerDistance = heightAGB + heightBGB;

	float horPenetration = minHorDistance - abs(diff.x);
	float verPenetration = minVerDistance - abs(diff.y);

	bool isPositiveDiff;

	float displacementA = 0;
	float displacementASign;

	float displacementB = 0;
	float displacementBSign;

	if (horPenetration > verPenetration) // Colisionan verticalmente
	{
		isPositiveDiff = (diff.y > 0.f);

		displacementASign = (isPositiveDiff) ? -1.f : 1.f;
		displacementBSign = (isPositiveDiff) ? 1.f : -1.f;

		displacementA = verPenetration * displacementASign;
		displacementB = verPenetration * displacementBSign;

		separationA.y = displacementA;
		separationB.y = displacementB;

		typeOfPenetration = TYPE_PENETRATION::VERTICAL;
	}
	else // Colisionan horizontalmente
	{
		isPositiveDiff = (diff.x > 0.f);
		displacementASign = (isPositiveDiff) ? -1.f : 1.f;
		displacementBSign = (isPositiveDiff) ? 1.f : -1.f;

		displacementA = horPenetration * displacementASign;
		displacementB = horPenetration * displacementBSign;

		separationA.x = displacementA;
		separationB.x = displacementB;

		typeOfPenetration = TYPE_PENETRATION::HORIZONTAL;
	}

	entityA.x += separationA.x;
	entityA.y += separationA.y;

	entityB.x += separationB.x;
	entityB.y += separationB.y;

	return typeOfPenetration;
}


TYPE_PENETRATION SolveCollisionMap(Ball& entity, float maxWidth, float minWidth, float maxHeight, float minHeight)
{
	TYPE_PENETRATION typeOfPenetration = TYPE_PENETRATION::NONE;

	float minHorDistance = entity.cir.x - entity.cir.radius - minWidth;
	float maxHorDistance = entity.cir.x + entity.cir.radius;

	float minVerDistance = entity.cir.y - entity.cir.radius - minHeight;
	float maxVerDistance = entity.cir.y + entity.cir.radius;

	bool downHorPenetration = maxHorDistance > maxWidth - entity.cir.radius;
	bool upHorPenetration = minHorDistance < 0;

	bool downVerPenetration = maxVerDistance > maxHeight - entity.cir.radius;
	bool upVerPenetration = minVerDistance < 0;

	Vector2 separation;
	separation.x = 0;
	separation.y = 0;

	if (downHorPenetration)
		separation.x = maxHorDistance - maxWidth;
	else if (upHorPenetration)
		separation.x = minHorDistance;

	if (downVerPenetration)
		separation.y = maxVerDistance - maxHeight;
	else if (upVerPenetration)
		separation.y = minVerDistance;

	if (downVerPenetration || upVerPenetration)
	{
		typeOfPenetration = VERTICAL;
		entity.dirY *= -1.f;
	}

	if (downHorPenetration || upHorPenetration)
	{
		typeOfPenetration = HORIZONTAL;
		entity.dirX *= -1.f;
	}

	entity.cir.x -= separation.x;
	entity.cir.y -= separation.y;

	return typeOfPenetration;
}

TYPE_PENETRATION SolveCollisionMap(Rectangle& entity, float maxWidth, float minWidth, float maxHeight, float minHeight)
{
	TYPE_PENETRATION typeOfPenetration = TYPE_PENETRATION::NONE;

	float halfWidth = (entity.width / 2);
	float halfHeight = (entity.height / 2);

	float entityCenteredPosX = entity.x;
	float entityCenteredPosY = entity.y;

	float minHorDistance = entityCenteredPosX - halfWidth - minWidth;
	float maxHorDistance = entityCenteredPosX + halfWidth;

	float minVerDistance = entityCenteredPosY - halfHeight - minHeight;
	float maxVerDistance = entityCenteredPosY + halfHeight;

	bool downHorPenetration = maxHorDistance > maxWidth - halfWidth;
	bool upHorPenetration = minHorDistance < 0;

	bool downVerPenetration = maxVerDistance > maxHeight - halfHeight;
	bool upVerPenetration = minVerDistance < 0;

	Vector2 separation;
	separation.x = 0;
	separation.y = 0;

	if (downHorPenetration)
		separation.x = maxHorDistance - maxWidth;
	else if (upHorPenetration)
		separation.x = minHorDistance;

	if (downVerPenetration)
		separation.y = maxVerDistance - maxHeight;
	else if (upVerPenetration)
		separation.y = minVerDistance;

	if (downVerPenetration || upVerPenetration)
		typeOfPenetration = VERTICAL;

	if (downHorPenetration || upHorPenetration)
		typeOfPenetration = HORIZONTAL;

	entity.x -= separation.x;
	entity.y -= separation.y;

	return typeOfPenetration;
}

void NormalizeVector(float& x, float& y)
{
	Vector2 zero;
	zero.x = 0;
	zero.y = 0;

	float length = sqrt(x * x + y * y);

	x = (length > 0.f) ? x / length : zero.x;
	y = (length > 0.f) ? y / length : zero.y;
}

void BouncingAngle(Ball& ball, Rectangle& rect)
{
	float maxBounceAngle = 70.0f * (PI / 180.0f);

	float intersectPointX = ball.cir.x - rect.x;
	float intersectPointY = ball.cir.y - rect.y;

	float relativePointX = intersectPointX / (rect.width / 2);
	float relativePointY = intersectPointY / (rect.height / 2);

	float bounceAngle = relativePointY * maxBounceAngle;

	if (fabs(intersectPointX) > 1.f)
	{
		ball.dirX = relativePointY * cos(bounceAngle);
		ball.dirY = sin(bounceAngle);
	}
	else
	{
		ball.dirX = 0;
		ball.dirY = (ball.dirY > 0) ? 1.0f : -1.0f;
	}

	NormalizeVector(ball.dirX, ball.dirY);
}

void BouncingBalls(Ball& b1, Ball& b2)
{
	Vector2 normalCol;

	normalCol.x = b1.cir.x - b2.cir.x;
	normalCol.y = b1.cir.y - b2.cir.y;
	NormalizeVector(normalCol.x, normalCol.y);

	Vector2 relativeDir;
	relativeDir.x = b1.dirX - b2.dirX;
	relativeDir.y = b1.dirY - b2.dirY;

	float dirNormalized = relativeDir.x * normalCol.x + relativeDir.y * normalCol.y;

	if (dirNormalized > 0)
		return;

	b1.dirX = b1.dirX - normalCol.x * dirNormalized;
	b1.dirY = b1.dirY - normalCol.y * dirNormalized;

	b2.dirX = b2.dirX + normalCol.x * dirNormalized;
	b2.dirY = b2.dirY + normalCol.y * dirNormalized;
}
