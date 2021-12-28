#include "main.h"
int steps = 0;
vector<vector<char>> grid;

pair<int,int> newRC(int r, int c, char ch){
    if(ch == '>'){
        c = (c + 1) % grid[0].size();
    }else{
        r = (r + 1) % grid.size();
    }
    return {r, c};
}

bool moveChar(char ch){
    bool move = false;
    vector<vector<char>> newGrid = grid;
    for(int r = 0; r < grid.size(); r++){
        for(int c = 0; c < grid[0].size(); c++){
            if(grid[r][c] == ch){
                pair<int,int> ele = newRC(r,c,ch);
                if(grid[ele.first][ele.second] == '.'){
                    move = true;
                    newGrid[ele.first][ele.second] = ch;
                    newGrid[r][c] = '.';
                }
            }
        }
    }
    grid = newGrid;
    return move;
}
void solve(ifstream &fin){
   for(string line; getline(fin, line);){
        vector<char> row;
        for(char ch : line) row.push_back(ch);
        grid.push_back(row);
   }
   bool move = true;
   while(move){
       steps++;
       bool east = moveChar('>');
       bool south =  moveChar('v');
       move = east || south;
   }
   cout<<steps<<endl;
}

int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
    return 0;
}
