#include "pch.h"
#include "../JinhoCommonProject/AttendanceManagement.cpp"

using namespace std;

class playertFixture : public testing::Test
{
protected:
	void SetUp(void) override
	{
		curPlayer.setPlayerPoints(0);
		curPlayer.setPlayerWeekAttendData("monday", 0);
		curPlayer.setPlayerWeekAttendData("tuesday", 0);
		curPlayer.setPlayerWeekAttendData("wednesday", 0);
		curPlayer.setPlayerWeekAttendData("thursday", 0);
		curPlayer.setPlayerWeekAttendData("friday", 0);
		curPlayer.setPlayerWeekAttendData("saturday", 0);
		curPlayer.setPlayerWeekAttendData("sunday", 0);
		curGrade = NULL;
	}
	void TearDown(void) override
	{

	}
public:
	player curPlayer;
	string testName = "Jinho";
	InterfaceGrade * curGrade;
};

TEST_F(playertFixture, setPlayerName)
{
	/* Arrange */
	curPlayer.setPlayerName(testName);
	/* Act */
	string result = curPlayer.getPlayerName();
	/* Assert */
	EXPECT_EQ(result, testName);
}

TEST_F(playertFixture, incPlayerPointsWithWeekMonday)
{
	/* Arrange */
	curPlayer.incPlayerPointsWithWeek("monday");

	/* Act */
	int result = curPlayer.getPlayerPoints();

	/* Assert */
	EXPECT_EQ(result, curPlayer.DAY_OF_THE_WEEK_EXCEPT_WEEKEND_AND_WENDESDAY_ATTEND_SCORE);
}
TEST_F(playertFixture, incPlayerPointsWithWeekWednesday)
{
	/* Arrange */
	curPlayer.incPlayerPointsWithWeek("wednesday");

	/* Act */
	int result = curPlayer.getPlayerPoints();

	/* Assert */
	EXPECT_EQ(result, curPlayer.WENDESDAY_ATTEND_SCORE);
}

TEST_F(playertFixture, incPlayerPointsWithWeekWeekend)
{
	/* Arrange */
	curPlayer.incPlayerPointsWithWeek("saturday");

	/* Act */
	int result = curPlayer.getPlayerPoints();

	/* Assert */
	EXPECT_EQ(result, curPlayer.WEEKEND_ATTEND_SCORE);
}

TEST_F(playertFixture, incPlayerWeekAttendData)
{
	/* Arrange */
	curPlayer.incPlayerWeekAttendData("monday");
	curPlayer.incPlayerWeekAttendData("tuesday");
	curPlayer.incPlayerWeekAttendData("wednesday");
	curPlayer.incPlayerWeekAttendData("thursday");
	curPlayer.incPlayerWeekAttendData("friday");
	curPlayer.incPlayerWeekAttendData("saturday");
	curPlayer.incPlayerWeekAttendData("sunday");

	/* Act &Assert */
	EXPECT_EQ(1, curPlayer.getPlayerWeekAttendData("monday"));
	EXPECT_EQ(1, curPlayer.getPlayerWeekAttendData("monday"));
	EXPECT_EQ(1, curPlayer.getPlayerWeekAttendData("tuesday"));
	EXPECT_EQ(1, curPlayer.getPlayerWeekAttendData("wednesday"));
	EXPECT_EQ(1, curPlayer.getPlayerWeekAttendData("thursday"));
	EXPECT_EQ(1, curPlayer.getPlayerWeekAttendData("friday"));
	EXPECT_EQ(1, curPlayer.getPlayerWeekAttendData("saturday"));
	EXPECT_EQ(1, curPlayer.getPlayerWeekAttendData("sunday"));
}

TEST_F(playertFixture, incPlayerPointWithBonus)
{
	/* Arrange */
	curPlayer.setPlayerWeekAttendData("wednesday", curPlayer.WEDNESDAY_BONUS_STANDARD);
	curPlayer.setPlayerWeekAttendData("saturday", curPlayer.WEEKEND_BONUS_STANDARD);
	int result = curPlayer.WEDNESDAY_BONUS_STANDARD + curPlayer.WEEKEND_BONUS_STANDARD;
	/* Act &Assert */
	curPlayer.incPlayerPointWithBonus();

	/* Assert */
	EXPECT_EQ(result, curPlayer.getPlayerPoints());
}

TEST_F(playertFixture, getPlayerGradeNormal)
{
	/* Arrange */
	curPlayer.setPlayerPoints(curPlayer.NORMAL_SCORE_STANDARD);
	curPlayer.definePlayerGrade();

	/* Act */
	curGrade = curPlayer.getPlayerGrade();

	/* Assert */
	EXPECT_EQ("NORMAL", curGrade->notifyGradeInfo());
	EXPECT_EQ(true, curGrade->isNeedToBeRemoved());
}

TEST_F(playertFixture, getPlayerGradeSilver)
{
	/* Arrange */
	curPlayer.setPlayerPoints(curPlayer.SILVER_SCORE_STANDARD);
	curPlayer.definePlayerGrade();

	/* Act */
	curGrade = curPlayer.getPlayerGrade();

	/* Assert */
	EXPECT_EQ("SILVER", curGrade->notifyGradeInfo());
	EXPECT_EQ(false, curGrade->isNeedToBeRemoved());
}

TEST_F(playertFixture, getPlayerGradeGold)
{
	/* Arrange */
	curPlayer.setPlayerPoints(curPlayer.GOLD_SCORE_STANDARD);
	curPlayer.definePlayerGrade();

	/* Act  */
	curGrade = curPlayer.getPlayerGrade();

	/* Assert */
	EXPECT_EQ("GOLD", curGrade->notifyGradeInfo());
	EXPECT_EQ(false, curGrade->isNeedToBeRemoved());
}

TEST_F(playertFixture, notNeedToBeRmoved)
{
	/* Arrange */
	curPlayer.setPlayerPoints(curPlayer.NORMAL_SCORE_STANDARD);
	curPlayer.setPlayerWeekAttendData("saturday", 1);
	curPlayer.definePlayerGrade();

	/* Act &Assert */
	int expected = false;

	/* Assert */
	EXPECT_EQ(expected, curPlayer.needToBeRmoved());
}

TEST_F(playertFixture, needToBeRmoved)
{
	/* Arrange */
	curPlayer.setPlayerPoints(curPlayer.NORMAL_SCORE_STANDARD);
	curPlayer.setPlayerWeekAttendData("wednesday", 0);
	curPlayer.setPlayerWeekAttendData("saturday", 0);
	curPlayer.definePlayerGrade();

	/* Act &Assert */
	int expected = true;

	/* Assert */
	EXPECT_EQ(expected, curPlayer.needToBeRmoved());
}


class playerMaptFixture : public testing::Test
{
protected:
	void SetUp(void) override
	{
		curPlayerMap = new playerMap();
	}
	void TearDown(void) override
	{
		delete(curPlayerMap);
	}
public:
	playerMap * curPlayerMap;
	string testName1 = "Jinho";
	string testName2 = "Test";
};

TEST_F(playerMaptFixture, playerAttendanceGetIDCnt)
{
	/* Arrange */
	curPlayerMap->playerAttendance("Jinho", "tuesday");
	curPlayerMap->playerAttendance("Test", "wednesday");
	
	/* Act &Assert */
	int result = curPlayerMap->getIDCnt();

	/* Assert */
	EXPECT_EQ(result, 2);
}

TEST_F(playerMaptFixture, getPlayerInfo)
{
	/* Arrange */
	curPlayerMap->playerAttendance("Jinho", "tuesday");
	curPlayerMap->playerAttendance("Test", "wednesday");

	/* Act */
	curPlayerMap->getPlayerInfo();
	int result = curPlayerMap->getIDCnt();

	/* Assert */
	EXPECT_EQ(result, 2);
}