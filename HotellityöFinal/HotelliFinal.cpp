// Eetu Tuominen
// Hotellityö
//4p

// Otetaan käyttöön kirjastot
#include <iostream> // Cin ja Cout 
#include <cmath>
#include <vector> // Vektorit käyttöön.
#include <random> // Satunaislukujen luontiin
#include <algorithm> // Saadaan muutama ohjelmassa hyödynnetty komento
#include <string> // getline

using namespace std; // Otetaan käyttöön standardi- kirjasto, ei siis tarivta std:: etuliitettä

struct HotelliHuone {  // Luodaan struct- hotellihuoneelle. Tällä saadaan varattua yksittäisen hotellihuoneen tiedot.
    double huoneNumero;
    string huoneTyyppi;
    bool varattu;
    string varaaja;
    int oidenMaara;
    double hintaPerYo;
    int varausnumero;
};

int varausNumero(vector<HotelliHuone>& huoneet) { // Ensimmäinen aliohjelma. Tällä luodaan uniikki varausnumero jokaiselle huoneelle. 
    while (true) { // While- loop jolla tarkistetaan että lukua ei ole käytetty aiemmin


        // Tässä satunaislukugeneraattori, jota käytän ohjelmassa useita kertoja

        random_device random; // Luodaan "siemen" lukugeneraattorille
        mt19937 generaattori(random()); // Alustetaan satunaisnumero
        uniform_int_distribution<> vali(10000, 99999); // Asetetaan väli, jolle luku arvotaan
        int luku = vali(generaattori); // Annetaan kokonaislukumuuttujalle 'luku' arvoksi generaattorin luoma luku.


        /* Seuraavassa rivissä käytän muuttujaa auto, joka on minulle uusi tuttavuus. 
        Käytänössä rivi toimii niin, että se etsii 'huoneet' nimiseltä kokoelmalta alusta loppuun lukua, jonka generaattori loi.
        Tämän koodin syntaksi vaatii todella rankkaa stack overflown kaivelua sekä tekoälyn apua, että ymmärsin sen toiminnan. 
        Tästä lisää koodin esitelmässä.*/

        auto varattuNo = find_if(huoneet.begin(), huoneet.end(), [luku](const HotelliHuone& huone) { 
            return huone.varausnumero == luku;
            });

        if (varattuNo == huoneet.end()) { // Jos varattuNo tutkii loppuun asti (huoneet.end) toteaa se, että lukua ei löydy ja sitä voi käyttää.
            return luku; 
        }
    } // Jos luku löytyi jo, pyrii tämä while loop siihen asti, että uniikki luku syntyy.
}

void viivat() { // Aliohjelma jonka loin tekemään viivan, ettei tarvitse kirjoittaa. Hiemnan turha, mutta hyvää harjoitusta silti.
    cout << endl << "===&&&===&&&===&&&===&&&===" << endl;
}


int huoneidenArvonta() { // Yksinkertain aliohjelma, joka arpoo huoneiden määrän
    random_device random;
    mt19937 generaattori(random());
    uniform_int_distribution<> vali(20, 150);
    return 2 * vali(generaattori); // kertomalla luku 2 varmistetaan, että se on parillinen
}

double laskeAlennus(double alkuperainenHinta) { // Aliohjelma alennuksen arpomiseksi ja laskemiseksi.
    random_device random; // Aiemmin selitetty
    mt19937 generaattori(random());
    uniform_int_distribution<> vali(0, 2); // Arpoo nyt luvun 0 1 tai 2, jonka mukaan valitaan alennus
    int aleprossa = vali(generaattori);
    double uusiHinta;

    if (aleprossa == 0) { // Jos arvottiin 0, ei tule alennusta
        uusiHinta = alkuperainenHinta;
        cout << "Valitettavasti et saanut alennusta. Hinta on " << alkuperainenHinta << " Euroa." << endl;
    }
    else if (aleprossa == 1) { // Jos arvottiin 1 tulee 10% ale, eli luku kerrotaan 0.9
        uusiHinta = alkuperainenHinta * 0.9;
        cout << "Sait alennusta 10 %. Hinta on " << uusiHinta << " Euroa." << endl;
    }
    else { // Jos arvottiin 2, tulee 20% alea, eli hinta kerrotaan 0,8
        uusiHinta = alkuperainenHinta * 0.8;
        cout << "Sait alennusta 20 %. Onneksi olkoon! Hinta on " << uusiHinta << " Euroa." << endl;
    }

    return uusiHinta; // Alihojelma palauttaa hotellihuoneen hinnan alennuksen jälkeen
}

bool onVapaa(const HotelliHuone& huone) { // Tarkistaa vektorilta onko huone varattu. Const muuttujaa käytetään siksi, ettei aliohjelma vahingossa mene virhetilaan ja käytä väärää dataa
    return !huone.varattu;  // Tässä ! edessä, koska structissa josta ohjelma katsoo huone.varattu arvoa, on true jos varattu. Nyt ohjelma palauttaa siis sen negaation.
}

void varaaHuone(vector<HotelliHuone>& huoneet, int huoneTyyppi) {

    // Taas tuttu satunaislukugeneraattori, pienellä twistillä
    random_device random;
    mt19937 generaattori(random());
    shuffle(huoneet.begin(), huoneet.end(), generaattori); // Shuffle komento sekoittaa vektorin sisällön siten, että sitä katsellaan satunaisessa järjestyksessä

    auto etsinta = find_if(huoneet.begin(), huoneet.end(), onVapaa); // Find if komento etsii annetulta väliltä ensimmäisen kohdan, joka palauttaa onVapaa aliohjelmaa käyttäen arvon 'true'

    if (etsinta != huoneet.end()) { // Tarkistaa, että äskeinen ohjelma löysi vapaan huoneen, eikä palauttanut vain viimeistä mahdollista arvoa
        cout << "Anna nyt nimi, jolla huone varataan: ";
        string nimi;
        cin.ignore(); 
        getline(cin, nimi); // Otetaan talteen käyttäjän antama tieto, ylempi cin.ignore poistaa mahdolliset ylimääräiset tiedot.

        int yot;
        while (true) { // While- loop kysyy yömäärää kunnen käyttäjä antaa positiivisen kokonaisluvun
            cout << "Montako yötä haluatte yöpyä?" << endl;
            cin >> yot;

            // Seuraava koodinpala aiheutti ongelmia. En millään meinannut löytää toimivaa komentoa tarkistamaan lukua ja sitten tyhjentämään sisääntullutta tietoa.

            if (cin.fail() || yot <= 0) { // Tarkistaa että annettiin kokonaisluku ja että se on enemmän kuin 0
                cin.clear(); // Jos ei annettu oiken, tyhjennetään saatu tieto rekisteristä ja aloitetaan alusta 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Tämä kertoo input streamille, että tietyt ehdot täyttävä teksti heitetään pois.
                // Ylemmän rivin sisältö tarkoittaa sitä, että kaikki merkit ja tieto heitetään pois seuraavaan rivinvaihtoon tai siihen että kaikki merkit on poistettu asti
                cout << "Virheellinen syöte. Syötä positiivinen kokonaisluku." << endl;
            }
            else {
                break; // Jos luku on sopiva poistutaan while- loopista
            }
        }

        double uusiHinta = laskeAlennus(etsinta->hintaPerYo); // Lasketaan muuttujalle uusiHinta arvo käyttäen aliohjelmaa laskeAlennus


        // Tässä näkyy yksi kohdista, missä tekoälyn avulla opin uuden tavan optimoida koodia. Lisää tästä esitelmässä
        etsinta->varattu = true;  // Viedään arvoja structille
        etsinta->varaaja = nimi;
        etsinta->oidenMaara = yot;
        etsinta->varausnumero = varausNumero(huoneet);// Viedään aliohjelmalla luotu varausnumero

        viivat();
        // Printtaillaan tekstiä
        cout << "Varattu huone numero " << etsinta->huoneNumero
            << " nimellä " << etsinta->varaaja
            << " " << etsinta->oidenMaara << " yöksi." << endl
            << "Huoneen hinta yöltä on: " << uusiHinta << " Euroa." << endl
            << "Kokonaishinta: " << uusiHinta * yot << " Euroa." << endl
            << "Varausnumerosi: " << etsinta->varausnumero << endl;
    }
    else { // jos  huoneTyyppi on 1 ja huoneet on varattu tulostetaan vaihtoehto ennen ':' merkkiä, jos huonetyyppi != 1 tulostetaan jälempi vaihtoehto
        cout << (huoneTyyppi == 1 ? "Kaikki yhden hengen huoneet ovat varattuja."
            : "Kaikki kahden hengen huoneet ovat varattuja.")
            << " Kokeile toista huonetyyppiä." << endl;
    }

    while (true) { // While loop jolla odotetaan että käyttäjä haluaa jatkaa eteenpäin.
        string jatka;
        cout << "Kirjoita 'jatka' ja paina enter palataksesi alkunäyttöön. Tämä tyhjentää aiemman tekstin." << endl;
        getline(cin >> ws, jatka); // ws skippaa "whitespacen" inputista. Eli välilyönnit rivivaihdot yms
        if (jatka != "jatka") { 
            cout << "Virheellinen syöte. Kokeile uudestaan." << endl;
        }
        else { // Jos käyttäjä antoi oikean inputin, poistutaan while loopista
            break;
        }
    }

    system("cls"); // Tyhjentää konsolista tekstin
}

void tarkistaHuone(vector<HotelliHuone>& huoneet) { // Aliohjelma jonka avulla tarkastetaan huoneen tila
    while (true) { // Kysytään haluaako tarkistaa nimellä vai varausnumerolla
        int valinta;
        cout << "Haluatko tarkistaa huoneen tilan nimellä vai varausnumerolla? Kirjoita 1 (nimi) tai 2 (numero): ";
        cin >> valinta;

        if (valinta == 1) { // Jos nimellä 
            cout << "Anna nimi: ";
            string nimi;
            getline(cin >> ws, nimi);

            auto tarkistus = find_if(huoneet.begin(), huoneet.end(), [nimi](const HotelliHuone& huone) { // Etsii vektorista structia jossa ilmestyisi annettu nimi
                return huone.varaaja == nimi;
                });

            if (tarkistus != huoneet.end()) { // Jos löytyi huone 
                cout << "Huone " << tarkistus->huoneNumero << ": "
                    << (tarkistus->varattu ? "Varattu nimellä " + tarkistus->varaaja : "Vapaa") << endl; // Tässä taas ? funktiolla katsotaan onko varrattu true vai false ja toimitaan sen mukaan
            }
            else {
                cout << "Huonetta nimellä " << nimi << " ei löydy." << endl; // Jos nimellä ei löydy
            }
            break;
        }
        else if (valinta == 2) { // Jos numerolla
            cout << "Anna varausnumero: ";
            int numero;
            cin >> numero;

            auto tarkistus = find_if(huoneet.begin(), huoneet.end(), [numero](const HotelliHuone& huone) { // Sama kuin äsken mutta etsitään varausnumeroa
                return huone.varausnumero == numero;
                });

            if (tarkistus != huoneet.end()) {
                cout << "Huone " << tarkistus->huoneNumero << ": "
                    << (tarkistus->varattu ? "Varattu nimellä " + tarkistus->varaaja : "Vapaa") << endl;
            }
            else {
                cout << "Huonetta varausnumerolla " << numero << " ei löydy." << endl;
            }
            break;
        }
        else { // Jos antaa epäsopivan inputin
            cout << "Virheellinen valinta. Yritä uudelleen." << endl;
        }
    }

    while (true) { // Aiemmin jo nähty, tällä poistutaan takaisin pääohjelmaan
        string jatka;
        cout << "Kirjoita 'jatka' ja paina enter palataksesi alkunäyttöön. Tämä tyhjentää aiemman tekstin." << endl;
        getline(cin >> ws, jatka);
        if (jatka != "jatka") {
            cout << "Virheellinen syöte. Kokeile uudestaan." << endl;
        }
        else {
            break;
        }
    }

    system("cls");
}

int main() { // Itse pääohjelma
    setlocale(LC_ALL, "fi_FI"); // Alustetaan ääkköset koodiin
    vector<HotelliHuone> yhHuoneet, khHuoneet; // Luodaan vektorit
    int kaikkiHuoneet = huoneidenArvonta(); // Määritellään huoneiden määrä heti alussa

    for (int i = 0; i <= kaikkiHuoneet / 2; i++) { // Alustetaan for loopilla kaikki 1h huone structit
        HotelliHuone huone;
        huone.huoneNumero = i;
        huone.huoneTyyppi = "1h Huone";
        huone.varattu = false;
        huone.varaaja = "";
        huone.oidenMaara = 0;
        huone.hintaPerYo = 100.0;
        huone.varausnumero = 0;
        yhHuoneet.push_back(huone);
    }
    for (int i = 0; i <= kaikkiHuoneet / 2; i++) { // Sama mutta 2h huoneet
        HotelliHuone huone;
        huone.huoneNumero = i + kaikkiHuoneet / 2;
        huone.huoneTyyppi = "2h Huone";
        huone.varattu = false;
        huone.varaaja = "";
        huone.oidenMaara = 0;
        huone.hintaPerYo = 150.0;
        huone.varausnumero = 0;
        khHuoneet.push_back(huone);
    }

    while (true) { // Ns. main menu. While loop varmistaa, että saadaan jokin sopiva vastaus.
        cout << "Tervetuloa hotellin huonevarausjärjestelmään"<< endl;
        viivat();
        cout << "[1] Varaa huone" << endl << "[2] Tarkista huoneen tila" << endl << "[3] Poistu ohjelmasta" << endl;;
        viivat();

        int valinta; // Katsotaan mitä käyttäjä valitsi
        cin >> valinta;

        if (valinta == 1) { // Jos valinta oli 1

            /* Tämä kohta jäi hieman harmittamaan, koska olisi varmasti paremmalla ajalla ehtinyt tekemään fiksumman.
            Oman helpotukseni vuoksi pyydän tässä käyttäjää valitsemaan 1 ja 2 huoneen välillä, koska ne ovat erillisillä vektoreilla*/

            cout << "Valitse 1h (1) tai 2h (2) ja paina enter: ";
            int tyyppi;
            cin >> tyyppi;

            if (tyyppi == 1) varaaHuone(yhHuoneet, tyyppi); // Aliohjelma tutkii vektoria yhHuoneet
            else if (tyyppi == 2) varaaHuone(khHuoneet, tyyppi); // Aliohjelma tutkii vektoria khHuoneet
            else cout << "Virheellinen valinta" << endl; // Valinta on virheellinen
        }
        else if (valinta == 2) { // Jos haluu tutkailla huoneita
            cout << "Tarkista 1h (1) tai 2h (2): ";
            int tyyppi;
            cin >> tyyppi;

            if (tyyppi == 1) tarkistaHuone(yhHuoneet); // Samaa kuin äsken
            else if (tyyppi == 2) tarkistaHuone(khHuoneet);
            else cout << "Virheellinen valinta." << endl;
        }
        else if (valinta == 3) { // suljetaan ohjelma, eli rikotaan while loop.
            cout << "Kiitos! Näkemiin." << endl;
            break;
        }
        else {
            cout << "Virheellinen valinta. Yritä uudelleen." << endl;
        }
    }

    return 0; // poistutaan ohjelmasta
}
