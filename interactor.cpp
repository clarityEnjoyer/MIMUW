#include <bits/stdc++.h>
#include "zbior_ary.h"
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

#define int long long 
#define min(a, b) (((a) < (b)) ? (a) : (b))

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