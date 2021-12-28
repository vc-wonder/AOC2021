#include "main.h"
vector<vector<bool>> visited;
int get_size(int col, int row, vector<vector<int>> matrix) {

    if ( col == -1 || row == -1 || col == matrix.size() || row == matrix[0].size() ) return 0;
    if ( matrix[col][row] == 9 || visited[col][row] == 1 ) return 0;

    visited[col][row] = 1;

    return 1 + get_size(col,row-1,matrix) +
            get_size(col-1,row,matrix) +
            get_size(col,row+1,matrix) +
            get_size(col+1,row,matrix);
}

void solve(ifstream &fin){
    vector<vector<int>> input;
    int row = 0, col = 0;
    for (string line;getline(fin, line);) {
        vector<int> i; col = 0;
        for(char ch : line){
            col++;
            i.push_back(ch - '0');
        }
        input.push_back(i);
        row++;
    }
    auto islow = [&input, &row, &col](int i, int j){
        vector<vector<int>> dirs = {{-1,0},{0,-1},{1,0},{0, 1}};
        for( auto dir : dirs)    {
            int r = i + dir[0];
            int c = j + dir[1];
            if(r >= 0 && r < row && c >= 0 && c< col){
                if(input[i][j] >= input[r][c]) return false;
            }
        }
        return true;
    };
    visited.resize(input.size(), vector<bool>(input[0].size(),0));

    int ans = 0;
    vector<int> pq;
    for(int i = 0; i <row;i++){
        for(int j = 0; j <col;j++){
            if(islow(i, j)){
                int size = get_size(i, j, input);
                pq.push_back(size);
                int risk = input[i][j] + 1;
                ans += risk;
            }
        }
    }
    cout<<ans<<endl;

    long ans2 = 1;
    sort(pq.begin(), pq.end(),[](int a, int b){ return a > b;});
    for(int i=0;i<3;i++){
        ans2 *= pq[i];
    }
    cout<<ans2<<endl;

}

int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
}
