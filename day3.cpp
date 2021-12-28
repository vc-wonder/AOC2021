#include "main.h"
const int SIZE = 12;

void solve(ifstream &fin){
    vector<pair<int,int>> counts(SIZE, {0,0});
    string bits;
    vector<string> input;
    while(fin >> bits){
        input.push_back(bits);
        for(int i =0 ;i<SIZE;i++){
            if(bits[i] == '0') counts[i].first += 1;
            else counts[i].second += 1;
        }
    }
    string epsilon, gamma;
    for(int i =0 ;i<SIZE;i++){
        if(counts[i].second > counts[i].first){
            epsilon += '1';
            gamma += '0';
        } else {
            epsilon += '0';
            gamma += '1';
        }
    }
    long result = stoi(epsilon, 0, 2) * stoi(gamma, 0, 2);
    cout<<result<<endl;
    //part2
    vector<string> oxygen = input, co2 = input;
    auto update = [](vector<string> &o, bool oxygen){
        int bit = 0;
        while(o.size() > 1){
            unordered_map<int, vector<string>> values;
            for(auto x : o){
                values[x[bit] - '0'].push_back(x);
            }
            if(oxygen){
                if(values[0].size() > values[1].size()) o = values[0];
                else if(values[0].size() <= values[1].size()) o = values[1];
            }else{
                if(values[0].size() <= values[1].size()) o = values[0];
                else if(values[0].size() > values[1].size()) o = values[1];
            }
            bit++;
        }
    };
    update(oxygen, true);
    update(co2, false);
    result = stoi(oxygen[0], 0, 2) * stoi(co2[0], 0, 2);
    cout<<result<<endl;

}

int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
    return 0;
}
