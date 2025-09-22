#include <iostream>

using namespace std;

#define interface struct

struct InterfaceGrade
{
	virtual string notifyGradeInfo(void) = 0;
	virtual bool isNeedToBeRemoved(void) = 0;
};

class normalGrade : public InterfaceGrade
{
public:
	string notifyGradeInfo(void) override
	{
		return "NORMAL";
	}
	bool isNeedToBeRemoved(void) override
	{
		return true;
	}
};

class silverGrade : public InterfaceGrade
{
public:
	string notifyGradeInfo(void) override
	{
		return "SILVER";
	}
	bool isNeedToBeRemoved(void) override
	{
		return false;
	}
};

class goldGrade : public InterfaceGrade
{
public:
	string notifyGradeInfo(void) override
	{
		return "GOLD";
	}
	bool isNeedToBeRemoved(void) override
	{
		return false;
	}
};