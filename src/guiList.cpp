#include "guiList.h"

guiList::guiList()
{
}

guiList::guiList(int t, int s)
{
	type = t; specialId = s;
}

guiList::guiList(int t, int s, guiAlan *a)
{
	type = t; specialId = s; alan = a;
//	cout << endl << "oluşumdaki alan = " << alan;
//	cout << endl << "oluşumdaki type değeri = " << type;
}

guiList::~guiList()
{
}

