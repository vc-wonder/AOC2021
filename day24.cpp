#include "main.h"
vector<unordered_map<int, long long>> memo(14);

vector<vector<int>> input(14);

int runProgram(int iteration, int value, int z){
    int w = value, x = 0, y = 0, z1=z;
    x *= input[iteration][0];
    x += z;
    if(x < 0 || input[iteration][1] <= 0){ return -1;}
    x %= input[iteration][1];
    if(input[iteration][2] == 0) {return -1;}
    z1 /= input[iteration][2];
    x += input[iteration][3];
    x = (x == w) ? 1 : 0;
    x = (x == input[iteration][4]) ? 1 : 0;
    y *= input[iteration][5];
    y += input[iteration][6];
    y *= x;
    y += input[iteration][7];
    z1 *= y;
    y *= input[iteration][8];
    y += w;
    y += input[iteration][9];
    y *= x;
    z1 += y;
    return z1;
}

long long util(int iteration, bool largest, int z){
    if(iteration == 14){
        return z == 0 ? 0 : -1;
    }
    if(memo[iteration].find(z) != memo[iteration].end()) return memo[iteration][z];
    long long ans = -1;
    for(int d = largest?9:1; (largest && d >= 1) || (!largest && d <= 9); d = largest?d-1:d+1){
        int z1 = runProgram(iteration, d, z);
        if(z1 == -1) continue;
        long long val = util(iteration + 1, largest, z1);
        if(val != -1) {
            ans = val + d * pow(10, 13 - iteration);
            break;
        }
    }
    return memo[iteration][z] = ans;
}

void solve(ifstream &fin) {
    int l = -1;
    for (string line; getline(fin, line);) {
        vector<string> ele = splitOnString(line, " ");
        if(ele[0] != "inp"){
            if(ele[2][0] >= 'a' && ele[2][0] <= 'z') continue;
            else input[l].push_back(stoi(ele[2]));
        }
        else {
            l++;
        }
    }
    cout<<util(0, true, 0)<< endl;
    memo.clear();
    memo.resize(14, unordered_map<int, long long>());
    cout<<util(0, false, 0)<< endl;
}

int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
    return 0;
}
