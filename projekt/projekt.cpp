#include <iostream>

using namespace std;

class Notatka{

    public:
    string zawartosc;
    string nazwa;

    Notatka(string nazwa, string zawartosc){
        this->nazwa = nazwa;
        this->zawartosc = zawartosc;
    }
    
    void nadpiszZawartosc(string text){
        this->zawartosc = text;
    }

    void wyswietlZawartosc(){
        cout << this->zawartosc << endl;
    }
};

class Folder{
    public:
    string nazwa;
    Notatka* notatki[10];
    int liczbaNotatek = 0;

    Folder(string nazwa){
        this->nazwa = nazwa;
    }

    void dodajNotatke(Notatka* notatka){
        this->notatki[this->liczbaNotatek] = notatka;
        this->liczbaNotatek++;
    }

    void wyswietl(){
        for(int i = 0 ; i < this->liczbaNotatek ; i++){
            cout << "-" <<  this->notatki[i]->nazwa << endl;
        }
    }

    void wyswietlZawartoscNotatki(string nazwa){
        for(int i = 0 ; i < this->liczbaNotatek ; i++){
            if(this->notatki[i]->nazwa == nazwa){
                cout << "Zawartosc notatki " << nazwa << ": \n";
                notatki[i]->wyswietlZawartosc();
                return;
            }
        }
    }

    void usun(){
        for(int i = 0; i < liczbaNotatek ; i++){
            delete(notatki[i]);
        }
    }
};


class Konto{
    protected:
    string login;
    string haslo;
    bool czyZalogowany = false;
};

class KontoAdministatora : public Konto{
    friend class MenagerUzytkownikow;
    public:
    KontoAdministatora(string login, string haslo){
        this->login = login;
        this->haslo= haslo;
    }
    void usunNotatke(Notatka* notatka){
        if(!this->czyZalogowany){
            cout << "Administator nie jest zalogowany! Nie udalo sie usunac notatki\n";
            return;
        }
        cout << "Poprawnie usunieto notatke " << notatka->nazwa << endl;
        delete(notatka);
    }
    void usunFolder(Folder* folder){
        if(!this->czyZalogowany){
            cout << "Administator nie jest zalogowany! Nie udalo sie usunac folderu\n";
            return;
        }
        cout << "Poprawnie usunieto folder\n";
        folder->usun();
        delete(folder);
    }
};

class KontoUzytkownika : public Konto{

    friend class KontoAdministatora;
    Folder* foldery[10];
    int liczbafolderow = 0;
    public:
    friend class MenagerUzytkownikow;
    KontoUzytkownika(string login, string haslo){
        this->login = login;
        this->haslo = haslo;
    }

    Folder* utworzFolder(string nazwa){
        if(!this->czyZalogowany){
            throw runtime_error("Uzytkownik nie jest zalogowany !\n");
        }

        Folder* f = new Folder(nazwa);
        this->foldery[this->liczbafolderow] = f;
        this->liczbafolderow++;
        return f;
    }

    void wyswietlFoldery(){
        if(!this->czyZalogowany){
            cout << "Uzytkownik nie jest zalogowany !\n";
            return;
        }

        cout << "Aktualne foldery uzytkownika " << this->login << ": " << endl;
        for(int i = 0; i < this->liczbafolderow ; i++){
            cout << "-" << this->foldery[i]->nazwa << endl;
        }
    }

    void utworzNotatke(string nazwafolderu, string nazwanotatki, string zawartosc){
        if(!this->czyZalogowany){
            cout << "Uzytkownik nie jest zalogowany !\n";
            return;
        }

        for(int i = 0 ; i < this->liczbafolderow ; i++){
            if(this->foldery[i]->nazwa == nazwafolderu){
                Notatka* n = new Notatka(nazwanotatki, zawartosc);
                this->foldery[i]->dodajNotatke(n);
            }
        }
    }

    void wyswietlNotatki(){
        if(!this->czyZalogowany){
            cout << "Uzytkownik nie jest zalogowany !\n";
            return;
        }
        for(int i = 0; i < this->liczbafolderow ; i++){
            cout << this->foldery[i]->nazwa << ": " << endl;
            this->foldery[i]->wyswietl();
        }
    }

    void wyswietlZawartoscNotatki(string nazwaf, string nazwan){
        if(!this->czyZalogowany){
            cout << "Uzytkownik nie jest zalogowany !\n";
            return;
        }    
        for(int i = 0 ; i < this->liczbafolderow ; i++){
            if(this->foldery[i]->nazwa == nazwaf){
                this->foldery[i]->wyswietlZawartoscNotatki(nazwan);
                return;
            }
        }
    }

    void usunFolder(KontoAdministatora* admin, Folder* folder){
        cout << "Uzytkownik " << this->login << " wysyla prosbe u usuniecie folderu " << folder->nazwa << endl;
        admin->usunFolder(folder);

    }

};



//Najwazniejsza klasa
class MenagerUzytkownikow{
    public: 
    string nazwa;
    KontoAdministatora* administratorzy[10];
    KontoUzytkownika* uzytkownicy[100];
    int zarejestrowanychAdmin = 0;
    int zarejestrowanychUzyt = 0;

    MenagerUzytkownikow(string nazwa){
        this->nazwa = nazwa;
    }

    KontoUzytkownika* utworzUzytkownika(string login, string haslo){
        KontoUzytkownika* user1 = new KontoUzytkownika(login,haslo);
        this->uzytkownicy[zarejestrowanychUzyt] = user1;
        zarejestrowanychUzyt++;
        return user1;
    }

    KontoAdministatora* utworzAdministratora(string login, string haslo){
        KontoAdministatora* admin1 = new KontoAdministatora(login,haslo);
        this->administratorzy[zarejestrowanychAdmin] = admin1;
        zarejestrowanychAdmin++;
        return admin1;
    }

    KontoAdministatora* zalogujA(string login, string haslo){
        for(int i = 0; i < this->zarejestrowanychAdmin ; i++){
            if(this->administratorzy[i]->login == login && this->administratorzy[i]->haslo == haslo){
                cout << "Zalogowano poprawnie administratora " << login << " !!!" << endl;
                this->administratorzy[i]->czyZalogowany = true;
                return this->administratorzy[i];
            }
        }
        throw runtime_error("Nie udaolo sie zalogowac administratora\n");
    }

    KontoUzytkownika* zalogujU(string login, string haslo){
        for(int i = 0; i < this->zarejestrowanychUzyt ; i++){
            if(this->uzytkownicy[i]->login == login && this->uzytkownicy[i]->haslo == haslo){
                cout << "Zalogowano poprawnie uzytkownika " << login << " !!!" << endl;
                this->uzytkownicy[i]->czyZalogowany = true;
                return this->uzytkownicy[i];
            }
        }
        throw runtime_error("Nie udalo sie zalogowac uzytkownika\n");
    }
};


int main(){
    MenagerUzytkownikow* menager = new MenagerUzytkownikow("menager");
    KontoAdministatora* admin1 = menager->utworzAdministratora("admin", "admin");
    KontoUzytkownika* user1 = menager->utworzUzytkownika("user1","trudnehaslo");
    
    admin1 = menager->zalogujA("admin","admin");
    user1 = menager->zalogujU("user1","trudnehaslo");
    

    Folder* folder1 = user1->utworzFolder("folder1");
    Folder* folder2 = user1->utworzFolder("folder2");
    user1->wyswietlFoldery();
    //user1->utworzNotatke("folder1","notatka1","Wypadaloby sie pouczyc");
    //user1->utworzNotatke("folder1","notatka2","Moze kiedy indziej");
    //user1->utworzNotatke("folder1","notatka3","Jeszcze mamy duzo czasu");
    //user1->wyswietlNotatki();
    //user1->wyswietlZawartoscNotatki("folder1","notatka3");

    //user1.utworzFolder("folder");
    user1->usunFolder(admin1,folder1);
    return 0;
}