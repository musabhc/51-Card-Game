#include "startup.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
startup::startup()
{
    cout << "************** 51 OYUNU **************" <<endl;
    string select = "1- Basla | 2- Kurallar ve Genel Oynanis | 3- Emegi Gecenler | 4- Yazi Rengi Secimi | 5- Cikis", choose = "Yapmak istediginiz islem:";
    string line = "--------------------------------------------------------", error = "Lutfen gecerli bir islem secin!";
    int selecting;
    donus:
    cout << line << endl;
    cout << select << endl;
    cout << choose << endl;
    cin >> selecting;
    if(selecting == 1)
    {
        system("CLS");
    }
    else if (selecting == 2)
    {
        cout << "Oyunda Joker yoktur."
                "\nOyuncu, bilgisayara karsi oynar ve oyuncunun elinde 15 adet kart vardir."
                "\nBilgisayar ise 14 adet karta sahiptir.\nKartlar 2ser 2ser dagitilir."
                "\nSon kart herkese gosterilir."
                "\nSeri ve cifte dizim program tarafindan sizin icin otomatik olarak yapilir ve size gosterilir."
                "\nKurallara aykiri hareketler icin ceza sistemi oyunda mevcut degildir."
                "\nKurallara aykiri hareket etmeyi denerseniz program sizi uyarir ve islemi engeller. "
                "\nOyunumuzdaki cifte sistemimiz pere gore degil tamamen cifte uzerinedir."
                "\nCifte acabilmek icin 4, 5, 6 veya 7 cifte sahip olmaniz gerekmektedir." << endl;
        goto donus;
    }
    else if (selecting == 5)
    {
        exit(0);
    }
    else if (selecting == 3)
    {
        cout << "Team 100 Alanlar" << endl; //Takım adını yazdırdık
        cout << "Recep GEMALMAZ, Damla Su KARADOGAN, Erdogan KILINC, Musa BUHURCU" << endl; //Takım üyelerini yazdırdık
        goto donus;
    }
    else if (selecting == 4)
    {
        int renkSecim;
        hata:
        cout << "Renkler program kapatilip acilinca sifirlanir!" << endl;
        const char *renkler[17] = {"Ust Menu", "Siyah", "Mavi", "Yesil", "Deniz Mavisi", "Kirmizi", "Mor", "Sari", "Beyaz", "Gri", "Acik Mavi", "Acik Yesil",
                                  "Acik Deniz Mavisi", "Acik Kirmizi", "Acik Mor", "Acik Sari", "Parlak Beyaz"};
        for(int i = 0; i < 17; i++)
        {
            cout << i << "-" << renkler[i] << endl;
        }
        cout << "Sectiginiz rengin numarasi: ";
        cin >> renkSecim;
        switch(renkSecim)
        {
        case 0:
            goto donus;
        case 1:
            system("color 0");
            system("CLS");
            goto donus;
        case 2:
             system("color 1");
             system("CLS");
             goto donus;
        case 3:
            system("color 2");
            system("CLS");
            goto donus;
        case 4:
            system("color 3");
            system("CLS");
            goto donus;
        case 5:
            system("color 4");
            system("CLS");
            goto donus;
        case 6:
            system("color 5");
            system("CLS");
            goto donus;
        case 7:
            system("color 6");
            system("CLS");
            goto donus;
        case 8:
            system("color 7");
            system("CLS");
            goto donus;
        case 9:
            system("color 8");
            system("CLS");
            goto donus;
        case 10:
            system("color 9");
            system("CLS");
            goto donus;
        case 11:
            system("color a");
            system("CLS");
            goto donus;
        case 12:
            system("color b");
            system("CLS");
            goto donus;
        case 13:
            system("color c");
            system("CLS");
            goto donus;
        case 14:
            system("color d");
            system("CLS");
            goto donus;
        case 15:
            system("color e");
            system("CLS");
            goto donus;
        case 16:
            system("color f");
            system("CLS");
            goto donus;
        default:
            cout << "Bilinmeyen secim! Tekrar Deneyin!" << endl;
            goto hata;
        }
    }
    else
    {
        cout << error << endl;
        goto donus;
    }
}

