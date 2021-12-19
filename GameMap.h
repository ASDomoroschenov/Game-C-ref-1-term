#pragma once

#include <vector>
#include <algorithm>

struct SizeMap {
	int x, 
		y;
};

class GameMap
{
private:
	int **map = NULL;
	SizeMap size;
	int length = 0;

public:
	GameMap();
	GameMap(SizeMap, int);
	GameMap(int, int, int);
	~GameMap();

	bool SetPosition(SizeMap, int);
	bool IsEmpty(SizeMap);
	bool IsEmpty(int, int);
	void SetMap(SizeMap, int);
	void SetMap(int, int, int);
	int GetValue(SizeMap);
	int GetValue(int, int);
	int GetLength() { return length; };
	SizeMap GetSize() { return size; };
	int CheckList(std::vector<int> a);
	int CheckingWin();
	bool CanMove();
	SizeMap GetCenter();
};

