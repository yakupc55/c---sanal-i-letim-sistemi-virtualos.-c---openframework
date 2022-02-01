#include "program.h"
float program::addMainX, program::addMainY = 0;

program::program()
{
	specialIdSayac = 0;
	activeGui = -1;
}//fonksiyon sonu

program::~program()
{
}//fonksiyon sonu

void program::addGuiParametres(buttonGui* button, guiAlan* alan)
{
	button->alan = alan;
	alan->specialId = specialIdSayac;
	alan->click = true;
	button->imgCreate();

	//listede ilk değer tip oluyor buton tip 0 dır.
	guiListesi.push_back(new guiList(0, specialIdSayac, alan));
	buttonGuiList.push_back(button);
	alan->y += addMainY;
	//gerekli artırmalar uygulanıyor
	specialIdSayac++;
}//fonksiyon sonu

void program::addGuiParametres(codeTextEditor* textCode, guiAlan* alan)
{
	textCode->alan = alan;
	alan->specialId = specialIdSayac;
	alan->click = true;
	//allocate işlemini yaptık.
	textCode->fbo.allocate(alan->witdh, alan->height);;
	//listede ilk değer tip oluyor textEditorCode tip 1 dır.
	guiListesi.push_back(new guiList(1, specialIdSayac, alan));
	textEditorList.push_back(textCode);
	alan->y += addMainY;
	specialIdSayac++;
}//fonksiyon sonu

void program::drawGui(float MainXt,float MainYt)
{
	guiAlan* alan;
	guiList* list;
	for (int i = 0; i < guiListesi.size(); i++)
	{
		alan = guiListesi[i]->alan;

		list = guiListesi[i];

		if (alan->active) {

			switch (list->type)
			{
				// button için draw işlemi
			case 0:
				buttonGui *btn;
				btn = buttonGuiList[searchIdbutton(guiListesi[i]->specialId)];
				btn->draw(MainXt, MainYt);
				break;
				// text editör için draw işlemi
			case 1:
				codeTextEditor *text;
				text = textEditorList[searchIdtextCode(guiListesi[i]->specialId)];
				text->draw(MainXt, MainYt);

			}// switch sonu
		}//if sonu
	}//for sonu
}//fonksiyon sonu

void program::mousePressed(int x, int y, int button,float MainX,float MainY)
{
	// tüm liste taranıyor.
	for (int i = 0; i < guiListesi.size(); i++)
	{
		// sadece aktif olanlarla işlem yapılıyor
		if (guiListesi[i]->alan->active) {
			//sadece click evente açık olanlar işleme alınıyor
			if (guiListesi[i]->alan->click) {
				// tıklanma zamanında alana dek gelip gelmediğine bakılıyor 
				if (tarama(*guiListesi[i]->alan, x, y,MainX,MainY)) {
					//bu kısım program kısmına özgü oluşturulmuştur. ana guiler sadece
					// butonlardan oluştuğu için çoklu tıklama mekanizmaları çalış durumda
					// değildir.
					//eğer tiklanma gerçekleşmisse onu aktive gui haline getiriyoruz. 
					lastActiveGui = activeGui;

					if (lastActiveGui >= 0) {
						guiListesi[activeGui]->alan->runActive=false;
					}// if asonu
					
					//klavye basımı gibi tarzı durumlar için aktif alan belirlemede kullanılır
					activeGui = i;
					guiListesi[activeGui]->alan->runActive = true;

					switch (guiListesi[i]->type) {
						//button için olan yapılandırma
					case 0: guiListesi[i]->alan->clickEvent(); break;
						//codeTextEditör için olan yapılandırma
					case 1:
						//gelen değerlerin dinamik konumlarına döndürülüyor
						int mx = x / MainX;
						int my = y / MainY;
						codeTextEditor * text;
						text = textEditorList[searchIdtextCode(guiListesi[i]->specialId)];
						text->clikc(mx,my,button);
						break;
					}// switch sonu
					
				}// tarama ifi sonu
			}//click durumu sorgulama
		}// if sonu
	}// for sonu

}//fonksiyon sonu

void program::keyPressed(int key)
{
	// active adresin -1 den farklı olması gerekiyor. 
	if (activeGui >= 0) {
		//keypress aktif ise
		if (guiListesi[activeGui]->alan->keypress) {
			switch (guiListesi[activeGui]->type) {
				// butonlar için olanı
			case 0: break;
				// codetexteditör için olanları
			case 1: 
				codeTextEditor * text;
				text = textEditorList[searchIdtextCode(guiListesi[activeGui]->specialId)];
				text->keypressed(key);
				break;
			}
		}// keypress aktiflik kontrol ifi sonu
	}// active gui kontrol ifi
}//fonksiyon sonu

int program::searchIdbutton(int id)
{
	int donecek = -1;

	for (int i = 0; i < buttonGuiList.size(); i++)
	{
		if (buttonGuiList[i]->alan->specialId == id) {
			donecek = i;
			break;
		}// if sonu
	}// for sonu
	return donecek;
}//fonksiyon sonu

int program::searchIdtextCode(int id)
{
	int donecek = -1;

	for (int i = 0; i < textEditorList.size(); i++)
	{
		if (textEditorList[i]->alan->specialId == id) {
			donecek = i;
			break;
		}// if sonu
	}// for sonu
	return donecek;
}//fonksiyon sonu


bool program::tarama(guiAlan alan, int x, int y, float MainX, float MainY)
{
	bool durum = false;
	int mx = x / MainX;
	int my = y / MainY;
	
	if (alan.x <= mx && (alan.witdh + alan.x) >= mx && alan.y <= my && (alan.height + alan.y) >= my) {
		durum = true;
	}
	return durum;

}// fonksi;yon sonu