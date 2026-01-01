#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <queue>
using namespace std;

int N, M, K;

struct GroundTile
{
private:
    int yangbun;
    vector<int> treeOlds;

public:

    void InitializeYangbun(int yangbun)
    {
        this->yangbun = yangbun;
    }

    void AddTree(int treeOld)
    {
        for (int i = 0; i < treeOlds.size(); i++)
        {
            if (treeOlds[i] < treeOld)
            {
                treeOlds.insert(treeOlds.begin() + i, treeOld);
                return;
            }
        }

        treeOlds.insert(treeOlds.begin(), treeOld);
    }

    void Reset()
    {
        //index = 0;
    }

    void AddYangbun(int yangbun)
    {
        this->yangbun += yangbun;
    }

    int GetTreeCount()
    {
        return treeOlds.size();
    }
    
    bool HasTree()
    {
        return treeOlds.size() > 0;
    }

    void AddYoungTree()
    {
        treeOlds.push_back(1);
    }

    void DoDie(int index)
    {
        treeOlds.erase(treeOlds.begin() + index);
    }

    bool TryGrow(int index)
    {
        if (yangbun >= treeOlds[index])
        {
            yangbun -= treeOlds[index];
            treeOlds[index] += 1;
            //index += 1;
            return true;
        }
        else
        {
            return false;
        }
    }

    int GetTreeOld(int index)
    {
        return treeOlds[index];
    }
};

struct DeadTree
{
    int old;
    pair<int, int> pos;
};

vector<vector<int>> constYangbunArr;
vector<vector<GroundTile>> farm;

GroundTile* GetGround(pair<int, int> pos)
{
    return &farm[pos.first][pos.second];
}

void AddYangBun(pair<int, int> yangbunPos, int yangBun)
{
    GetGround(yangbunPos)->AddYangbun(yangBun);
}

bool CanPlant(pair<int, int> newTree)
{
    return newTree.first >= 0 && newTree.first < N && newTree.second >= 0 && newTree.second < N;
}

void Plant(pair<int, int> newTree)
{
    GetGround(newTree)->AddYoungTree();
}

vector<pair<int, int>> GetBunsikAbleTrees()
{
    vector<pair<int, int>> list;
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            auto ground = GetGround(pair<int, int>(y, x));
            for (int k = 0; k < ground->GetTreeCount(); k++)
            {
                int old = ground->GetTreeOld(k);
                if (old % 5 == 0)
                    list.push_back(pair<int, int>(y, x));
            }
        }
    }

    return list;
}

void DoBunsik(pair<int, int> treePos)
{
    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            if (dy == 0 && dx == 0)
                continue;

            auto newTree = pair<int, int>(treePos.first + dy, treePos.second + dx);
            if (CanPlant(newTree))
                Plant(newTree);
        }
    }
}

vector<DeadTree> Spring()
{
    vector<DeadTree> deadTreeOlds;

    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            auto ground = GetGround(pair<int, int>(y, x));
            if (ground->HasTree() == false)
                continue;

            int treeCount = ground->GetTreeCount();
            for (int k = treeCount - 1; k >= 0; k--)
            {
                bool result = ground->TryGrow(k);
                if (result == false)
                {
                    DeadTree deadTree;
                    deadTree.old = ground->GetTreeOld(k);
                    deadTree.pos = pair<int, int>(y, x);

                    deadTreeOlds.push_back(deadTree);
                    ground->DoDie(k);
                }
            }
            ground->Reset();
        }
    }

    return deadTreeOlds;
}

void Summer(vector<DeadTree> deadTreeOlds)
{
    for (auto deadTree : deadTreeOlds)
    {
        int yangbun = deadTree.old / 2;
        AddYangBun(deadTree.pos, yangbun);
    }
}

void Autumn()
{
    auto bunsikAbleTrees = GetBunsikAbleTrees();
    for (auto bunsikAbleTree : bunsikAbleTrees)
    {
        DoBunsik(bunsikAbleTree);
    }
}

void Winter()
{
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            AddYangBun(pair<int, int>(y, x), constYangbunArr[y][x]);
        }
    }
}

//https://www.acmicpc.net/problem/16235

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M >> K;

    farm = vector<vector<GroundTile>>(N, vector<GroundTile>(N));
    constYangbunArr = vector<vector<int>>(N, vector<int>(N));

    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            int yangbun;
            cin >> yangbun;
            GroundTile ground;
            ground.InitializeYangbun(5);
            constYangbunArr[y][x] = yangbun;
            farm[y][x] = ground;
        }
    }

    for (int m = 0; m < M; m++)
    {
        int y, x, old;
        cin >> y >> x >> old;
        farm[y - 1][x - 1].AddTree(old);
    }

    while (K--)
    {
        auto deadTree = Spring();
        Summer(deadTree);
        Autumn();
        Winter();
    }

    int aliveTreeCnt = 0;
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            aliveTreeCnt += farm[y][x].GetTreeCount();
        }
    }

    cout << aliveTreeCnt;

    return 0;
}
