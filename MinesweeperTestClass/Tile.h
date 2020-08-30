#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
using namespace sf;
using namespace std;


class Tile {
private:
	Texture t;
	Sprite s;

	int numMines = 0;
	bool isMine = false;

	bool isClicked = false;
	bool isFlag = false;

	int X = 0;
	int Y = 0;
public:
	Tile() {
		t.loadFromFile("images/tile_hidden.png");
		s.setTexture(t);
	}
	Tile(string name, int row, int column) {
		t.loadFromFile("images/" + name + ".png");
		s.setTexture(t);
		X = 32 * row;
		Y = 32 * column;
		s.setPosition((float)X, (float)Y);
	}
	void SetTexture(string name) {
		t.loadFromFile("images/" + name + ".png");
		s.setTexture(t);
	}
	Vector2i GetPosition() {
		Vector2i po(X, Y);
		return po;
	}
	void SetPosition(Vector2i pos) {
		X = pos.x;
		Y = pos.y;
		Vector2f pos2((float)X, (float)Y);
		s.setPosition(pos2);
	}
	const Sprite& GetSprite() const{
		return s;
	}
	void isAMine() {
		//cout << "LOL1" << endl;
		isMine = true;
		//cout << "LOL2" << endl;
	}
	void notMine() {
		isMine = false;
	}
	bool theMine(){
		//cout << "LOL" << endl;
		return isMine;
	}
	void isAFlag() {
		if (isFlag) {
			isFlag = false;
		}
		else {
			isFlag = true;
		}
	}
	bool theFlag() {
		//cout << "LOL" << endl;
		return isFlag;
	}
	void SurroundingMines(vector<vector<Tile *>> &tiles) {
		numMines = 0;
		bool it = tiles.at(Y / 32).at(X / 32)->theMine();
		if (it) {
			isMine = true;
		}
		if (X != 0) {
			if (Y != 0) {
				if (tiles.at(Y / 32 - 1).at(X / 32 - 1)->theMine()) {
					++numMines;
				}
				if (tiles.at(Y / 32 - 1).at(X / 32)->theMine()) {
					++numMines;
				}
			}
			if (Y != 480) {
				if (tiles.at(Y / 32 + 1).at(X / 32 - 1)->theMine()) {
					++numMines;
				}
				if (tiles.at(Y / 32 + 1).at(X / 32)->theMine()) {
					++numMines;
				}
			}
			if (tiles.at(Y / 32).at(X / 32 - 1)->theMine()) {
				++numMines;
			}
		}
		if (X != 768) {
			if (Y != 0) {
				if (tiles.at(Y / 32 - 1).at(X / 32 + 1)->theMine()) {
					++numMines;
				}
				if (X == 0) {
					if (tiles.at(Y / 32 - 1).at(X / 32)->theMine()) {
						++numMines;
					}
				}
			}
			if (Y != 480) {
				if (tiles.at(Y / 32 + 1).at(X / 32 + 1)->theMine()) {
					++numMines;
				}
				if (X == 0) {
					if (tiles.at(Y / 32 + 1).at(X / 32)->theMine()) {
						++numMines;
					}
				}
			}
			if (tiles.at(Y / 32).at(X / 32 + 1)->theMine()) {
				++numMines;
			}
		}
	}
	void Recursion(vector<vector<Tile *>> &tiles) {
		//Call SurroundingMines
		if (X != 0) {
			if (Y != 0) {
				tiles.at(Y / 32 - 1).at(X / 32 - 1)->SurroundingMines(tiles);
				if (tiles.at(Y / 32 - 1).at(X / 32 - 1)->theMine()) {
					++numMines;
					//is a mine ->ignore
				}
				else {
					//is not a mine
					if (!tiles.at(Y / 32 - 1).at(X / 32 - 1)->wasClicked()) {
						tiles.at(Y / 32 - 1).at(X / 32 - 1)->Click();
						int n = tiles.at(Y / 32 - 1).at(X / 32 - 1)->GetNumMines();
						if (n > 0) {
							string s = "number_" + to_string(n);
							tiles.at(Y / 32 - 1).at(X / 32 - 1)->SetTexture(s);
						}
						else {
							tiles.at(Y / 32 - 1).at(X / 32 - 1)->SetTexture("tile_revealed");
							//set texture to tile_revealed.png

							tiles.at(Y / 32 - 1).at(X / 32 - 1)->Recursion(tiles);
							//RECURSION RECURSION
						}
						//was not clicked
					}
					//was clicked and not a mine->ignore
				}

				tiles.at(Y / 32 - 1).at(X / 32)->SurroundingMines(tiles);
				if (tiles.at(Y / 32 - 1).at(X / 32)->theMine()) {
					++numMines;
					//is a mine ->ignore
				}
				else {
					//is not a mine
					if (!tiles.at(Y / 32 - 1).at(X / 32)->wasClicked()) {
						tiles.at(Y / 32 - 1).at(X / 32)->Click();
						int n = tiles.at(Y / 32 - 1).at(X / 32)->GetNumMines();
						if (n > 0) {
							string s = "number_" + to_string(n);
							tiles.at(Y / 32 - 1).at(X / 32)->SetTexture(s);
						}
						else {
							tiles.at(Y / 32 - 1).at(X / 32)->SetTexture("tile_revealed");
							//set texture to tile_revealed.png

							tiles.at(Y / 32 - 1).at(X / 32)->Recursion(tiles);
							//RECURSION RECURSION
						}
						//was not clicked
					}
					//was clicked and not a mine->ignore
				}
			}
			if (Y != 480) {
				tiles.at(Y / 32 + 1).at(X / 32 - 1)->SurroundingMines(tiles);
				if (tiles.at(Y / 32 + 1).at(X / 32 - 1)->theMine()) {
					++numMines;
					//is a mine ->ignore
				}
				else {
					//is not a mine
					if (!tiles.at(Y / 32 + 1).at(X / 32 - 1)->wasClicked()) {
						tiles.at(Y / 32 + 1).at(X / 32 - 1)->Click();
						int n = tiles.at(Y / 32 + 1).at(X / 32 - 1)->GetNumMines();
						if (n > 0) {
							string s = "number_" + to_string(n);
							tiles.at(Y / 32 + 1).at(X / 32 - 1)->SetTexture(s);
						}
						else {
							tiles.at(Y / 32 + 1).at(X / 32 - 1)->SetTexture("tile_revealed");
							//set texture to tile_revealed.png

							tiles.at(Y / 32 + 1).at(X / 32 - 1)->Recursion(tiles);
							//RECURSION RECURSION
						}
						//was not clicked
					}
					//was clicked and not a mine->ignore
				}
				tiles.at(Y / 32 + 1).at(X / 32)->SurroundingMines(tiles);
				if (tiles.at(Y / 32 + 1).at(X / 32)->theMine()) {
					++numMines;
					//is a mine ->ignore
				}
				else {
					//is not a mine
					if (!tiles.at(Y / 32 + 1).at(X / 32)->wasClicked()) {
						tiles.at(Y / 32 + 1).at(X / 32)->Click();
						int n = tiles.at(Y / 32 + 1).at(X / 32)->GetNumMines();
						if (n > 0) {
							string s = "number_" + to_string(n);
							tiles.at(Y / 32 + 1).at(X / 32)->SetTexture(s);
						}
						else {
							tiles.at(Y / 32 + 1).at(X / 32)->SetTexture("tile_revealed");
							//set texture to tile_revealed.png

							tiles.at(Y / 32 + 1).at(X / 32)->Recursion(tiles);
							//RECURSION RECURSION
						}
						//was not clicked
					}
					//was clicked and not a mine->ignore
				}
			}
			tiles.at(Y / 32).at(X / 32 - 1)->SurroundingMines(tiles);
			if (tiles.at(Y / 32).at(X / 32 - 1)->theMine()) {
				++numMines;
				//is a mine ->ignore
			}
			else {
				//is not a mine
				if (!tiles.at(Y / 32).at(X / 32 - 1)->wasClicked()) {
					tiles.at(Y / 32).at(X / 32 - 1)->Click();
					int n = tiles.at(Y / 32).at(X / 32 - 1)->GetNumMines();
					if (n > 0) {
						string s = "number_" + to_string(n);
						tiles.at(Y / 32).at(X / 32 - 1)->SetTexture(s);
					}
					else {
						tiles.at(Y / 32).at(X / 32 - 1)->SetTexture("tile_revealed");
						//set texture to tile_revealed.png

						tiles.at(Y / 32).at(X / 32 - 1)->Recursion(tiles);
						//RECURSION RECURSION
					}
					//was not clicked
				}
				//was clicked and not a mine->ignore
			}
		}
		if (X != 768) {
			if (Y != 0) {
				tiles.at(Y / 32 - 1).at(X / 32 + 1)->SurroundingMines(tiles);
				if (tiles.at(Y / 32 - 1).at(X / 32 + 1)->theMine()) {
					++numMines;
					//is a mine ->ignore
				}
				else {
					//is not a mine
					if (!tiles.at(Y / 32 - 1).at(X / 32 + 1)->wasClicked()) {
						tiles.at(Y / 32 - 1).at(X / 32 + 1)->Click();
						int n = tiles.at(Y / 32 - 1).at(X / 32 + 1)->GetNumMines();
						if (n > 0) {
							string s = "number_" + to_string(n);
							tiles.at(Y / 32 - 1).at(X / 32 + 1)->SetTexture(s);
						}
						else {
							tiles.at(Y / 32 - 1).at(X / 32 + 1)->SetTexture("tile_revealed");
							//set texture to tile_revealed.png

							tiles.at(Y / 32 - 1).at(X / 32 + 1)->Recursion(tiles);
							//RECURSION RECURSION
						}
						//was not clicked
					}
					//was clicked and not a mine->ignore
				}
				if (X == 0) {
					tiles.at(Y / 32 - 1).at(X / 32)->SurroundingMines(tiles);
					if (tiles.at(Y / 32 - 1).at(X / 32)->theMine()) {
						++numMines;
						//is a mine ->ignore
					}
					else {
						//is not a mine
						if (!tiles.at(Y / 32 - 1).at(X / 32)->wasClicked()) {
							tiles.at(Y / 32 - 1).at(X / 32)->Click();
							int n = tiles.at(Y / 32 - 1).at(X / 32)->GetNumMines();
							if (n > 0) {
								string s = "number_" + to_string(n);
								tiles.at(Y / 32 - 1).at(X / 32)->SetTexture(s);
							}
							else {
								tiles.at(Y / 32 - 1).at(X / 32)->SetTexture("tile_revealed");
								//set texture to tile_revealed.png

								tiles.at(Y / 32 - 1).at(X / 32)->Recursion(tiles);
								//RECURSION RECURSION
							}
							//was not clicked
						}
						//was clicked and not a mine->ignore
					}
				}
			}
			if (Y != 480) {
				tiles.at(Y / 32 + 1).at(X / 32 + 1)->SurroundingMines(tiles);
				if (tiles.at(Y / 32 + 1).at(X / 32 + 1)->theMine()) {
					++numMines;
					//is a mine ->ignore
				}
				else {
					//is not a mine
					if (!tiles.at(Y / 32 + 1).at(X / 32 + 1)->wasClicked()) {
						tiles.at(Y / 32 + 1).at(X / 32 + 1)->Click();
						int n = tiles.at(Y / 32 + 1).at(X / 32 + 1)->GetNumMines();
						if (n > 0) {
							string s = "number_" + to_string(n);
							tiles.at(Y / 32 + 1).at(X / 32 + 1)->SetTexture(s);
						}
						else {
							tiles.at(Y / 32 + 1).at(X / 32 + 1)->SetTexture("tile_revealed");
							//set texture to tile_revealed.png

							tiles.at(Y / 32 + 1).at(X / 32 + 1)->Recursion(tiles);
							//RECURSION RECURSION
						}
						//was not clicked
					}
					//was clicked and not a mine->ignore
				}
				if (X == 0) {
					tiles.at(Y / 32 + 1).at(X / 32)->SurroundingMines(tiles);
					if (tiles.at(Y / 32 + 1).at(X / 32)->theMine()) {
						++numMines;
						//is a mine ->ignore
					}
					else {
						//is not a mine
						if (!tiles.at(Y / 32 + 1).at(X / 32)->wasClicked()) {
							tiles.at(Y / 32 + 1).at(X / 32)->Click();
							int n = tiles.at(Y / 32 + 1).at(X / 32)->GetNumMines();
							if (n > 0) {
								string s = "number_" + to_string(n);
								tiles.at(Y / 32 + 1).at(X / 32)->SetTexture(s);
							}
							else {
								tiles.at(Y / 32 + 1).at(X / 32)->SetTexture("tile_revealed");
								//set texture to tile_revealed.png

								tiles.at(Y / 32 + 1).at(X / 32)->Recursion(tiles);
								//RECURSION RECURSION
							}
							//was not clicked
						}
						//was clicked and not a mine->ignore
					}
				}
			}
			tiles.at(Y / 32).at(X / 32 + 1)->SurroundingMines(tiles);
			if (tiles.at(Y / 32).at(X / 32 + 1)->theMine()) {
				++numMines;
				//is a mine ->ignore
			}
			else {
				//is not a mine
				if (!tiles.at(Y / 32).at(X / 32 + 1)->wasClicked()) {
					tiles.at(Y / 32).at(X / 32 + 1)->Click();
					int n = tiles.at(Y / 32).at(X / 32 + 1)->GetNumMines();
					if (n > 0) {
						string s = "number_" + to_string(n);
						tiles.at(Y / 32).at(X / 32 + 1)->SetTexture(s);
					}
					else {
						tiles.at(Y / 32).at(X / 32 + 1)->SetTexture("tile_revealed");
						//set texture to tile_revealed.png

						tiles.at(Y / 32).at(X / 32 + 1)->Recursion(tiles);
						//RECURSION RECURSION
					}
					//was not clicked
				}
				//was clicked and not a mine->ignore
			}
		}
		//.Click()
		//if(wasClicked()){
		//	

	}
	int GetNumMines() {
		return numMines;
	}
	void Click() {
		isClicked = true;
	}
	bool wasClicked() {
		return isClicked;
	}
	void unClick() {
		isClicked = false;
	}
};