#include "startup.h"
#include "crew.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
crew::crew()
{
	system("CLS");
	int secim = 1;
	cout << "-------------Emegi Gecenler-------------" << endl;
	cout << "Recep GEMALMAZ, Damla Su KARADOGAN, Erdogan KILINC, Musa BUHURCU" << endl;
	cout << "Menuye donmek icin 0 yaziniz! " << endl;
	while (secim != 0)
	{
		cin >> secim;
		if (secim == 0) {
			startup();
		}
		else {
			cout << "Hatali giris yaptiniz! Menuye donmek icin 0 yazin!" << endl;
		}
	}
}