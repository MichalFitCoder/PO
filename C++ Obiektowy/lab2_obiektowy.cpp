#include <iostream>

using namespace std;

class WezelListy{
    public:
    string imieStudenta;   
    string nazwiskoStudenta;
    double sredniaOcenStudenta;
    char plecStudenta;
    WezelListy* wskNastepny;
    WezelListy* wskPoprzedni;
    //Konstruktor;
    WezelListy(string imStudenta,string nzStudenta,double srOCStudenta,char plStudenta);

};

class ListaStudentow{
    public:
    WezelListy* glowa;
    WezelListy* ogon;
    int aktualnaDlugoscListy;
    //Metody klasy
    void dodajNowegoStudentaNaPoczatekListy(string imieStudenta, string nazwiskoStudenta,double srOcStudenta,char plStudenta);
    void usunZListyStudentaOPodanymImieniuINazwisku(string imieStudenta, string nazwiskoStudenta);
    WezelListy* zwrocWezelListyStudentowOPodanymNrPozycji(int nrPozycji);
    void wyswietlDaneWezlowZListyStudentowOSredniejOcenWyzszejOdZadanej(double srednia);
    WezelListy* zwrocWezelZListyStudentowDlaKobietyOSredniejOcenNajblizszejZadanej(double srednia);
    //Konstruktor
    ListaStudentow();
    //Destruktor
    ~ListaStudentow();

};

int menu(){
    int option;
    cout << "Program do zarzadzania lista studentow"<< endl;
    cout << "[0] - wyjscie z programu" << endl;
    cout << "[1] - dodawanie nowego studenta na poczatek listy" << endl;
    cout << "[2] - usuwanie z listy studenta" << endl;
    cout << "[3] - wyswietlanie informacji o studencie na podanej pozycji" << endl;
    cout << "[4] - wyswietlanie informacji o studentach majacych srednia wyzsza od podanej" << endl;
    cout << "[5] - wyswietlanie informacji o kobiecie majacej srednia najblizsza podanej" << endl;
    cout << "[6] - wyswietlanie listy" << endl;    
    cout << "==============================================================================" << endl;
    cout << "Wprowadz nr operacji: ";
    cin >> option;
    return option;
}

void dodaj(ListaStudentow* list){
    string imie,nazwisko;
    double srocen;
    char plec;

    cout << "Podaj nazwisko studenta: "; cin >> nazwisko;
    cout << "Podaj imie studenta: "; cin >> imie;
    cout << "Podaj srednia ocen studenta: "; cin >> srocen;
    cout << "Podaj plec studenta[m/k]: " << endl; cin >> plec; 
    //Sprawdzanie poprawnosci danych
    if(srocen > 5 || srocen < 2){
        cout << "Niepoprawna wartosc sredniej ocen [2.0 - 5.0], nie udalo sie dodac studenta";
        return;
    }
    if(plec!='m' && plec!='k'){
        cout << "Podano niepoprawna plec [m/k], nie udalo sie dodac studenta";
        return;
    } 
    list->dodajNowegoStudentaNaPoczatekListy(imie,nazwisko,srocen,plec);
}
void usun(ListaStudentow* list){
    string imie, nazwisko;
    cout << "Podaj imie: "; cin >> imie;
    cout << "Podaj nazwisko: "; cin >> nazwisko;
    list->usunZListyStudentaOPodanymImieniuINazwisku(imie,nazwisko);
}
    

void showList(ListaStudentow* list){
    if(list->aktualnaDlugoscListy == 0){
        cout << "Lista jest aktualnie pusta " << endl;
        return;
    }
    WezelListy* p = list->glowa;
    cout << "Obecna lista studentow to: " << endl;
    while(p){
        cout << "Nazwisko: " << p->nazwiskoStudenta << "  Imie: " << p->imieStudenta << "  Srednia ocen: " << p->sredniaOcenStudenta << "  Plec: " << p->plecStudenta << endl;
        p = p->wskNastepny;
    }
}

void pozycja(ListaStudentow* list){
    int n;
    cout << "Podaj pozycje studenta do wywietlenia: ";
    cin >> n;
    if(!list->zwrocWezelListyStudentowOPodanymNrPozycji(n)){ 
        cout << "Nie ma indexu o takiej pozycji" << endl; 
        return;
    }else{ 
        cout << "Nazwisko: " << list->zwrocWezelListyStudentowOPodanymNrPozycji(n)->nazwiskoStudenta << endl;
        cout << "Imie: " << list->zwrocWezelListyStudentowOPodanymNrPozycji(n)->imieStudenta << endl;
    }
}

void srednia(ListaStudentow* list){
    double n;
    cout << "Podaj srednia: ";
    cin >> n;
    list->wyswietlDaneWezlowZListyStudentowOSredniejOcenWyzszejOdZadanej(n);
}

void najblizszaSrednia(ListaStudentow* list){
    double n;
    WezelListy* p;
    cout << "Podaj srednia: ";
    cin >> n;
    p = list->zwrocWezelZListyStudentowDlaKobietyOSredniejOcenNajblizszejZadanej(n);
    
    cout << "Nazwisko: " << p->nazwiskoStudenta << endl;
    cout << "Imie: " << p->imieStudenta << endl;
    cout << "Srednia: " << p->sredniaOcenStudenta << endl;
}

int main(){
    int choice;
    ListaStudentow* list = new ListaStudentow();
    list->aktualnaDlugoscListy = 0;
    while(choice = menu()){ //Wywolywane jest menu a jego wartosc przypisywana do choice
        switch(choice){
            case 1: dodaj(list);
                break;
            case 2: usun(list);
                break;
            case 3: pozycja(list);
                break;
            case 4:
                    srednia(list);
                break;
            case 5:
                    najblizszaSrednia(list);
                break;
            case 6: showList(list);
                break;
            default:
            cout << "Podana wartosc jest niepoprawna! Prosze podac wybrac jedna z opcji";
        }
    };
    showList(list);
    return 0;
}

void ListaStudentow::dodajNowegoStudentaNaPoczatekListy(string imie, string nazwisko,double srocen,char plec)
{
    WezelListy* student = new WezelListy(imie,nazwisko,srocen,plec);
    if(this->aktualnaDlugoscListy == 0){ // Gdy lista jest pusta dodajemy pierwszy element
        this->glowa = student;
        this->ogon = student;
        this->glowa->wskNastepny = student;
        this->ogon->wskPoprzedni = student;
        this->ogon->wskNastepny = NULL;
        this->glowa->wskPoprzedni = NULL;
    }else{  // Gdy lista ma juz jakies elementy dodajemy element na poczatek
        this->glowa->wskPoprzedni = student;
        student->wskNastepny = this->glowa;
        this->glowa = student;
    }
    this->aktualnaDlugoscListy++;
    cout << "Poprawnie dodano studenta" << endl;

}

void ListaStudentow::usunZListyStudentaOPodanymImieniuINazwisku(string imie, string nazwisko)
{
    WezelListy* p = this->glowa;
    if(!this->glowa){
        cout << "Lista jest aktualnie pusta";
        return;
    }// Gdy lista ma jeden element
    if(!this->glowa->wskNastepny && this->glowa->nazwiskoStudenta == nazwisko && this->glowa->imieStudenta == imie){
        this->glowa->wskNastepny = NULL;
        this->ogon->wskPoprzedni = NULL;
        this->glowa = NULL;
        this->ogon = NULL;
        delete(p);
    }else if(this->glowa->nazwiskoStudenta == nazwisko && this->glowa->imieStudenta == imie){
        this->glowa = this->glowa->wskNastepny;
        this->glowa->wskPoprzedni = NULL;
    }else{
    while(p){
        if(p->imieStudenta == imie && p->nazwiskoStudenta == nazwisko){
            p->wskPoprzedni->wskNastepny = p->wskNastepny;
            p->wskNastepny->wskPoprzedni = p->wskPoprzedni;
            delete(p);
        } 
        p = p->wskNastepny;
    }
    }
    this->aktualnaDlugoscListy--;
}

WezelListy *ListaStudentow::zwrocWezelListyStudentowOPodanymNrPozycji(int nrPozycji)
{
    WezelListy* p = this->glowa;
    for(int i = 0 ; i < nrPozycji ; i++){
        if(!p) return NULL;
        p = p->wskNastepny;
    }
    return p;
}

void ListaStudentow::wyswietlDaneWezlowZListyStudentowOSredniejOcenWyzszejOdZadanej(double srednia)
{
    WezelListy* p = this->glowa;
    for(int i = 0 ; i < this->aktualnaDlugoscListy ; i++){
        if(p->sredniaOcenStudenta > srednia){
            cout << "Nazwisko: " << p->nazwiskoStudenta << endl;
            cout << "Imie: " << p->imieStudenta << endl;
        }
        p = p->wskNastepny;
    }
}

WezelListy* ListaStudentow::zwrocWezelZListyStudentowDlaKobietyOSredniejOcenNajblizszejZadanej(double srednia)
{
    int index = 0;
    double roznica = 0;
    double minRoznica = 5;
    WezelListy* p = this->glowa;
    if(!this->aktualnaDlugoscListy) return NULL;
    for(int i = 0 ; i < this->aktualnaDlugoscListy ; i++){
        if(p->plecStudenta == 'k'){
            roznica = abs(p->sredniaOcenStudenta - srednia);
        }
        if(roznica < minRoznica){
            minRoznica = roznica;
            index = i;
        }
        p = p->wskNastepny;
    
    }

    return this->zwrocWezelListyStudentowOPodanymNrPozycji(index);
}

ListaStudentow::ListaStudentow()
{
}

WezelListy::WezelListy(string imStudenta, string nzStudenta, double srOCStudenta, char plStudenta)
{
    this->imieStudenta = imStudenta;
    this->nazwiskoStudenta = nzStudenta;
    this->sredniaOcenStudenta = srOCStudenta;
    this->plecStudenta = plStudenta;
}
