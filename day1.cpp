#include "main.h"
void solve(ifstream &fin){
    vector<int> input;
    for(string line; getline(fin,line);) {
        input.push_back(stoi(line));
    }
    int count = 0, i=1;
    while(i < input.size()){
        if(input[i] > input[i-1]){
            count++;
        }
        i++;
    }
    cout<<count<<endl;
    //part2
    vector<long> input2;
    i = 2;
    while(i < input.size()){
        int s =  input[i] + input[i-1] + input[i-2];
        input2.push_back(s);
        i++;
    }
    count = 0;
    i=1;
    while(i < input2.size()){
        if(input2[i] > input2[i-1]){
            count++;
        }
        i++;
    }
    cout<<count<<endl;
}

int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
    return 0;
}
