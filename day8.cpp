#include "main.h"

int difference(string a, string b){
    int c = 0;
    set<char> a1;
    for(char ch: a) a1.insert(ch);
    for(char ch: b) if(a1.count(ch) > 0) c++;
    return c;
}
void solve(ifstream &fin){
    vector<vector<string>> patterns;
    vector<vector<string>> inputs;
    for (string line;getline(fin, line);) {
        auto split = splitOnString(line, " | ");
        patterns.push_back(splitOnString(split[0], " "));
        inputs.push_back(splitOnString(split[1], " "));
    }
    int count = 0;

    auto isUnique = [] (int a) -> bool{
        return a == 3 || a == 7 || a == 2 || a == 4;
    };

    for(auto ele : inputs){
        for(auto pattern : ele){
            if(isUnique(pattern.size())){
                count++;
            }
        }
    }
    cout<<count<<endl;

    //part2

    int sum = 0, i = 0 ;
    for(auto ele : patterns){
        map<string,int> values;
        sort(ele.begin(), ele.end(),[](auto a, auto b){return a.size() < b.size();});
        auto sorted = [](string s)-> string {sort(s.begin(),s.end());return s;};
        values[sorted(ele[0])] = 1;
        values[sorted(ele[1])] = 7;
        values[sorted(ele[2])] = 4;
        values[sorted(ele[9])] = 8;
        string seven = sorted(ele[1]);
        string four = sorted(ele[2]);
        for(auto pat : ele){
            string key = sorted(pat);
            if(pat.size() == 5 ){
                if( difference(key, seven) == 3){
                    values[key] = 3;
                }else if(difference(key, four) == 3){
                    values[key] = 5;
                }
                else {
                    values[key] = 2;
                }
            }else if(pat.size() == 6){
                if(difference(key, four) == 4){
                    values[key] = 9;
                }else if(difference(key, seven) == 3){
                    values[key] = 0;
                }
                else {
                    values[key] = 6;
                }
            }
        }

        int number = 0;
        //printVector(inputs[i]);
        for(auto pat : inputs[i]){
            number *= 10;
            number += values[sorted(pat)];
            //cout<<values[sorted(pat)]<<" ";
        }
       // cout<<number<<endl;
        sum += number;
        i++;
    }
    cout<<sum<<endl;
}

int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
}
