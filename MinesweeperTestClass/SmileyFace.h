#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class SmileyFace {
private:
	Texture t;
	Sprite s;

	bool isClicked = false;

	int X;
	int Y;
public:
	SmileyFace() {
		t.loadFromFile("images/face_happy.png");
		s.setTexture(t);
	}
	void Click() {
		isClicked = true;
	}
	bool wasClicked() {
		return isClicked;
	}
	Vector2i GetPosition() {
		Vector2i po(X, Y);
		return po;
	}
	void SetTexture(string name) {
		t.loadFromFile("images/" + name + ".png");
		s.setTexture(t);
	}
	void SetPosition(Vector2i pos) {
		X = pos.x;
		Y = pos.y;
		Vector2f pos2((float)X, (float)Y);
		s.setPosition(pos2);
	}
	const Sprite& GetSprite() const {
		return s;
	}
};