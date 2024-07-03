#include <bits/stdc++.h>

using namespace std;

char grid[30][30];
string line;
int R, C, blobSize;

int dr[] = {1, 1, 0, -1, -1, -1, 0, 1};            // the order is:
int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};            // S/SE/E/NE/N/NW/W/SW

void floodfill(int r, int c) {  // returns the size of CC
    if ((r < 0) || (r >= R) || (c < 0) || (c >= C)) return; // outside grid
    if (grid[r][c] == '0') return;                // does not have color c1
    grid[r][c] = '0';                               // to avoid cycling
    blobSize++;                                     // increment size of CC
    for (int d = 0; d < 8; ++d) floodfill(r + dr[d], c + dc[d]);
}

// inside int main()
int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    //freopen("error.txt", "w", stderr);

    int tc;
    getline(cin, line);
    tc = stoi(line);
    getline(cin, line);
    while (tc--) {

        // check 1st line for size of C
        R = 1;
        getline(cin, line);
        C = line.size();
        for (int i = 0; i < C; ++i) grid[0][i] = line[i];

        while (getline(cin, line)) {
            if (line.empty()) break;
            for (int i = 0; i < C; ++i) grid[R][i] = line[i];
            R++;
        }

        int bestSize = 0;
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                if (grid[i][j] == '1') {
                    blobSize = 0;
                    floodfill(i, j);
                    bestSize = max(bestSize, blobSize);
                }
        cout << bestSize << endl;
        if (tc) cout << endl;
    }

    cerr << "time taken : " << (float) clock() / CLOCKS_PER_SEC << " secs" << endl;
    return 0;
}