#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007

//#define p 313

#define NM 300000

int pref[NM];

#define LOG 21

int etq[LOG][NM];

vector <tuple<int, int, int>> tupl; //pierwszy, drugi, indeks

int log_t (int n) {
  if (n < 2) {
    return 0;
  }
  return log_t(n/2) + 1;
}

int pow_t(int n, int k) {
  if (k == 0) {
    return 1;
  }
  if (k == 1) {
    return n;
  }
  if (k % 2 == 0) {
    int m = pow_t(n, k/2);
    return m * m;
  }
  if (k % 2 == 1) {
    return n * pow_t(n, k - 1);
  }
}

int ctoi(char c) {
  return (int) c - 'a';
}

int itsize(int it, int n) {
  return n - it;
}

void ecreate(int it, int n) {
  int jump = pow_t(2, it - 1);

  for (int i = 0; i < n - pow_t(2, it) + 1; i++) {
    tupl.push_back({etq[it - 1][i], etq[it - 1][i + jump], i});
  }

  sort(tupl.begin(), tupl.end());

  int e = 1;

  etq[it][get<2>(tupl[0])] = e;

  int s = tupl.size();

  for (int i = 1; i < s; i++) {
    pair<int, int> pi = {get<0>(tupl[i]), get<1>(tupl[i])};
    pair<int, int>pi_ = {get<0>(tupl[i - 1]), get<1>(tupl[i - 1])};

    if (pi > pi_) {
      e++;
    }

    etq[it][get<2>(tupl[i])] = e;
  }

  tupl.clear();
}

pair<int, int> find_etq(int i, int j) {
  int len = j - i + 1;
  int max_pow = log_t(len);
  pair<int, int> p = {etq[max_pow][i], etq[max_pow][j - pow_t(2, max_pow) + 1]};
  return p;
}

int compare(int a, int b, int c, int d) { //krótsze, dłuższe

  int r = (d - c) - (b - a);
  int l1 = b - a + 1;
  pair<int, int> etq2 = find_etq(c, c + l1 - 1);
  pair<int, int> etq1 = find_etq(a, b);
  //cout <<endl<<etq1.first<< ","<<etq1.second<<" "<<endl<<etq2.first<<","<<etq2.second<<endl;
  if (etq1 == etq2 && r == 0) {
    return 0;
  }
  if (etq1 > etq2) {
    return 1;
  }
  return -1;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int n, m;
  cin >> n >> m;
  string str;
  cin >> str;

  for (int i = 0; i < n; i++) {
    etq[0][i] = ctoi(str[i] + 1);
  }

  int max_pow = log_t(n);

  for (int i = 1; i < max_pow + 1; i++) {
    ecreate(i, n);
  }

  // for (int i = 0; i < max_pow + 1; i++) {
  //   for (int j = 0; j < n; j++) {
  //     cout << etq[i][j] << " ";
  //   }
  //   cout <<endl;
  // }

  for (int i = 0; i < m; i++) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    a--;
    b--;
    c--;
    d--;
    int r;
    if (b - a < d - c) {
      r = compare(a, b, c, d);
      if ( r== 1) {
        cout << ">\n";
      }
      else if (r == -1) {
        cout << "<\n";
      }
      else {
        cout << "=\n";
      }
    }
    else {
      r = compare(c, d, a, b);
      if ( r== 1) {
        cout << "<\n";
      }
      else if (r == -1) {
        cout << ">\n";
      }
      else {
        cout << "=\n";
      }
    }
  }
  return 0;
}
