#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define sz(a) int((a).size())
typedef vector<int> vi;
typedef double T; // long double, Rational, double + mod<P>...
typedef vector<T> vd;
typedef vector<vd> vvd;

const T eps = 1e-8, inf = 1 / .0;
#define MP make_pair
#define ltj(X) if(s == -1 || MP(X[j],N[j]) < MP(X[s],N[s])) s=j

struct LPSolver {
    int m, n;
    vi N, B;
    vvd D;

    LPSolver(const vvd &A, const vd &b, const vd &c) :
            m(sz(b)), n(sz(c)), N(n + 1), B(m), D(m + 2, vd(n + 2)) {
        FOR(i, 0, m) FOR(j, 0, n) D[i][j] = A[i][j];
        FOR(i, 0, m) {
            B[i] = n + i;
            D[i][n] = -1;
            D[i][n + 1] = b[i];
        }
        FOR(j, 0, n) {
            N[j] = j;
            D[m][j] = -c[j];
        }
        N[n] = -1;
        D[m + 1][n] = 1;
    }

    void pivot(int r, int s) {
        T *a = D[r].data(), inv = 1 / a[s];
        FOR(i, 0, m + 2) if (i != r && abs(D[i][s]) > eps) {
                T *b = D[i].data(), inv2 = b[s] * inv;
                FOR(j, 0, n + 2) b[j] -= a[j] * inv2;
                b[s] = a[s] * inv2;
            }
        FOR(j, 0, n + 2) if (j != s) D[r][j] *= inv;
        FOR(i, 0, m + 2) if (i != r) D[i][s] *= -inv;
        D[r][s] = inv;
        swap(B[r], N[s]);
    }

    bool simplex(int phase) {
        int x = m + phase - 1;
        for (;;) {
            int s = -1;
            FOR(j, 0, n + 1) if (N[j] != -phase) ltj(D[x]);
            if (D[x][s] >= -eps) return true;
            int r = -1;
            FOR(i, 0, m) {
                if (D[i][s] <= eps) continue;
                if (r == -1 || MP(D[i][n + 1] / D[i][s], B[i])
                               < MP(D[r][n + 1] / D[r][s], B[r]))
                    r = i;
            }
            if (r == -1) return false;
            pivot(r, s);
        }
    }

    T solve(vd &x) {
        int r = 0;
        FOR(i, 1, m) if (D[i][n + 1] < D[r][n + 1]) r = i;
        if (D[r][n + 1] < -eps) {
            pivot(r, n);
            if (!simplex(2) || D[m + 1][n + 1] < -eps) return -inf;
            FOR(i, 0, m) if (B[i] == -1) {
                    int s = 0;
                    FOR(j, 1, n + 1) ltj(D[i]);
                    pivot(i, s);
                }
        }
        bool ok = simplex(1);
        x = vd(n);
        FOR(i, 0, m) if (B[i] < n) x[B[i]] = D[i][n + 1];
        return ok ? D[m][n + 1] : inf;
    }
};

// from sample input 1:
// let x1 be num of cake 1, x2 be num of cake 2
// maximize ax + by
// subject to
// -x <= -1
// -y <= -1
// x + y <= m
// -2x - y <= -sigma
// direct implementation with template from: https://isaaclo97.github.io/en/resources/codes/Simplex.html
// plus checking + - small ints around the solution to get the best value

double mm, sigma;
bool ok(vi sol) {
    int x = sol[0], y = sol[1];
    return x >= 1 && y >= 1 && x + y <= mm && 2 * x + y >= sigma;
}
int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    //freopen("error.txt", "w", stderr);

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 4, m = 2;
    vvd A(n, vd(m));
    vd b(n), c(m);
    cin >> c[0] >> c[1]; // a, b
    cin >> mm >> sigma;
    b = {-1, -1, mm, -sigma};
    A = {{-1, 0},
         {0, -1},
         {1, 1},
         {-2, -1}};

    LPSolver solver(A, b, c);
    vd x;
    T value = solver.solve(x);
    vi sol;
    for (double i : x) {
        sol.push_back(round(i));
    }
    int bestVal = -1;
    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            vi temp = sol;
            temp[0] += i;
            temp[1] += j;
            if (ok(temp)) {
                int curr = c[0] * temp[0] + c[1] * temp[1];
                if (curr > bestVal) {
                    bestVal = curr;
                }
            }
        }
    }
    cout << bestVal << endl;

    cerr << "time taken : " << (float) clock() / CLOCKS_PER_SEC << " secs" << endl;
    return 0;
}
