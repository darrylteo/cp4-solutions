#include <bits/stdc++.h>

using namespace std;

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    //freopen("error.txt", "w", stderr);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int a,b;
    cin >> a >> b;
    cout << __gcd(a,b) << endl;

    cerr << "time taken : " << (float) clock() / CLOCKS_PER_SEC << " secs\n";
    return 0;
}