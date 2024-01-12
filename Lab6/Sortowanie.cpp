#include <iostream>

using namespace std;

template<typename T, typename Sort> class Kolekcja{
    public: // Testowo
    T tablicaDanych[100];
    Sort rodzajSortowania;
    int counter = 0;
    public:
    void dodaj(T wartosc);
    T zdejmij();
    void posortuj();
    void wydrukuj();
    void oproznij();

};

template<typename T, typename Sort> class LIFO : public Kolekcja<T, Sort>{
    public:
    LIFO(Sort rdzSort){
        this->rodzajSortowania = rdzSort;
    };
    void dodaj(T wartosc){
        if(this->counter < 99){
            this->tablicaDanych[this->counter] = wartosc;
            this->counter++;
        }else cout << "Tablica jest pelna, nie dodano elementu";
    }
    void wydrukuj(){
        cout << "Aktualny wydruk tablicy: \n";
        for(int i = 0 ; i < this->counter; i++){
            cout << this->tablicaDanych[i] << " ";
        }
        cout << endl;
    }
    void posortuj(){
        this->rodzajSortowania.posortuj(this->tablicaDanych,this->counter);
    };
    T zdejmij(){
        if(this->counter > 0){
            this->counter--;
            return this->tablicaDanych[this->counter]; 
        }else cout << "Tablica jest pusta, brak elementu do zwrotu\n";
            return -1;

    }
    void oproznij(){
        this->counter = 0;
    }
};

template<typename T, typename Sort> class FIFO : public Kolekcja<T, Sort>{
    public:
    FIFO(Sort rdzSort){
        this->rodzajSortowania = rdzSort;
    };
        void dodaj(T wartosc){
        if(this->counter < 99){
            this->tablicaDanych[this->counter] = wartosc;
            this->counter++;
        }else cout << "Tablica jest pelna, nie dodano elementu";
    }
    void wydrukuj(){
        cout << "Aktualny wydruk tablicy: \n";
        for(int i = 0 ; i < this->counter; i++){
            cout << this->tablicaDanych[i] << " ";
        }
        cout << endl;
    }
    void posortuj(){
        this->rodzajSortowania.posortuj(this->tablicaDanych,this->counter);
    };
    void zdejmij(){
        if(this->counter > 0)
        int pom = this->tablicaDanych[0];
        for(int i = 0 ; i < this->counter ; i++){
            this->tablicaDanych[i] = this->tablicaDanych[i+1];
        }
        this->counter--;
    }
    void oproznij(){ //Nie usuwa elementow tylko ustawia counter na 0 przez co nowe elementy beda nadpisawac stare
        //wyswietlanie i zdejmowanie dziala na podstawie countera wiec stare dane nie beda brane pod uwage 
        this->counter = 0;
    }
};

template<typename T> class Sortowanie{
    public:
    void posortuj(T* tablica, int rozmiar);
};

template<typename T> class SortowanieMalejaco : public Sortowanie<T>{
    public:
    void posortuj(T* tab, int size){
        cout << "Sorturj malejaco...\n";
        int gap = size / 1.3;
        bool swapped = true;
        while (gap > 1 || swapped) {
            if (gap > 1) gap /= 1.3;

            swapped = false;

            for (int i = 0; i < size - gap; i++) {
                int j = i + gap;
                if (tab[i] < tab[j]) {
                    swap(tab[i], tab[j]);
                    swapped = true;
                }
            }
        }
    }
};

template<typename T> class SortowanieRosnaco : public Sortowanie<T>{
    public:
    void posortuj(T* tab, int size){
        cout << "Sortuje rosnaco...\n";
        int gap = size / 1.3;
        bool swapped = true;
        while (gap > 1 || swapped) {
            if (gap > 1) gap /= 1.3;

            swapped = false;

            for (int i = 0; i < size - gap; i++) {
                int j = i + gap;
                if (tab[i] > tab[j]) {
                    swap(tab[i], tab[j]);
                    swapped = true;
                }
            }
        }
    }
};





int main(){
    SortowanieMalejaco<double> sDesc; 
    SortowanieRosnaco<double> sAsc;

    FIFO<double, SortowanieMalejaco <double>> fifo(sDesc); 
    LIFO<double, SortowanieRosnaco <double>> lifo2(sAsc); 


    fifo.dodaj(123.32);
    fifo.dodaj(13.32);
    fifo.dodaj(12.32);
    fifo.dodaj(23.32);
    fifo.dodaj(1233.32);

    lifo2.dodaj(123.32);
    lifo2.dodaj(13.32);
    lifo2.dodaj(12.32);
    lifo2.dodaj(23.32);
    lifo2.dodaj(1233.32);
    
    fifo.wydrukuj();

    fifo.posortuj();

    fifo.wydrukuj();
    fifo.oproznij();

    fifo.wydrukuj();

    fifo.dodaj(34.32);
    fifo.dodaj(4323.322);
    fifo.posortuj();
    fifo.wydrukuj();

    lifo2.posortuj();
    lifo2.wydrukuj();


    return 0;
}