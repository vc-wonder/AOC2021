#include "main.h"

unordered_map<char,int> score,score2;
unordered_map<char,char> mapping;
unordered_map<char,int> invalid;

void solve(ifstream &fin){
    vector<unsigned long long> ans2;
    for(string line; getline(fin,line);){
        bool corrupted = false;
        stack<char> ss;

        for(char ch : line){
            if(ch == '{' || ch == '(' || ch == '<' || ch == '['){
                ss.push(ch);
            }else{
                if(ss.empty()) {invalid[ch]++;corrupted=true;break;}
                else if(ss.top() != mapping[ch]) {
                    //cout<<ss.top()<<"!="<<mapping[ch]<<endl;
                    invalid[ch]++;
                    corrupted = true;
                    break;
                }
                else ss.pop();
            }
        }
        if(!corrupted){
            unsigned long long  ans = 0;
            // cout<<"uncorrupted";
            // cout<<ss.size()<<endl;

            while(!ss.empty()){
                char ch = ss.top();//cout<<ss.top()<<endl;
                ans = (ans*5) + score2[ch];
                ss.pop();
            }
            //cout<<ans<<endl;
            ans2.push_back(ans);
        }
        //cout<<endl;
    }
    int s = 0;
    for(auto ele : invalid){
        //cout<<ele.first<<"->"<<ele.second<<endl;
        s += (ele.second * score[ele.first]);
    }
    cout<<s<<endl;
    sort(ans2.begin(), ans2.end());
    //pv(ans2);
    cout<<ans2[ans2.size()/2]<<endl;
}
int main() {
    score[')'] = 3;
    score[']'] = 57;
    score['}'] = 1197;
    score['>'] = 25137;
    score2['('] = 1;
    score2['['] = 2;
    score2['{'] = 3;
    score2['<'] = 4;
    mapping[')'] = '(';
    mapping[']'] = '[';
    mapping['}'] = '{';
    mapping['>'] = '<';
    ifstream fin("input");
    solve(fin);
    fin.close();
    return 0;
}
