#pragma once
class Snake
{
public:
	Array<Rect> body;
	int length = 1;
private:
	Vec2 move_dir;

public:

	Snake(Rect Inital_Pos);
	bool CollisionTest(int startX, int startY, int width, int height);
	void body_add(Rect a);
	void draw();
	void move();
	void SetUp();
	void SetDown();
	void SetRight();
	void SetLeft();
};
