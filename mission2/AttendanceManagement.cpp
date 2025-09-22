#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "GradeFactory.cpp"
using namespace std;

#define MAX_DATA_NUM	(500)
/* 인덱스 1번부터 사용 */
#define MAX_PLAYER_NUM	(100)


class player
{
public:
	const int MONDAY = 0;
	const int TUESDAY = 1;
	const int WEDNESDAY = 2;
	const int THURSDAY = 3;
	const int FRIDAY = 4;
	const int SATURDAY = 5;
	const int SUNDAY = 6;
	const int WEEK_MAX = 7;

	const int WEDNESDAY_BONUS_STANDARD = 10;
	const int WEEKEND_BONUS_STANDARD = 10;

	const int WEDNESDAY_BONUS_SCORE = 10;
	const int WEEKEND_BONUS_SCORE = 10;


	const int GOLD_SCORE_STANDARD = 50;
	const int SILVER_SCORE_STANDARD = 30;
	const int NORMAL_SCORE_STANDARD = 0;

	const int DAY_OF_THE_WEEK_EXCEPT_WEEKEND_AND_WENDESDAY_ATTEND_SCORE = 1;
	const int WEEKEND_ATTEND_SCORE = 2;
	const int WENDESDAY_ATTEND_SCORE = 3;
	player()
	{
		this->playerWeekAttendData = vector<int>(WEEK_MAX, 0);
		this->playerPoints = 0;
		this->playerName = "";
	}
	
	/* 요일 문자열에서 요일 인덱스 획득 */
	int getWeekIndex(string week)
	{
		int weekIndex = 0xFF;
		if (week == "monday") {
			weekIndex =  MONDAY;
		}
		else if (week == "tuesday"){
			weekIndex = TUESDAY;
		}
		else if (week == "wednesday") {
			weekIndex = WEDNESDAY;
		}
		else if (week == "thursday") {
			weekIndex = THURSDAY;
		}
		else if (week == "friday") {
			weekIndex = FRIDAY;
		}
		else if (week == "saturday") {
			weekIndex = SATURDAY;
		}
		else if (week == "sunday") {
			weekIndex = SUNDAY;
		}
		return weekIndex;
	}
	void incPlayerWeekAttendData(string week)
	{
		this->playerWeekAttendData[getWeekIndex(week)] += 1;
	}
	void setPlayerWeekAttendData(string week, int attandedData)
	{
		this->playerWeekAttendData[getWeekIndex(week)] = attandedData;
	}
	int getPlayerWeekAttendData(string week)
	{
		return this->playerWeekAttendData[getWeekIndex(week)];
	}
	string getPlayerName(void)
	{
		return this->playerName;
	}
	void setPlayerName(string playerName)
	{
		this->playerName = playerName;
	}
	int getPlayerPoints(void)
	{
		return this->playerPoints;
	}
	void setPlayerPoints(int point)
	{
		this->playerPoints = point;
	}
	void incPlayerPointsWithWeek(string week)
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
		this->playerPoints += addPoint;
	}
	void incPlayerPointWithBonus(void)
	{
		int bonusPoint = 0;
		if (this->playerWeekAttendData[WEDNESDAY] >= WEDNESDAY_BONUS_STANDARD) {
			bonusPoint += WEDNESDAY_BONUS_SCORE;
		}

		if (this->playerWeekAttendData[SATURDAY] + this->playerWeekAttendData[SUNDAY] >= WEEKEND_BONUS_STANDARD) {
			bonusPoint += WEEKEND_BONUS_SCORE;
		}
		this->playerPoints += bonusPoint;
	}
	void definePlayerGrade(void)
	{
		if (this->playerPoints >= GOLD_SCORE_STANDARD) {
			this->playerGrade = new goldGrade();
		}
		else if (this->playerPoints >= SILVER_SCORE_STANDARD) {
			this->playerGrade = new silverGrade();;
		}
		else {
			this->playerGrade = new normalGrade();
		}
	}
	InterfaceGrade * getPlayerGrade(void)
	{
		return this->playerGrade;
	}
	bool needToBeRmoved(void)
	{
		bool isPlayerGradeNormal = this->playerGrade->isNeedToBeRemoved() ? true : false;
		bool isPlayerAttendedWednesday = this->playerWeekAttendData[WEDNESDAY] == 0 ? true : false;
		bool isPlayerAttendedWeekend = (this->playerWeekAttendData[SATURDAY] == 0 && this->playerWeekAttendData[SUNDAY] == 0) ? true : false;

		if (isPlayerGradeNormal && isPlayerAttendedWednesday && isPlayerAttendedWeekend)
		{
			return true;
		}
		return false;
	}
private:
	vector<int> playerWeekAttendData;
	int playerPoints;
	InterfaceGrade * playerGrade;
	string playerName;
};

class playerMap
{
public:
	playerMap()
	{
		this->playerIDMap.clear();
		this->players = vector<player>(MAX_PLAYER_NUM);
		this->idCnt = 0;

	}
	void playerAttendance(string playerName, string week)
	{
		if (playerIDMap.count(playerName) == 0)
		{
			playerIDMap.insert({ playerName, ++idCnt });
			players[idCnt].setPlayerName(playerName);
		}
		int playerID = playerIDMap[playerName];

		//사용자ID별 요일 데이터에 1씩 증가
		players[playerID].incPlayerWeekAttendData(week);
		players[playerID].incPlayerPointsWithWeek(week);
	}
	void getPlayerInfo(void)
	{
		reflectBonusPoint();

		for (int curPlayerID = 1; curPlayerID <= this->idCnt; curPlayerID++)
		{
			players[curPlayerID].definePlayerGrade();

			cout << "NAME : " << players[curPlayerID].getPlayerName() << ", ";
			cout << "POINT : " << players[curPlayerID].getPlayerPoints() << ", ";
			cout << "GRADE : " << players[curPlayerID].getPlayerGrade()->notifyGradeInfo();
			cout << endl;
		}

		std::cout << "\n";
		std::cout << "Removed player\n";
		std::cout << "==============\n";
		for (int curPlayerID = 1; curPlayerID <= this->idCnt; curPlayerID++) {
			if (players[curPlayerID].needToBeRmoved())
			{
				std::cout << players[curPlayerID].getPlayerName() << "\n";
			}
		}
	}
	void reflectBonusPoint(void)
	{
		for (int curPlayerID = 1; curPlayerID <= this->idCnt; curPlayerID++)
		{
			players[curPlayerID].incPlayerPointWithBonus();
		}
	}
	int getIDCnt(void)
	{
		return this->idCnt;
	}
	
private:
	map<string, int> playerIDMap;
	vector<player> players;
	int idCnt;
};
