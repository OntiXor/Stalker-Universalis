#pragma once

class Group {
private:
	bool IsPlayable;
	string name;
	Image emblem, flag;
public:
	Group(string name, Image emblem) {
		IsPlayable = false;
		this->emblem = emblem;
		this->name = name;
	}
	Group(string name, Image emblem, Image flag) {
		IsPlayable = true;
		this->emblem = emblem;
		this->name = name;
		this->flag = flag;
	}
	Image GetImg() {
		return emblem;
	}
	Image GetFlag() {
		return flag;
	}
	string GetName() {
		return name;
	}
};

Group Groups[] = {
		Group(
			stalkers,
			Image(stalk)
		),
		Group(
			bandits,
			Image(bandt),
			Image(bandtf)
		),
		Group(
			svoboda,
			Image(svobd),
			Image(svobdf)
		),
		Group(
			dolg,
			Image(dolgp),
			Image(dolgpf)
		),
		Group(
			monolit,
			Image(monol),
			Image(monolf)
		),
		Group(
			army,
			Image(armyp),
			Image(armypf)
		),
		Group(
			mercenar,
			Image(mercs),
			Image(mercsf)
		),
		Group(
			renegats,
			Image(reneg)
		),
		Group(
			science,
			Image(scin),
			Image(scinf)
		)
};

class Point {
	string name;
	int x, y;
	int owner;
public:
	Point(int x, int y, int owner) {
		this->x = x;
		this->y = y;
		this->owner = owner;
	}
	Point(int x, int y, int owner, string name) {
		this->name = name;
		this->x = x;
		this->y = y;
		this->owner = owner;
	}
	int GetOwnerId() {
		return owner;
	}
	void SetOwner(int owner) {
		this->owner = owner;
	}
	int GetX() {
		return x;
	}
	int GetY() {
		return y;
	}
	void Shtorka(POINT mouse, HDC screen) {
		string* shtor = new string;
		*shtor = name + " (" + Groups[owner].GetName() + ")\0";

		if (
			mouse.x >= x - camX &&
			mouse.y >= y - camY &&
			mouse.x <= x - camX + 50 &&
			mouse.y <= y - camY + 50
			) {
			
			TextOutA(screen, mouse.x + 20, mouse.y, shtor->c_str(), shtor->size());
			delete shtor;
			if (LeftButton) {
				
			}
		}
	}
	bool IsClicked() {
		return Groups[owner].GetImg().IsClicked(x, y);
	}
};

class Person {
	char* name;
	int money, xp;
public:
	Person() {
		money = 0;
		xp = 0;
		name = 0;
	}
	Person(int money, int xp) {
		this->money = money;
		this->xp = xp;
		name = 0;
	};
};

class Sqwad {
	int x, y;
	int group;
	int stk_amount;
	Person* persons;
public:
	Sqwad(int n, int xp, int money, int x, int y) {
		this->x = x;
		this->y = y;
		persons = new Person[n];
		stk_amount = n;
		for (int i = 0; i < stk_amount; i++) {
			persons[i] = Person(money/n, xp/n);
		}
	}
	int GetGroupID() {
		return group;
	}
	int GetX() {
		return x;
	}
	int GetY() {
		return y;
	}
	void Shtorka(POINT mouse, HDC screen) {
		if (
			mouse.x >= x - camX &&
			mouse.y >= y - camY &&
			mouse.x <= x - camX + 15 &&
			mouse.y <= y - camY + 15
			) {

			TextOutA(screen, mouse.x + 20, mouse.y, (char*)&"Группа сталкеров", 18);
			if (LeftButton) {

			}
		}
	}
};