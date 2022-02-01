#pragma once
#ifndef _CODEDATA
#define _CODEDATA
#include "ofMain.h"

class codeMainDatas {
	public:
	static int depolananInt;
};

union memoryData {
	int *intData;
	float *floatData;
	double *doubleData;
	bool *boolData;
	char *charData;
	string *dataString;
};

class codeAddVar
{
public:
	codeAddVar();
};

// type degeri : 0;
class codeAddIntWithData : public codeAddVar
{
public:
	int data;
	codeAddIntWithData( int d);
	void islemYap();
};

// type degeri 1;
class codeAddIntWithUserAdress : public codeAddVar
{
public:
	int data;
	codeAddIntWithUserAdress(int d);
	void islemYap();
};

// type degeri 2;
class codeChangeIntWithData : public codeAddVar
{
public:
	int data;
	codeChangeIntWithData(int d);
	void islemYap();
};

union processData {
	codeAddIntWithData* addIntWithData;
	codeAddIntWithUserAdress * codeAddIntWithUserAdress;
	codeChangeIntWithData* changeIntWithData;
};

class codeClass {

public:
	codeClass();
	int type;
	processData data;
};
#endif