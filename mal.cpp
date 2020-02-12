#include <bits/stdc++.h>

using namespace std;

set<pair<int, int>> pomalowane;

int biale;

void usunOdc(set<pair<int, int>>::iterator odc) {
    biale -= (odc->second - odc->first + 1);
    pomalowane.erase(odc);
}

void wstawOdc(pair<int, int> odc) {
    biale += (odc.second - odc.first + 1);
    pomalowane.insert(odc);
}

void wstawDobrze(set<pair<int, int>>::iterator pocz, pair<int, int> elem) {
    if (pocz == pomalowane.end()) {
        pocz--;
        if (pocz->second >= elem.first) {
            pair<int, int> newElem = {min(elem.first, pocz->first), max(elem.second, pocz->second)};
            usunOdc(pocz);
            wstawOdc(newElem);
        }
        else {
            wstawOdc(elem);
        }
        return;
    }

    if (pocz->first == elem.first) {
        //do nothing
        return;
    }

    if (pocz != pomalowane.begin()) {
        pocz--;
    }

    if (pocz->second < elem.first - 1) {
        pocz++;
    }
    int firstBeg = pocz->first;
    int lastEnd = -1;
    while (pocz != pomalowane.end() && pocz->first <= elem.second + 1) {
        lastEnd = pocz->second;
        auto copy = pocz;
        pocz++;
        usunOdc(copy);
    }

    wstawOdc({min(elem.first, firstBeg), max(elem.second, lastEnd)});
}

void usunDobrze(set<pair<int, int>>::iterator pocz, pair<int, int> elem) {
    if (pocz == pomalowane.end()) {
        pocz--;
        if (pocz->second >= elem.first) {
            if (pocz->first == elem.first) {
                usunOdc(pocz);
                return;
            }
            pair<int, int> nowyElem = {pocz->first, elem.first - 1};
            wstawOdc(nowyElem);

            if (pocz->second > elem.second) {
                pair<int, int> nowyElem2 = {elem.second + 1, pocz->second};
                wstawOdc(nowyElem2);
            }
            usunOdc(pocz);
        }

        else {
            //do nothing
        }
        return;
    }

    if (pocz->first == elem.first) {
        if (pocz->second > elem.second) {
            pair<int, int> newElem = {elem.second + 1, pocz->second};
            usunOdc(pocz);
            wstawOdc(newElem);
        }
        else {
            usunOdc(pocz);
        }
        return;
    }

    if (pocz != pomalowane.begin()) {
        pocz--;
    }

    if (pocz->second < elem.first) {
        pocz++;
    }

    if (pocz->first < elem.first) {
        pair<int, int> newElem = {pocz->first, elem.first - 1};
        auto copy = pocz;
        wstawOdc(newElem);

        if (pocz->second > elem.second) {
            pair<int, int> newElem2 = {elem.second + 1, pocz->second};
            wstawOdc(newElem2);
        }
        pocz++;
        usunOdc(copy);
    }

    while (pocz != pomalowane.end() && pocz->second <= elem.second) {
        auto copy = pocz;
        pocz++;
        usunOdc(copy);
    }
    if (pocz != pomalowane.end()) {
        if (pocz->first <= elem.second && pocz->second > elem.second) {
            pair<int, int> newElem = {elem.second + 1, pocz->second};
            usunOdc(pocz);
            wstawOdc(newElem);
        }
    }
}

int main() {

    std::ios_base::sync_with_stdio(false);

    int n, m;

    cin >> n >> m;
    biale = 0;

    for (int i = 0; i < m; i++) {
        int pocz, kon;
        char typ;
        cin >> pocz >> kon >> typ;
        //cout << pocz << " " << kon << " " << typ << "\n";
        pair<int, int> elem = {pocz, kon};

        if (typ == 'B') {
            if (pomalowane.empty()) {
                pomalowane.insert(elem);
                biale += (kon - pocz + 1);
            }
            else {
                auto poczIt = pomalowane.lower_bound(elem);
                wstawDobrze(poczIt, elem);
            }
        }

        else {
            if (pomalowane.empty()) {
                //do nothing
            } else {
                auto poczIt = pomalowane.lower_bound(elem);
                usunDobrze(poczIt, elem);
            }
        }

        cout << biale << endl;
    }
    return 0;
}
