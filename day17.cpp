#include "main.h"

void solve(ifstream &fin){
    vector<pair<int, int>> velocities;
    for(string line; getline(fin,line);) {
        vector<string> s = splitOnString(splitOnString(line,": ")[1], ", ");
        vector<string> X = splitOnString(s[0].substr(s[0].find('=')+1),"..");
        vector<string> Y = splitOnString(s[1].substr(s[1].find('=')+1),"..");
        int xs = stoi(X[0]);
        int xe = stoi(X[1]);
        int ys = stoi(Y[0]);
        int ye = stoi(Y[1]);
        int height = INT_MIN;
        auto inBounds = [&](auto start){
            return start.first  >= xs && start.first <= xe &&
                   start.second  >= ys && start.second <= ye;
        };
        for (int y = ys; y <= -ys-1; y++) {
            for (int x = 1; x <= xe; x++) {
                pair<int,int> start = {0,0};
                int vx = x, vy = y;
                while(start.first <= xe && start.second >= ys){
                    start = {start.first + vx, start.second + vy};
                    if (inBounds(start)){
                        velocities.push_back({start.first ,start.second});
                        break;
                    }
                    vy--;
                    if (vx > 0) vx--;
                    height = max(height,start.second);

                }
            }
        }
        cout<<height<<endl;
        cout<<velocities.size()<<endl;
    }
}

int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
    return 0;
}
