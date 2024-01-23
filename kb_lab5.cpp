#include <iostream>
using namespace std;

class Zamowienie{
string marka;
string model;
double pojemnoscSilnika;
int liczbaCylindrowSilnika;
int mocSilnika;
int maxMomentObrotowySilnika;
int rozmiarKol;
public:
string tabDodatkoweWyposazenie[4];
Zamowienie(string marka,string model,double pojemnoscSilnika,int liczbaCylindrowSilnika,int mocSilnika,int maxMomentObrotowySilnika,int rozmiarKol,string* tabDodatkoweWyposazenie)
{
    this->marka=marka;
    this->model=model;
    this->pojemnoscSilnika=pojemnoscSilnika;
    this->liczbaCylindrowSilnika=liczbaCylindrowSilnika;
    this->mocSilnika=mocSilnika;
    this->maxMomentObrotowySilnika=maxMomentObrotowySilnika;
    this->rozmiarKol=rozmiarKol;
    this->tabDodatkoweWyposazenie[0]=tabDodatkoweWyposazenie[0];
    this->tabDodatkoweWyposazenie[1]=tabDodatkoweWyposazenie[1];
    this->tabDodatkoweWyposazenie[2]=tabDodatkoweWyposazenie[2];
    this->tabDodatkoweWyposazenie[3]=tabDodatkoweWyposazenie[3];
}
string getMarka(){return this->marka;}
string getModel(){return this->model;}
double getPojemnoscSilnika(){return this->pojemnoscSilnika;}//na schemacie funkcja int
int getLiczbaCylindrowSilnika(){return this->liczbaCylindrowSilnika;}
int getMocSilnika(){return this->mocSilnika;}
int getMaxMomentObrotowySilnika(){return this->maxMomentObrotowySilnika;}
int getRozmiarKol(){return this->rozmiarKol;}
};

class Kolo{
int rozmiar;
public:
Kolo(int rozmiar){this->rozmiar=rozmiar;}
int getRozmiar(){return this->rozmiar;}
~Kolo(){}
};

class Silnik{
double pojemnosc;
int liczbaCylindrow;
int moc;
int maxMomentObrotowy;
public:
    Silnik(double pojemnosc,int liczbaCylindrow,int moc,int maxMoment){
    this->pojemnosc=pojemnosc;
    this->liczbaCylindrow=liczbaCylindrow;
    this->moc=moc;
    this->maxMomentObrotowy=maxMoment;
    }
    double getPojemnosc(){return this->pojemnosc;}
    int getLiczbaCylindrow(){return this->liczbaCylindrow;}
    int getMoc(){return this->moc;}
    int getMaxMomentObrotowy(){return this->maxMomentObrotowy;}
};

class DodatkoweWyposazenie{
string nazwa;
public:
    DodatkoweWyposazenie(string nazwa){this->nazwa=nazwa;}
    string getNazwa(){return this->nazwa;}
};

class Samochod{
string marka;
string model;
Silnik silnik;
Kolo* kola[4];
DodatkoweWyposazenie* dodatkoweWyposazenie[4];
Samochod(string marka,string model,double pojemnoscSilnika,int liczbaCylindrowSilnika,int mocSilnika,int maxMomentObrotowySilnika,int rozmiarKol):
    silnik(pojemnoscSilnika,liczbaCylindrowSilnika,mocSilnika,maxMomentObrotowySilnika){
        this->marka=marka;
        this->model=model;
        kola[0] = new Kolo(rozmiarKol);
        kola[1] = new Kolo(rozmiarKol);
        kola[2] = new Kolo(rozmiarKol);
        kola[3] = new Kolo(rozmiarKol);
        this->dodatkoweWyposazenie[0]=NULL;
        this->dodatkoweWyposazenie[1]=NULL;
        this->dodatkoweWyposazenie[2]=NULL;
        this->dodatkoweWyposazenie[3]=NULL;
    }
public:
void wyswietlSpecyfikacje() {
        cout<<"Specyfikacja samochodu:"<<endl;
        cout<<"Marka: "<<marka<<endl;
        cout<<"Model: "<<model<<endl;
        cout<<"Pojemnosc silnika: "<<silnik.getPojemnosc()<<" L"<<endl;
        cout<<"Liczba cylindrow silnika: "<<silnik.getLiczbaCylindrow()<<endl;
        cout<<"Moc silnika: "<<silnik.getMoc()<<" KM"<<endl;
        cout<<"Rozmiar kol: "<<kola[0]->getRozmiar()<<" cali"<<endl;
        cout<<"Maksymalny moment obrotowy silnika: "<<silnik.getMaxMomentObrotowy()<<"obr/min"<<endl;
        for (int i = 0; i < 4; i++){
            if (dodatkoweWyposazenie[i] != NULL){
                cout << "Dodatkowe wyposazenie " << i + 1 << ": " << dodatkoweWyposazenie[i]->getNazwa() << endl;
            }
        }
}
    static Samochod* wyprodukujSamochod(Zamowienie* zamowienie) {
        Samochod* samochod = new Samochod(
            zamowienie->getMarka(),
            zamowienie->getModel(),
            zamowienie->getPojemnoscSilnika(),
            zamowienie->getLiczbaCylindrowSilnika(),
            zamowienie->getMocSilnika(),
            zamowienie->getMaxMomentObrotowySilnika(),
            zamowienie->getRozmiarKol()
        );

        for (int i = 0; i < 4; i++) {
            if (!zamowienie->tabDodatkoweWyposazenie[i].empty()) {
                samochod->dodajWyposazenie(new DodatkoweWyposazenie(zamowienie->tabDodatkoweWyposazenie[i]));
            }
        }

        return samochod;
    }
    void dodajWyposazenie(DodatkoweWyposazenie* wyposazenie) {
        for (int i = 0; i < 4; i++) {
            if (dodatkoweWyposazenie[i] == NULL) {
                dodatkoweWyposazenie[i] = wyposazenie;
                break;
            }
        }
    }
    ~Samochod() {
        for (int i = 0; i < 4; i++) {
            delete kola[i];
            if (dodatkoweWyposazenie[i] != NULL) {
                delete dodatkoweWyposazenie[i];
            }
        }
    }
};

class FabrykaSamochodow{
string nazwa;
public:
    FabrykaSamochodow(string nazwa){this->nazwa=nazwa;}
    Samochod* wyprodukujSamochod(Zamowienie* zamowienie) {
        Samochod* samochod = Samochod::wyprodukujSamochod(zamowienie);
        return samochod;
    }
    void doposazWyprodukowaneAuto(Samochod* samochod, Zamowienie* zamowienie) {
        for (int i = 0; i < 4; i++) {
            if (!zamowienie->tabDodatkoweWyposazenie[i].empty()) {
                samochod->dodajWyposazenie(new DodatkoweWyposazenie(zamowienie->tabDodatkoweWyposazenie[i]));
            }
        }
    }
};
int main()
{
    string wyposazenie[4] = {"Kot"};
    Zamowienie zamowienie1("Toyota", "Camry", 2.5, 4, 200, 300, 17, wyposazenie);

    FabrykaSamochodow fabryka("Toyota Motors w Walbrzychu");

    Samochod* samochod1 = fabryka.wyprodukujSamochod(&zamowienie1);

    samochod1->wyswietlSpecyfikacje();
    cout<<endl;
    string wyposazenie2[4] = {"Podgrzewane fotele", "Kamera cofania", "Bluetooth"};
    Zamowienie zamowienie2("BMW", "X5", 3.0, 6, 300, 400, 19, wyposazenie2);

    Samochod* samochod2 = fabryka.wyprodukujSamochod(&zamowienie2);
    samochod2->wyswietlSpecyfikacje();

    cout<<endl;
    string wyposazenie3[4] = {"Szyberdach","Gasnica","Trojkat","Radio"};
    Zamowienie zamowienie3("", "", 0.0, 0, 0, 0, 0, wyposazenie3);
    fabryka.doposazWyprodukowaneAuto(samochod1,&zamowienie3);
    samochod1->wyswietlSpecyfikacje();

    delete samochod1;
    delete samochod2;
    return 0;
}

