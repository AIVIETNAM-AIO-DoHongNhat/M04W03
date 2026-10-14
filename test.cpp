#include<bits/stdc++.h>
#define ll long long
using namespace std;

// se[k] = crack[k].se: vị trí cuối cùng mà giá trị k xuất hiện trong dãy Golomb.
// crack[k].fi = se[k-1] + 1, nên chỉ cần lưu se (tiết kiệm một nửa bộ nhớ).
vector<ll> se;
ll q = 1;   // con trỏ chỉ đi tiến: giá trị q mà vị trí i nằm trong crack[q]

// Sinh thêm se[] cho tới chỉ số k
void gen(ll k){
    while((ll)se.size() <= k){
        ll i = se.size();
        while(!(se[q-1] < i && i <= se[q])) q++;
        se.push_back(se[i-1] + q);   // giá trị i xuất hiện a_i = q lần
    }
}

int main(){
    ll N, MOD;
    cin >> N >> MOD;
    se.reserve(11000000);   // N = 1e18 cần khoảng 1.01e7 phần tử (~88MB)
    se = {0, 1, 3};

    // Tổng a_1 + ... + a_N = sum_i i * (số lần i xuất hiện trong N vị trí đầu).
    // Mọi giá trị i nằm trong crack[p] đều xuất hiện đúng p lần,
    // nên xử lý cả khoảng [crack[p].fi, crack[p].se] một lần thay vì từng i.
    __int128 ans = 0;
    ll pos = 0;   // số vị trí đã được phủ bởi các giá trị trước khoảng hiện tại
    for(ll p = 1; ; p++){
        gen(p);
        ll lo = se[p-1] + 1, hi = se[p];
        ll cnt = hi - lo + 1;
        if(pos + (__int128)cnt * p <= N){
            // cả khoảng nằm trọn trong N vị trí: cộng p * (lo + ... + hi)
            __int128 s = (__int128)cnt * (lo + hi) / 2;
            ans = (ans + (__int128)p * (s % MOD)) % MOD;
            pos += cnt * p;
            if(pos == N) break;
        } else {
            // chỉ f giá trị đầu của khoảng nằm trọn trong N vị trí
            ll f = (N - pos) / p;
            __int128 s = (__int128)f * (2 * lo + f - 1) / 2;
            ans = (ans + (__int128)p * (s % MOD)) % MOD;
            // giá trị lo + f bị cắt ở vị trí N, chỉ xuất hiện r lần
            ll r = N - pos - f * p;
            ans = (ans + (__int128)((lo + f) % MOD) * r) % MOD;
            break;
        }
    }
    cout << (ll)ans << '\n';
    return 0;
}
