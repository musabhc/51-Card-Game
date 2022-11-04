#include "startup.h"
#include "renkSecim.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
renkSecim::renkSecim()
{
    int renkSecim = -1;
    system("CLS");
    cout << "Renkler program kapatilip acilinca sifirlanir!" << endl;
    const char* renkler[17] = {"Siyah", "Mavi", "Yesil", "Deniz Mavisi", "Kirmizi", "Mor", "Sari", "Beyaz", "Gri", "Acik Mavi", "Acik Yesil",
                              "Acik Deniz Mavisi", "Acik Kirmizi", "Acik Mor", "Acik Sari", "Parlak Beyaz", "Ust Menu"};
    for (int i = 0; i < 17; i++)
    {
        cout << i+1 << "-" << renkler[i] << endl;
    }
    cout << "0" << "-" << renkler[16] << endl;

    while (renkSecim < 0 || renkSecim > 17) 
    {
        cout << "Sectiginiz rengin numarasi: ";
        cin >> renkSecim;
        switch (renkSecim)
        {
        case 0:
            startup();
            break;
        case 1:
            system("color 0");
            break;

        case 2:
            system("color 1");
            break;
        case 3:
            system("color 2");
            break;
        case 4:
            system("color 3");
            break;
        case 5:
            system("color 4");
            break;
        case 6:
            system("color 5");
            break;
        case 7:
            system("color 6");
            break;
        case 8:
            system("color 7");
            break;
        case 9:
            system("color 8");
            break;
        case 10:
            system("color 9");
            break;
        case 11:
            system("color a");
            break;
        case 12:
            system("color b");
            break;
        case 13:
            system("color c");
            break;
        case 14:
            system("color d");
            break;
        case 15:
            system("color e");
            break;
        case 16:
            system("color f");
            break;
        default:
            cout << "Bilinmeyen secim! Tekrar Deneyin!" << endl;
        }
    }
    startup();
}