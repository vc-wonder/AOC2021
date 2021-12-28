#include "main.h"

void solve(ifstream &fin){
    string algo;
    set<pair<int,int>> image;
    bool first = true;int ROWS = 0, COLS = 0;
    for(string line; getline(fin,line);) {
        if (first) {
            algo = line;
            first = false;
        }
        else if (line.empty()) continue;
        else{
            COLS = 0;
            vector<char> row;
            for (char ch : line) {
                if(ch == '#') {
                    image.insert({ROWS,COLS});
                }
                COLS++;
            }
            ROWS++;
        }
    }
    ROWS--,COLS--;
    vector<vector<int>> dirs = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,0},
                                    {0,1},{1,-1},{1,0},{1,1}};

    auto program = [&](int steps){
        int rs = 0, cs = 0, re = ROWS, ce = COLS;
        set<pair<int,int>> pixels1 = image;
        char infinite = '0';
        while(steps--){
            set<pair<int,int>> pixels2;

            for(auto ele : pixels1){
                rs = min(ele.first, rs);
                re = max(ele.first, re);
                cs = min(ele.second, cs);
                ce = max(ele.second, ce);
            }
            for(int r = rs-1; r <= re+1; r++) {
                for (int c = cs-1; c <= ce+1; c++) {
                    string binary = "";
                    for (auto ele : dirs) {
                        int row = r + ele[0];
                        int col = c + ele[1];
                        if(row >= rs && row <= re && col >= cs && col <= ce){
                            binary += pixels1.count({row, col}) > 0 ? '1' : '0';
                        }
                        else{
                            binary += infinite;
                        }
                    }
                    int pos = stoi(binary, 0, 2);
                    if(algo[pos] == '#'){
                        pixels2.insert({r,c});
                    }
                }
            }
            pixels1 = pixels2;
            infinite = infinite == '0'? '1': '0';
        }
        cout<<pixels1.size()<<endl;

    };
    program(2);
    program(50);
}

int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
    return 0;
}
