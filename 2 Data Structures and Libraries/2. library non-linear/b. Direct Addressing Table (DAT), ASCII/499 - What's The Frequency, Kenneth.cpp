#include <bits/stdc++.h>

using namespace std;

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    //freopen("error.txt", "w", stderr);

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string buf;
    while (getline(cin, buf)) {
        int charset[128] = {};
        for (char c : buf) {
            if (isalpha(c)) charset[c]++;
        }

        int myMax = 0;
        for (int i = 0; i < 128; i++) myMax = max(myMax, charset[i]);
        for (int i = 0; i < 128; i++) if (charset[i] == myMax) cout << (char) i;
        cout << " " << myMax << endl;

    }

    cerr << "time taken : " << (float) clock() / CLOCKS_PER_SEC << " secs" << endl;
    return 0;
}
