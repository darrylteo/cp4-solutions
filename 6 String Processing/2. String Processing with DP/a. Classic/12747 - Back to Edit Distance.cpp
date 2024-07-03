#include <bits/stdc++.h>

using namespace std;

// ref: https://morris821028.github.io/2014/10/03/oj/uva/uva-12747/

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    //freopen("error.txt", "w", stderr);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T, cases = 1;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n+1), b(n+1);
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            a[x] = i; // a[k] tells the index of k in the array. e.g. a = 2 3 1. a[2] = 0
        }
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            b[i] = a[x]; // b[i] tells the index of x in the array a. e.g. b = 3 2 1. a[3] = 1, b[0] = 1, b[1] = 0, b[2] = 2
        }
        // b is the important matrix. we can ignore a now.
        // we find longest increasing subsequence because if b increasing means it is same order as a
        // the non increasing ones will be removed/inserted
        vector<int> v;
        v.push_back(b[0]);
        for (int i = 1; i < n; i++) {
            int pos = upper_bound(v.begin(), v.end(), b[i]) - v.begin();
            if (pos == v.size()) {
                v.push_back(b[i]);
            } else {
                v[pos] = b[i];
            }
        }
        cout << "Case " << cases++ << ": " << (n - v.size()) * 2 << '\n';
    }

    cerr << "time taken : " << (float) clock() / CLOCKS_PER_SEC << " secs" << endl;
    return 0;
}