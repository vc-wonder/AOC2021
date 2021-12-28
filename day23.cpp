#include "main.h"
vector<vector<char>> grid1(5, vector<char>(13, '#'));
vector<vector<char>> target(5, vector<char>(13, '#'));
set<pair<int,int>> nowaiting = {{1,3}, {1, 5}, {1, 7}, {1,9}};
int COLS = 13, ROWS = 5;

int energy(char c) {
    switch (c) {
        case 'A': return 1;
        case 'B': return 10;
        case 'C': return 100;
        case 'D': return 1000;
        default:  return -1;
    }
}
bool equals(vector<vector<char>> &grid,vector<vector<char>> &dest){
    for(int i=0;i < grid.size();i++){
        for(int j=0;j < grid.size();j++){
            if(grid[i][j] != dest[i][j]) return false;
        }
    }
    return true;
}
int findMinimum(vector<vector<char>> grid){
    if(equals(grid, target)) return 0;
    //TODO: Did solution by hand, method needs implementation
    return INT_MAX;
}

char getChar(int col){
    if(col == 3) return 'A';
    if(col == 5) return 'B';
    if(col == 7) return 'C';
    if(col == 9) return 'D';
};

void solve(ifstream &fin){
    int l = 0;
    for(string line; getline(fin, line);){
        int c = 0;
        for(char ch : line){
            if(ch == '#' || ch == ' ') {
                grid1[l][c] = '#'; target[l][c] = '#';
                c++;
            }
            else if(ch == '.'){
                grid1[l][c] = ch;target[l][c] = ch;
                c++;
            }else{
                grid1[l][c] = ch;target[l][c] = getChar(c);
                c++;
            }
        }
        //printVector(target[l]);
        l++;
    }
    cout<<findMinimum(grid1);
}

int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
    return 0;
}
