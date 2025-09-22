#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#define WEDNESDAY_BONUS_STANDARD (10)
#define WEEKEND_BONUS_STANDARD (10)

#define WEDNESDAY_BONUS_SCORE (10)
#define WEEKEND_BONUS_SCORE (10)


#define MAX_DATA_NUM	(500)
/* 인덱스 1번부터 사용 */
#define MAX_PLAYER_NUM	(100)
typedef enum grade
{
	GOLD = 2,
	SILVER = 1,
	NORMAL = 0
} e_grade;

typedef enum grade_standard
{
	GOLD_SCORE_STANDARD = 50,
	SILVER_SCORE_STANDARD = 30,
	NORMAL_SCORE_STANDARD = 0
} e_grade_standard;

typedef enum attendation_score
{
	DAY_OF_THE_WEEK_EXCEPT_WEEKEND_AND_WENDESDAY_ATTEND_SCORE = 1,
	WEEKEND_ATTEND_SCORE = 2,
	WENDESDAY_ATTEND_SCORE = 3
} e_attendation_score;

typedef enum week
{
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY,
	WEEK_MAX = 7
} e_week;

map<string, int> playerIDMap;
int idCnt = 0;

int playerWeekAttendData[MAX_PLAYER_NUM][WEEK_MAX];
int playerPoints[MAX_PLAYER_NUM];
int playerGrade[MAX_PLAYER_NUM];
string playerNames[MAX_PLAYER_NUM];

/* 요일 문자열에서 요일 인덱스 획득 */
int getWeekIndex(string week)
{
	if (week == "monday")
	{
		return MONDAY;
	}
	else if (week == "tuesday")
	{
		return TUESDAY;
	}
	else if (week == "wednesday")
	{
		return WEDNESDAY;
	}
	else if (week == "thursday")
	{
		return THURSDAY;
	}
	else if (week == "friday")
	{
		return FRIDAY;
	}
	else if (week == "saturday")
	{
		return SATURDAY;
	}
	else if (week == "sunday")
	{
		return SUNDAY;
	}
}

int getPlayerGrade(int playerID)
{
	int playerGrade;
	if (playerPoints[playerID] >= GOLD_SCORE_STANDARD) {
		playerGrade = GOLD;
	}
	else if (playerPoints[playerID] >= SILVER_SCORE_STANDARD) {
		playerGrade = SILVER;
	}
	else {
		playerGrade = NORMAL;
	}
	return playerGrade;
}
bool needToBeRmoved(int playerID)
{
	bool isPlayerGradeNormal = playerGrade[playerID] == NORMAL ? true : false;
	bool isPlayerAttendedWednesday = playerWeekAttendData[playerID][WEDNESDAY] == 0 ? true : false;
	bool isPlayerAttendedWeekend = (playerWeekAttendData[playerID][SATURDAY] == 0 && playerWeekAttendData[playerID][SUNDAY] == 0) ? true : false;

	if (isPlayerGradeNormal && isPlayerAttendedWednesday && isPlayerAttendedWeekend)
	{
		return true;
	}
	return false;
}

int getAddPointForPlayer(string week)
{
	int addPoint = 0;
	if (week == "wednesday") {
		addPoint = WENDESDAY_ATTEND_SCORE;
	}
	else if (week == "saturday" || week == "sunday") {
		addPoint = WEEKEND_ATTEND_SCORE;
	}
	else
	{
		addPoint = DAY_OF_THE_WEEK_EXCEPT_WEEKEND_AND_WENDESDAY_ATTEND_SCORE;
	}

	return addPoint;
}

int getBonusPoint(int playerID)
{
	int bonusPoint = 0;
	if (playerWeekAttendData[playerID][WEDNESDAY] >= WEDNESDAY_BONUS_STANDARD) {
		bonusPoint += WEDNESDAY_BONUS_SCORE;
	}

	if (playerWeekAttendData[playerID][SATURDAY] + playerWeekAttendData[playerID][SUNDAY] >= WEEKEND_BONUS_STANDARD) {
		bonusPoint += WEEKEND_BONUS_SCORE;
	}
	return bonusPoint;
}

void printPlayerInfo(int playerID)
{
	cout << "NAME : " << playerNames[playerID] << ", ";
	cout << "WEEK : " << playerWeekAttendData[playerID][WEDNESDAY] << ", ";
	cout << "POINT : " << playerPoints[playerID] << ", ";
	cout << "GRADE : ";

	if (playerGrade[playerID] == GOLD) {
		cout << "GOLD" << "\n";
	}
	else if (playerGrade[playerID] == SILVER) {
		cout << "SILVER" << "\n";
	}
	else {
		cout << "NORMAL" << "\n";
	}
}

void printPlayerInfoNeedToBeRemoved(void)
{
	std::cout << "\n";
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (int playerID = 1; playerID <= idCnt; playerID++) {
		if (needToBeRmoved(playerID))
		{
			std::cout << playerNames[playerID] << "\n";
		}
	}
}
void givePlayerIDToPlayer(string playerName, string week) {
	//ID 부여
	if (playerIDMap.count(playerName) == 0)
	{
		playerIDMap.insert({ playerName, ++idCnt });
		playerNames[idCnt] = playerName;
	}
	int playerID = playerIDMap[playerName];

	//사용자ID별 요일 데이터에 1씩 증가
	playerWeekAttendData[playerID][getWeekIndex(week)] += 1;
	playerPoints[playerID] += getAddPointForPlayer(week);
}

void inputPlayerInfo() {
	ifstream fin{ "attendance_weekday_500.txt" }; //500개 데이터 입력

	for (int dataIdx = 0; dataIdx < MAX_DATA_NUM; dataIdx++) {
		string playerName, attendedWeek;
		fin >> playerName >> attendedWeek;
		givePlayerIDToPlayer(playerName, attendedWeek);
	}

	for (int playerID = 1; playerID <= idCnt; playerID++) {
		playerPoints[playerID] += getBonusPoint(playerID);
		playerGrade[playerID] = getPlayerGrade(playerID);
		printPlayerInfo(playerID);
	}
	printPlayerInfoNeedToBeRemoved();
}

int main() {
	inputPlayerInfo();
}