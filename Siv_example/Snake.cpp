#include "stdafx.h"
#include "Snake.h"

Snake::Snake(Rect Inital_) : move_dir(Vec2(1,0))
{
	body.push_back(Inital_);
}
bool Snake::CollisionTest(int startX, int startY, int width, int height)
{
	if(startX > body.front().x || body.front().x >= startX + width)
	{
		return false;
	}
	if (startY > body.front().y || startY + height <= body.front().y)
	{
		return false;
	}

	for (int i = 1; i < body.size(); i++) {
		if (body.at(i) == body.front()) {
			return false;
		}
	}
	return true;
}
void Snake::body_add(Rect a)
{
	body.push_back(a);
}
void Snake::SetUp()
{
	move_dir = Vec2(0, 1);
}

void Snake::move()
{
	Rect front = body.front();
	if (move_dir == Vec2(1, 0)) {
		body.push_front(Rect{front.x + 51 , front.y , front.w , front.h});
	}
	if (move_dir == Vec2(-1, 0)) {
		body.push_front(Rect{ front.x - 51 , front.y , front.w , front.h });
	}
	if (move_dir == Vec2(0, -1)) {
		body.push_front(Rect{ front.x , front.y + 51 , front.w , front.h });
	}
	if (move_dir == Vec2(0, 1)) {
		body.push_front(Rect{ front.x , front.y - 51 , front.w , front.h });
	}
	body.pop_back();
}

void Snake::SetDown()
{
	move_dir = Vec2(0, -1);
}

void Snake::SetRight()
{
	move_dir = Vec2(1, 0);
}

void Snake::draw()
{
	int h = 0;
	for (auto elem : body) {
		h += 10;
		elem.draw(ColorF{ HSV(h) });
	}
}

void Snake::SetLeft()
{
	move_dir = Vec2(-1, 0);
}
