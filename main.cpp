#include "card.h"
#include "deck.h"
#include "hand.h"
#include "per.h"
#include "menu.h"
#include "startup.h"

bool isPcOpened = false;
bool isUserOpened = false;

void printOpenedDeckList(vector<Deck>& openedDeck) {
    for (int i = 0; i < openedDeck.size(); ++i) {
        Deck deck = openedDeck.at(i);
        deck.printDeck();
    }
    cout << endl;
}

bool hasDualDeck(vector<Deck>& openedDeck) {
    for (int i = 0; i < openedDeck.size(); ++i) {
        Deck deck = openedDeck.at(i);
        if (deck.getCards().size() == 2) {
            return true;
        }
    }
    return false;
}

bool makeSelection(Hand& hand, Deck& floor, Deck& table, vector<Deck>& openedDeck, bool isPc) //se�im ekran�
{

    string cardThrowWarning = "Once kart atmalisiniz";
    string cardCantFind = "Kart Numarasini giriniz-->";
    string cardNumberEnter = "Kart Numarasini giriniz-->";
    string serialOpenError = "Kartlarinizi acabilmeniz icin en az 51 olmalisiniz!";
    string dualOpenError = "Kartlarinizi acabilmek icin en az 5 cifte sahip olmaniz gerekmektedir!";
    string isleme = "Lutfen isleme yapmayi deneyeceginiz kart numarasini yaziniz: ";
    string floorDeckP = "Floor: ";
    bool isTurn = false;
    int selection;
    if (!isPc) //e�er s�ra bilgisayarda de�ilse men�y� se�imi al�c� fonksiyon ile beraber �a��r.
    {
        selection = menu().getSelection(); //men�n�n se�im al�c� ile �a��r�lmas�
    }
    else {
        if (hand.getIsDrawCard()) //s�ra bilgisayarda ise kart �ekip �ekmedi�ini kontrol et e�er true ise
        {
            selection = 3; //3 numaral� if�e git
        }
        else {
            if (hand.isCardHandleFunc()) {
                selection = 2; //de�ilse 2 numaral� if�e git
            }
            else {
                selection = 0;
            }

        }

    }
    if (selection == 0) {
        if (!isPc) {
            if (isUserOpened) {
                if (hand.getIsDrawCard()) {
                    int kartNumber;
                    printOpenedDeckList(openedDeck);
                    floor.printDeck();
                    cout << "Hand: " << endl;
                    cout << endl;
                    hand.printHand();
                    cout << isleme;
                    cin >> kartNumber;
                    bool cardFind = false;
                    Card foundCard = hand.getCards().at(0);
                    for (int i = 0; i < hand.getCards().size(); ++i) {
                        Card card = hand.getCards().at(i);
                        if (card.getId() == kartNumber) {
                            foundCard = card;
                            cardFind = true;
                            break;
                        }

                    }
                    if (cardFind) {
                        cout << floorDeckP << endl;
                        printOpenedDeckList(openedDeck);
                        for (int i = 0; i < openedDeck.size(); i++) {
                            Deck deck = openedDeck.at(i);
                            if (deck.getCards().size() > 2) {//seri demek oluyor
                                if ((deck.getCards().at(0).getCardNumber() ==
                                    deck.getCards().at(1).getCardNumber()) &&
                                    (deck.getCards().at(0).getCardNumber() ==
                                        foundCard.getCardNumber()) && (deck.getCards().size() < 4)) {//Renk dizili
                                    for (int j = 0; j < deck.getCards().size(); ++j) {
                                        Card card = deck.getCards().at(j);
                                        if (foundCard.getCardType() != card.getCardType()) {
                                            deck.addCardToBack(foundCard);
                                            hand.removeCard(foundCard);
                                            break;
                                        }
                                    }
                                }
                                else if ((deck.getCards().at(0).getCardNumber() !=
                                    deck.getCards().at(1).getCardNumber()) && (foundCard.getCardType() ==
                                        deck.getCards().at(
                                            0).getCardType())) {
                                    Card firstCard = deck.getCards().at(0);
                                    Card lastCard = deck.getCards().at(deck.getCards().size() - 1);
                                    if (firstCard.getCardNumber() - foundCard.getCardNumber() == 1) {
                                        deck.addCardToFront(foundCard);
                                        hand.removeCard(foundCard);
                                        break;
                                    }
                                    else if (foundCard.getCardNumber() - lastCard.getCardNumber() == 1) {
                                        deck.addCardToBack(foundCard);
                                        hand.removeCard(foundCard);
                                        break;

                                    }

                                }

                            }
                            //

                        }
                    }
                    else //kart bulunamad�ysa yani kullan�c� yanl�� numara girdiyse
                    {
                        cout << cardCantFind << endl; //kart�n bulunamad���n� kullan�c�ya bildir
                    }

                }
                else {
                    cout << "Once kart cekmelisin" << endl;
                }


            }
            else {
                cout << "Elin acik degil" << endl;
            }
        }
        else {
            if (isPcOpened) {
                if (hand.getIsDrawCard()) {
                    for (int i = 0; i < hand.getCards().size(); ++i) {
                        Card foundCard = hand.getCards().at(i);
                        cout << floorDeckP << endl;
                        printOpenedDeckList(openedDeck);
                        for (int i = 0; i < openedDeck.size(); i++) {
                            Deck deck = openedDeck.at(i);
                            if (deck.getCards().size() > 2) {//seri demek oluyor
                                if ((deck.getCards().at(0).getCardNumber() ==
                                    deck.getCards().at(1).getCardNumber()) &&
                                    (deck.getCards().at(0).getCardNumber() ==
                                        foundCard.getCardNumber()) && (deck.getCards().size() < 4)) {//Renk dizili
                                    for (int j = 0; j < deck.getCards().size(); ++j) {
                                        Card card = deck.getCards().at(j);
                                        if (foundCard.getCardType() != card.getCardType()) {
                                            deck.addCardToBack(foundCard);
                                            hand.removeCard(foundCard);
                                            break;
                                        }
                                    }
                                }
                                else if ((deck.getCards().at(0).getCardNumber() !=
                                    deck.getCards().at(1).getCardNumber()) && (foundCard.getCardType() ==
                                        deck.getCards().at(
                                            0).getCardType())) {
                                    Card firstCard = deck.getCards().at(0);
                                    Card lastCard = deck.getCards().at(deck.getCards().size() - 1);
                                    if (firstCard.getCardNumber() - foundCard.getCardNumber() == 1) {
                                        deck.addCardToFront(foundCard);
                                        hand.removeCard(foundCard);
                                        break;
                                    }
                                    else if (foundCard.getCardNumber() - lastCard.getCardNumber() == 1) {
                                        deck.addCardToBack(foundCard);
                                        hand.removeCard(foundCard);
                                        break;

                                    }

                                }

                            }
                            //

                        }

                    }


                }
                else {
                    //pc daha kart cekmemis
                }


            }
            else {
                //pcnin eli acik degil
            }
        }
        hand.setIsCardHandle(true);


    }
    else if (selection == 1) {
        if (!hand.getIsDrawCard()) //e�er
        {
            cout << cardThrowWarning << endl; // kart �ekmesi i�in uyar� ver
            return false;
        }
        else //e�er kart �ekilmi�se
        {
            Card floorCard = floor.getCards().at(
                0); //yerdeki kartlar� temsilen bir obje olu�tur bu objeye destenin en ba��ndaki kart� ekle
            hand.addCardToBack(floorCard); // yerdeki kart� eldeki kartlar�n en sonuna ekle
            floor.removeCard(floorCard); // yerdeki kart� sil ��nk� ele ald�k
            hand.setIsDrawCard(false); // kart �ekti�ini false yap
            if (!isPc) //s�ra bilgisayarda m� kontrol et
            {
                int chosenWay = menu().getWayChoose(); //�ift mi seri mi gidilecek se�im yap
                if (chosenWay == 1) // seri git
                {
                    hand.setIsSerialHand(true); //elin seri oldu�unu bildir
                    hand.alignSerial(); //kartlar� seri olarak diz
                }
                else {
                    hand.setIsSerialHand(false); //seri gidilmeyece�ini bildir
                    hand.alignDual(); // kartlar� �ifte olarak diz
                }
            }

        }

    }
    else if (selection == 3) //bilgisayar kart �ekmi�se
    {
        if (!hand.getIsDrawCard()) // kart �ekmediyse uyar� ver
        {
            cout << cardThrowWarning << endl; //kart �ekmesi i�in uyar�
            return false;
        }
        else //kart �ekmi�se
        {
            Card tableCard = table.getCards().at(
                0);  //masa kart� i�in obje olu�turup kartlar�n en ba��ndaki kart� masaya koy
            hand.addCardToBack(tableCard); //masadaki kart� ele ekle
            table.removeCard(tableCard); //masadaki kart� sil ��nk� elimizde
            hand.setIsDrawCard(false); //kart �ekmedi olarak bilgisayara g�ster
            if (!isPc) //s�ra bilgisayarda de�ilse
            {
                int chosenWay = menu().getWayChoose(); //sat�r 40�da a��klad�m.
                if (chosenWay == 1) {
                    hand.setIsSerialHand(true);
                    hand.alignSerial();
                }
                else {
                    hand.setIsSerialHand(false);
                    hand.alignDual();
                }
            }

        }

    }
    else if (selection == 2) //kart �ekmediyse
    {
        if (hand.getIsDrawCard()) //tekrar kontrol
        {
            cout << cardThrowWarning << endl; //kart �ekmesi i�in uyar� ver
            return false;
        }
        else //�ektiyse
        {
            while (true) {
                int kartNumber;
                if (!isPc) //s�ra bilgisayarda de�ilse
                {
                    hand.printHand(); //eldeki kartlar� yazd�r
                    cout << cardNumberEnter; //hangi kart�n at�laca��n� se�mesini s�yl�yor
                    cin >> kartNumber; // se�imi al�yor
                    bool cardFind = false; //kart mevcut mu
                    for (int i = 0; i <
                        hand.getCards().size(); ++i) //kartlar� kontrol ederek kullan�c�n�n yazd��� kart�n mevcut olup olmad���na bak�yor
                    {
                        Card card = hand.getCards().at(i); //her bir kart� card ad�ndaki bir objeye at�yor
                        if (card.getId() ==
                            kartNumber) //e�er kullan�c�n�n yazd��� numara ile objedeki numara uyu�uyorsa
                        {
                            floor.addCardToFront(card); //kart� yere at�yor
                            hand.removeCard(card); //kart� elden siliyor
                            cardFind = true; //kart�n bulundu�unu sisteme bildiriyor
                            break; //a�amadan ��k�yor
                        }

                    }
                    if (cardFind) //e�er kart bulunduysa
                    {
                        hand.setIsDrawCard(true); //kart �ekti diye sisteme bildiriyor
                        int chosenWay = menu().getWayChoose(); //kullan�c�n�n yapaca�� se�im i�in men�y� �a��r�yor.
                        if (chosenWay == 1) //40. sat�r
                        {
                            hand.setIsSerialHand(true);
                            hand.alignSerial();
                        }
                        else {
                            hand.setIsSerialHand(false);
                            hand.alignDual();
                        }
                        break;
                    }
                    else //kart bulunamad�ysa yani kullan�c� yanl�� numara girdiyse
                    {
                        cout << cardCantFind << endl; //kart�n bulunamad���n� kullan�c�ya bildir
                    }
                }
                else //s�ra bilgisayarda ise
                {
                    if (!hand.getOtherCardHand().getCards().empty()) {
                        Card card = hand.getOtherCardHand().getCards().at(0); //bilgisayar� bir kart al�yor
                        floor.addCardToFront(card); //yere kart at�yor
                        hand.removeCard(card); //elinden att��� kart siliniyor
                        hand.setIsDrawCard(true); //bilgisayar�n kart �ekti�i sisteme bildiriliyor.
                        break;
                    }
                    //else | pc kazan�r lakin bunu tur d�ng�s�n�n en ba��nda kontrol edece�iz.
                }
            }
            isTurn = true; //tur bitti�ini sisteme bildir
        }
        hand.setIsCardHandle(false);

    }
    else if (selection == 4) {
        int total = 0; //ge�ici de�i�kenler tan�mlad�k
        //hand.alignSerial(); SER� D�Z�M OLMAZSA D�YE

        for (int k = 0; k < hand.getSerialAlignedHand().size(); k++) //seri kartlar� tar�yoruz
        {
            Deck deck; //ge�ici deck olu�turuyoruz
            deck = hand.getSerialAlignedHand().at(k); //ge�ici de�i�kene ata
            for (int i = 0; i < deck.getCards().size(); i++) //ge�ici de�i�keni taramaya ba�la
            {
                total += deck.getCards().at(i).getCardNumber(); //tempe ilk kart�n numaras�n� at�yoruz
            }
        }
        cout << total << endl; //TOTAL

        if (total >= 51) {
            cout << "SERI ACTIK" << endl;
            isUserOpened = true;
            for (int k = 0; k < hand.getSerialAlignedHand().size(); k++) {
                Deck deck;
                deck = hand.getSerialAlignedHand().at(k);
                openedDeck.push_back(deck);
                for (int i = 0; i < deck.getCards().size(); ++i) {
                    Card card = deck.getCards().at(i);
                    floor.addCardToBack(card);
                    hand.removeCard(card);
                }
            }
            hand.clearSerialHand();

        }
        else {
            cout << serialOpenError << endl;
        }
        return false;
    }
    else if (selection == 5) {
        if (hand.getDualAlignedHand().size() >= 5) {
            cout << "CIFT ACTIK" << endl;
            isUserOpened = true;
            for (int k = 0; k < hand.getDualAlignedHand().size(); k++) {
                Deck deck;
                deck = hand.getDualAlignedHand().at(k);
                openedDeck.push_back(deck);
                for (int i = 0; i < deck.getCards().size(); ++i) {
                    Card card = deck.getCards().at(i);
                    hand.removeCard(card);
                }
            }
            hand.clearDualHand();
        }
        else {
            cout << dualOpenError << endl;
        }
        return false;

    }
    return isTurn;
}

int main() {
    string userHandS = "MY Hand", pcHandS = "PC Hand";
    string userDeck = "MY Deck", pcDeck = "PC Deck";
    string restart = "If you want to restart game press 1 and press anything else to exit";
    string pcWon = "PC won the game! Press 1 to restart game and press anything else to exit: ";
    string userWon = "You won the game! Press 1 to restart game and press anything else to exit: ";
    string draw = "Game draw! Press 1 to restart game and press anything else to exit: ";
    string line = "--------------------------------------------------------------------", lastCard = "---------- SON KART----------";
    Deck table, floor; // masa ve yeri tan�mla
    vector<Deck> openedDecks;
    // table t�m kartlar�n bulundu�u
    Hand my, pc; //kullan�c� ve bilgisayar�n ellerinin objelerini olu�tur
restart:
    table.clear();
    my.clear();
    pc.clear();
    floor.clear();
    startup();
    //deck olusturma
    for (int i = 0; i < 104; ++i) {
        CardType cardType = maca;
        if (i / 13 == 0 || i / 13 == 4) {
            cardType = maca;
        }
        else if (i / 13 == 1 || i / 13 == 5) {
            cardType = sinek;
        }
        else if (i / 13 == 2 || i / 13 == 6) {
            cardType = kupa;
        }
        else if (i / 13 == 3 || i / 13 == 7) {
            cardType = karo;
        }
        Card card(i, (i % 13) + 2, cardType);
        table.addCardToBack(card);
    }

    //Kartlar�n kar�lmas�
    table.mixDeck(); //kartlar� kar��t�rt
    //table.printDeck(); //kartlar� yazd�r TEST �GES�

    //Kart secimi
    Card random1 = table.getRandomCard(); //rastgele bir kart se�
    table.moveToEnd(random1); //bunu en sona at
    cout << endl; //bo�luk b�rak
    // table.printDeck(); // masadaki kartlar� (b�t�n desteyi) yazd�r. TEST �GES�

    //Kartlar� da��t
    int myHandSize = my.getCards().size(); //eldeki kartlar�n miktar�n� al
    for (int i = 0; i < 28; ++i) {
        Card card = table.getCards().at(i);//masadaki i. kartlar� al�p card objesine at�yor
        if (i % 4 == 0 ||
            i % 4 == 1) //i�nin 4�e tam b�l�m�n� �zel olarak kontrol ediyor yani 2 kart pcye 2 kart ise bize verecek
        {
            if (myHandSize == 1 && i == 0) {
                continue;
            }
            if (myHandSize == 2 && i == 1) {
                continue;
            }
            my.addCardToBack(card); //bize kart verdi
            table.removeCard(card); //desteden o kart� sildi
        }
        else if (i % 4 == 2 || i % 4 == 3) {
            pc.addCardToBack(card); //pcye verdi
            table.removeCard(card); //desteden sildi
        }
    }
    //fazla karti ekleme (15. kart)
    Card card = table.getCards().at(0); //fazla kart� objeye atay�p
    my.addCardToBack(card); // bizim destemize ekledi
    table.removeCard(card); //ve desteden sildi

    cout << endl;
    cout << lastCard << endl; //destenin sonundaki kart�n yaz�laca��n� bildiren string

    table.getCards().at(table.getCards().size() - 1).printCard(); //destenin en sonundaki kart� yazd�r�yoruz

    cout << endl;
    cout << endl;

    cout << userDeck << endl; //MY Hand yaz�s�
    cout << line << endl; // "----"ler

    my.printDeck(); // kendi destemizi yazd�rd�k

    /*

    cout << endl;
    cout << endl;

    cout << pcDeck << endl; // Bilgisayar�n destesi
    cout << line << endl; // "---"ler

    pc.printDeck(); //bilgisayar�n destesi yaz�ld�

    */

    int chosenWay = menu().getWayChoose(); //tek-�ift gidi� sorgusu
    if (chosenWay == 1) //40.sat�r
    {
        my.setIsSerialHand(true);
        my.alignSerial();
    }
    else {
        my.setIsSerialHand(false);
        my.alignDual();
    }

    cout << userHandS << endl; //elimizi bast�raca��z
    my.printHand(); //elimizi bast�rd�k

    cout << endl;
    cout << endl;

    cout << pcHandS << endl;
    pc.setIsSerialHand(true);
    pc.alignSerial();
    //pc.printHand(); //test �gesi

    //OYUNUN OYNANMASI
    int turn = 0; //TUR SAYISI 0DAN BA�LAR
    my.setIsDrawCard(false); // kart �ekmedi�imiz sisteme bildirilir
    while (true) {
        if (my.getCards().size() == 0) {
            int s;
            cout << userWon << endl;
            cin >> s;
            if (s == 1) {
                goto restart;
            }
            else {
                exit(1);
            }
        }
        else if (pc.getCards().empty()) {
            int s;
            cout << pcWon << endl;
            cin >> s;
            if (s == 1) {
                goto restart;
            }
            else {
                exit(1);
            }
        }
        else if (table.getCards().empty()) {
            if (isUserOpened == false && isPcOpened == false) {
                cout << "Game Draw" << endl;
                int last;
                cout << restart << endl;
                cin >> last;
                if (last == 1) {
                    goto restart;
                }
                else {
                    exit(1);
                }
            }
            else if (isUserOpened == true && isPcOpened == false) {
                int s;
                cout << userWon << endl;
                cin >> s;
                if (s == 1) {
                    goto restart;
                }
                else {
                    exit(1);
                }
            }
            else if (isUserOpened == false && isPcOpened == true) {
                int s;
                cout << pcWon << endl;
                cin >> s;
                if (s == 1) {
                    goto restart;
                }
                else {
                    exit(1);
                }
            }
            else if (isUserOpened == true && isPcOpened == true) {
                int userTotal = 0, pcTotal = 0;
                for (int i = 0; i < my.getCards().size(); i++) {
                    userTotal += my.getCards().at(i).getCardNumber();
                }
                for (int i = 0; i < pc.getCards().size(); i++) {
                    pcTotal += pc.getCards().at(i).getCardNumber();
                }
                if (userTotal < pcTotal) {
                    int s;
                    cout << userWon << endl;
                    cin >> s;
                    if (s == 1) {
                        goto restart;
                    }
                    else {
                        exit(1);
                    }
                }
                else if (pcTotal < userTotal) {
                    int s;
                    cout << pcWon << endl;
                    cin >> s;
                    if (s == 1) {
                        goto restart;
                    }
                    else {
                        exit(1);
                    }
                }
                else {
                    int s;
                    cout << draw << endl;
                    cin >> s;
                    if (s == 1) {
                        goto restart;
                    }
                    else {
                        exit(1);
                    }
                }
            }
        }
        if (turn % 2 == 0) //bizim turumuz
        {
            bool isTurn = makeSelection(my, floor, table, openedDecks, false);
            cout << userHandS << endl;
            my.printHand();
            if (isTurn) {
                turn += 1;
            }
        }
        else {
            //pcnin s�ras�
            bool isTurn = makeSelection(pc, floor, table, openedDecks, true);
            cout << pcHandS << endl;
            pc.setIsSerialHand(true);
            pc.alignSerial();
            //pc.printHand(); //TEST �GES�
            if (isTurn) {
                turn += 1;
            }
        }
    }


    //    my.alignSerial();
    //    pc.alignSerial();


    per(my, pc);
    cout << endl;
    menu();

}


