#include <bits/stdc++.h>

using namespace std;

// ._. decided to read the editorial. it's on page 12 https://www.comp.nus.edu.sg/~acmicpc/2015/ACM2015_ans.pdf
// imagine the \ touches the |
//                  |___\
//                      |__\
//                          |_\
//                            |\
// the above is one quadrant. we put less steep ones above and more steep below
// we generate these vals using gcd
// n triangles generated can make a polygon with 4*n sides

struct tri {
    int l, h;

    // flatter gradient ones 1st 平らな勾配のものを最初に << generated by copilot lol pretty 上手い
    bool operator<(const tri &other) const {
        return (double) l / h < (double) other.l / other.h;
    }
};

// multiplier for the 4 quadrants. goes up right, up left, down left, down right back to start
const int dirx[] = {1, -1, -1, 1};
const int diry[] = {1, 1, -1, -1};

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    //freopen("error.txt", "w", stderr);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    cin >> n;
    vector<tri> tris;
    tris.push_back({1, 1});
    int idx = 3;
    while (tris.size() < n / 4 + 1) { // we might generate some extra triangles
        for (int i = 1; i <= idx / 2; ++i) {
            if (__gcd(i, idx - i) == 1) {
                tris.push_back({i, idx - i}); // e.g. 1,2
                tris.push_back({idx - i, i}); // e.g. 2,1
            }
        }
        ++idx;
    }
    sort(tris.begin(), tris.end());
    reverse(tris.begin(), tris.end());
    int x = 2e7, y = 0; // start mid bot (assume usual graph axes with top right as positive)
//    cout << "(" << x << "," << y << ")" << '\n';
    cout << x << " " << y << '\n';
    int cnt = 1;
    for (int d = 0; d < 4; ++d) {
        for (int i = 0; i < ceil(n / 4.0); ++i) {
            x += tris[i].l * dirx[d];
            y += tris[i].h * diry[d];
//            cout << "(" << x << "," << y << ")" << '\n'; // use this to plot in desmos. it looks pretty
            cout << x << " " << y << '\n';
            ++cnt;
            if (cnt == n) {
                return 0;
            }
        }
        reverse(tris.begin(), tris.end());
    }

    cerr << "time taken : " << (float) clock() / CLOCKS_PER_SEC << " secs\n";
    return 0;
}
