#include "main.h"
vector<vector<int>> dirs = {{1,  0},{-1, 0},{0,  1},{0,  -1},
                            {1,  1},{-1, -1},{1,  -1},{-1, 1}};

void flash(vector<vector<int>>& grid, int x, int y){
    grid[x][y] += 1;
    if (grid[x][y]==10) {
        for(auto dir : dirs){
            int row = x + dir[0];
            int col = y + dir[1];
            if(row >= 0 && row < grid.size() && col >= 0 && col < grid[0].size()){
                flash(grid, row, col);
            }
        }
    }
}

int countFlashes(vector<vector<int>>& grid){
    int c=0;
    for(int x=0; x<grid.size(); ++x){
        for(int y=0; y<grid[0].size(); ++y){
            if (grid[x][y] > 9) {
                c++;
                grid[x][y] = 0;
            }
        }
    }
    return c;
}

void solve(ifstream &fin){
    vector<vector<int>> octopus;
    vector<vector<int>> octopus2;
    for(string line; getline(fin,line);) {
        vector<int> ele;
        for(char ch : line){
            ele.push_back(ch - '0');
        }
        // printVector(ele);
        octopus.push_back(ele);
    }
    int count = 0, steps = 100; octopus2 = octopus;
    while(steps--){
        for(int x=0; x<octopus.size(); ++x){
            for(int y=0; y<octopus[0].size(); ++y){
                flash(octopus, x, y);
            }
        }
        count += countFlashes(octopus);
    }
    cout<<count<<endl;

    //part2
    int step = 0;
    while(true){
        step++;
        for(int x=0; x<octopus2.size(); ++x){
            for(int y=0; y<octopus2[0].size(); ++y){
                flash(octopus2, x, y);
            }
        }
        countFlashes(octopus2);
        int s = 0;
        for(auto row : octopus2){
            for(auto ele : row){
                s += ele;
            }
        }
        if(s == 0) break;
    }

    cout<<step<<endl;

}
int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
    return 0;
}
