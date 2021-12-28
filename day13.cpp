#include "main.h"

void reset(vector<vector<char>> &grid, int x, int y){
    grid.resize(x);
    for(auto &ele : grid){
        ele.resize(y);
    }
}
void fold(vector<vector<char>> &grid, string dir, int num, int &count ){
    int rows = grid.size();
    int cols = grid[0].size();
    if(dir == "y"){
        for(int r = 0; r < num; r++){
            for(int c = 0; c < cols;c++){
                if(grid[rows-r-1][c] == '#') grid[r][c] = '#';
                if(grid[r][c] == '#') count++;
            }
        }
        reset(grid, num, grid[0].size());
    }else{
        for(int r = 0; r < rows;r++){
            for(int c = 0; c < num;c++){
                if(grid[r][cols-c-1] == '#') grid[r][c] = '#';
                if(grid[r][c] == '#') count++;
            }
        }
        reset(grid, rows, num);
    }
}
void solve(ifstream &fin){
    vector<vector<char>> grid(1500,vector<char>(1500, ' '));
    int rows = INT_MIN, cols = INT_MIN;
    bool first = true;
    for(string line; getline(fin,line);) {
        if(!line.empty() && line[0] == 'f'){
            auto s = splitOnString(line, " ");
            vector<string> pos = splitOnString(s[2], "=");
            int count = 0;
            fold(grid, pos[0], stoi(pos[1]), count);
            if(first){
                cout<<count<<endl;
                first = false;
            }
        }
        else if(line.empty()){
            reset(grid, rows+1,cols+1);
        }
        else{
            vector<string> points = splitOnString(line, ",");
            int x = stoi(points[0]);
            int y = stoi(points[1]);
            grid[y][x] = '#';
            rows = max(rows, y);
            cols = max(cols, x);
        }
    }
    for(auto &ele : grid){
        printVector(ele);
    }
}

int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
    return 0;
}
