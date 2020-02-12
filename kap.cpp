#include <bits/stdc++.h>

using namespace std;

#define N 200000
#define XY 1000000000

using t_3_ul = tuple<int64_t, int64_t, int>; //coor, revcoor, i
bool used[N];
int icoor[N];
int ircoor[N];
int from[N];
vector<t_3_ul> coor; //1
vector<t_3_ul> rev_coor;

int64_t ret_x(int i) {
  return get<0>(coor[icoor[i]]);
}

int64_t ret_y(int i) {
  return get<0>(rev_coor[ircoor[i]]);
}

int64_t absv(int64_t x) {
  if (x < 0) {
    return (-1) * x;
  }
  return x;
}

void calcpush(int64_t i, int64_t ic, int64_t d, priority_queue<pair<int64_t, int>> &q) {
  if (!used[ic]) {
    int64_t dist = min(absv(ret_x(i) - ret_x(ic)), absv(ret_y(i) - ret_y(ic)));
    q.push({(-1) * (d + dist), ic});
  }
}

int main () {
  std::ios_base::sync_with_stdio(false);
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    unsigned long x, y;
    cin >> x >> y;
    coor.push_back({x, y, i}); //1
    rev_coor.push_back({y, x, i}); //2
  }

  t_3_ul start = coor.front();
  t_3_ul finish = coor.back();

  sort(coor.begin(), coor.end());
  sort(rev_coor.begin(), rev_coor.end());



  for (int i = 0; i < n; i++) {
    icoor[get<2>(coor[i])] = i;
    ircoor[get<2>(rev_coor[i])] = i;
  }

  // cout << "\n\n";
  //
  // for (int i = 0; i < n; i++) {
  //   cout << get<2>(rev_coor[i]) << ' ';
  // }
  //
  // cout << "\n\n";
  //
  // for(int i = 0; i < n; i++) {
  //   cout << ircoor[i] << " ";
  // }
  //
  // cout << "\n\n";
  //
  // for (int i = 0; i < n; i++) {
  //   cout << ret_x(i) << " " << ret_y(i) << endl;
  // }
  //
  // cout << "\n\n";
  //for (int i = 0; i < n; i++) {cout << icoor[i]<< " ";}
  //


  priority_queue<pair<int64_t, int>> q;//-odleglosc, indeks
  q.push({0, 0});

  int64_t route = 0;

  while(!q.empty()) {
    pair<int64_t, int> p = q.top();

    if (p.second == n-1) {
      route = (-1) * p.first;
      break;
    }

    q.pop();
    int i = p.second;
    int64_t x = ret_x(i);
    int64_t y = ret_y(i);
    int64_t d = (-1) * p.first;
    int cprev = icoor[i] - 1;
    int cnext = icoor[i] + 1;
    int rprev = ircoor[i] - 1;
    int rnext = ircoor[i] + 1;

    if (!used[i]) {
      used[i] = true;

      if (cprev >= 0) {
        int ic = get<2>(coor[cprev]);
        calcpush(i, ic, d, q);
      }
      if (cnext < n) {
        int ic = get<2>(coor[cnext]);
        calcpush(i, ic, d, q);
      }

      if (rnext < n) {
        int ic = get<2>(rev_coor[rnext]);
        calcpush(i, ic, d, q);
      }
      if (rprev >= 0) {
        int ic = get<2>(rev_coor[rprev]);
        calcpush(i, ic, d, q);
      }
    }
  }
  cout << route;

  //cout << INT64_MAX;

  return 0;

}

/*
5
2 2
1 1
4 5
7 1
6 7

*/
