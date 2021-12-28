#include "main.h"
string t;
map<pair<char,char>,char> rules;

long long runProgram(int steps){
    map<pair<char,char>, long long> pairsCount;
    for(int i = 0;i<t.size()-1;i++){
        pairsCount[{t[i],t[i+1]}]++;
    }
    while(steps--){
        map<pair<char,char>, long long> newPairsCount;
        for(auto [k,v]: pairsCount){
            if(rules.count(k)){
                newPairsCount[{k.first,rules[k]}] += v;
                newPairsCount[{rules[k],k.second}] += v;;
            }else{
                newPairsCount[k] += v;
            }
        }
        pairsCount = newPairsCount;
    }
    unordered_map<char, long long> charCount;
    for(auto [k,v] : pairsCount){
        charCount[k.first] += v;
    }
    charCount[t.back()]++;

    long long minValue = LONG_LONG_MAX, maxValue = LONG_LONG_MIN;
    for(pair<char, long long> p: charCount){
        minValue = p.second < minValue?p.second:minValue;
        maxValue = p.second >= maxValue?p.second:maxValue;
    }
    return maxValue-minValue;
}
void solve(ifstream &fin){
    for(string line; getline(fin,line);) {
        if(!line.empty() && t.empty()){
            t = line;
            continue;
        }
        else if(!line.empty()) rules[{line[0],line[1]}] = line[6];
    }
    cout<<runProgram(10)<<endl;
    cout<<runProgram(40)<<endl;
}

int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
    return 0;
}