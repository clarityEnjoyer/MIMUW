#include <bits/stdc++.h>
using namespace std;
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
int Q;

struct ciag{
  int p, k;
  inline int mod (){
    return p<0? (-p)%Q : p%Q;
  }
  void write(){
    wrot (p, k, mod())
  }
};

typedef struct zbior_ary {
  vector<ciag>ciagi;
  //ciagi będą uporzadkowane najpierw wg rosnących reszt mod q, a potem wg rosnących początków. 
  int len(){
    return (int)ciagi.size();
  }
  void i();
}zbior_ary;

zbior_ary ciag_arytmetyczny(int a, int q, int b){
  Q=q;
  zbior_ary _new;
  _new.ciagi.pb({a,b});
  return _new;
}

zbior_ary singleton(int a){
  zbior_ary _new;
  _new.ciagi.pb({a,a});
  return _new;
}

zbior_ary suma(zbior_ary A, zbior_ary B){
  int iter_A=0, iter_B=0;
  int len_A=A.len(), len_B=B.len();
  vector<ciag>wynik;
  // w obrebie jednego zbioru ciagi są rozłączne!
  while(iter_A<len_A&&iter_B<len_B){
    ciag *a = &A.ciagi[iter_A],*b = &B.ciagi[iter_B];//a i b to aktualnie rozpatrywane podciągi z A i B
    if (a->mod()<b->mod()){
      //a jest w porządku wczesniej niz b
      wynik.pb(*a);
      iter_A++;
      continue;
    }
    if (a->mod()>b->mod()){
      wynik.pb(*b);
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
      wynik.pb(*b);
      iter_B++;
    }
    else {
      wynik.pb(*a);
      iter_A++;
    }
  }
  //wszystko co zostało należy albo do A, albo do B. to znaczy ze reszta podciągów jest parami rozłączna (to wynika z wczesniejszej konstrukcji)
  while(iter_A<len_A)wynik.pb(A.ciagi[iter_A++]);
  while(iter_B<len_B)wynik.pb(B.ciagi[iter_B++]);
  zbior_ary _new;
  _new.ciagi=wynik;
  return _new;
}

// Daje w wyniku zbior reprezentujacy czesc wspolna zbiorow A i B.
zbior_ary iloczyn(zbior_ary A, zbior_ary B){
  int iter_A=0, iter_B=0;
  int len_A=A.len(), len_B=B.len();
  vector<ciag>wynik;
  // w obrebie jednego zbioru ciagi są rozłączne!
  while(iter_A<len_A&&iter_B<len_B){
    ciag *a = &A.ciagi[iter_A],*b = &B.ciagi[iter_B];//a i b to aktualnie rozpatrywane podciągi z A i B
    if (a->mod()<b->mod()){
      //a jest w porządku wczesniej niz b
      iter_A++;
      continue;
    }
    if (a->mod()>b->mod()){
      iter_B++;
      continue;
    }
    //jesli są rowne modula to patrze po początkach (i koncach)
    if (a->p>=b->p){
      if (a->p<=b->k){
        //jest miedzy nimi przeciecie
        ciag _t = {a->p,min(b->k, a->k)};
        wynik.pb(_t);
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
        wynik.pb(_t);
        if (a->k<b->k)iter_A++;
        else iter_B++;
      }
      //nie ma przeciecia czyli ---ap----ak--bp---bk
      else iter_A++;
    }
  }
  //wszystko co zostało należy albo do A, albo do B. to znaczy ze reszta podciągów jest parami rozłączna (to wynika z wczesniejszej konstrukcji)
  //wiec przeciecia juz nie znajdziemy
  zbior_ary _new;
  _new.ciagi=wynik;
  return _new;
}

// Daje w wyniku zbior A \ B.
zbior_ary roznica(zbior_ary A, zbior_ary B){
  int iter_A=0, iter_B=0;
  int len_A=A.len(), len_B=B.len();
  vector<ciag>wynik;
  // w obrebie jednego zbioru ciagi są rozłączne!
  while(iter_A<len_A&&iter_B<len_B){
    ciag *a = &A.ciagi[iter_A],*b = &B.ciagi[iter_B];//a i b to aktualnie rozpatrywane podciągi z A i B
    if (a->mod()<b->mod()){
      //a jest w porządku wczesniej niz b
      iter_A++;
      wynik.pb(*a);
      continue;
    }
    if (a->mod()>b->mod()){
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
        iter_B++;
      }
      //nie ma przeciecia czyli ---bp----bk--ap---ak
      else iter_B++;
    }

    //drugi - przypadek
    else{
      if (b->p<=a->k){
        //jest miedzy nimi przeciecie
        ciag _t = {a->p,(b->p)-Q};
        if (_t.k>=_t.p)wynik.pb(_t);//jesli _t nie jest zdegenerowany to dodamy
        //poprawiamy a
        a->p=b->k+Q;
        if (a->k<a->p)iter_A++;//po "obcieciu" a zdegenerował się
        else iter_B++;//POWINNO DZIAŁAĆ XDD   bo ak >=bk+Q  --- czyyyyli b już mi nic nie da!
      }
      //nie ma przeciecia czyli ---ap----ak--bp---bk
      else {
        wynik.pb(*a);
        iter_A++;
      }
    }
  }
  //wszystko co zostało należy albo do A, albo do B. to znaczy ze reszta podciągów jest parami rozłączna (to wynika z wczesniejszej konstrukcji)
  //dodajmy resztę z A ;)
  while(iter_A<len_A)wynik.pb(A.ciagi[iter_A++]);
  zbior_ary _new;
  _new.ciagi=wynik;
  return _new;
}

// Daje w wyniku true wtw. gdy liczba b nalezy do zbioru A.
bool nalezy(zbior_ary A, int b){
  int bmod=(b>0?b%Q:(-b)%Q);
  // wrot("szukamy ", b, bmod)
  int l,r,mid;
  //będziemy szukać przedziału, gdzie ciągi mają ten sam mod co b.
  //a w nim wyszukamy juz po początku
  //to sa 3 binsearche: mod_lowerbound, mod_upperbound i poczatek_lowerbound
  l=0; r=A.len();
  while(l<r){
    mid=(l+r)>>1;
    if (A.ciagi[mid].mod()>=bmod)r=mid;
    else l=mid+1;
  }
  if (l>=A.len()||A.ciagi[l].mod()!=bmod)return false;//sprawdzamy że 1)istnieje ciag o mod >= modb. 2)istnieje ciag o mod==modb
  // wr "etap1\n";
  int mod_lowerbound =l;
  r=A.len();//l moze zostac nie zmienione;)
  while (l<r){
    mid=(l+r)>>1;
    if (A.ciagi[mid].mod()>bmod)r=mid;
    else l=mid+1;
  }
  //r jest juz na upperbound  - wskazuje element o p > b (lub koniec tablicy)
  r--;
  //ustawiam l ;)
  l = mod_lowerbound;
  // na przedziale [l,r] mamy mod == modb
  while(l<r){
    mid=(l+r)>>1;
    //znajdzmy pierwszy ciag taki, ze jego pocz >b (wiemy ze jesli istnieje ciag o pocz ==b to jest on i tak tylko jeden)
    //bo podciagi są rozlaczne!
    if (A.ciagi[mid].p>b)r=mid;
    else l=mid+1;
  }
  //oczywiscie jesli pocz > b to na nic nam to
  if (l>=A.len()||A.ciagi[l].p>b)l--;
  // wr l << " xd"<<endl;
  //pocz <=b
  if (A.ciagi[l].p<=b&&b<=A.ciagi[l].k)return true;
  return false;
}

// Wynikiem funkcji jest liczba elementow w zbiorze A.
unsigned moc(zbior_ary A){
  int wynik=0;
  each(i,A.ciagi)wynik+=(i.k - i.p)/Q +1;
  return wynik;
}

// Wynikiem funkcji jest Ary_q(A), czyli minimalna liczba parami rozlacznych ciagow arytmetycznych o roznicy q, ktorych suma jest zbior A.
unsigned ary(zbior_ary A){
  return A.len();
}

void zbior_ary::i(){
  wrot(ary(*this),moc(*this), " - ary i moc");
  wr "ciagi: \n";
  each(a, this->ciagi)a.write();
  wre
}


signed main(){
ios_base::sync_with_stdio(0); cin.tie(NULL);

zbior_ary x = ciag_arytmetyczny(1,2,1'000'001);
zbior_ary y = ciag_arytmetyczny(11,2,101);
auto c = roznica(x,y);
c= suma(c,singleton(10));
zbior_ary d= ciag_arytmetyczny(2,2,12);

c= suma(c,d);
c.i();

c=roznica(c,ciag_arytmetyczny(97,2,105));
c.i();
int xd;
while(cin>>xd){
  wr xd << "\t \t" <<nalezy(c,xd);
  wre
}


}