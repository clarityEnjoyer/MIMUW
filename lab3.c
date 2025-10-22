#include <stdbool.h>

int global_q;

typedef struct zbior_ary {
    int ile_podciagow=1;// nasze ary(A)
    int poczatki[],konce[];
} zbior_ary;



// Funkcja daje w wyniku zbior reprezentujacy ciag arytmetyczny o elemencie poczatkowym a, końcowym b i roznicy q>0, tj. {a,a+q,...,b}.
// Mozesz zalozyc, ze we wszystkich zapytaniach w danym tescie wartosc q bedzie taka sama.
// Mozesz zalozyc, ze ta funkcja zostanie wywolana jako pierwsza.
zbior_ary ciag_arytmetyczny(int a, int q, int b){
    global_q=q;
    zbior_ary nowy_zbior;
    nowy_zbior.poczatki = malloc(sizeof(int));
    nowy_zbior.konce = malloc(sizeof(int));
    nowy_zbior.poczatki[0]=a;
    nowy_zbior.konce[0]=b;
}

// Daje w wyniku zbior zlozony z samego elementu a, tj. {a}.
zbior_ary singleton(int a);

// Daje w wyniku zbior reprezentujacy teoriomnogosciowa sume zbiorow A i B.
zbior_ary suma(zbior_ary A, zbior_ary B);

// Daje w wyniku zbior reprezentujacy czesc wspolna zbiorow A i B.
zbior_ary iloczyn(zbior_ary A, zbior_ary B);

// Daje w wyniku zbior A \ B.
zbior_ary roznica(zbior_ary A, zbior_ary B);

// Daje w wyniku true wtw. gdy liczba b nalezy do zbioru A.
bool nalezy(zbior_ary A, int b);

// Wynikiem funkcji jest liczba elementow w zbiorze A.
unsigned moc(zbior_ary A){
    int count=0;
    for(int i=0;i<A.ile_podciagow;i++){
        count+=((A.konce[i]-A.poczatki[i])/global_q)+1;
    }
    return count;
}

// Wynikiem funkcji jest Ary_q(A), czyli minimalna liczba parami rozlacznych ciagow arytmetycznych o roznicy q, ktorych suma jest zbior A.
unsigned ary(zbior_ary A){
    return A.ile_podciagow;
}