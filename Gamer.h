#pragma once

enum GamerStatus {
	Computer = 0,
	Player,
	Player1,
	Player2
};

class Gamer
{
private:
	GamerStatus status;
	int mark;

public:
	Gamer() {}
	~Gamer() {}

	void SetField(GamerStatus mode, int m);
	int GetMark() { return mark; };
	GamerStatus GetStatus() { return status; }
};

