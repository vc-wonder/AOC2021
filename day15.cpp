#include "main.h"
using node = tuple<int,int,int>;

int findMinimumRisk(vector<vector<int>> &grid)
{
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
    vector<vector<bool>> visit(m, vector<bool>(n, 0));
    priority_queue<node, vector<node>, greater<node>> pq;

    dist[0][0] = grid[0][0];
    pq.emplace(dist[0][0], 0, 0);
    int x[4] = {0, 1, -1, 0}, y[4] = {1, 0, 0, -1};

    while(!visit[m - 1][n - 1]) {
        auto cur = pq.top();pq.pop();
        if(dist[get<1>(cur)][get<2>(cur)] < get<0>(cur))
            continue;
        visit[get<1>(cur)][get<2>(cur)] = true;
        for(int i = 0; i < 4; i++){
            int dy = get<2>(cur) + x[i],
            dx = get<1>(cur) + y[i];
            if(dy >= n || dx >= m || dy < 0 || dx < 0)
                continue;
            int d = dist[get<1>(cur)][get<2>(cur)] + grid[dx][dy];
            if(d < dist[dx][dy]) {
                pq.emplace(d, dx, dy);
                dist[dx][dy] = d;
            }
        }
    }
    return dist[m - 1][n - 1];
}


void solve(ifstream &fin){
    vector<vector<int>> grid;
    for(string line; getline(fin,line);) {
        vector<int> l;
        for(char ch : line){
            l.push_back(ch-'0');
        }
        grid.push_back(l);
    }
    cout<<findMinimumRisk(grid) - grid[0][0]<<endl;

    //part2
    int R = grid.size(), C = grid[0].size();
    vector<vector<int>> new_grid((R*5), vector<int>(C*5, 0));
    for(int r=0;r<R;r++) {
        for (int c = 0; c < C; c++) {
            int num = grid[r][c];
            for(int i=0;i<5;i++) {
                for (int j=0;j<5;j++) {
                    int new_num = num + i + j;
                    if (new_num > 9) new_num -= 9;
                    new_grid[r + i * R][c + j * C] = new_num;
                }
            }
        }
    }
    cout<<findMinimumRisk(new_grid) - grid[0][0]<<endl;
}

int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
    return 0;
}
