#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

struct pt {
    ld x, y;
    int id;
};

struct cmp_x {
    bool operator()(const pt &a, const pt &b) const {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    }
};

struct cmp_y {
    bool operator()(const pt &a, const pt &b) const {
        return a.y < b.y;
    }
};

int n;
vector<pt> a;

double mindist;
pair<int, int> best_pair;

void upd_ans(const pt &a, const pt &b) {
    double dist = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    if (dist < mindist) {
        mindist = dist;
        best_pair = {a.id, b.id};
    }
}

vector<pt> t;

void rec(int l, int r) {
    if (r - l <= 3) {
        for (int i = l; i < r; ++i) {
            for (int j = i + 1; j < r; ++j) {
                upd_ans(a[i], a[j]);
            }
        }
        sort(a.begin() + l, a.begin() + r, cmp_y());
        return;
    }

    int m = (l + r) >> 1;
    ld midx = a[m].x;
    rec(l, m);
    rec(m, r);

    merge(a.begin() + l, a.begin() + m, a.begin() + m, a.begin() + r, t.begin(), cmp_y());
    copy(t.begin(), t.begin() + r - l, a.begin() + l);

    int tsz = 0;
    for (int i = l; i < r; ++i) {
        if (abs(a[i].x - midx) < mindist) {
            for (int j = tsz - 1; j >= 0 && a[i].y - t[j].y < mindist; --j)
                upd_ans(a[i], t[j]);
            t[tsz++] = a[i];
        }
    }
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    //freopen("error.txt", "w", stderr);

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (cin >> n, n) {
        a.resize(n);
        t.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i].x >> a[i].y;
            a[i].id = i;
        }
        vector<pt> b = a; // copy of a
        sort(a.begin(), a.end(), cmp_x());
        mindist = 1E20;
        rec(0, n);
        if (mindist < 10000) {
            cout << fixed << setprecision(4) << mindist << endl;
        } else {
            cout << "INFINITY" << endl;
        }
    }

    cerr << "time taken : " << (float) clock() / CLOCKS_PER_SEC << " secs" << endl;
    return 0;
}