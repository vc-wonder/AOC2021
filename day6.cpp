#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>

using namespace std;

void solve(ifstream fin, int limit){
    string input;
    fin>>input;
    std::stringstream ss(input);
    unordered_map<int,long long> list;
    for (int i; ss >> i;) {
        list[i]++;
        if (ss.peek() == ',')
            ss.ignore();
    }
    int num = 0;
    while(num < limit){
        unordered_map<int,long long> new_list;
        for(auto ele : list){
            if(ele.first == 0) {
                new_list[6]+=ele.second;
                new_list[8]+=ele.second;
            }
            else {
                new_list[ele.first-1]+=ele.second;
            }
        }
        list = new_list;
        num++;
    }
    long long s=0;
    for(auto ele : list) s+=ele.second;
    cout<<s<<endl;

}

int main() {
    solve(ifstream("input"), 80);
    solve(ifstream("input"), 256);
}
