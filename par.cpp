#include <bits/stdc++.h>

using namespace std;

#define SIZE 524300
#define M 500001
#define N 500001

pair<int, int> tree[SIZE];
int parents[SIZE];
vector<pair<int, int>> querr[M]; //kolejnosc, node
int answ[M]; //kolejnosc, odpowiedz // init -1

int child1(int n) {
  return tree[n].first;
}

int child2(int n) {
  return tree[n].second;
}

int parent(int n) {
  if (n == 1 || n == 0) {
    return -1;
  }
  return parents[n];
}

void DFS (int skad, int teraz, int odleglosc, int *najw_odl, int *najw) {
  if (teraz != -1) {
    if (*najw_odl <= odleglosc) {
      *najw_odl = odleglosc;
      *najw = teraz;
    }

    int dok1, dok2;
    if (parent(teraz) == skad) {
      dok1 = child1(teraz);
      dok2 = child2(teraz);
    }
    else if (child1(teraz) == skad) {
      dok1 = parent(teraz);
      dok2 = child2(teraz);
    }
    else {
      dok1 = child1(teraz);
      dok2 = parent(teraz);
    }
    DFS(teraz, dok1, odleglosc + 1, najw_odl, najw);
    DFS(teraz, dok2, odleglosc + 1, najw_odl, najw);
  }
}

void DFS2(int skad, int teraz, vector<int> &sciezka) {
  if (teraz != -1) {
    int dok1, dok2;
    if (parent(teraz) == skad) {
      dok1 = child1(teraz);
      dok2 = child2(teraz);
    }
    else if (child1(teraz) == skad) {
      dok1 = parent(teraz);
      dok2 = child2(teraz);
    }
    else {
      dok1 = child1(teraz);
      dok2 = parent(teraz);
    }

    sciezka.emplace_back(teraz);

    int size = sciezka.size();

    if (!querr[teraz].empty()) {
      for (pair<int, int> p: querr[teraz]) {
        if (p.second == 0) {
          answ[p.first] = teraz;
        }
        else if (size - p.second - 1 >= 0) {
          answ[p.first] = sciezka[size - p.second - 1];
        }
      }
    }
    DFS2(teraz, dok1, sciezka);
    DFS2(teraz, dok2, sciezka);
    sciezka.pop_back();
  }
}

void init_tree() {
  for (int i = 0; i < SIZE; i++) {
    tree[i].first = -1;
    tree[i].second = -1;
  }
}

void init_ans() {
  for (int i = 0; i < M; i++) {
    answ[i] = -1;
  }
}

void poka_drzewo(int root) {
  if (root != -1) {
    cout << root << " ";
    poka_drzewo(child1(root));
    poka_drzewo(child2(root));
  }
}

int main() {
  int n;
  cin >> n;

  //std::ios_base::sync_with_stdio(false);

  init_tree();
  init_ans();

  for (int i = 1; i < n + 1; i++) {
    int c1, c2;
    //cin >> c1 >> c2;
    scanf("%d %d", &c1, &c2);
    tree[i].first = c1;
    tree[i].second = c2;
    if (c1 != -1) parents[c1] = i;
    if (c2 != -1) parents[c2] = i;
  }

  int m;
  cin >> m;

  for (int i = 0; i < m; i++) {
    int a, d;
    //cin >> a >> d;
    scanf("%d %d", &a, &d);
    querr[a].push_back({i, d});
  }

  int d = 0;
  int dnode1 = 0;
  int dnode2 = 0;

  DFS(-1, 1, 0, &d, &dnode1);
  d = 0;
  DFS(-1, dnode1, 0, &d, &dnode2);

  vector<int> sciezka;
  DFS2(-1, dnode1, sciezka);
  DFS2(-1, dnode2, sciezka);

  for (int i = 0; i < m; i++) {
    //cout << answ[i] << '\n';
    printf("%d\n", answ[i]);
  }

  return 0;
}
/*
8
3 4
-1 6
2 5
-1 -1
7 -1
-1 -1
8 -1
-1 -1
6
1 3
1 4
1 5
6 1
6 4
6 5
*/
