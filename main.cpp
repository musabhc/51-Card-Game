#include "card.h"
#include "deck.h"
#include "hand.h"
#include "per.h"
#include "menu.h"
#include "startup.h"

bool isPcOpened = false;
bool isUserOpened = false;

void printOpenedDeckList(vector<Deck> &openedDeck) {
    for (int i = 0; i < openedDeck.size(); ++i) {
        Deck deck = openedDeck.at(i);
        deck.printDeck();
    }
    cout << endl;
}

bool hasDualDeck(vector<Deck> &openedDeck) {
    for (int i = 0; i < openedDeck.size(); ++i) {
        Deck deck = openedDeck.at(i);
        if (deck.getCards().size() == 2) {
            return true;
        }
    }
    return false;
}

bool makeSelection(Hand &hand, Deck &floor, Deck &table, vector<Deck> &openedDeck, bool isPc) //seçim ekranı
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
    if (!isPc) //eğer sıra bilgisayarda değilse menüyü seçimi alıcı fonksiyon ile beraber çağır.
    {
        selection = menu().getSelection(); //menünün seçim alıcı ile çağırılması
    } else {
        if (hand.getIsDrawCard()) //sıra bilgisayarda ise kart çekip çekmediğini kontrol et eğer true ise
        {
            selection = 3; //3 numaralı if´e git
        } else {
            if (hand.isCardHandleFunc()) {
                selection = 2; //değilse 2 numaralı if´e git
            } else {
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
                                } else if ((deck.getCards().at(0).getCardNumber() !=
                                            deck.getCards().at(1).getCardNumber()) && (foundCard.getCardType() ==
                                                                                       deck.getCards().at(
                                                                                               0).getCardType())) {
                                    Card firstCard = deck.getCards().at(0);
                                    Card lastCard = deck.getCards().at(deck.getCards().size() - 1);
                                    if (firstCard.getCardNumber() - foundCard.getCardNumber() == 1) {
                                        deck.addCardToFront(foundCard);
                                        hand.removeCard(foundCard);
                                        break;
                                    } else if (foundCard.getCardNumber() - lastCard.getCardNumber() == 1) {
                                        deck.addCardToBack(foundCard);
                                        hand.removeCard(foundCard);
                                        break;

                                    }

                                }

                            }
                            //

                        }
                    } else //kart bulunamadıysa yani kullanıcı yanlış numara girdiyse
                    {
                        cout << cardCantFind << endl; //kartın bulunamadığını kullanıcıya bildir
                    }

                } else {
                    cout << "Once kart cekmelisin" << endl;
                }


            } else {
                cout << "Elin acik degil" << endl;
            }
        } else {
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
                                } else if ((deck.getCards().at(0).getCardNumber() !=
                                            deck.getCards().at(1).getCardNumber()) && (foundCard.getCardType() ==
                                                                                       deck.getCards().at(
                                                                                               0).getCardType())) {
                                    Card firstCard = deck.getCards().at(0);
                                    Card lastCard = deck.getCards().at(deck.getCards().size() - 1);
                                    if (firstCard.getCardNumber() - foundCard.getCardNumber() == 1) {
                                        deck.addCardToFront(foundCard);
                                        hand.removeCard(foundCard);
                                        break;
                                    } else if (foundCard.getCardNumber() - lastCard.getCardNumber() == 1) {
                                        deck.addCardToBack(foundCard);
                                        hand.removeCard(foundCard);
                                        break;

                                    }

                                }

                            }
                            //

                        }

                    }


                } else {
                    //pc daha kart cekmemis
                }


            } else {
                //pcnin eli acik degil
            }
        }
        hand.setIsCardHandle(true);


    } else if (selection == 1) {
        if (!hand.getIsDrawCard()) //eğer
        {
            cout << cardThrowWarning << endl; // kart çekmesi için uyarı ver
            return false;
        } else //eğer kart çekilmişse
        {
            Card floorCard = floor.getCards().at(
                    0); //yerdeki kartları temsilen bir obje oluştur bu objeye destenin en başındaki kartı ekle
            hand.addCardToBack(floorCard); // yerdeki kartı eldeki kartların en sonuna ekle
            floor.removeCard(floorCard); // yerdeki kartı sil çünkü ele aldık
            hand.setIsDrawCard(false); // kart çektiğini false yap
            if (!isPc) //sıra bilgisayarda mı kontrol et
            {
                int chosenWay = menu().getWayChoose(); //çift mi seri mi gidilecek seçim yap
                if (chosenWay == 1) // seri git
                {
                    hand.setIsSerialHand(true); //elin seri olduğunu bildir
                    hand.alignSerial(); //kartları seri olarak diz
                } else {
                    hand.setIsSerialHand(false); //seri gidilmeyeceğini bildir
                    hand.alignDual(); // kartları çifte olarak diz
                }
            }

        }

    } else if (selection == 3) //bilgisayar kart çekmişse
    {
        if (!hand.getIsDrawCard()) // kart çekmediyse uyarı ver
        {
            cout << cardThrowWarning << endl; //kart çekmesi için uyarı
            return false;
        } else //kart çekmişse
        {
            Card tableCard = table.getCards().at(
                    0);  //masa kartı için obje oluşturup kartların en başındaki kartı masaya koy
            hand.addCardToBack(tableCard); //masadaki kartı ele ekle
            table.removeCard(tableCard); //masadaki kartı sil çünkü elimizde
            hand.setIsDrawCard(false); //kart çekmedi olarak bilgisayara göster
            if (!isPc) //sıra bilgisayarda değilse
            {
                int chosenWay = menu().getWayChoose(); //satır 40´da açıkladım.
                if (chosenWay == 1) {
                    hand.setIsSerialHand(true);
                    hand.alignSerial();
                } else {
                    hand.setIsSerialHand(false);
                    hand.alignDual();
                }
            }

        }

    } else if (selection == 2) //kart çekmediyse
    {
        if (hand.getIsDrawCard()) //tekrar kontrol
        {
            cout << cardThrowWarning << endl; //kart çekmesi için uyarı ver
            return false;
        } else //çektiyse
        {
            while (true) {
                int kartNumber;
                if (!isPc) //sıra bilgisayarda değilse
                {
                    hand.printHand(); //eldeki kartları yazdır
                    cout << cardNumberEnter; //hangi kartın atılacağını seçmesini söylüyor
                    cin >> kartNumber; // seçimi alıyor
                    bool cardFind = false; //kart mevcut mu
                    for (int i = 0; i <
                                    hand.getCards().size(); ++i) //kartları kontrol ederek kullanıcının yazdığı kartın mevcut olup olmadığına bakıyor
                    {
                        Card card = hand.getCards().at(i); //her bir kartı card adındaki bir objeye atıyor
                        if (card.getId() ==
                            kartNumber) //eğer kullanıcının yazdığı numara ile objedeki numara uyuşuyorsa
                        {
                            floor.addCardToFront(card); //kartı yere atıyor
                            hand.removeCard(card); //kartı elden siliyor
                            cardFind = true; //kartın bulunduğunu sisteme bildiriyor
                            break; //aşamadan çıkıyor
                        }

                    }
                    if (cardFind) //eğer kart bulunduysa
                    {
                        hand.setIsDrawCard(true); //kart çekti diye sisteme bildiriyor
                        int chosenWay = menu().getWayChoose(); //kullanıcının yapacağı seçim için menüyü çağırıyor.
                        if (chosenWay == 1) //40. satır
                        {
                            hand.setIsSerialHand(true);
                            hand.alignSerial();
                        } else {
                            hand.setIsSerialHand(false);
                            hand.alignDual();
                        }
                        break;
                    } else //kart bulunamadıysa yani kullanıcı yanlış numara girdiyse
                    {
                        cout << cardCantFind << endl; //kartın bulunamadığını kullanıcıya bildir
                    }
                } else //sıra bilgisayarda ise
                {
                    if (!hand.getOtherCardHand().getCards().empty()) {
                        Card card = hand.getOtherCardHand().getCards().at(0); //bilgisayarı bir kart alıyor
                        floor.addCardToFront(card); //yere kart atıyor
                        hand.removeCard(card); //elinden attığı kart siliniyor
                        hand.setIsDrawCard(true); //bilgisayarın kart çektiği sisteme bildiriliyor.
                        break;
                    }
                    //else | pc kazanır lakin bunu tur döngüsünün en başında kontrol edeceğiz.
                }
            }
            isTurn = true; //tur bittiğini sisteme bildir
        }
        hand.setIsCardHandle(false);

    } else if (selection == 4) {
        int total = 0; //geçici değişkenler tanımladık
        //hand.alignSerial(); SERİ DİZİM OLMAZSA DİYE

        for (int k = 0; k < hand.getSerialAlignedHand().size(); k++) //seri kartları tarıyoruz
        {
            Deck deck; //geçici deck oluşturuyoruz
            deck = hand.getSerialAlignedHand().at(k); //geçici değişkene ata
            for (int i = 0; i < deck.getCards().size(); i++) //geçici değişkeni taramaya başla
            {
                total += deck.getCards().at(i).getCardNumber(); //tempe ilk kartın numarasını atıyoruz
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

        } else {
            cout << serialOpenError << endl;
        }
        return false;
    } else if (selection == 5) {
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
        } else {
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
    Deck table, floor; // masa ve yeri tanımla
    vector<Deck> openedDecks;
    // table tüm kartların bulunduğu
    Hand my, pc; //kullanıcı ve bilgisayarın ellerinin objelerini oluştur
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
        } else if (i / 13 == 1 || i / 13 == 5) {
            cardType = sinek;
        } else if (i / 13 == 2 || i / 13 == 6) {
            cardType = kupa;
        } else if (i / 13 == 3 || i / 13 == 7) {
            cardType = karo;
        }
        Card card(i, (i % 13) + 2, cardType);
        table.addCardToBack(card);
    }

    //Kartların karılması
    table.mixDeck(); //kartları karıştırt
    //table.printDeck(); //kartları yazdır TEST ÖGESİ

    //Kart secimi
    Card random1 = table.getRandomCard(); //rastgele bir kart seç
    table.moveToEnd(random1); //bunu en sona at
    cout << endl; //boşluk bırak
    // table.printDeck(); // masadaki kartları (bütün desteyi) yazdır. TEST ÖGESİ

    //Kartları dağıt
    int myHandSize = my.getCards().size(); //eldeki kartların miktarını al
    for (int i = 0; i < 28; ++i) {
        Card card = table.getCards().at(i);//masadaki i. kartları alıp card objesine atıyor
        if (i % 4 == 0 ||
            i % 4 == 1) //i´nin 4´e tam bölümünü özel olarak kontrol ediyor yani 2 kart pcye 2 kart ise bize verecek
        {
            if (myHandSize == 1 && i == 0) {
                continue;
            }
            if (myHandSize == 2 && i == 1) {
                continue;
            }
            my.addCardToBack(card); //bize kart verdi
            table.removeCard(card); //desteden o kartı sildi
        } else if (i % 4 == 2 || i % 4 == 3) {
            pc.addCardToBack(card); //pcye verdi
            table.removeCard(card); //desteden sildi
        }
    }
    //fazla karti ekleme (15. kart)
    Card card = table.getCards().at(0); //fazla kartı objeye atayıp
    my.addCardToBack(card); // bizim destemize ekledi
    table.removeCard(card); //ve desteden sildi

    cout << endl;
    cout << lastCard << endl; //destenin sonundaki kartın yazılacağını bildiren string

    table.getCards().at(table.getCards().size() - 1).printCard(); //destenin en sonundaki kartı yazdırıyoruz

    cout << endl;
    cout << endl;

    cout << userDeck << endl; //MY Hand yazısı
    cout << line << endl; // "----"ler

    my.printDeck(); // kendi destemizi yazdırdık

    /*

    cout << endl;
    cout << endl;

    cout << pcDeck << endl; // Bilgisayarın destesi
    cout << line << endl; // "---"ler

    pc.printDeck(); //bilgisayarın destesi yazıldı

    */

    int chosenWay = menu().getWayChoose(); //tek-çift gidiş sorgusu
    if (chosenWay == 1) //40.satır
    {
        my.setIsSerialHand(true);
        my.alignSerial();
    } else {
        my.setIsSerialHand(false);
        my.alignDual();
    }

    cout << userHandS << endl; //elimizi bastıracağız
    my.printHand(); //elimizi bastırdık

    cout << endl;
    cout << endl;

    cout << pcHandS << endl;
    pc.setIsSerialHand(true);
    pc.alignSerial();
    //pc.printHand(); //test ögesi

    //OYUNUN OYNANMASI
    int turn = 0; //TUR SAYISI 0DAN BAŞLAR
    my.setIsDrawCard(false); // kart çekmediğimiz sisteme bildirilir
    while (true) {
        if (my.getCards().size() == 0) {
            int s;
            cout << userWon << endl;
            cin >> s;
            if (s == 1) {
                goto restart;
            } else {
                exit(1);
            }
        } else if (pc.getCards().empty()) {
            int s;
            cout << pcWon << endl;
            cin >> s;
            if (s == 1) {
                goto restart;
            } else {
                exit(1);
            }
        } else if (table.getCards().empty()) {
            if (isUserOpened == false && isPcOpened == false) {
                cout << "Game Draw" << endl;
                int last;
                cout << restart << endl;
                cin >> last;
                if (last == 1) {
                    goto restart;
                } else {
                    exit(1);
                }
            } else if (isUserOpened == true && isPcOpened == false) {
                int s;
                cout << userWon << endl;
                cin >> s;
                if (s == 1) {
                    goto restart;
                } else {
                    exit(1);
                }
            } else if (isUserOpened == false && isPcOpened == true) {
                int s;
                cout << pcWon << endl;
                cin >> s;
                if (s == 1) {
                    goto restart;
                } else {
                    exit(1);
                }
            } else if (isUserOpened == true && isPcOpened == true) {
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
                    } else {
                        exit(1);
                    }
                } else if (pcTotal < userTotal) {
                    int s;
                    cout << pcWon << endl;
                    cin >> s;
                    if (s == 1) {
                        goto restart;
                    } else {
                        exit(1);
                    }
                } else {
                    int s;
                    cout << draw << endl;
                    cin >> s;
                    if (s == 1) {
                        goto restart;
                    } else {
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
        } else {
            //pcnin sırası
            bool isTurn = makeSelection(pc, floor, table, openedDecks, true);
            cout << pcHandS << endl;
            pc.setIsSerialHand(true);
            pc.alignSerial();
            //pc.printHand(); //TEST ÖGESİ
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


