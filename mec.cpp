#include <bits/stdc++.h>

using namespace std;

bitset<50> etykiety[40000];
unsigned long long etykietyL[40000];

int main() {
  int n, m;
  scanf("%d %d", &n, &m);

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      int z;
      scanf("%d", &z);
      if (j >= n/2) {
        etykiety[z - 1].set(i);
      }
    }
  }
/*
  for (int i = 0; i < n; i++) {
    cout << etykiety[i] << endl;
  }
*/
  for (int i = 0; i < n; i++) {
    etykietyL[i] = etykiety[i].to_ullong();
  }

  sort(etykietyL, etykietyL + n);

  for (int i = 0; i < n - 1; i++) {
    if (etykietyL[i] == etykietyL[i + 1]) {
      cout << "NIE";
      return 0;
    }
  }
  cout << "TAK";
  return 0;
}

