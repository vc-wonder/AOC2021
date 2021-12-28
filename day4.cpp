#include "main.h"

bool check(vector<vector<int>> &board){
    for(int i=0;i<5;i++){
        int s = 0;
        for(int j=0;j<5;j++){
            s += board[i][j];
        }
        if(s == 5) return true;
    }
    for(int i=0;i<5;i++){
        int s = 0;
        for(int j=0;j<5;j++){
            s += board[j][i];
        }
        if(s == 5) return true;
    }
    return false;
}

void solve(ifstream &fin){
    string numbers;
    fin>>numbers;
    vector<string> nums = splitOnString(numbers, ",");

    unordered_map<int,vector<tuple<int,int,int>>> locations;
    unordered_map<int, unordered_set<int>> unmarked;

    int x, board = 0;
    while(fin >> x){
        locations[x].push_back(make_tuple(board, 0, 0));
        unmarked[board].insert(x);
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                if(i==0 && j==0)continue;
                fin>>x;
                locations[x].push_back(make_tuple(board, i, j));
                unmarked[board].insert(x);
            }
        }
        board++;
    }
    long result1, result2;

    vector<vector<vector<int>>> boards(
            board, vector<vector<int>>(5,vector<int>(5,0)));

    bool first = true, win = false;
    int s = 0;
    unordered_set<int> boardsset;
    for(int i=0;i<board;i++){boardsset.insert(i);}

    for(const auto& ele : nums){
        int n=stoi(ele);
        for(auto location : locations[n]){
            int b = get<0>(location);
            int r = get<1>(location);
            int c = get<2>(location);
            boards[b][r][c]++;
            unmarked[b].erase(n);
            if(check(boards[b])){
                boardsset.erase(b);
                if(first){
                   for(int j : unmarked[b]) s += j;
                   result1 =  n * s;
                   first = false;
                   s = 0;
               }else if(boardsset.empty()){
                   for(int j : unmarked[b]) s += j;
                   result2 =  n * s;
                   win = true;
                   break;
                }
            }
        }
        if(win) break;
    }
    cout<<result1<<endl;
    cout<<result2<<endl;
}

int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
    return 0;
}
