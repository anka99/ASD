# include <bits/stdc++.h>

using namespace std;
#define N 100001

int od_ilu_zal[N];
vector<int> co_zal[N];
int progr[N];

int main() {
  int n, m, k;
  std::ios_base::sync_with_stdio(false);
  cin >> n >> m >> k;

  for (int i = 0; i < n; i++) {
    cin >> progr[i + 1];
    progr[i + 1] = progr[i + 1] * (-1);
  }

  for (int i = 0; i < m; i++) {
    int od, co;
    cin >> co >> od;
    co_zal[od].push_back(co);
    od_ilu_zal[co]++;
  }

  priority_queue<pair<int, int>> pqueue;
  for (int i = 1; i < n + 1; i++) {
    if (od_ilu_zal[i] == 0) {
      pqueue.push({progr[i], i});
    }
  }

  vector<int> result;
  int proj = 0;

  while (proj < k) {
    proj++;
    pair<int, int> next = pqueue.top();
    pqueue.pop();

    for(int i: co_zal[next.second]) {
      od_ilu_zal[i]--;
      if (od_ilu_zal[i] == 0) {
        pqueue.push({progr[i], i});
      }
    }

    int to_ins = next.first;
    result.push_back(to_ins);
  }

  int p = 0;
  for (int i: result) {
    p = max(p, i * (-1));
  }

  cout << p;
  return 0;
}

