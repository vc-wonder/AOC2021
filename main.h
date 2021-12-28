#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>

using namespace std;

template<typename T>
void printVector(vector<T> input){
    for(auto ele : input) cout<<ele<<" ";
    cout<<endl;
}

vector<string> splitOnChar(const string &input, char delimiter){
    stringstream ss(input);
    vector<string> result;
    for(string word;getline(ss, word, delimiter);){
        result.push_back(word);
    }
    return result;
}

vector<string> splitOnString(const string &input, string delimiter){
    vector<string> result;
    int start = 0;
    int end = input.substr(0).find(delimiter);
    while(start < end){
        string word = input.substr(start, end-start);
        result.push_back(word);
        start = end + delimiter.size();
        end = start + input.substr(start).find(delimiter);
    }
    //last word
    string word = input.substr(start);
    result.push_back(word);
    return result;
}
