# include <Siv3D.hpp> // OpenSiv3D v0.6.3
#include "Snake.h"
void Main()
{
	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });
	const int Start_x = 145;
	const int Start_y = 45;
	const int Rects_w = 50;
	const int Rects_h = 50;
	const int offset = 1;
	Rect food;
	bool Is_Active = false;

	int score = 0;

	Array<Rect> rects;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			rects.push_back(Rect{ Start_x + (Rects_w + offset) * j , Start_y + (Rects_h + offset) * i , Rects_w , Rects_h });
		}
	}

	Snake s(rects.at(0));
	bool bCanMove = true;
	uint64 curTime;
	uint64 moveTime = 1000.0f;

	SmallRNG rng1{ static_cast<uint64_t>(DateTime::Now().year + DateTime::Now().hour + DateTime::Now().second) };

	uint64 foodTime;
	const uint64 RespawnTime = 2.0f;
	food = rects.at(Random(1, 99, rng1));
	Is_Active = true;
	foodTime = Time::GetSec();
	const Font font{ 30 };
	while (System::Update())
	{
		font(score).drawAt(Vec2(30,30), Palette::Black);
		for (auto r : rects)
		{
			r.draw();
		}
		if (Is_Active)
		{
			food.draw(Palette::Darkslategray);
		}
		else
		{
			if (Time::GetSec() - foodTime > RespawnTime)
			{
				do
				{
					food = rects.at(Random(0, 99, rng1));
				} while (s.body.count(food) != 0);
				Is_Active = true;
			}
		}
		
		s.draw();
		if (bCanMove)
		{
			s.move();
			if (!s.CollisionTest(Start_x, Start_y, 10 * (Rects_w + offset), 10 * (Rects_h + offset)))
			{
				break;
			}
			if (s.CollisionTest(food.x, food.y, food.w, food.h) && Is_Active)
			{
				if (moveTime > 200) {
					moveTime -= 100.0f;
				}
				s.body_add(food);
				Is_Active = false;
				score += 5;
			}
			curTime = Time::GetMillisec();
			bCanMove = false;
		}
		else
		{
			if (Time::GetMillisec() - curTime > moveTime)
				bCanMove = true;
		}
		if (KeyW.pressed())
		{
			s.SetUp();
		}
		if (KeyS.pressed())
		{
			s.SetDown();
		}
		if (KeyA.pressed())
		{
			s.SetLeft();
		}
		if (KeyD.pressed())
		{
			s.SetRight();
		}
	}
}

