#include <bits/stdc++.h>
// #include "zbior_ary.h"
#define rep(i, n) for(int i= 0; i<(n); i++)
#define reps(i,s, n) for(int i= (s); i<(n); i++)
#define each(a, x) for (auto &a : x)
#define vv(T) vector<T>
#define endl '\n'
#define sz(x) (int)x.size()
#define ll long long
#define all(c) begin(c), end(c)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

#define wr cout<<
#define wre wr endl;
#define wrut(a) {wre each(i,(a))wr i<<" "; wre}
#define wrot(a,b,c) {wre wr a; wr " "; wr b; wr " "; wr c; wre}
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>

// #include "zbior_ary.h"
#define int long long 
#define min(a, b) (((a) < (b)) ? (a) : (b))
int Q;// >0

typedef struct ciag{
  int p, k;
}ciag;

int mod (const ciag *x){
  int _g = x->p%Q;
  if (_g<0)_g+=Q;
  return _g;
}

typedef struct CiagVec{
  ciag *data;
  size_t size;//jako indeks wskazuje pierwszy "element" za vectorem :)
  size_t capacity;
}CiagVec;

void add(CiagVec* V, ciag c){
  if (V->data == NULL){
    //the vector is empty
    V->data = (ciag*)malloc(sizeof(ciag));
    V->capacity = 1;
  }else if (V->size>=V->capacity){
    V->capacity *= 2;
    V->data = (ciag*)realloc(V->data, V->capacity * sizeof(ciag));
  }
  *(V->data + V->size++) = c;//dodajmy na koncu nowy element :D
}

CiagVec deepcopy(CiagVec* v) {
    CiagVec kopia = {0};
    kopia.capacity = v->capacity;
    kopia.size = v->size;
    kopia.data = (ciag*)malloc(kopia.capacity * sizeof(ciag));
    memcpy(kopia.data, v->data, kopia.size * sizeof(ciag)); // Kopiuje dane
    return kopia;
}

//zbior_ary to de facto nic innego jak vector ciagów!
typedef struct zbior_ary {
  CiagVec ciagi;
}zbior_ary;

int len(zbior_ary X){
  return (int)X.ciagi.size;
}

zbior_ary ciag_arytmetyczny(int a, int q, int b){
  Q=q;
  zbior_ary _new={0};
  ciag tmp = {a,b};
  add(&_new.ciagi, tmp);
  return _new;
}

zbior_ary singleton(int a){
  zbior_ary _new={0};
  ciag tmp = {a,a};
  add(&_new.ciagi, tmp);
  return _new;
}

void FREE(zbior_ary *X){
  free(X->ciagi.data);
  X->ciagi.data=NULL;
}

zbior_ary suma(zbior_ary orygA, zbior_ary orygB){
  zbior_ary A = {0};
  A.ciagi = deepcopy(&orygA.ciagi);
  zbior_ary B = {0};
  B.ciagi = deepcopy(&orygB.ciagi);
  zbior_ary _new={0};
  int iter_A=0, iter_B=0;
  int len_A=len(A), len_B=len(B);
  CiagVec* wynik = &_new.ciagi;
  // w obrebie jednego zbioru ciagi są rozłączne!
  while(iter_A<len_A&&iter_B<len_B){
    ciag *a = A.ciagi.data + iter_A,*b = B.ciagi.data + iter_B;//a i b to aktualnie rozpatrywane podciągi z A i B
    if (mod(a)<mod(b)){
      //a jest w porządku wczesniej niz b
      add(wynik,*a);
      iter_A++;
      continue;
    }
    if (mod(a)>mod(b)){
      add(wynik,*b);
      iter_B++;
      continue;
    }
    //jesli są rowne modula to patrze po początkach (i koncach)
    if ((a->p>=b->p&&a->p<=b->k+Q)||(b->p>a->p&&b->p<=a->k+Q)){
      //przecinaja się - jeden zjada drugiego
      if (b->k>a->k){
        b->p=min(b->p, a->p);
        iter_A++;
      }
      else {
        a->p=min(b->p, a->p);
        iter_B++;
      }
      //ustawiam tak, aby zachować wlasnosc rozłącznosci!
      continue;
    }

    if (a->p>=b->p){
      add(wynik,*b);
      iter_B++;
    }
    else {
      add(wynik,*a);
      iter_A++;
    }
  }
  //wszystko co zostało należy albo do A, albo do B. to znaczy ze reszta podciągów jest parami rozłączna (to wynika z wczesniejszej konstrukcji)
  while(iter_A<len_A)add(wynik,A.ciagi.data[iter_A++]);
  while(iter_B<len_B)add(wynik,B.ciagi.data[iter_B++]);
  FREE(&A);
  FREE(&B);
  return _new;
}

zbior_ary iloczyn(zbior_ary orygA, zbior_ary orygB){
  zbior_ary A = {0};
  A.ciagi = deepcopy(&orygA.ciagi);
  zbior_ary B = {0};
  B.ciagi = deepcopy(&orygB.ciagi);
  zbior_ary _new={0};
  int iter_A=0, iter_B=0;
  int len_A=len(A), len_B=len(B);
  CiagVec* wynik = &_new.ciagi;
  // w obrebie jednego zbioru ciagi są rozłączne!
  while(iter_A<len_A&&iter_B<len_B){
    ciag *a = A.ciagi.data + iter_A,*b = B.ciagi.data + iter_B;//a i b to aktualnie rozpatrywane podciągi z A i B
    if (mod(a)<mod(b)){
      //a jest w porządku wczesniej niz b
      iter_A++;
      continue;
    }
    if (mod(a)>mod(b)){
      iter_B++;
      continue;
    }
    //jesli są rowne modula to patrze po początkach (i koncach)
    if (a->p>=b->p){
      if (a->p<=b->k){
        //jest miedzy nimi przeciecie
        ciag _t = {a->p,min(b->k, a->k)};
        add(wynik,_t);
        if (a->k<b->k)iter_A++;
        else iter_B++;
      }
      //nie ma przeciecia czyli ---bp----bk--ap---ak
      else iter_B++;
    }

    //symetryczny - drugi - przypadek
    else{
      if (b->p<=a->k){
        //jest miedzy nimi przeciecie
        ciag _t = {b->p,min(b->k, a->k)};
        add(wynik,_t);
        if (a->k<b->k)iter_A++;
        else iter_B++;
      }
      //nie ma przeciecia czyli ---ap----ak--bp---bk
      else iter_A++;
    }
  }
  //wszystko co zostało należy albo do A, albo do B. to znaczy ze reszta podciągów jest parami rozłączna (to wynika z wczesniejszej konstrukcji)
  //wiec przeciecia juz nie znajdziemy
  FREE(&A);
  FREE(&B);
  return _new;
}

zbior_ary roznica(zbior_ary orygA, zbior_ary orygB){
  zbior_ary A = {0};
  A.ciagi = deepcopy(&orygA.ciagi);
  zbior_ary B = {0};
  B.ciagi = deepcopy(&orygB.ciagi);
  zbior_ary _new={0};
  int iter_A=0, iter_B=0;
  int len_A=len(A), len_B=len(B);
  CiagVec* wynik = &_new.ciagi;
  // w obrebie jednego zbioru ciagi są rozłączne!
  while(iter_A<len_A&&iter_B<len_B){
    ciag *a = A.ciagi.data + iter_A,*b = B.ciagi.data + iter_B;//a i b to aktualnie rozpatrywane podciągi z A i B
    if (mod(a)<mod(b)){
      //a jest w porządku wczesniej niz b
      add(wynik,*a);
      iter_A++;
      continue;
    }
    if (mod(a)>mod(b)){
      iter_B++;
      continue;
    }
    //jesli są rowne modula to patrze po początkach (i koncach)
    if (a->p>=b->p){
      if (a->p<=b->k){
        //jest miedzy nimi przeciecie
        //po prostu obetnę 'a' tak, zeby tego przeciecia nie bylo i wstawie z powrotem
        a->p=b->k+Q;
        if (a->k<a->p)iter_A++;//po "obcieciu" a zdegenerował się   ----- b pokrywał a
        //teraz spróbuję też obciąć B :)
        b->p=a->k+Q;
        if (b->k<b->p)iter_B++;
      }
      //nie ma przeciecia czyli ---bp----bk--ap---ak
      else iter_B++;
    }

    //drugi - przypadek
    else{
      if (b->p<=a->k){
        //jest miedzy nimi przeciecie
        ciag _t = {a->p,(b->p)-Q};
        if (_t.k>=_t.p)add(wynik,_t);//jesli _t nie jest zdegenerowany to dodamy
        //poprawiamy a
        a->p=b->k+Q;
        if (a->k<a->p)iter_A++;//po "obcieciu" a zdegenerował się
        else iter_B++;//POWINNO DZIAŁAĆ XDD   bo ak >=bk+Q  --- czyyyyli b już mi nic nie da!
      }
      //nie ma przeciecia czyli ---ap----ak--bp---bk
      else {
        add(wynik,*a);
        iter_A++;
      }
    }
  }
  //wszystko co zostało należy albo do A, albo do B. to znaczy ze reszta podciągów jest parami rozłączna (to wynika z wczesniejszej konstrukcji)
  //dodajmy resztę z A ;)
  while(iter_A<len_A)add(wynik,A.ciagi.data[iter_A++]);
  FREE(&A);
  FREE(&B);
  return _new;
}

bool nalezy(zbior_ary A, int b){
  int bmod=b%Q;
  if (bmod<0)bmod+=Q;
  int l,r,mid;
  //będziemy szukać przedziału, gdzie ciągi mają ten sam mod co b.
  //a w nim wyszukamy juz po początku
  //to sa 3 binsearche: mod_lowerbound, mod_upperbound i poczatek_lowerbound
  l=0; r=len(A);
  while(l<r){
    mid=(l+r)>>1;
    if (mod(&A.ciagi.data[mid])>=bmod)r=mid;
    else l=mid+1;
  }
  if (l>=len(A)||mod(&A.ciagi.data[l])!=bmod)return false;//sprawdzamy że 1)istnieje ciag o mod >= modb. 2)istnieje ciag o mod==modb
  int mod_lowerbound =l;

  r=len(A);//l moze zostac nie zmienione;)
  while (l<r){
    mid=(l+r)>>1;
    if (mod(&A.ciagi.data[mid])>bmod)r=mid;
    else l=mid+1;
  }
  //r jest juz na upperbound  - wskazuje element o p > b (lub koniec tablicy)
  // wr "--->r ";wr r; wre
  r--;
  //ustawiam l ;)
  l = mod_lowerbound;
  // na przedziale [l,r] mamy mod == modb
  //do tego momentu powinno byc git. teraz mam obsluzyc indeksy
  while(l<r){
    mid=(l+r)>>1;
    //znajdzmy pierwszy ciag taki, ze jego pocz >b (wiemy ze jesli istnieje ciag o pocz ==b 
    ///to jest on i tak tylko jeden, bo podciagi są rozlaczne!
    if (A.ciagi.data[mid].p>b)r=mid;
    else l=mid+1;
  }
  ///ROZWAZ TO UWAZNIE!!!
  // [l]>>>>>>>>>>>[r] wszystkie mają p wieksze od b!
  //oczywiscie jesli pocz > b to na nic nam to
  // tez moglo byc tak, ze zaden nie ma p>b   [l]<<<<<<<[r]

  //[lb,ub] to na pewno valid przedział był
  if (A.ciagi.data[l].p>b){
    if (l>mod_lowerbound)l--;//rzeczywiscie znalazłem większy. czy moge zmniejszyc l pozostając w [lb,ub]?
    else return false;
  }
  //pocz <=b
  if (A.ciagi.data[l].p<=b&&b<=A.ciagi.data[l].k)return true;//modula juz są zgodne:)
  return false;
}

unsigned moc(zbior_ary A){
  int wynik=0;
  int n = A.ciagi.size;
  for (int i=0; i<n; i++){
    wynik+=(A.ciagi.data[i].k - A.ciagi.data[i].p)/Q +1;
  }
  return wynik;
}

unsigned ary(zbior_ary A){
  return len(A);
}

void print(zbior_ary A){
    vv(int)wyn;
    int n = A.ciagi.size;
    for (int i=0; i<n; i++)
      for (int j=A.ciagi.data[i].p; j<=A.ciagi.data[i].k; j+=Q)wyn.pb(j);
    sort(all(wyn));
    each(i,wyn)wr i<<" ";
    wre
}


signed main()
{
    // ios_base::sync_with_stdio(false);
    // cin.tie(0);

    int t;
    bool p;
    cin >> t >> p;

    vector<zbior_ary> v;

    for (int i = 0; i < t; ++i)
    {
        int type;
        cin >> type;

        if (type == 0){
            int a, q, b;
            cin >> a >> q >> b;
            v.push_back(ciag_arytmetyczny(a, q, b));
            if (p) print(v.back());
        }
        else if (type == 1)
        {
            int a;
            cin >> a;
            v.push_back(singleton(a));
            if (p) print(v.back());
        }
        else if (type == 2)
        {
            int a, b;
            cin >> a >> b;
            v.push_back(suma(v[a], v[b]));
            if (p) print(v.back());
        }
        else if (type == 3)
        {
            int a, b;
            cin >> a >> b;
            v.push_back(iloczyn(v[a], v[b]));
            if (p) print(v.back());
        }
        else if (type == 4)
        {
            int a, b;
            cin >> a >> b;

            v.push_back(roznica(v[a], v[b]));
            if (p) print(v.back());
        }
        else if (type == 5)
        {
            int idx, a;
            cin >> idx >> a;
            cout << nalezy(v[idx], a) << '\n';
        }
        else if (type == 6)
        {
            int a;
            cin >> a;
            cout << moc(v[a]) << '\n';
        }
        else if (type == 7)
        {
            int a;
            cin >> a;
            cout << ary(v[a]) << '\n';
        }
    }
    each (z, v)FREE(&z);
}