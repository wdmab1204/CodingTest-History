#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Country {
    int id;
    int gold;
    int silver;
    int bronze;

    int rank;

    Country(int id, int gold, int silver, int bronze) {
        this->id = id;
        this->gold = gold;
        this->silver = silver;
        this->bronze = bronze;
    }

    int Equal(Country other) {
        if (this->gold > other.gold)
            return 1;
        if (this->gold < other.gold)
            return -1;
        if (this->silver > other.silver)
            return 1;
        if (this->silver < other.silver)
            return -1;
        if (this->bronze > other.bronze)
            return 1;
        if (this->bronze < other.bronze)
            return -1;
        return 0;
    }
};

int main() {
    
    int countryCnt, targetId;
    cin >> countryCnt >> targetId;
    vector<Country> v;

    for (int i = 0; i < countryCnt; i++) {
        int id, gold, silver, bronze;
        cin >> id >> gold >> silver >> bronze;
        Country county(id, gold, silver, bronze);
        v.push_back(county);
    }

    sort(v.begin(), v.end(), [](Country a, Country b) {
        int comp = a.Equal(b);
        if (comp == 0)
            return a.id < b.id;
        else
            return comp > 0;
        });

    Country before(-1, -1, -1, -1);
    for (int i = 0; i < countryCnt; i++) {
        int rank = i + 1;

        if (v[i].Equal(before) == 0) {
            v[i].rank = before.rank;
        }
        else {
            v[i].rank = rank;
            before = v[i];
        }

        if (v[i].id == targetId) {
            cout << v[i].rank;
            return 0;
        }
    }

    /*for (auto& c : v) {
        cout << c.id << " " << c.gold << " " << c.silver << " "<< c.bronze << endl;
    }*/

    return 0;
}
