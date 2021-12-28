#include "main.h"

using namespace std;

void solve(ifstream &fin){
    vector<string> dirs;
    vector<int> values;
    for(string line; getline(fin,line);) {
        auto split = splitOnString(line, " ");
        dirs.push_back(split[0]);
        values.push_back(stoi(split[1]));
    }
    long d = 0,h = 0, aim = 0;
    for(int i=0; i<values.size();i++){
        if(dirs[i] == "up") d -= values[i];
        else if(dirs[i] == "down") d += values[i];
        else h += values[i];
    }
    cout<<d*h<<endl;
    //part2
    d = 0,h = 0;
    for(int i=0; i<values.size();i++){
        if(dirs[i] == "up") aim -= values[i];
        else if(dirs[i] == "down") aim += values[i];
        else {
            h += values[i];
            d += (aim * values[i]);
        }
    }
    cout<<d*h<<endl;
}

int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
    return 0;
}
