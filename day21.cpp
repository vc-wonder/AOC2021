#include "main.h"
map<tuple<int,int,int,int>, pair<long long,long long>> scores;
unordered_map<int,int> rolls;

pair<long long,long long> playGame1(int p1s, int p2s, int p1, int p2){
    int dice = 0, result;
    auto rollDice = [&]() { dice++; return dice;};
    while (true) {
        int s = 0, steps = 3;
        while (steps--) s += rollDice();
        p1 = (p1 + s) % 10;
        p1s += p1 == 0 ? 10 : p1;
        if (p1s >= 1000) {
            result = p2s;
            break;
        }
        s = 0, steps = 3;
        while (steps--) s += rollDice();
        p2 = (p2 + s) % 10;
        p2s += p2 == 0 ? 10 : p2;
        if (p2s >= 1000) {
            result = p1s;
            break;
        }
    }
    return {result,dice};
}

pair<long long,long long> playGame2(int p1s, int p2s, int p1, int p2){
    auto key = make_tuple(p1s,p2s,p1,p2);
    if(scores.count(key)) return scores[key];
    if(p1s >= 21) {return {1,0};}
    if(p2s >= 21) {return {0,1};}
    scores[key] = {0,0};
    for(auto roll : rolls){
       int dsum = roll.first;
       int freq = roll.second;
       int pos = (dsum + p1)% 10 == 0? 10 : (dsum + p1)% 10;
       auto s = playGame2(p2s, p1s + pos, p2, pos);
       scores[key].first += (s.second * freq);
       scores[key].second += (s.first * freq);
    }
    return scores[key];
}

void solve(ifstream &fin) {
    string line;
    getline(fin, line);
    int p1 = stoi(line.substr(line.find(':') + 1));
    getline(fin, line);
    int p2 = stoi(line.substr(line.find(':') + 1));

    auto result = playGame1(0, 0,p1,p2);
    cout<<(result.first * result.second)<<endl;

    for(int d1 = 1; d1 <= 3; d1++){
        for(int d2 = 1; d2 <= 3; d2++){
            for(int d3 = 1; d3 <= 3; d3++){
                int sum = d1 + d2 + d3;
                rolls[sum]++;
            }
        }
    }
    result = playGame2(0, 0,p1,p2);
    cout<<max(result.first, result.second)<<endl;
}

int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
    return 0;
}
