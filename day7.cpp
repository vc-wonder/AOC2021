#include "main.h"
using namespace std;

void solve(ifstream &fin){
    vector<int> positions;
    string line; fin>>line;
    int sum = 0;
    for(auto ele : splitOnString(line,",")){
        int n = stoi(ele);
        sum += n;
        positions.push_back(n);
    }
    sort(positions.begin(), positions.end());
    int N = positions.size();
    int median;
    if (N % 2 == 0) median = (positions[N/2] + positions[N/2 - 1])/2;
    else median = positions[(N + 1) / 2];
    int fuel = 0;
    for (const auto& pos : positions) fuel += abs(pos - median);
    cout<<fuel<<endl;
    //part2
    int mean = sum/N;
    fuel = 0;
    for (const auto& pos : positions){
        int dist = abs(pos - mean);
        fuel += (dist * (dist + 1) / 2);
    }
    cout<<fuel<<endl;
}

int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
}
