#include <iostream>
#include <bits/stdc++.h>

using namespace std;

unsigned long MOD = 1000000000;

int ciag[1000];
unsigned long prawa[1001][1000]; //[dlugosc][poczatek]
unsigned long lewa[1001][1000];

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n + 1; i++) {
      for (int j = 0; j < n; j++) {
        lewa[i][j] = 0;
        prawa[i][j] = 0;
      }
    }

    for (int j = 0; j < n; j++) {
      prawa[1][j] = 1;
      //lewa[1][j] = 1;
    }

    for (int i = 0; i < n; i++) {
      cin >> ciag[i];
    }

    if (n == 1) {
      cout << 1 << endl;
      return 0;
    }

    for (int d = 2; d < n + 1; d++) {
      for (int p = 0; p + d - 1 < n; p++) {
        int pp = 0;
        if (ciag[p + d - 1] > ciag[p + d - 2]) {
          pp = 1;
        }

        int pl = 0;
        if (ciag[p + d - 1] > ciag[p]) {
          pl = 1;
        }

        prawa[d][p] = (prawa[d - 1][p] * pp + lewa[d - 1][p] * pl) % MOD;

        int lp = 0;
        if ( ciag[p] < ciag[p + d - 1]) {
          lp = 1;
        }

        int ll = 0;
        if (ciag[p] < ciag[p + 1]) {
          ll = 1;
        }

        lewa[d][p] = (prawa[d - 1][p + 1] * lp + lewa[d - 1][p + 1] * ll) % MOD;
      }
    }
/*
    for (int d = 1; d < n + 1; d++) {
      for (int p = 0; p + d < n + 1; p++) {
        cout << prawa[d][p] << " ";
      }
      cout << endl;
    }

    for (int d = 1; d < n + 1; d++) {
      for (int p = 0; p + d < n + 1; p++) {
        cout << lewa[d][p] << " ";
      }
      cout << endl;
    }
*/
    cout << (prawa[n][0]
    + lewa[n][0]) % MOD << endl;

    return 0;

}
