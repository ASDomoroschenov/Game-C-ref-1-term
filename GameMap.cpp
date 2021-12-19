#include "GameMap.h"

GameMap::GameMap()
{
    size.x = 0;
    size.y = 0;
    
    length = 0;
    
    map = new int* [size.x];

    for (int i = 0; i < size.x; i++) {
        map[i] = new int[size.y];
    }
}

GameMap::GameMap(SizeMap _size, int l)
{
    size = _size;

    length = l;

    map = new int* [size.x];
    for (int i = 0; i < size.x; i++) {
        map[i] = new int[size.y];
    }

    for (int i = 0; i < size.x; i++) {
        for (int j = 0; j < size.y; j++) {
            map[i][j] = 0;
        }
    }
}

GameMap::GameMap(int i, int j, int l)
{
    size.x = i;
    size.y = j;

    length = l;

    map = new int* [size.x];
    for (i = 0; i < size.x; i++) {
        map[i] = new int[size.y];
    }

    for (i = 0; i < size.x; i++) {
        for (j = 0; j < size.y; j++) {
            map[i][j] = 0;
        }
    }
}

GameMap::~GameMap()
{
    for (int i = 0; i < size.x; i++) {
        delete[] map[i];
    }

    delete[] map;
}

bool GameMap::SetPosition(SizeMap cell, int c)
{
    if (IsEmpty(cell)) {
        map[cell.x][cell.y] = c;
        return true;
    }
    else {
        return false;
    }
}

bool GameMap::IsEmpty(SizeMap cell)
{
    if (map[cell.x][cell.y] == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool GameMap::IsEmpty(int i, int j)
{
    if (map[i][j] == 0) {
        return true;
    }
    else {
        return false;
    }
}

void GameMap::SetMap(SizeMap _size, int l)
{
    size = _size;

    length = l;

    map = new int* [size.x];
    for (int i = 0; i < size.x; i++) {
        map[i] = new int[size.y];
    }

    for (int i = 0; i < size.x; i++) {
        for (int j = 0; j < size.y; j++) {
            map[i][j] = 0;
        }
    }
}

void GameMap::SetMap(int i, int j, int l)
{
    size.x = i;
    size.y = j;

    length = l;

    map = new int* [size.x];
    for (int i = 0; i < size.x; i++) {
        map[i] = new int[size.y];
    }

    for (int i = 0; i < size.x; i++) {
        for (int j = 0; j < size.y; j++) {
            map[i][j] = 0;
        }
    }
}

int GameMap::GetValue(SizeMap cell)
{
    return map[cell.x][cell.y];
}

int GameMap::GetValue(int i, int j)
{
    return map[i][j];
}

int GameMap::CheckList(std::vector<int> a)
{
    if (a.size() < length)
        return 0;

    bool winPl1 = false;
    bool winPl2 = false;

    int count1 = 0, count2 = 0;

    for (int i = 0; i < a.size(); i++) {
        for (int j = i; j < i + length; j++) {
            if (j < a.size()) {
                if (a[j] == 1) {
                    count1++;
                }
            }
            else
                break;
        }

        if (count1 >= length) {
            winPl1 = true;
            break;
        }

        count1 = 0;
    }

    for (int i = 0; i < a.size(); i++) {
        for (int j = i; j < i + length; j++) {
            if (j < a.size()) {
                if (a[j] == 2) {
                    count2++;
                }
            }
            else
                break;
        }

        if (count2 >= length) {
            winPl2 = true;
            break;
        }

        count2 = 0;
    }

    if (winPl1 && winPl2) {
        return 3;
    }
    else if (!winPl1 && winPl2) {
        return 2;
    }
    else if (winPl1 && !winPl2) {
        return 1;
    }
    else
        return 0;
}

int GameMap::CheckingWin()
{
    int stateWin = 0;
    std::vector<int> check;

    for (int i = 0; i < size.x; i++) {
        for (int j = 0; j < size.y; j++) {
            check.push_back(map[i][j]);
        }

        stateWin = CheckList(check);
        check.clear();

        if (stateWin == 3) {
            return 3;
        }
        else if (stateWin == 2) {
            return 2;
        }
        else if (stateWin == 1) {
            return 1;
        }
    }

    for (int i = 0; i < size.x; i++) {
        for (int j = 0; j < size.y; j++) {
            check.push_back(map[j][i]);
        }

        stateWin = CheckList(check);
        check.clear();

        if (stateWin == 3) {
            return 3;
        }
        else if (stateWin == 2) {
            return 2;
        }
        else if (stateWin == 1) {
            return 1;
        }
    }

    for (int i = 0; i < size.x; ++i)
    {
        for (int j = 0; i + j < size.y; ++j) {
            check.push_back(map[i + j][j]);
        }

        stateWin = CheckList(check);
        check.clear();

        if (stateWin == 3) {
            return 3;
        }
        else if (stateWin == 2) {
            return 2;
        }
        else if (stateWin == 1) {
            return 1;
        }
    }

    for (int i = 1; i < size.x; ++i)
    {
        for (int j = 0; i + j < size.y; ++j) {
            check.push_back(map[i + j][j]);
        }

        stateWin = CheckList(check);
        check.clear();

        if (stateWin == 3) {
            return 3;
        }
        else if (stateWin == 2) {
            return 2;
        }
        else if (stateWin == 1) {
            return 1;
        }
    }

    for (int j = size.y; j > 0; --j) {
        for (int i = 0; i < size.x; ++i)
        {
            if (size.x - j - i >= 0) {
                check.push_back(map[i][size.x - j - i]);
            }
        }

        stateWin = CheckList(check);
        check.clear();

        if (stateWin == 3) {
            return 3;
        }
        else if (stateWin == 2) {
            return 2;
        }
        else if (stateWin == 1) {
            return 1;
        }
    }

    for (int j = 0; j < size.y; ++j) {
        for (int i = 0; i < size.x; ++i)
        {
            if (size.x + j - i < size.x) {
                check.push_back(map[i][size.x + j - i]);
            }
        }

        stateWin = CheckList(check);
        check.clear();

        if (stateWin == 3) {
            return 3;
        }
        else if (stateWin == 2) {
            return 2;
        }
        else if (stateWin == 1) {
            return 1;
        }
    }

    if (CanMove())
        return 0;
    else
        return 3;
}

bool GameMap::CanMove()
{
    for (int i = 0; i < size.x; i++) {
        for (int j = 0; j < size.y; j++) {
            if (map[i][j] == 0) {
                return true;
            }
        }
    }

    return false;
}

SizeMap GameMap::GetCenter()
{
    SizeMap center;
    int x;

    if (size.x % 2 != 0) {
        x = (size.x - 1) / 2;
    }
    else {
        x = (size.x / 2) - 1;
    }

    center.x = x;
    center.y = x;

    return center;
}
