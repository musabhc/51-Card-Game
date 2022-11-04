#include "startup.h"
#include "kurallar.h"
#include "renkSecim.h"
#include "crew.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
startup::startup()
{
    system("CLS");
    cout << "************** 51 OYUNU **************" << endl;
    string select = "1- Basla\n2- Kurallar ve Genel Oynanis\n3- Emegi Gecenler\n4- Yazi Rengi Secimi\n5- Cikis", choose = "Yapmak istediginiz islem: ";
    string line = "--------------------------------------------------------", error = "Lutfen gecerli bir islem secin!";
    int selecting = 0;
    cout << line << endl;
    cout << select << endl;
    cout << choose;
    while (selecting <= 0 || selecting > 5)
    {
        cin >> selecting;
        if (selecting == 1)
        {
            system("CLS");
        }
        else if (selecting == 2)
        {
            kurallar();
        }
        else if (selecting == 3)
        {
            crew();
        }
        else if (selecting == 4)
        {
            renkSecim();
        }
        else if (selecting == 5)
        {
            exit(0);
        }
        else
        {
            cout << error << endl;
        }
    }
}

