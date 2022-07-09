#pragma once

const WORD GapTime = 200;

class keybord {
private:
	SYSTEMTIME last_time;
	SYSTEMTIME systime;
public:
	keybord() {
		GetSystemTime(&systime);
		GetSystemTime(&last_time);
	}

	bool CanPress() {
		GetSystemTime(&systime);
		if (systime.wMilliseconds - last_time.wMilliseconds >= GapTime || systime.wSecond != last_time.wSecond) {
			return true;
		}
		else return false;
	}

	bool IsKeyPressed(int nVirtKey) {
		bool st;
		st = GetKeyState(nVirtKey) & 0xFFFE;
		return st;
	}
	void SetNewKeyTime() {
		GetSystemTime(&last_time);
	}
};