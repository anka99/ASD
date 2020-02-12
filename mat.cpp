#include <iostream>
#include <string>

using namespace std;

int main() {
  string carpet;
  cin >> carpet;

  int l = carpet.length();

  if (l == 1) {
    cout << 1;
    return 0;
  }

  int d = 0;
  int i = 0;

  while (i < l && carpet[i] == '*') {
    i++;
  }

  if (i == l) {
    cout << 1;
    return 0;
  }

  int p = i;

  for (int j = p; j < l; j++) {
    if (carpet[j] != '*') {
      int nd = j - p;
      if ((d == 0 || nd < d) && carpet[j] != carpet[p]) {
        d = nd;
      }
      p = j;
    }
  }

  if (d == 0) {
    cout << 1;
    return 0;
  }

  cout << (l - d + 1);

  return 0;
}
