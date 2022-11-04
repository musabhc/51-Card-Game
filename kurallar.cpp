#include "startup.h"
#include "kurallar.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
kurallar::kurallar()
{
	system("CLS");
	int secim = 0;
	cout << "Oyunda Joker yoktur."
	"\nOyuncu, bilgisayara karsi oynar ve oyuncunun elinde 15 adet kart vardir."
	"\nBilgisayar ise 14 adet karta sahiptir."
	"\nKartlar 2ser 2ser dagitilir."
	"\nSon kart herkese gosterilir."
	"\nSeri ve cifte dizim program tarafindan sizin icin otomatik olarak yapilir ve size gosterilir."
	"\nKurallara aykiri hareketler icin ceza sistemi oyunda mevcut degildir."
	"\nKurallara aykiri hareket etmeyi denerseniz program sizi uyarir ve islemi engeller. "
	"\nOyunumuzdaki cifte sistemimiz pere gore degil tamamen cifte uzerinedir."
	"\nCifte acabilmek icin 4, 5, 6 veya 7 cifte sahip olmaniz gerekmektedir."
	"\nMenuye donmek icin -1 yaziniz: " << endl;
	while (secim != -1) {
		cin >> secim;
		if (secim == -1) {
			startup();
		}
		else {
			cout << "Hatali bir secim yaptiniz! Tekrar deneyin: " << endl;
		}
	}
}