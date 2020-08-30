#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"
#include "SmileyFace.h"
#include "MineDebug.h"
#include "Test1.h"
#include "Digits.h"
#include <vector>
#include <random>
#include <ctime>
#include <map>
#include <fstream>
using namespace sf;
using namespace std;


mt19937 mt((unsigned int) time(0));
int Random(int min, int max) {
	uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}
// test
/*bool Find(vector<vector<Tile *>> v, Vector2i position) {
	bool f = false;
	return v.at(position.y / 32).at(position.x / 32)->theMine();
}*/
bool Win(vector<vector<Tile *>> &v) {
	bool w = true;
	for (unsigned int i = 0; i < v.size(); i++) {
		for (unsigned int i2 = 0; i2 < v.at(0).size(); i2++) {
			if (v.at(i).at(i2)->theMine()) {
				continue;
			}
			else {
				if (!v.at(i).at(i2)->wasClicked() || v.at(i).at(i2)->theFlag()) {
					w = false;
				}
			}
			
		}
	}
	if (w) {
		for (unsigned int i = 0; i < v.size(); i++) {
			for (unsigned int i2 = 0; i2 < v.at(0).size(); i2++) {
				if (v.at(i).at(i2)->theMine()) {
					v.at(i).at(i2)->SetTexture("flag");
				}
				v.at(i).at(i2)->Click();
			}
		}
		//set all mines to flags
		return true;
	}
	else {
		return false;
	}
}
void Lose(vector<vector<Tile *>> &v) {
	for (unsigned int i = 0; i < v.size(); i++) {
		for (unsigned int i2 = 0; i2 < v.at(0).size(); i2++) {
			if (v.at(i).at(i2)->theMine()) {
				v.at(i).at(i2)->SetTexture("mine");
			}
			v.at(i).at(i2)->Click();
		}
	}
}
bool FindInt(vector<Vector2i> &v, Vector2i a) {
	bool result = false;
	for (size_t i = 0; i < v.size(); i++) {
		if (v.at(i).y == a.y && v.at(i).x == a.x) {
			result = true;
			i = v.size();
		}
	}
	return result;
}

int main()
{
	

	RenderWindow window(VideoMode(800, 600), "Minesweeper", Style::Titlebar | Style::Close);
	//window.setSize(800, 600);

	SmileyFace * face = new SmileyFace();
	
	MineDebug * debugger = new MineDebug();

	int firstDigit = 0;
	int secondDigit = 5;
	int thirdDigit = 0;


	int numFlag = 0;

	int mineCount = 50;
	int mineCount1 = 0;
	int mineCount2 = 0;

	Test1 * test1 = new Test1();


	vector<Vector2i> t1;

	ifstream inFile("boards/testboard.brd");
	for (int i = 0; i < 16; i++) {
		for (int i2 = 0; i2 < 25; i2++) {
			string s;
			s = inFile.get();
			if (s == "\n") {
				s = inFile.get();
			}
			if (s == "1") {
				++mineCount1;
				Vector2i f(i2, i);
				t1.push_back(f);
			}
		}
	}

	Test2 * test2 = new Test2();

	vector<Vector2i> t2;

	ifstream inFile2("boards/testboard2.brd");
	for (int i = 0; i < 16; i++) {
		for (int i2 = 0; i2 < 25; i2++) {
			string s2;
			s2 = inFile2.get();
			if (s2 == "\n") {
				s2 = inFile2.get();
			}
			if (s2 == "1") {
				++mineCount2;
				Vector2i f2(i2, i);
				t2.push_back(f2);
			}
			//cout << s2;
		}
		//cout << endl;
	}



	Digits * digits = new Digits();

	

	const unsigned int width = 25;
	const unsigned int height = 16;

	//MININ

	bool win = false;
	bool lose = false;


	//mines.clear(); at some point

	vector<vector<Tile *>> tiles;
	
	
	
	int mode = 0;    //3 for debug, everything else ->not debug
	int modeScreen = 0; //0, 1, 2



	int x = Random(0, (int)(800 / 32) - 1);
	int y = Random(0, (int)(512 / 32) - 1);
	
	Vector2i f(x, y);

	vector<Vector2i> xy;
	for (size_t i = 0; i < (unsigned) mineCount; i++) {
		while (FindInt(xy, f)) {
			x = Random(0, (int)(800 / 32) - 1);
			y = Random(0, (int)(512 / 32) - 1);
			f = Vector2i(x, y);
		}
		xy.push_back(f);
		x = Random(0, (int)(800 / 32) - 1);
		y = Random(0, (int)(512 / 32) - 1);
		f = Vector2i(x, y);
	}



	vector<Tile *> mineTiles;
	for (size_t i = 0; i < (unsigned) mineCount; i++) {
		Tile * t = new Tile();
		t->SetPosition(xy.at(i));
		mineTiles.push_back(t);
	}//hidden texture
	//ONLY FOR DEBUGGING				THE OTHER MINES ARE IN ___tiles___


	vector<vector<Tile *>> grayTiles;
	for (unsigned int i = 0; i < height; i++) {
		vector<Tile *> v;
		for (unsigned int i2 = 0; i2 < width; i2++) {
			Vector2i position(32 * i2, 32 * i);
			Tile * tile = new Tile();
			tile->SetPosition(position);
			Vector2i f(i2, i);
			if (!FindInt(xy, f)) {
				tile->SetTexture("tile_revealed");
			}
			v.push_back(tile);
		}

		grayTiles.push_back(v);
	}



	for (unsigned int i = 0; i < height; i++) {
		vector<Tile *> v;
		for (unsigned int i2 = 0; i2 < width; i2++) {
			Vector2i position(32 * i2, 32 * i);
			Tile * tile = new Tile();
			tile->SetPosition(position);
			Vector2i f(i2, i);
			if (FindInt(xy, f)) {
				tile->isAMine();
				if (mode == 3) {
					tile->SetTexture("mine");
				}
			}
			v.push_back(tile);
		}
		
		tiles.push_back(v);
	}
	//SetMines(tiles, /*mineCount*/40, width, height, mode);

	//MODES
	
	//0, 1, 2, 3 --- 0 is default
	//affects digit count
//		^
	//  | MINE COUNT
	

	vector<vector<Tile *>>::iterator iter = tiles.begin();

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				window.close();
				break;
			case Event::MouseButtonPressed:
				if (event.key.code == Mouse::Left) {
					Vector2i local = Mouse::getPosition(window);
					if (local.x > 0 && local.x < 800 && local.y > 512) {
						//SmileyFace
						//reset tiles
						//switch modeScreen to 0
						//call unClicked() for test 1 and test2 
						if (local.y > 512 && local.y < int(window.getSize().y) && local.x > int(window.getSize().x / 2 - 32) && local.x < int(window.getSize().x / 2 + 32)) {
							face->SetTexture("face_happy");

							lose = false;
							win = false;

							tiles.clear();
							//read in tile 1 and tile 2 again
							modeScreen = 0;
							mineCount = 50;
							numFlag = 0;
							
							firstDigit = mineCount / 100;
							secondDigit = (mineCount / 10) % 10;
							thirdDigit = mineCount % 10;

							mineCount1 = 0;
							mineCount2 = 0;
							test1->unClick();
							test2->unClick();

							
							t1.clear();
							t2.clear();
							xy.clear();
							mineTiles.clear();
							grayTiles.clear();
							tiles.clear();
							
							inFile = ifstream("boards/testboard.brd");
							for (int i = 0; i < 16; i++) {
								for (int i2 = 0; i2 < 25; i2++) {
									string s;
									s = inFile.get();
									if (s == "\n") {
										s = inFile.get();
									}
									if (s == "1") {
										++mineCount1;
										Vector2i f(i2, i);
										t1.push_back(f);
									}
								}
							}
							inFile2 = ifstream("boards/testboard2.brd");
							for (int i = 0; i < 16; i++) {
								for (int i2 = 0; i2 < 25; i2++) {
									string s2;
									s2 = inFile2.get();
									if (s2 == "\n") {
										s2 = inFile2.get();
									}
									if (s2 == "1") {
										++mineCount2;
										Vector2i f2(i2, i);
										t2.push_back(f2);
									}
									//cout << s2;
								}
								//cout << endl;
							}
							x = Random(0, (int)(800 / 32) - 1);
							y = Random(0, (int)(512 / 32) - 1);
							f = Vector2i(x, y);
							for (size_t i = 0; i < (unsigned) mineCount; i++) {
								while (FindInt(xy, f)) {
									x = Random(0, (int)(800 / 32) - 1);
									y = Random(0, (int)(512 / 32) - 1);
									f = Vector2i(x, y);
								}
								xy.push_back(f);
								x = Random(0, (int)(800 / 32) - 1);
								y = Random(0, (int)(512 / 32) - 1);
								f = Vector2i(x, y);
							}
							for (size_t i = 0; i < (unsigned) mineCount; i++) {
								Tile * t = new Tile();
								t->SetPosition(xy.at(i));
								mineTiles.push_back(t);
							}//hidden texture
							//ONLY FOR DEBUGGING				THE OTHER MINES ARE IN ___tiles___

							for (unsigned int i = 0; i < height; i++) {
								vector<Tile *> v;
								for (unsigned int i2 = 0; i2 < width; i2++) {
									Vector2i position(32 * i2, 32 * i);
									Tile * tile = new Tile();
									tile->SetPosition(position);
									Vector2i f(i2, i);
									if (!FindInt(xy, f)) {
										tile->SetTexture("tile_revealed");
									}
									v.push_back(tile);
								}

								grayTiles.push_back(v);
							}

							for (unsigned int i = 0; i < height; i++) {
								vector<Tile *> v;
								for (unsigned int i2 = 0; i2 < width; i2++) {
									Vector2i position(32 * i2, 32 * i);
									Tile * tile = new Tile();
									tile->SetPosition(position);
									Vector2i f(i2, i);
									if (FindInt(xy, f)) {
										tile->isAMine();
										if (mode == 3) {
											tile->SetTexture("mine");
										}
									}
									v.push_back(tile);
								}

								tiles.push_back(v);
							}
						}

						//test1

						if (local.x > 560 && local.x < 624 && local.y / 32 >= 16 && local.y / 32 < 18) {
							if (!test1->wasClicked()) {
								if (lose == true) {
									lose = false;
									face->SetTexture("face_happy");
								}
								if (win == true) {
									win = false;
									face->SetTexture("face_happy");
								}
								//if()

								numFlag = 0;

								mineCount1 = 0;
								t1.clear();
								inFile = ifstream("boards/testboard.brd");
								for (int i = 0; i < 16; i++) {
									for (int i2 = 0; i2 < 25; i2++) {
										string s;
										s = inFile.get();
										if (s == "\n") {
											s = inFile.get();
										}
										if (s == "1") {
											++mineCount1;
											Vector2i f(i2, i);
											t1.push_back(f);
										}
									}
								}

								if (mode != 3) {
									firstDigit = mineCount1 / 100;
									secondDigit = (mineCount1 / 10) % 10;
									thirdDigit = mineCount1 % 10;
								}

								mineCount = mineCount1;

								if (mode == 3) {
									firstDigit = 0;
									secondDigit = 0;
									thirdDigit = 0;
								}
								/*else {
									firstDigit = (mineCount - numFlag) / 100;
									secondDigit = ((mineCount - numFlag) / 10) % 10;
									thirdDigit = (mineCount - numFlag) / 10;
								}*/
								if (modeScreen == 2) {
									test2->unClick();
								}
								modeScreen = 1;
								test1->Click();

								//t2.clear();

								mineTiles.clear();
								grayTiles.clear();
								tiles.clear();
								for (size_t i = 0; i < (unsigned) mineCount; i++) {
									Tile * t = new Tile();
									t->SetPosition(t1.at(i));
									mineTiles.push_back(t);
								}
								for (unsigned int i = 0; i < height; i++) {
									vector<Tile *> v;
									for (unsigned int i2 = 0; i2 < width; i2++) {
										Vector2i position(32 * i2, 32 * i);
										Tile * tile = new Tile();
										tile->SetPosition(position);
										Vector2i f(i2, i);
										if (!FindInt(t1, f)) {
											tile->SetTexture("tile_revealed");
										}
										v.push_back(tile);
									}

									grayTiles.push_back(v);
								}
								for (unsigned int i = 0; i < height; i++) {
									vector<Tile *> v;
									for (unsigned int i2 = 0; i2 < width; i2++) {
										Vector2i position(32 * i2, 32 * i);
										Tile * tile = new Tile();
										tile->SetPosition(position);
										Vector2i f(i2, i);
										if (FindInt(t1, f)) {
											tile->isAMine();
											if (mode == 3) {
												tile->SetTexture("mine");
											}
										}
										v.push_back(tile);
									}

									tiles.push_back(v);
								}
							}
							
						}

						//test2
						if (local.x > 624 && local.x < 688 && local.y / 32 >= 16 && local.y / 32 < 18) {
							if (!test2->wasClicked()) {
								if (lose == true) {
									lose = false;
									face->SetTexture("face_happy");
								}
								if (win == true) {
									win = false;
									face->SetTexture("face_happy");
								}
								numFlag = 0;

								mineCount2 = 0;
								t2.clear();
								inFile2 = ifstream("boards/testboard2.brd");
								for (int i = 0; i < 16; i++) {
									for (int i2 = 0; i2 < 25; i2++) {
										string s2;
										s2 = inFile2.get();
										if (s2 == "\n") {
											s2 = inFile2.get();
										}
										if (s2 == "1") {
											++mineCount2;
											Vector2i f(i2, i);
											t2.push_back(f);
										}
									}
								}

								if (mode != 3) {
									firstDigit = mineCount2 / 100;
									secondDigit = (mineCount2 / 10) % 10;
									thirdDigit = mineCount2 % 10;
								}

								mineCount = mineCount2;
								if (mode == 3) {
									firstDigit = 0;
									secondDigit = 0;
									thirdDigit = 0;
								}
								/*else {
									firstDigit = (mineCount - numFlag) / 100;
									secondDigit = ((mineCount - numFlag) / 10) % 10;
									thirdDigit = (mineCount - numFlag) / 10;
								}*/

								if (modeScreen == 1) {
									test1->unClick();
								}
								modeScreen = 2;
								test2->Click();

								//t1.clear();

								mineTiles.clear();
								grayTiles.clear();
								tiles.clear();
								for (size_t i = 0; i < (unsigned) mineCount; i++) {
									Tile * t = new Tile();
									t->SetPosition(t2.at(i));
									mineTiles.push_back(t);
								}
								for (unsigned int i = 0; i < height; i++) {
									vector<Tile *> v;
									for (unsigned int i2 = 0; i2 < width; i2++) {
										Vector2i position(32 * i2, 32 * i);
										Tile * tile = new Tile();
										tile->SetPosition(position);
										Vector2i f(i2, i);
										if (!FindInt(t2, f)) {
											tile->SetTexture("tile_revealed");
										}
										v.push_back(tile);
									}

									grayTiles.push_back(v);
								}
								for (unsigned int i = 0; i < height; i++) {
									vector<Tile *> v;
									for (unsigned int i2 = 0; i2 < width; i2++) {
										Vector2i position(32 * i2, 32 * i);
										Tile * tile = new Tile();
										tile->SetPosition(position);
										Vector2i f(i2, i);
										if (FindInt(t2, f)) {
											tile->isAMine();
											if (mode == 3) {
												tile->SetTexture("mine");
											}
										}
										v.push_back(tile);
									}

									tiles.push_back(v);
								}
							}

						}



						//MineDebug
						//switch mode to 3
						//cout << local.x << "\t" << local.y << endl;
						//cout << debugger->GetPosition().x << "\t     " << debugger->GetPosition().y << endl;
						if (local.x > 496 && local.x < 560 && local.y / 32 >= 16 && local.y / 32 < 18) {
							if (mode == 3) {
								mode = 0;
								for (unsigned int i = 0; i < height; i++) {
									for (unsigned int i2 = 0; i2 < width; i2++) {
										Vector2i f(i2, i);
										if (modeScreen == 1) {
											//cout << "YOLO" << endl;
											if (FindInt(t1, f)) {
												tiles.at(i).at(i2)->isAMine();
												tiles.at(i).at(i2)->SetTexture("tile_hidden");
												if (tiles.at(i).at(i2)->theFlag()) {
													tiles.at(i).at(i2)->SetTexture("flag");
												}
											}
										}
										else if (modeScreen == 2) {
											//cout << "HI THERE" << endl;
											if (FindInt(t2, f)) {
												tiles.at(i).at(i2)->isAMine();
												tiles.at(i).at(i2)->SetTexture("tile_hidden");
												if (tiles.at(i).at(i2)->theFlag()) {
													tiles.at(i).at(i2)->SetTexture("flag");
												}
											}
										}
										else {
											if (FindInt(xy, f)) {
												tiles.at(i).at(i2)->isAMine();
												tiles.at(i).at(i2)->SetTexture("tile_hidden");
												if (tiles.at(i).at(i2)->theFlag()) {
													tiles.at(i).at(i2)->SetTexture("flag");
												}
											}
										}
									}
								}
								firstDigit = (mineCount - numFlag) / 100;
								secondDigit = ((mineCount - numFlag) / 10) % 10;
								thirdDigit = (mineCount - numFlag) % 10;
							}
							else {
								mode = 3;
								for (unsigned int i = 0; i < height; i++) {
									for (unsigned int i2 = 0; i2 < width; i2++) {
										Vector2i f(i2, i);
										if (modeScreen == 1) {
											if (FindInt(t1, f)) {
												tiles.at(i).at(i2)->isAMine();
												tiles.at(i).at(i2)->SetTexture("mine");
											}
										}
										else if (modeScreen == 2) {
											//cout << "HI" << endl;
											if (FindInt(t2, f)) {
												tiles.at(i).at(i2)->isAMine();
												tiles.at(i).at(i2)->SetTexture("mine");
											}
										}
										else {
											if (FindInt(xy, f)) {
												tiles.at(i).at(i2)->isAMine();
												tiles.at(i).at(i2)->SetTexture("mine");
											}
										}
									}
								}
								firstDigit = 0;
								secondDigit = 0;
								thirdDigit = 0;
							}
							//cout << mode << endl;
						}
						//reset Digits (FLAGS FLAGS FLAGS)
					}
					if (local.y > 0 && local.y < 512) {
						if (local.x > 0 && local.x < 800) {
							int x = local.x / 32;
							int y = local.y / 32;
																		//ADD FUNCTIONALITY FOR REVEALING SURROUNDING TILES (RECURSION)
							bool it = tiles.at(y).at(x)->theMine();
							//cout << "YES" << it << endl;
							if (it && !tiles.at(y).at(x)->wasClicked()) {
								//is a mine
								tiles.at(y).at(x)->Click();
								tiles.at(y).at(x)->isAMine();
								if (modeScreen == 0) {
									tiles.at(y).at(x)->SetTexture("mine");
								}
								//reveal all mines
								//end game
								//set mineCount = 0 (change digit sprite)
								if (mode == 1) {
									mineCount1 = 0;
								}
								if (mode == 2) {
									mineCount2 = 0;
								}
								mineCount = 0;

								firstDigit = 0;
								secondDigit = 0;
								thirdDigit = 0;
								//Change to Cool Sunglasses

								face->SetTexture("face_lose");
								lose = true;
								Lose(tiles);
								//do this for all tiles and mines --> ->Click(); to prevent any further clicking...
							}
							else {
								if (!tiles.at(y).at(x)->wasClicked()) {
									tiles.at(y).at(x)->Click();
									tiles.at(y).at(x)->SurroundingMines(tiles);
									//cout << x << "\t" << y << endl;
									int n = tiles.at(y).at(x)->GetNumMines();
									if (n > 0) {
										string s = "number_" + to_string(n);
										tiles.at(y).at(x)->SetTexture(s);
									}
									else {
										tiles.at(y).at(x)->SetTexture("tile_revealed");
										//set texture to tile_revealed.png

										tiles.at(y).at(x)->Recursion(tiles);
										//RECURSION RECURSION
									}
									if (Win(tiles)) {
										win = true;
										face->SetTexture("face_win");
									}
								}
								//is not a mine
							}
						}
					}
				}
				if (event.key.code == Mouse::Right) {
					Vector2i local = Mouse::getPosition(window);
					if (local.x > 0 && local.x < 800 && local.y > 0 && local.y < 512) {
						int x = local.x / 32;
						int y = local.y / 32;
						//ADD FUNCTIONALITY FOR REVEALING SURROUNDING TILES (RECURSION)
						//bool it = tiles.at(y).at(x)->theFlag();
						//cout << "YES" << it << endl;
						if (!tiles.at(y).at(x)->wasClicked()) {
							//is a flag
							if (mode != 3) {
								++numFlag;
								if ((mineCount - numFlag) < 0) {
									--numFlag;
								}
							}
							else {
								if (!tiles.at(y).at(x)->theMine()) {
									++numFlag;
									if ((mineCount - numFlag) < 0) {
										--numFlag;
									}
								}
							}

							tiles.at(y).at(x)->Click();
							tiles.at(y).at(x)->isAFlag();
							
							tiles.at(y).at(x)->SurroundingMines(tiles);
							/*if (tiles.at(y).at(x)->theMine()) {
								if (modeScreen == 1) {
									--mineCount1;
									if (mineCount1 < 0) {
										mineCount1 = 0;
									}
								}
								if (modeScreen == 2) {
									--mineCount2;
									if (mineCount2 < 0) {
										mineCount2 = 0;
									}
								}
								--mineCount;
								if (mineCount < 0) {
									mineCount = 0;
								}
							}*/

							if (mode != 3) {
								firstDigit = (mineCount - numFlag) / 100;
								secondDigit = ((mineCount - numFlag) / 10) % 10;
								thirdDigit = (mineCount - numFlag) % 10;
							}
							
							tiles.at(y).at(x)->SetTexture("flag");

							//reveal all mines
							//end game
							//set mineCount = 0 (change digit sprite)
							//Change to Cool Sunglasses
							//do this for all tiles and mines --> ->Click(); to prevent any further clicking...
						}
						else {
							if (tiles.at(y).at(x)->theFlag()) {
								tiles.at(y).at(x)->unClick();
								tiles.at(y).at(x)->isAFlag();

								if (mode != 3) {
									--numFlag;
									if (numFlag < 0) {
										numFlag = 0;
									}
								}
								else {
									if (!tiles.at(y).at(x)->theMine()) {
										--numFlag;
										if (numFlag < 0) {
											numFlag = 0;
										}
									}
								}
								//limit should be 0

								tiles.at(y).at(x)->SurroundingMines(tiles);
								/*if (tiles.at(y).at(x)->theMine()) {
									if (modeScreen == 1) {
										++mineCount1;
									}
									if (modeScreen == 2) {
										++mineCount2;
									}
									++mineCount;
								}*/


								if (mode != 3) {
									firstDigit = (mineCount - numFlag) / 100;
									secondDigit = ((mineCount - numFlag) / 10) % 10;
									thirdDigit = (mineCount - numFlag) % 10;
								}

								//if (modeScreen == 0) {
									tiles.at(y).at(x)->SetTexture("tile_hidden");
								//}
							}
						}
					}
				}
			}
		}
		//Update()
		//Draw()
		window.clear(Color::White);//Color(189,189,189));
		
		//cout << mode << endl;
		//DEBUG
		if (mode == 3) {
			//DEBUG MODE
			//if modeScreen == 0
			//if modeScreen == 1
			//if modeScreen == 2

			//unpressed part behind mine
			for (size_t i = 0; i < (unsigned) mineCount; i++) {
				if (modeScreen == 1) {
					mineTiles.at(i)->SetPosition(Vector2i(t1.at(i).x * 32, t1.at(i).y * 32));
				}
				else if (modeScreen == 2) {
					mineTiles.at(i)->SetPosition(Vector2i(t2.at(i).x * 32, t2.at(i).y * 32));
				}
				else {
					mineTiles.at(i)->SetPosition(Vector2i(xy.at(i).x * 32, xy.at(i).y * 32));
				}
				window.draw(mineTiles.at(i)->GetSprite());
			}

			//gray behind numbers
			for (unsigned int i = 0; i < height; i++) {
				for (unsigned int i2 = 0; i2 < width; i2++) {
					grayTiles.at(i).at(i2)->SetPosition(grayTiles.at(i).at(i2)->GetPosition());
					window.draw(grayTiles.at(i).at(i2)->GetSprite());
				}
			}

			//mine or digit value
			for (unsigned int i = 0; i < height; i++) {
				for (unsigned int i2 = 0; i2 < width; i2++) {
					tiles.at(i).at(i2)->SetPosition(tiles.at(i).at(i2)->GetPosition());
					window.draw(tiles.at(i).at(i2)->GetSprite());
				}
			}
			//cout << "HELLO THERE" << endl;
		}
		else {
			//gray behind numbers
			for (unsigned int i = 0; i < height; i++) {
				for (unsigned int i2 = 0; i2 < width; i2++) {
					grayTiles.at(i).at(i2)->SetPosition(grayTiles.at(i).at(i2)->GetPosition());
					window.draw(grayTiles.at(i).at(i2)->GetSprite());
				}
			}

			for (unsigned int i = 0; i < height; i++) {
				for (unsigned int i2 = 0; i2 < width; i2++) {
					tiles.at(i).at(i2)->SetPosition(tiles.at(i).at(i2)->GetPosition());
					window.draw(tiles.at(i).at(i2)->GetSprite());
				}
			}
		}

		Vector2i position1(window.getSize().x / 2 - 32, 512);
		face->SetPosition(position1);
		window.draw(face->GetSprite());

		Vector2i position2(window.getSize().x / 2 + 96, 512);
		debugger->SetPosition(position2);
		window.draw(debugger->GetSprite());

		Vector2i position3(window.getSize().x / 2 + 160, 512);
		test1->SetPosition(position3);
		window.draw(test1->GetSprite());

		Vector2i position4(window.getSize().x / 2 + 224, 512);
		test2->SetPosition(position4);
		window.draw(test2->GetSprite());

		Vector2i position5(0, 512);
		digits->SetPosition(position5);
		
		
		//MODES


		//mineCount = 50;
		digits->SetTexture1(firstDigit);
		digits->SetTexture2(secondDigit);
		digits->SetTexture3(thirdDigit);
		for (size_t i = 1; i <= 3; i++) {
			window.draw(digits->GetSprite(i));
		}


		iter = tiles.begin();//use or don't use?????idk
		window.display();
	}
	return 0;
}