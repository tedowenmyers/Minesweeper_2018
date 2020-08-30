#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Test1 {
private:
	Texture t;
	Sprite s;

	bool isClicked = false;

	int X;
	int Y;
public:
	Test1() {
		t.loadFromFile("images/test_1.png");
		s.setTexture(t);
	}
	void Click() {
		isClicked = true;
	}
	void unClick() {
		isClicked = false;
	}
	bool wasClicked() {
		return isClicked;
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
//Test2
class Test2 {
private:
	Texture t;
	Sprite s;

	bool isClicked = false;

	int X;
	int Y;
public:
	Test2() {
		t.loadFromFile("images/test_2.png");
		s.setTexture(t);
	}
	void Click() {
		isClicked = true;
	}
	void unClick() {
		isClicked = false;
	}
	bool wasClicked() {
		return isClicked;
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