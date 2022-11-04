#include "menu.h"
#include "hand.h"
#include "per.h"
#include <iostream>

using namespace std;

int menu::getWayChoose()
{
    //Tek çift gitme
    cout << endl;
    cout << line << endl;
    cout << endl;
    cout << oneDouble;
    cout << space;
    cout << space << endl;
    cout << endl;
    cout << choose;
    cin >> wayChoose;
    return wayChoose;
}



int menu::getSelection()
{
    //Kart al-çek
    cout << line << endl;
    cout << endl;
    cout << skills << endl;
    cout << endl;
    cout << endl;
    cout << choose;
    cin >> selection;
    return selection;
}
