#ifndef MENU_H
#define MENU_H
#include <iostream>

class menu {
public:
    int getSelection();

    int getWayChoose();

    std::string choose = "Yapmak istediginiz islemi seciniz: ";

    std::string line = "--------------------------------------------------------";

    std::string space = "   ";

    std::string oneDouble = "1- Seri Dizim | 2- Cifte Dizim";

    std::string skills = "0- Yere Kart Isle | 1- Yerden Kart Cek | 2- Elden Kart Cikar | 3- Desteden Kart Cek | 4- Yere Seri Ac | 5- Yere Cift Ac";

    int selection, wayChoose;
};

#endif // MENU_H
