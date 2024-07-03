#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

ull nCk(ull n, ull k) {
    if (k > n) return 0;
    if (k * 2 > n) k = n - k;
    if (k == 0) return 1;

    ull result = n;
    for (ull i = 2; i <= k; ++i) {
        result *= (n - i + 1);
        result /= i;
    }
    return result;
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    //freopen("error.txt", "w", stderr);

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        ull n, k;
        cin >> n >> k;
        cout << nCk(n, k - 1) << '\n';
    }

    cerr << "time taken : " << (float) clock() / CLOCKS_PER_SEC << " secs" << '\n';
    return 0;
}


