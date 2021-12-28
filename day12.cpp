#include "main.h"

map<string,vector<string>> nodes;
unordered_set<string> visited;

int findPaths1(string &current){
    if(current == "end") return 1;
    int paths = 0;
    for(auto &ele : nodes[current]){
        if(!visited.count(ele)) {
            if(islower(ele[0])) visited.insert(ele);
            paths += findPaths1(ele);
            if(visited.count(ele)) visited.erase(ele);
        }
    }
    return paths;
}

int findPaths2(string &current, bool twice){
    if(current == "end") return 1;
    int paths = 0;
    for(auto &ele : nodes[current]){
        if(!visited.count(ele)){
            if(islower(ele[0])) visited.insert(ele);
            paths += findPaths2(ele, twice);
            if(visited.count(ele)) visited.erase(ele);
        }else if (!twice && ele != "start"){
            paths += findPaths2( ele, true);
        }
    }
    return paths;
}
void solve(ifstream &fin){
    vector<vector<int>> octopus;
    for(string line; getline(fin,line);) {
        auto edge = splitOnString(line, "-");
        nodes[edge[0]].push_back(edge[1]);
        nodes[edge[1]].push_back(edge[0]);
    }
    string start = "start";
    visited.insert(start);
    cout<<findPaths1(start)<<endl;
    visited.clear();
    visited.insert(start);
    cout<<findPaths2(start, false);
}
int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
    return 0;
}
