#include "main.h"

vector<int> convert(string input){
    vector<int> result;
    for(int i=0;i<input.size();){
        char ch = input[i++];
        if(ch == '[') result.push_back(-1);
        else if(ch == ',') result.push_back(-2);
        else if(ch == ']') result.push_back(-3);
        else{
            result.push_back(ch-'0');
        }
    }
    return result;
}
long magnitude(vector<int> input){
    stack<char> open;
    stack<long> num;
    for(auto ele : input){
        if(ele == -1) continue;
        else if(ele == -2) continue;
        else if(ele == -3){
            long a = num.top() * 2;num.pop();
            long b = num.top() * 3;num.pop();
            num.push(a+b);
        }else{
            num.push(ele);
        }
    }
    return num.top();
}
bool explode(vector<int> &input){
    int i = 0, depth = 0;
    while(i < input.size()){
        if (input[i] == -1) {
            ++depth;
            if (depth == 5) {
                break;
            }
        } else if (input[i] == -3) {
            --depth;
        }
        ++i;
    }
    if (i == input.size()) {
        return false;
    }
    int j;
    for(j = i-1; j >= 0; j--){
        if(input[j] != -1 && input[j] != -2 && input[j] != -3){
            break;
        }
    }
    if(j >= 0){
        input[j] += input[i+1];
    }
    for(j = i+5; j < input.size(); j++){
        if(input[j] != -1 && input[j] != -2 && input[j] != -3){
            break;
        }
    }
    if(j >= 0){
        input[j] += input[i+3];
    }
    input.erase(input.begin() + i, input.begin() + i + 5);
    input.insert(input.begin() + i, 0);
    return true;
}
bool split(vector<int> &input){
    auto it = input.begin();
    while(it != input.end()){if(*it >= 10){break;}it++;}
    if (it == input.end()) {
        return false;
    }
    int val = *it;
    it = input.erase(it);
    input.insert(it, {-1, val/2, -2, (val+1)/2, -3});
    return true;
}
vector<int> reduce(vector<int> result){
    bool done = false;
    while(!done){
        if(explode(result) || split(result) ){
            continue;
        }
        else done = true;
    }
    //cout<<reverse(result)<<endl;
    return result;
}

vector<int> add(vector<int> left, vector<int> right){
    vector<int> input;
    input.push_back(-1);
    input.insert(input.end(), left.begin(), left.end());
    input.push_back(-2);
    input.insert(input.end(), right.begin(), right.end());
    input.push_back(-3);
    return reduce(input);
}

void solve(ifstream &fin){
    vector<vector<int>> input;
    for(string line; getline(fin,line);) {
        input.push_back(convert(line));
    }
    vector<int> i1 = input[0];
    for(int i = 1;i<input.size();i++){
        i1 = add(i1, input[i]);
    }
    cout<<magnitude(i1)<<endl;
    long ans = INT_MIN;
    for(int i = 0;i<input.size();i++){
        for(int j = i+1;j<input.size();j++){
            ans = max(ans, magnitude(
                    add(input[i],input[j])
                    ));
            ans = max(ans, magnitude(
                    add(input[j],input[i])
            ));
        }
    }
    cout<<ans<<endl;
}

int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
    return 0;
}
