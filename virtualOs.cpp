#include "virtualOs.h"

// static float int ilk atamalar
float virtualOs::WindowX , virtualOs::WindowY, virtualOs::MainX, virtualOs::MainY, virtualOs::DrawX, virtualOs::DrawY = 0;
// Ana windows kısmını etkin hale getirdik
bool virtualOs::mainAppAktive = true;
//program ilk çalıştırılırkenki runu aktif hale getirdik. 
bool virtualOs::setupRunDurum = true;
// Ana windowsumuzun dizi değeri olan 0 aktif uygulama yaptık.
int virtualOs::aktifUygulama = 0;

// Anawindowsun textbilgisi
string virtualOs::appName = "VIRTUALOS V.0.0.1 (Minimal prototype)";

//gui için oluşturulan static değişkenler
int virtualOs::eventSayac = 0;
int virtualOs::specialIdSayac = 0;
vector<guiList*> virtualOs::guiListesi;
vector<buttonGui*> virtualOs::buttonGuiList;
vector<guiList*> virtualOs::liste1;

//programs için veriler
int virtualOs::currentProgramNO = 0;
vector<program *> virtualOs::programListesi;
program virtualOs::desktopProgram = program();
program virtualOs::codeProgram = program();
program virtualOs::slaytProgram = program();
program virtualOs::vLangProgram = program();
vector<int> virtualOs::programRunList;

// teknik program buttonları
buttonGui virtualOs::buttonMinimize, virtualOs::buttonClose;

//slayt kısmı
ofImage virtualOs::slaytImage;
int virtualOs::slaytNo , virtualOs::maxSlayt = 1 ;
buttonGui  virtualOs::slaytBack, virtualOs::slaytNext;

//code kısmı
codeTextEditor virtualOs::textEditor;

//code bilgilendirme Alanı
vector<string> virtualOs::bilgilendirmeler;
double virtualOs::timer = 0;
bool virtualOs::bilgilendirmeDurumu, virtualOs::timerBD = false;


virtualOs::virtualOs() {

}// constructor sonu

void virtualOs::setup() {
	// ekranın boyutlarına göre tekrarlanan çizim yapısına yönelik kullanılır.
	setupHesap();

	//480 * 640 ölçülerine göre hesaplanmıştır
	//üst kısımama %5 luk bir alan ayrılmıştır
	yuzde5Y = DrawY / 20;
	yuzde90Y = DrawY * 0.9;

	//programlar için ana çalıştırayın eklenmesi
	setupProgramSystem();

	// üst kısım program ana bilgisi ve kapatma yapıları bulunur
	setupUst();

	// programların kendilerine ayrılan çalışma alanı
	setupOrta();

	//çalışan programları gördüğümüz teknik alan. 
	setupAlt();

	//çeşitli test kodlarının çalıştırılması için ayrılan bir alan
	//setupTestCode();
	//test2();

}// setup sonu

void virtualOs::draw() {

	//	ofBackground(255,255,255,255);
	ustMotor();
	ortaMotor();
	altMotor();
	drawGui();

	// çeşitli durumlarda ekranda beliren bilgilendirme durumu
	drawBilgilendirmeAlani();
}//draw sonu

void virtualOs::update()
{

}// update sonu

void virtualOs::windowResized(int x, int y) {
	WindowX = x;
	WindowY = y;
	hesapla();
}//window resized sonu

void virtualOs::keyPressed(int key) {
	std::cout << "basilan deger = "<<key<<endl;
	
	//sistem olarak key yapılandırmaları şimdilik program kısmındaki guiler için çalışmaktadır.
	programListesi[currentProgramNO]->keyPressed(key);
}// fonksiyon sonu

void virtualOs::mousePressed(int x, int y, int button)
{
	std::cout << endl << "x = " << x << " y = " << y << "button = " << button << endl;
	// tüm liste taranıyor.
	for (int i = 0; i < guiListesi.size(); i++)
	{
		// sadece aktif olanlarla işlem yapılıyor
		if (guiListesi[i]->alan->active) {
			//sadece click evente açık olanlar işleme alınıyor
			if (guiListesi[i]->alan->click) {
				// tıklanma zamanında alana dek gelip gelmediğine bakılıyor 
				if (tarama(*guiListesi[i]->alan,x,y)) {
					guiListesi[i]->alan->clickEvent();
				}// tarama if sonu
			}// tarama if sonu
		}// if sonu
	}// for sonu
	programListesi[currentProgramNO]->mousePressed(x,y,button,MainX,MainY);
	altMousePressed(x,y,button);
}//fonksiyon sonu

void virtualOs::setupUst()
{
	//ana fontumuz
	fontSize = 12;
	font.load("arial.ttf", fontSize);

	ust.allocate(DrawX, yuzde5Y, GL_RGB);
	ust.begin();
	ofClear(255, 0, 0, 255);
	ust.end();

	//ust kısım için ayrılan
	// grimsi bir renk tonu
	ustColorOne = ofColor(105, 105, 105);
	ustColorTwo = ofColor(130, 130, 130);

	//image kodları
	//ust kısım için ayrılan
	ustMinimize.loadImage("images\\buttons\\minimize.png");
	ustClose.loadImage("images\\buttons\\close.png");
	ustCloseX = DrawX - yuzde5Y - 1 - 4;
	ustMinimizeX = DrawX - ((yuzde5Y + 2) * 2) - 5;

	//burdan itibaren gui sistemine göre bir yapılandırma yapılmıştır.
	buttonMinimizeA = guiAlan(ustMinimizeX, 0, yuzde5Y, yuzde5Y);
	buttonMinimize.imgYolaktiv = "images\\buttons\\minimize.png";
	addGuiParametres(&buttonMinimize,&buttonMinimizeA);

	buttonCloseA = guiAlan(ustCloseX, 0, yuzde5Y, yuzde5Y);
	buttonClose.imgYolaktiv = "images\\buttons\\close.png";
	addGuiParametres(&buttonClose, &buttonCloseA);

	//gui paremetlerini ekledikten sonra click tanımlamalarımızı yapıyoruz. 
	buttonMinimize.alan->clickEvent = &virtualOs::bntMinimizeClick;
	buttonClose.alan->clickEvent = &virtualOs::btnCloseClick;
	//butonları kapatıyoruz
	buttonMinimize.alan->active = false;
	buttonClose.alan->active = false;
	
}// fonksiyon sonu

void virtualOs::setupOrta()
{
	// alt kýsýma %10 lik bir alan ayrýlmýþtýr
	alt.allocate(DrawX, yuzde90Y, GL_RGBA, 4);
	alt.begin();
	ofClear(0, 255, 0, 255);
	alt.end();
	//eklenecek teknik programları belirtiyoruz.
	programAdd();
}// fonksiyon sonu

void virtualOs::setupAlt()
{
	programXLength = 104;
	// alt kýsýma %5 lik bir alan ayrýlmýþtýr
	orta.allocate(DrawX, yuzde5Y, GL_RGB);
	orta.begin();
	ofClear(255, 255, 255, 255);
	orta.end();

	//alt program için ilk yapılandırmalar
	runProgramAlan = guiAlan(0,yuzde5Y+yuzde90Y, programXLength,yuzde5Y);
	//desktopSürekli açık olacağı için onu hemen run programlara ekliyoruz.
	programRunList.push_back(0);
}// fonksiyon sonu

void virtualOs::setupHesap()
{
	//Ana çalışma sistemi
	DrawX = 480;
	DrawY = 640;
	WindowX = ofGetWindowWidth();
	WindowY = ofGetWindowHeight();
	hesapla();
}// fonksiyon sonu

void virtualOs::addGuiParametres(buttonGui *button, guiAlan *alan)
{
	button->alan = alan;
	alan->specialId = specialIdSayac;
	alan->click = true;
	alan->eventClickNO = eventSayac;
	button->imgCreate();

	guiListesi.push_back(new guiList(0, specialIdSayac, alan));
	buttonGuiList.push_back(button);

	//gerekli artırmalar uygulanıyor
	specialIdSayac++;
	eventSayac++;
}// fonksiyon sonu

void virtualOs::drawGui()
{
	buttonGui *btn;
	guiAlan *alan;
	guiList *list;
	for (int i = 0; i < guiListesi.size(); i++)
	{
		alan = guiListesi[i]->alan;

		list = guiListesi[i];

		if (alan->active) {

			switch (list->type)
			{
			case 0:
			btn = buttonGuiList[searchIdbutton(guiListesi[i]->specialId)];
			btn->draw(MainX,MainY);
				break;
			}// switch sonu
		}//if sonu
	}//for sonu
	//burda programlara ait drawguiyi yapılandırma içine alıyoruz. 
	programGuiDraw();
}//fonksiyon sonu

int virtualOs::searchIdbutton(int id)
{
	int donecek = -1;
	for (int i = 0; i < buttonGuiList.size(); i++)
	{
		if (buttonGuiList[i]->alan->specialId == id) {
			donecek = i;
			break;
		}//if sonu
	}//for sonu
	return donecek;
}// fonksiyon sonu

bool virtualOs::tarama(guiAlan alan,int x, int y)
{
	bool durum = false;
	
	int mx = x / MainX;
	int my = y / MainY;
	
	if (alan.x <= mx && (alan.witdh + alan.x) >=mx && alan.y<= my && (alan.height + alan.y) >= my) {
		durum = true;
	}
	return durum;
}// fonksiyon sonu

void virtualOs::ustMotor() {

	ust.begin();
//	ofClear(193,205,205,255);
	ofBackgroundGradient(ustColorOne, ustColorTwo, OF_GRADIENT_LINEAR);
	ofNoFill();
	ofDrawRectangle(0+1,0+1,DrawX-1,yuzde5Y-1);
	if (mainAppAktive) {
		appName = "VIRTUALOS V.0.0.1 (Minimal prototype)";

	}// if sonu
	else {
		appName = programListesi[currentProgramNO]->programName;
	}// else sonu
	font.drawString(appName, 24,(yuzde5Y+fontSize)/2);
	ust.end();
	ust.draw(0, 0, WindowX, hY(yuzde5Y));

}// fonksiyon sonu

void virtualOs::ortaMotor() {
	programDraw();
}// fonksiyon sonu

void virtualOs::altMotor() {
	alt.begin();
	ofBackgroundGradient(ustColorOne, ustColorTwo, OF_GRADIENT_LINEAR);
//	font.drawString(ofToString(ofGetHeight)+":"+ofToString(ofGetMinutes),DrawX-(fontSize*5),yuzde5Y+yuzde90Y+(fontSize)+2);
	font.drawString(ofGetTimestampString("%H:%M:%S"), DrawX - 64, (yuzde5Y + fontSize) / 2) ;
	alt.end();
	alt.draw(0, hY(yuzde5Y + yuzde90Y), WindowX, hY(DrawY - yuzde5Y));

	for (size_t i = 0; i < programRunList.size(); i++)
	{
		programListesi[programRunList[i]]->minImg.draw(hX(0+(i* programXLength)),hY(yuzde5Y+yuzde90Y),hX(programXLength),hY(yuzde5Y));
	}// for sonu
}// fonksiyon sonu

void virtualOs::ustGuiAktivlik(bool durum)
{
	buttonMinimize.alan->active = durum;
	buttonClose.alan->active = durum;
}// fonksiyon sonu

void virtualOs::programFboAllocate(ofFbo* fbo)
{
	fbo->allocate(DrawX,yuzde90Y);
	fbo->begin();
	ofClear(255, 255, 255,255);
	fbo->end();
}// fonksiyon son

void virtualOs::programDraw()
{
	if (setupRunDurum) {
	//	cout << endl << " orta motor setup run kismi calisti";
		programListesi[currentProgramNO]->setup();
		setupRunDurum = false;
	}
	programListesi[currentProgramNO]->draw();
	ofFbo* fbo = &programListesi[currentProgramNO]->fbo;
	fbo->draw(0, hY(yuzde5Y), WindowX, hY(yuzde90Y));
}// fonksiyon son

void virtualOs::programGuiDraw()
{
	programListesi[currentProgramNO]->drawGui(MainX,MainY);
}// fonksiyon son

void virtualOs::desktopAdd()
{
	desktopProgram.setup = &virtualOs::desktopSetup;
	desktopProgram.draw = &virtualOs::desktopDraw;
	desktopProgram.desktopProgram = true;
	desktopProgram.programName = "Desktop";
	programFboAllocate(&desktopProgram.fbo);
	programListesi.push_back(&desktopProgram);
	addDesktopProgram();
}// fonksiyon sonu

void virtualOs::desktopSetup()
{
//	cout << endl << "desktop setup basarili bir calisma yapti";
	ofImage *img = &desktopProgram.img;
	img->loadImage("images\\background\\backorta.jpg");
}// fonksiyon sonu

void virtualOs::desktopDraw()
{
//	cout << endl << "desktop draw basarili bir calisma yapti";
	ofFbo* fbo = &desktopProgram.fbo;
	ofImage* img = &desktopProgram.img;
	fbo->begin();
//	ofBackground(ofRandom(255));
	ofDrawBox(0, 0, 400);
	img->draw(0,0);
	fbo->end();

}// fonksiyon sonu

void virtualOs::setupTestCode()
{
	guiList a1 = guiList(0, 1);
	guiList a2 = guiList(1, 2);
	test(&a1,&buttonCloseA);
	test(&a2,&buttonMinimizeA);
	std::cout << endl << " a1 spe = " << &a1.alan;
	std::cout << endl << " a2 spe = " << &a2.alan;
	std::cout << endl << " a1 spe list = " << &liste1[0]->alan;
	std::cout << endl << " a2 spe list = " << &liste1[1]->alan;

}// fonksiyon sonu

void virtualOs::bntMinimizeClick()
{
	std::cout << endl << "minimize butonuna basildi";
	mainAppAktive = true;
	ustGuiAktivlik(!mainAppAktive);
	currentProgramNO = 0;
}// fonksiyon sonu

void virtualOs::btnCloseClick()
{
	std::cout << endl << "close butonuna basildi";
	for (int i = 0; i < programRunList.size(); i++)
	{
		if (programRunList[i] == currentProgramNO) {
			programRunList.erase(programRunList.begin()+i);
			break;
		}// if sonu
	}// for sonu
	mainAppAktive = true;
	ustGuiAktivlik(!mainAppAktive);
	currentProgramNO = 0;
}// fonksiyon sonu

void virtualOs::addDesktopProgram()
{
	int temelUzunluk = 128;
	int eklemeUzunlukY = 144;
	int boslukX = 24;
	int boslukY = 16;

	buttonSlaytA = guiAlan(boslukX,boslukY,temelUzunluk,temelUzunluk);
	buttonCodeA = guiAlan(boslukX, boslukY+(eklemeUzunlukY), temelUzunluk, temelUzunluk);
	
	buttonSlayt.imgYolaktiv = "images\\buttons\\slayt.png";
	desktopProgram.addGuiParametres(&buttonSlayt,&buttonSlaytA);

	buttonCode.imgYolaktiv = "images\\buttons\\code.png";
	desktopProgram.addGuiParametres(&buttonCode, &buttonCodeA);

	buttonSlayt.alan->clickEvent = &virtualOs::btnSlaytClick;
	buttonCode.alan->clickEvent = &virtualOs::btnCodeClick;
	
	//alt kısım için küçük resim eklemesi
	desktopProgram.minImg.loadImage("images\\buttons\\adesktop.png");
}// fonksiyon sonu

void virtualOs::btnSlaytClick()
{
	//slayt yapısının program kodu 2
	searchIdandAdd(2);
	std::cout << endl << "slayt butonu tiklama islemi basarili";
}// fonksiyon sonu

void virtualOs::btnCodeClick()
{
	//code yapısının program kodu 1
	searchIdandAdd(1);
	std::cout << endl << "code butonu tiklama islemi basarili";
}// fonksiyon sonu

void virtualOs::setupProgramSystem()
{
	program::addMainY = yuzde5Y;
}// fonksiyon sonu

void virtualOs::programAdd()
{
	desktopAdd();  // 0
	codeAdd();     // 1
	slaytAdd();    // 2
	vLangAdd();    // 3

}// fonksiyon sonu

void virtualOs::searchIdandAdd(int id)
{
	bool durum = true;
	for (int i = 0; i < programRunList.size(); i++)
	{
		if (programRunList[i] == id) {
			durum = false;
			break;
		}// if sonu
	}// for sonu
	if (durum)
	{
		programRunList.push_back(id);
		setupRunDurum = true;
	}//if sonu
	// her halükarda olacaklar
	mainAppAktive = false;
	ustGuiAktivlik(!mainAppAktive);
	currentProgramNO = id;
}// fonksiyon sonu

void virtualOs::altMousePressed(int x, int y, int button)
{
	//noktasal hesap için mx kullanılacak.
	int mx = x / MainX;
	int no;
	//hesaplamak için teknik bir alan yapısı oluşturuluyor
	guiAlan alan = guiAlan(0,yuzde5Y+yuzde90Y,(programRunList.size())* programXLength,yuzde5Y);
	if (tarama(alan,x,y)) {
		no = x / (hX(programXLength));
		if (no == programRunList.size()) no = programRunList.size()-1;
		//döngüdeki noyu asıl no ya çeviriyoruz.
		no = programRunList[no];
		//Eğer zaten açık değilse açma işlemi yap diyoruz.
		if (no != currentProgramNO) {
			if (programListesi[no]->desktopProgram) {
				mainAppAktive = true;
				ustGuiAktivlik(!mainAppAktive);
			}// if sonu
			else {
				mainAppAktive = false;
				ustGuiAktivlik(!mainAppAktive);
			}// else sonu
			currentProgramNO = no;
		}// current kontrol ifi sonu
	}// if alan tarama if sonu

}// fonksiyon sonu

void virtualOs::codeSetup()
{

}// fonksiyon sonu

void virtualOs::codeDraw()
{
	codeProgram.fbo.begin();
	ofBackground(255, 255, 255);

	codeProgram.fbo.end();
	
}// fonksiyon sonu

void virtualOs::addCodeProgram()
{
	//alt kısım için küçük resim eklemesi
	codeProgram.minImg.loadImage("images\\buttons\\acode.png");

	int btnsCodeX = 160;
	int btnsCodeY = 48;

	btnCodeDrawA = guiAlan(0,0,btnsCodeX,btnsCodeY);
	btnCodeSetupA = guiAlan(btnsCodeX, 0, btnsCodeX, btnsCodeY);
	btnCodeRunA = guiAlan(btnsCodeX*2,0, btnsCodeX, btnsCodeY);

	btnCodeDraw.imgYolaktiv = "images\\buttons\\drawpart.png";
	codeProgram.addGuiParametres(&btnCodeDraw, &btnCodeDrawA);

	btnCodeSetup.imgYolaktiv = "images\\buttons\\setuppart.png";
	codeProgram.addGuiParametres(&btnCodeSetup, &btnCodeSetupA);

	btnCodeRun.imgYolaktiv = "images\\buttons\\runcode.png";
	codeProgram.addGuiParametres(&btnCodeRun, &btnCodeRunA);


	btnCodeDraw.alan->clickEvent = &virtualOs::btnCodeDrawClick;
	btnCodeSetup.alan->clickEvent = &virtualOs::btnCodeSetupClick;
	btnCodeRun.alan->clickEvent = &virtualOs::btnCodeRunClick;

	textEditorA = guiAlan(0,btnsCodeY,DrawX,yuzde90Y-btnsCodeY);
	codeProgram.addGuiParametres(&textEditor, &textEditorA);
	textEditor.alan->keypress = true;
	textEditor.setup();
}// fonksiyon sonu

void virtualOs::codeAdd()
{
	codeProgram.setup = &virtualOs::codeSetup;
	codeProgram.draw = &virtualOs::codeDraw;
	codeProgram.programName = "RUN CODE V.0.0.1 (minimal version)";
	programFboAllocate(&codeProgram.fbo);
	programListesi.push_back(&codeProgram);
	addCodeProgram();
}// fonksiyon sonu

void virtualOs::drawBilgilendirmeAlani()
{
	if (bilgilendirmeDurumu) {
		if (bilgilendirmeler.size() >= 1) {
	
			if (timerBD) {
				if (ofGetElapsedTimeMillis() - timer <= 700) {
	
					float startY = (WindowY - fontSize) / 2;
					float startX = (WindowX - buzunlukX) / 2;
					
					bilgiFbo.draw(startX,startY);

				}// time düzen kontrol
				else {
					timerBD = false;

					bilgilendirmeler.erase(bilgilendirmeler.begin());
					}// else sonu
			}//timer sonu
			else {
				int fontSize = 15;
				ofTrueTypeFontSettings setting("font\\bilgilendirme.ttf", fontSize);
				setting.addRanges(ofAlphabet::Latin);
				ofTrueTypeFont bilfont;
				

				bilfont.load(setting);
				buzunlukX = bilfont.stringWidth(bilgilendirmeler[0]);
				buzunlukY = bilfont.stringHeight(bilgilendirmeler[0]);
				bilgiFbo.allocate(buzunlukX+4,buzunlukY+4);
				bilgiFbo.begin();
				ofBackground(200, 150, 245);
				ofSetColor(0, 0, 0);
				bilfont.drawString(bilgilendirmeler[0], 2, fontSize+4);
				bilgiFbo.end();

				timer = ofGetElapsedTimeMillis();

				timerBD = true;
			}//timer else sonu
		}// bilgilendirme ifi sonu
		else {
			bilgilendirmeDurumu = false;
		}// bilgilendirme else sonu
	}// bilgiendrimeDurumu ifi sonu
}// fonksiyon sonu

void virtualOs::slaytSetup()
{
	// tekrar açılışta düzeltiliyor.
	slaytNo = 1;
	slaytImage.loadImage("images\\slayt\\slayt1.jpg");
	slaytBack.alan->active = false;
}// fonksiyon sonu

void virtualOs::slaytDraw()
{
	slaytProgram.fbo.begin();
	ofBackground(255,255,255);
	slaytImage.draw(0,0,480,480);
	slaytProgram.fbo.end();
}// fonksiyon sonu

void virtualOs::addSlaytProgram()
{
	//alt kısım için küçük resim eklemesi
	slaytProgram.minImg.loadImage("images\\buttons\\aslayt.png");
	int slaytButtonH = 96;
	int slaytButtonW = 240;

	slaytBackA = guiAlan(0,yuzde90Y-slaytButtonH,slaytButtonW,slaytButtonH);
	slaytNextA = guiAlan(slaytButtonW, yuzde90Y - slaytButtonH, slaytButtonW, slaytButtonH);
	
	slaytBack.imgYolaktiv = "images\\buttons\\back.png";
	slaytProgram.addGuiParametres(&slaytBack,&slaytBackA);

	slaytNext.imgYolaktiv = "images\\buttons\\next.png";
	slaytProgram.addGuiParametres(&slaytNext, &slaytNextA);

	slaytBack.alan->clickEvent = &virtualOs::slaytBackClick;
	slaytNext.alan->clickEvent = &virtualOs::slaytNextClick;

	//elimizdeki slayt sayısını belirtiyoruz
	maxSlayt = 5;
}// fonksiyon sonu

void virtualOs::slaytAdd()
{
	slaytProgram.setup = &virtualOs::slaytSetup;
	slaytProgram.draw = &virtualOs::slaytDraw;
	slaytProgram.programName = "SLIDE SHOW (V.0.1)";
	programFboAllocate(&slaytProgram.fbo);
	programListesi.push_back(&slaytProgram);
	addSlaytProgram();
}// fonksiyon sonu

void virtualOs::slaytNextClick()
{
	if (slaytNo != maxSlayt) {
		slaytNo++;
		slaytImage.loadImage("images\\slayt\\slayt" + ofToString(slaytNo)+".jpg");

		//son sayıya ulaşınca nexti kapatıyoruz
		if (slaytNo==maxSlayt) {
			slaytNext.alan->active = false;
		}//if sonu

		//1 de iken kapalı olan geri butonu slayt 2 de açılmış oluyor. 
		else if(slaytNo==2) {
			slaytBack.alan->active = true;
		}//esle if sonu
	}// ana if sonu
}// fonksiyon sonu

void virtualOs::slaytBackClick()
{
	if (slaytNo != 1) {
		slaytNo--;
		slaytImage.loadImage("images\\slayt\\slayt" + ofToString(slaytNo) + ".jpg");

		// max tan bir aşşağıa düşmüssse nextin açılması gerekiyor
		if (slaytNo == maxSlayt - 1) {
			slaytNext.alan->active = true;
		}//if sonu

		//ilk sayıya inince geri butonunu kapatıyoruz
		else if (slaytNo == 1) {
			slaytBack.alan->active = false;
		}//esle if sonu
	}// if sonu
}// fonksiyon sonu

void virtualOs::btnCodeDrawClick()
{
	textEditor.activeDocument = 0;
}// fonksiyon sonu

void virtualOs::btnCodeSetupClick()
{
	textEditor.activeDocument = 1;
}// fonksiyon sonu

void virtualOs::btnCodeRunClick()
{
	std::cout << endl << " btn code run clic basarili ";
	bilgilendirmeDurumu = true;
	bilgilendirmeler.push_back("ilk bilgilendirme");
	bilgilendirmeler.push_back("ikinci az uzun bilgilendirme");
	bilgilendirmeler.push_back("üçüncü türkçe karekterli bilgilendirme");
	bilgilendirmeler.push_back("dördüncü \n cok satirli \n bilgilendirme");
	// her hangi bir bilgilendirme yoksa çalıştır.
	searchIdandAdd(3);
}// fonksiyon sonu

void virtualOs::vLangSetup()
{
	vLangProgram.fbo.begin();
	ofBackground(255, 255, 255);
	vLangProgram.fbo.end();
}// fonksiyon sonu

void virtualOs::vLangDraw()
{
	vLangProgram.fbo.begin();
	int a = ofRandom(480);
	int b = ofRandom(576);
	int c = ofRandom(10);
	ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255),ofRandom(255));
	ofDrawCircle(a, b, c);

	vLangProgram.fbo.end();
}// fonksiyon sonu

void virtualOs::vLangAdd()
{
	vLangProgram.setup = &virtualOs::vLangSetup;
	vLangProgram.draw = &virtualOs::vLangDraw;
	vLangProgram.programName = "RUN vLang V.0.0.1 (minimal version)";
	programFboAllocate(&vLangProgram.fbo);
	programListesi.push_back(&vLangProgram);
	addvLangProgram();
}// fonksiyon sonu

void virtualOs::addvLangProgram()
{
	vLangProgram.minImg.loadImage("images\\buttons\\avlang.png");

	setupNormalCodeLines.push_back("int num1;");
	setupNormalCodeLines.push_back("int num2;");
	setupNormalCodeLines.push_back("int num3;");
	setupNormalCodeLines.push_back("int r;");
	setupNormalCodeLines.push_back("int g;");
	setupNormalCodeLines.push_back("int b;");
	setupNormalCodeLines.push_back("int t;");

	drawNormalCodeLines.push_back("num1 = random(480);");
	drawNormalCodeLines.push_back("num2 = random(576);");
	drawNormalCodeLines.push_back("num3 = random(10);");
	drawNormalCodeLines.push_back("r = random(255);");
	drawNormalCodeLines.push_back("g = random(255);");
	drawNormalCodeLines.push_back("b = random(255);");
	drawNormalCodeLines.push_back("t = random(255);");
	/*drawNormalCodeLines.push_back("color(r,g,b,t);");
	drawNormalCodeLines.push_back("cirle(a,b,c);");*/

	string setupVeri = verileriAyristirLang(setupNormalCodeLines);
	string drawVeri = verileriAyristirLang(drawNormalCodeLines);

	//tek tek işlemek için ana yapıya ayırıyoruz. 
	setupNormalCodes = ofSplitString(setupVeri," ");
	drawNormalCodes = ofSplitString(drawVeri," ");

	normalCodetoByte(setupNormalCodes,&setupRunCode);
	normalCodetoByte(drawNormalCodes, &drawRunCode);
//	cout << endl << "setup normal codes size : " << setupNormalCodes.size();
//	cout << endl << "draw normal codes size : " << drawNormalCodes.size();

	//bazı test kodları


	map<string, int> mymap;
	mymap.insert(mymap.begin(), pair<string, int>("int", 1));
	
	std::cout << endl << "map test : " << mymap["int"];
	processData d11;
	std::cout << endl << "fonksiyonlu uzunluk : " << sizeof(d11);

	std::cout << endl << "user sayacındaki eleman sayisi : " << codeUsersVariables.size();

	for (int i = 0; i < codeUsersVariables.size(); i++)
	{
		std::cout << endl << i << ". eleman : " << codeUsersVariables[i];
	}// for sonu

	int num2 = ofRandom(255);
	std::cout << endl << " random(255) testi : " << num2;
}// fonksiyon sonu


string virtualOs::verileriAyristirLang(vector<string> veri)
{
	//temel string oluşturuldu.
	string text = "";
	for (int i = 0; i < veri.size(); i++)
	{
		text += veri[i];
	}

	// teknik boşluklama işlemi
	vector<string> dizi = { "=","(",")","/",";" ,","};

	for (int i = 0; i < dizi.size(); i++) {
		ofStringReplace(text,dizi[i]," "+ dizi[i]+ " ");
	}

	// son boşluk silimi 
	if (text[text.length()-1] == ' ') {
		std::cout << endl << "buraya girildi";
		text = text.substr(0, text.length() - 1);
	}
	
	// ilk boşluğun silimi
	if (text.at(0) == ' ') {
		text = text.substr(1, text.length());
	}
	
	//fazla boşlukların silinmesi işlemi
	for (int i = 0; i <12; i++) {
		ofStringReplace(text, "  "," ");
	}

	std::cout << endl << endl << text << endl << endl;
	return text;

}// fonksiyon sonu

void virtualOs::normalCodetoByte(vector<string> codes, vector<codeClass>* pro)
{
	elemanIndexTutucu = -1;
	//yüksek kompleks yapılarına sahip olduğu için test kodları sadece yorum haline getirildi
	pro->clear();
	converterSuccess = true;
	vector<string> systemNames;
	systemNames.push_back("int"); // int 0
	int codeSayac = 0;
	int codeMax = codes.size()-1;
	codeClass codeC;
	processData codeD;

	std::cout << endl << endl;
	std::cout << endl << "code sayac degeri : " << codeSayac;
	std::cout << endl << " code max değeri : " << codeMax;
	std::cout << endl << "kodeden gelen deger : " << codes[codeSayac];
	goto codefirstStart;

codeStart:
	std::cout << endl << "code sayac degeri : " << codeSayac;
	std::cout << endl << "kodeden gelen deger : " << codes[codeSayac];
	if (codeSayac != codeMax) codeSayac++; else goto codeEnd;
codefirstStart:

	std::cout << endl << "system sonucu elemanVarMi(systemNames, codes[codeSayac]): " << elemanVarMi(systemNames, codes[codeSayac]);
	if (elemanVarMi(systemNames, codes[codeSayac])) {
		std::cout << endl << "eleman index tutucu değeri : " << elemanIndexTutucu;
		switch (elemanIndexTutucu) {
			// case 0 durumu int durumu oluyor
		case 0: 
			std::cout << endl << "int kelimesi kısmına girdi";

			// isim kısmı için bir artırma yapılıyor.
			if (codeSayac != codeMax) codeSayac++; else goto codeHata;

			//aynı isim yoksa ekleme yap diyoruz
			std::cout << endl << "code sayac degeri : " << codeSayac;
			std::cout << endl << "kodeden gelen deger : " << codes[codeSayac];
			std::cout << endl << "eleman index tutucu değeri : " << elemanIndexTutucu;
			if (!elemanVarMi(codeUsersVariables, codes[codeSayac])) codeUsersVariables.push_back(codes[codeSayac]); else goto codeHata;
			std::cout << endl << "variable ye eklenen son deger : " << codeUsersVariables[codeUsersVariables.size()-1];
			// isimden sonra gelen atamamı yoksa bittim mi onu öğrenmek için artırma işlemi yapılıyor
			if (codeSayac != codeMax) codeSayac++; else goto codeHata;
			std::cout << endl << "code sayac degeri : " << codeSayac;
			std::cout << endl << "kodeden gelen deger : " << codes[codeSayac];

			if (codes[codeSayac]._Equal("=")) {
				std::cout << endl << "  = kısmına girildi ";
				if (codeSayac != codeMax) codeSayac++; else goto codeHata;
				// ilk ekleme yapısının eklenmesi
				codeC.type = 0;
				pro->push_back(codeC);
				codeD.addIntWithData = new codeAddIntWithData(ofToInt(codes[codeSayac]));
				pro->at(pro->size() - 1).data = codeD;

				if (codeSayac != codeMax) codeSayac++; else goto codeHata;

				if (codes[codeSayac]._Equal(";")) {
					std::cout << endl << "  ; kısmına girildi ";
					goto codeStart;
				}// kod bitim kontrolcüsü sonu

			}// eşittir durumuna göre yapılandırma
			else if (codes[codeSayac]._Equal(";")) {
				std::cout << endl << " direk olan ; kısmına girildi ";

				// ilk ekleme yapısının eklenmesi
				codeC.type = 0;
				pro->push_back(codeC);
				codeD.addIntWithData = new codeAddIntWithData(0);
				pro->at(pro->size() - 1).data = codeD;

				goto codeStart;

			}//kod sonlandırmaya göre yapılan artırma
			else {
				goto codeHata;
			}// geriye kalan durumlar

			break;
			std::cout << endl << endl;
		}// system kodları switch sonu
	}//sytem if kontrol sonu
	std::cout << endl << "code sayac degeri : " << codeSayac;
	std::cout << endl << "kodeden gelen deger : " << codes[codeSayac];
	std::cout << endl << "user variable sorgusundan gelen değer : " << (elemanVarMi(codeUsersVariables, codes[codeSayac]));

	if (elemanVarMi(codeUsersVariables, codes[codeSayac])) {
		std::cout << "bu kisma giris basarili ";
		//codeSayac += 6;
		//sayacımızı artırdık
		if (codeSayac != codeMax) codeSayac++; else goto codeHata;
	
		// tek ihtimal var eğer o ihtimal değilse hataya gönder dedik.
		if (!codes[codeSayac]._Equal("=")) goto codeHata;

		goto codeStart;
	}// eleman kontrol ifi

codeHata:
	converterSuccess = false;
	std::cout << endl << "kodda yazım hatası bulundu";
	goto codefinish;
codeEnd:
	std::cout << endl << "kod çevirimi başarılı bir şekilde gerçekleştrildi";
codefinish:
	std::cout << endl << "tüm islemler bitti";
	
}// fonksiyon sonu

bool virtualOs::elemanVarMi(vector<string> dizi, string aranan)
{
	bool durum = false;
	elemanIndexTutucu = -1;
	for (int i = 0; i < dizi.size(); i++)
	{
		std::cout << endl << i << ". eleman  = " << dizi[i];
		if (dizi[i]._Equal(aranan)) {
			elemanIndexTutucu = i;
			durum = true;
			break;
		}// if sonu
	}// for sonu
	return durum;
}// fonksiyon sonu

void virtualOs::test(guiList *gui, guiAlan *alan)
{
	gui->alan = alan;
	std::cout << endl << " eklenme sonrası alan = " << &gui->alan;
	liste1.push_back(gui);
}// fonksiyon sonu

void virtualOs::test2()
{
	std::cout << endl << "fonksiyon pointer basarili bir calisma gosterdi.";
}// fonksiyon sonu

void virtualOs::hesapla() {
	MainX = WindowX / DrawX;
	MainY = WindowY / DrawY;
	program::addMainY = hY(yuzde5Y);
}// fonksiyon sonu

float virtualOs::hX(float number) {
	return number * MainX;
}// fonksiyon sonu

float virtualOs::hY(float number) {
	return number * MainY;
}// fonksiyon sonu