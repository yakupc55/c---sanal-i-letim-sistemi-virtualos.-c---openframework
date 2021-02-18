#pragma once
#ifndef _VIRTUALOS
#define _VIRTUALOS
#include "ofMain.h"
#include "buttonGui.h"
#include "guiList.h"
#include "guiAlan.h"
#include "program.h"
#include "codeTextEditor.h"
#include "codeData.h"

class virtualOs
{
public:
	virtualOs();

	// Ana çatı fonksiyonlar
	void setup();
	void draw();
	void update();
	void windowResized(int w, int h);
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);

	// Ana motor teknik fonksiyonları
	static bool mainAppAktive;
	static int aktifUygulama;
	static string appName;

	//gui motoru teknik fonksiyon ve değişkenler
	static int specialIdSayac, eventSayac;
	static vector<guiList *> guiListesi;
	static vector<buttonGui *> buttonGuiList;
	static void addGuiParametres(buttonGui *button, guiAlan *alan);
	static void drawGui();
	static int searchIdbutton(int id);
	bool tarama(guiAlan alan,int x,int y);

	// Ana motor Draw fonksiyonları
	void ustMotor();
	void ortaMotor();
	void altMotor();
	
	//ust motor verileri
	ofColor ustColorOne, ustColorTwo;
	float fontSize;
	ofImage ustMinimize, ustClose;
	float ustMinimizeX, ustCloseX;
	static void ustGuiAktivlik(bool durum);

	//orta motor program verileri
	ofImage ortaBack;
	static vector<program *> programListesi;
	static int currentProgramNO;
	void programFboAllocate(ofFbo* fbo);

	//Desktop and program verileri
	void programDraw();
	static void programGuiDraw();
	void desktopAdd();
	static bool setupRunDurum; // program ilk açıldığında kendine ait run yapısının çalışması için
	static program desktopProgram;
	static void desktopSetup();
	static void desktopDraw();
	void addDesktopProgram();
	buttonGui buttonSlayt, buttonCode;
	guiAlan buttonSlaytA, buttonCodeA;
	static void btnSlaytClick();
	static void btnCodeClick();
	void setupProgramSystem();
	static vector<int> programRunList;
	void programAdd();
	static void searchIdandAdd(int id);

	//alt motor açık programlar uygulaması
	guiAlan runProgramAlan;
	void altMousePressed(int x,int y,int button);
	int programXLength;

	//code program verileri
	static program codeProgram;
	static void codeSetup();
	static void codeDraw();
	void addCodeProgram();
	void codeAdd();

	//code bilgilendirme alanı için
	static vector<string> bilgilendirmeler;
	static double timer;
	static bool bilgilendirmeDurumu , timerBD;
	void drawBilgilendirmeAlani();
	ofFbo bilgiFbo;
	float buzunlukX, buzunlukY;

	//slayt program verileri
	static program slaytProgram;
	static void slaytSetup();
	static void slaytDraw();
	void addSlaytProgram();
	void slaytAdd();
	vector<string> Slaytlar;
	static buttonGui slaytBack, slaytNext;
	guiAlan slaytBackA, slaytNextA;
	static void slaytBackClick();
	static void slaytNextClick();
	static ofImage slaytImage;
	static int slaytNo,maxSlayt;

	//runcode program verileri
	buttonGui btnCodeDraw, btnCodeSetup, btnCodeRun;
	guiAlan btnCodeDrawA, btnCodeSetupA, btnCodeRunA;
	static void btnCodeDrawClick();
	static void btnCodeSetupClick();
	static void btnCodeRunClick();
	static codeTextEditor textEditor;
	guiAlan textEditorA;

	//vLang program verileri
	static program vLangProgram;
	static void vLangSetup();
	static void vLangDraw();
	void addvLangProgram();
	void vLangAdd();
	vector<string> setupNormalCodeLines;
	vector<string> drawNormalCodeLines;
	vector<string> setupByteCodeLines;
	vector<string> drawByteCodeLines;
	vector<string> setupNormalCodes;
	vector<string> drawNormalCodes;
	string verileriAyristirLang(vector<string> veri);
	void normalCodetoByte(vector<string>, vector<codeClass> *pro);
	vector<codeClass> setupRunCode;
	vector<codeClass> drawRunCode;
	vector<string> codeUsersVariables;
	int codeUsersVariableSayac = 1;
	bool converterSuccess = false;
	bool elemanVarMi(vector<string> dizi, string aranan);
	int elemanIndexTutucu;

	//Ana motor teknik değişkenler
	ofFbo ust, alt, orta, fbo;
	int ustAktif, ortaAktif;

	//pencere hesaplamaları ile ilgili değişkenler
	static float WindowX, WindowY, MainX, MainY, DrawX, DrawY;
	float yuzde5Y, yuzde90Y;

	//pencere hesaplamalarý ile ilgili fonksiyonlar
	void hesapla();
	float hX(float number);
	float hY(float number);
	ofTrueTypeFont font;

	// alt kademelere bölünmüş yapılar
	void setupUst();
	void setupOrta();
	void setupAlt();
	void setupHesap();
	void setupTestCode();

	//ust kısım 
	static buttonGui buttonMinimize, buttonClose;
	guiAlan buttonMinimizeA, buttonCloseA;
	static void bntMinimizeClick();
	static void btnCloseClick();

	//test değişkenleri ve test fonksiyonları
	//guiList a1, a2;
	static vector<guiList*> liste1;
	static void test(guiList *gui, guiAlan* alan);
	static void test2();
};
#endif