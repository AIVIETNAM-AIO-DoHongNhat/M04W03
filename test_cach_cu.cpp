#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct dm {
    ll fi;
    ll se;
};
vector<dm> crack = {{0, 0}, {1, 1}, {2, 3}};
ll q = 1;
dm get(ll k){
    while((ll)crack.size() <= k){
        ll j = crack.size();
        dm c;
        c.fi = crack[j-1].se + 1;
        while(!(crack[q].fi <= j && j <= crack[q].se)) q++;
        c.se = c.fi + q - 1;
        crack.push_back(c);
    }
    return crack[k];
}
int main(){
    ll N, MOD;
    cin >> N >> MOD;
    dm cur = {2, 3};
    ll i = 2, p = 1;
    unsigned __int128 ans = 5; 
    while(cur.se < N){
        i++;
        cur.fi = cur.se + 1;
        while(i > get(p).se) p++;
        cur.se = cur.fi + p - 1;
        ans += (unsigned __int128)i * (min(cur.se, N) - cur.fi + 1);   // cắt khối cuối tại N
    }
    cout << (ll)(ans % MOD);
    return 0;
}
