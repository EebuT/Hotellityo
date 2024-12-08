// Eetu Tuominen
// Hotellity�
//4p

// Otetaan k�ytt��n kirjastot
#include <iostream> // Cin ja Cout 
#include <cmath>
#include <vector> // Vektorit k�ytt��n.
#include <random> // Satunaislukujen luontiin
#include <algorithm> // Saadaan muutama ohjelmassa hy�dynnetty komento
#include <string> // getline

using namespace std; // Otetaan k�ytt��n standardi- kirjasto, ei siis tarivta std:: etuliitett�

struct HotelliHuone {  // Luodaan struct- hotellihuoneelle. T�ll� saadaan varattua yksitt�isen hotellihuoneen tiedot.
    double huoneNumero;
    string huoneTyyppi;
    bool varattu;
    string varaaja;
    int oidenMaara;
    double hintaPerYo;
    int varausnumero;
};

int varausNumero(vector<HotelliHuone>& huoneet) { // Ensimm�inen aliohjelma. T�ll� luodaan uniikki varausnumero jokaiselle huoneelle. 
    while (true) { // While- loop jolla tarkistetaan ett� lukua ei ole k�ytetty aiemmin


        // T�ss� satunaislukugeneraattori, jota k�yt�n ohjelmassa useita kertoja

        random_device random; // Luodaan "siemen" lukugeneraattorille
        mt19937 generaattori(random()); // Alustetaan satunaisnumero
        uniform_int_distribution<> vali(10000, 99999); // Asetetaan v�li, jolle luku arvotaan
        int luku = vali(generaattori); // Annetaan kokonaislukumuuttujalle 'luku' arvoksi generaattorin luoma luku.


        /* Seuraavassa riviss� k�yt�n muuttujaa auto, joka on minulle uusi tuttavuus. 
        K�yt�n�ss� rivi toimii niin, ett� se etsii 'huoneet' nimiselt� kokoelmalta alusta loppuun lukua, jonka generaattori loi.
        T�m�n koodin syntaksi vaatii todella rankkaa stack overflown kaivelua sek� teko�lyn apua, ett� ymm�rsin sen toiminnan. 
        T�st� lis�� koodin esitelm�ss�.*/

        auto varattuNo = find_if(huoneet.begin(), huoneet.end(), [luku](const HotelliHuone& huone) { 
            return huone.varausnumero == luku;
            });

        if (varattuNo == huoneet.end()) { // Jos varattuNo tutkii loppuun asti (huoneet.end) toteaa se, ett� lukua ei l�ydy ja sit� voi k�ytt��.
            return luku; 
        }
    } // Jos luku l�ytyi jo, pyrii t�m� while loop siihen asti, ett� uniikki luku syntyy.
}

void viivat() { // Aliohjelma jonka loin tekem��n viivan, ettei tarvitse kirjoittaa. Hiemnan turha, mutta hyv�� harjoitusta silti.
    cout << endl << "===&&&===&&&===&&&===&&&===" << endl;
}


int huoneidenArvonta() { // Yksinkertain aliohjelma, joka arpoo huoneiden m��r�n
    random_device random;
    mt19937 generaattori(random());
    uniform_int_distribution<> vali(20, 150);
    return 2 * vali(generaattori); // kertomalla luku 2 varmistetaan, ett� se on parillinen
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

    return uusiHinta; // Alihojelma palauttaa hotellihuoneen hinnan alennuksen j�lkeen
}

bool onVapaa(const HotelliHuone& huone) { // Tarkistaa vektorilta onko huone varattu. Const muuttujaa k�ytet��n siksi, ettei aliohjelma vahingossa mene virhetilaan ja k�yt� v��r�� dataa
    return !huone.varattu;  // T�ss� ! edess�, koska structissa josta ohjelma katsoo huone.varattu arvoa, on true jos varattu. Nyt ohjelma palauttaa siis sen negaation.
}

void varaaHuone(vector<HotelliHuone>& huoneet, int huoneTyyppi) {

    // Taas tuttu satunaislukugeneraattori, pienell� twistill�
    random_device random;
    mt19937 generaattori(random());
    shuffle(huoneet.begin(), huoneet.end(), generaattori); // Shuffle komento sekoittaa vektorin sis�ll�n siten, ett� sit� katsellaan satunaisessa j�rjestyksess�

    auto etsinta = find_if(huoneet.begin(), huoneet.end(), onVapaa); // Find if komento etsii annetulta v�lilt� ensimm�isen kohdan, joka palauttaa onVapaa aliohjelmaa k�ytt�en arvon 'true'

    if (etsinta != huoneet.end()) { // Tarkistaa, ett� �skeinen ohjelma l�ysi vapaan huoneen, eik� palauttanut vain viimeist� mahdollista arvoa
        cout << "Anna nyt nimi, jolla huone varataan: ";
        string nimi;
        cin.ignore(); 
        getline(cin, nimi); // Otetaan talteen k�ytt�j�n antama tieto, ylempi cin.ignore poistaa mahdolliset ylim��r�iset tiedot.

        int yot;
        while (true) { // While- loop kysyy y�m��r�� kunnen k�ytt�j� antaa positiivisen kokonaisluvun
            cout << "Montako y�t� haluatte y�py�?" << endl;
            cin >> yot;

            // Seuraava koodinpala aiheutti ongelmia. En mill��n meinannut l�yt�� toimivaa komentoa tarkistamaan lukua ja sitten tyhjent�m��n sis��ntullutta tietoa.

            if (cin.fail() || yot <= 0) { // Tarkistaa ett� annettiin kokonaisluku ja ett� se on enemm�n kuin 0
                cin.clear(); // Jos ei annettu oiken, tyhjennet��n saatu tieto rekisterist� ja aloitetaan alusta 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // T�m� kertoo input streamille, ett� tietyt ehdot t�ytt�v� teksti heitet��n pois.
                // Ylemm�n rivin sis�lt� tarkoittaa sit�, ett� kaikki merkit ja tieto heitet��n pois seuraavaan rivinvaihtoon tai siihen ett� kaikki merkit on poistettu asti
                cout << "Virheellinen sy�te. Sy�t� positiivinen kokonaisluku." << endl;
            }
            else {
                break; // Jos luku on sopiva poistutaan while- loopista
            }
        }

        double uusiHinta = laskeAlennus(etsinta->hintaPerYo); // Lasketaan muuttujalle uusiHinta arvo k�ytt�en aliohjelmaa laskeAlennus


        // T�ss� n�kyy yksi kohdista, miss� teko�lyn avulla opin uuden tavan optimoida koodia. Lis�� t�st� esitelm�ss�
        etsinta->varattu = true;  // Vied��n arvoja structille
        etsinta->varaaja = nimi;
        etsinta->oidenMaara = yot;
        etsinta->varausnumero = varausNumero(huoneet);// Vied��n aliohjelmalla luotu varausnumero

        viivat();
        // Printtaillaan teksti�
        cout << "Varattu huone numero " << etsinta->huoneNumero
            << " nimell� " << etsinta->varaaja
            << " " << etsinta->oidenMaara << " y�ksi." << endl
            << "Huoneen hinta y�lt� on: " << uusiHinta << " Euroa." << endl
            << "Kokonaishinta: " << uusiHinta * yot << " Euroa." << endl
            << "Varausnumerosi: " << etsinta->varausnumero << endl;
    }
    else { // jos  huoneTyyppi on 1 ja huoneet on varattu tulostetaan vaihtoehto ennen ':' merkki�, jos huonetyyppi != 1 tulostetaan j�lempi vaihtoehto
        cout << (huoneTyyppi == 1 ? "Kaikki yhden hengen huoneet ovat varattuja."
            : "Kaikki kahden hengen huoneet ovat varattuja.")
            << " Kokeile toista huonetyyppi�." << endl;
    }

    while (true) { // While loop jolla odotetaan ett� k�ytt�j� haluaa jatkaa eteenp�in.
        string jatka;
        cout << "Kirjoita 'jatka' ja paina enter palataksesi alkun�ytt��n. T�m� tyhjent�� aiemman tekstin." << endl;
        getline(cin >> ws, jatka); // ws skippaa "whitespacen" inputista. Eli v�lily�nnit rivivaihdot yms
        if (jatka != "jatka") { 
            cout << "Virheellinen sy�te. Kokeile uudestaan." << endl;
        }
        else { // Jos k�ytt�j� antoi oikean inputin, poistutaan while loopista
            break;
        }
    }

    system("cls"); // Tyhjent�� konsolista tekstin
}

void tarkistaHuone(vector<HotelliHuone>& huoneet) { // Aliohjelma jonka avulla tarkastetaan huoneen tila
    while (true) { // Kysyt��n haluaako tarkistaa nimell� vai varausnumerolla
        int valinta;
        cout << "Haluatko tarkistaa huoneen tilan nimell� vai varausnumerolla? Kirjoita 1 (nimi) tai 2 (numero): ";
        cin >> valinta;

        if (valinta == 1) { // Jos nimell� 
            cout << "Anna nimi: ";
            string nimi;
            getline(cin >> ws, nimi);

            auto tarkistus = find_if(huoneet.begin(), huoneet.end(), [nimi](const HotelliHuone& huone) { // Etsii vektorista structia jossa ilmestyisi annettu nimi
                return huone.varaaja == nimi;
                });

            if (tarkistus != huoneet.end()) { // Jos l�ytyi huone 
                cout << "Huone " << tarkistus->huoneNumero << ": "
                    << (tarkistus->varattu ? "Varattu nimell� " + tarkistus->varaaja : "Vapaa") << endl; // T�ss� taas ? funktiolla katsotaan onko varrattu true vai false ja toimitaan sen mukaan
            }
            else {
                cout << "Huonetta nimell� " << nimi << " ei l�ydy." << endl; // Jos nimell� ei l�ydy
            }
            break;
        }
        else if (valinta == 2) { // Jos numerolla
            cout << "Anna varausnumero: ";
            int numero;
            cin >> numero;

            auto tarkistus = find_if(huoneet.begin(), huoneet.end(), [numero](const HotelliHuone& huone) { // Sama kuin �sken mutta etsit��n varausnumeroa
                return huone.varausnumero == numero;
                });

            if (tarkistus != huoneet.end()) {
                cout << "Huone " << tarkistus->huoneNumero << ": "
                    << (tarkistus->varattu ? "Varattu nimell� " + tarkistus->varaaja : "Vapaa") << endl;
            }
            else {
                cout << "Huonetta varausnumerolla " << numero << " ei l�ydy." << endl;
            }
            break;
        }
        else { // Jos antaa ep�sopivan inputin
            cout << "Virheellinen valinta. Yrit� uudelleen." << endl;
        }
    }

    while (true) { // Aiemmin jo n�hty, t�ll� poistutaan takaisin p��ohjelmaan
        string jatka;
        cout << "Kirjoita 'jatka' ja paina enter palataksesi alkun�ytt��n. T�m� tyhjent�� aiemman tekstin." << endl;
        getline(cin >> ws, jatka);
        if (jatka != "jatka") {
            cout << "Virheellinen sy�te. Kokeile uudestaan." << endl;
        }
        else {
            break;
        }
    }

    system("cls");
}

int main() { // Itse p��ohjelma
    setlocale(LC_ALL, "fi_FI"); // Alustetaan ��kk�set koodiin
    vector<HotelliHuone> yhHuoneet, khHuoneet; // Luodaan vektorit
    int kaikkiHuoneet = huoneidenArvonta(); // M��ritell��n huoneiden m��r� heti alussa

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

    while (true) { // Ns. main menu. While loop varmistaa, ett� saadaan jokin sopiva vastaus.
        cout << "Tervetuloa hotellin huonevarausj�rjestelm��n"<< endl;
        viivat();
        cout << "[1] Varaa huone" << endl << "[2] Tarkista huoneen tila" << endl << "[3] Poistu ohjelmasta" << endl;;
        viivat();

        int valinta; // Katsotaan mit� k�ytt�j� valitsi
        cin >> valinta;

        if (valinta == 1) { // Jos valinta oli 1

            /* T�m� kohta j�i hieman harmittamaan, koska olisi varmasti paremmalla ajalla ehtinyt tekem��n fiksumman.
            Oman helpotukseni vuoksi pyyd�n t�ss� k�ytt�j�� valitsemaan 1 ja 2 huoneen v�lill�, koska ne ovat erillisill� vektoreilla*/

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

            if (tyyppi == 1) tarkistaHuone(yhHuoneet); // Samaa kuin �sken
            else if (tyyppi == 2) tarkistaHuone(khHuoneet);
            else cout << "Virheellinen valinta." << endl;
        }
        else if (valinta == 3) { // suljetaan ohjelma, eli rikotaan while loop.
            cout << "Kiitos! N�kemiin." << endl;
            break;
        }
        else {
            cout << "Virheellinen valinta. Yrit� uudelleen." << endl;
        }
    }

    return 0; // poistutaan ohjelmasta
}
