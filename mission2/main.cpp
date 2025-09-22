#include "AttendanceManagement.cpp"

int main() {
	playerMap playerMapInfo;
	ifstream fin{ "attendance_weekday_500.txt" };
	for (int dataIdx = 0; dataIdx < MAX_DATA_NUM; dataIdx++) {
		string playerName, attendedWeek;
		fin >> playerName >> attendedWeek;
		playerMapInfo.playerAttendance(playerName, attendedWeek);
	}
	playerMapInfo.getPlayerInfo();
}