#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Digits {
private:
	Texture t1;
	Sprite s1;
	Texture t2;
	Sprite s2;
	Texture t3;
	Sprite s3;

	int X;
	int Y;
public:
	Digits() {
		t1.loadFromFile("images/digits.png");
		s1.setTexture(t1);
		s1.setTextureRect(IntRect(21 * 0, 0, 21, 32));
		t2.loadFromFile("images/digits.png");
		s2.setTexture(t2);
		s2.setTextureRect(IntRect(21 * 5, 0, 21, 32));
		t3.loadFromFile("images/digits.png");
		s3.setTexture(t3);
		s3.setTextureRect(IntRect(21 * 0, 0, 21, 32));
		Vector2i p(0, 512);
		SetPosition(p);
	}
	void SetTexture1(int d) {
		t1.loadFromFile("images/digits.png");
		s1.setTexture(t1);
		s1.setTextureRect(IntRect(21 * d, 0, 21, 32));
	}
	void SetTexture2(int d) {
		t2.loadFromFile("images/digits.png");
		s2.setTexture(t2);
		s2.setTextureRect(IntRect(21 * d, 0, 21, 32));
	}
	void SetTexture3(int d) {
		t3.loadFromFile("images/digits.png");
		s3.setTexture(t3);
		s3.setTextureRect(IntRect(21 * d, 0, 21, 32));
	}
	void SetPosition(Vector2i pos) {
		X = pos.x;
		Y = pos.y;
		Vector2f pos2((float)X, (float)Y);
		s1.setPosition(pos2);
		Vector2f pos3((float)X + 21, (float)Y);
		s2.setPosition(pos3);
		Vector2f pos4((float)X + 42, (float)Y);
		s3.setPosition(pos4);
	}
	const Sprite& GetSprite(int c) const {
		vector<Sprite> v;
		switch (c) {
		case 1:
			return s1;
		case 2:
			return s2;
		case 3:
			return s3;
		default:
			return s1;
		}
	}
};