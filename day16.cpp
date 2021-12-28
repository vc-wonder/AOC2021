#include "main.h"
int versions;
string input;

long long evaluate(vector<long long> values, int type){
    long long result;
    switch(type){
        case 0:{
                result = 0;
                while(!values.empty()) {
                    result += values.back();
                    values.pop_back();
                }
            }
            break;
        case 1:{
                result = 1;
                while(!values.empty()) {
                    result *= values.back();
                    values.pop_back();
                }
            }
            break;
        case 2:{
                result = LONG_LONG_MAX;
                while(!values.empty()) {
                    result = min(values.back(), result);
                    values.pop_back();
                }
            }
            break;
        case 3:{
                result = LONG_LONG_MIN;
                while(!values.empty()) {
                    result = max(values.back(), result);
                    values.pop_back();
                }
            }
            break;
        case 5:{
                long long val1 = values.back();values.pop_back();
                long long val2 = values.back();values.pop_back();
                result = val2 > val1?1:0;
            }
            break;
        case 6:{
                long long val1 = values.back();values.pop_back();
                long long val2 = values.back();values.pop_back();
                result = val2 < val1?1:0;
            }
            break;
        case 7:{
                long long val1 = values.back();values.pop_back();
                long long val2 = values.back();values.pop_back();
                result = val1 == val2?1:0;
            }
            break;
        default:
            result = 0;
            break;
    }
    return result;
}

long parsePacket(){
    int start = 0;
    string version, type;
    if(input.size() <= 6) return 0;
    for(int j = 0; j< 3 && start < input.size();j++){
        version += input[start++];
    }
    versions += stoi(version, 0, 2);
    for(int j = 0; j< 3 && start < input.size();j++){
        type += input[start++];
    }
    if(type != "100" && start < input.size()){
        int size = input[start++] == '0'? 15 : 11;
        vector<long long> values;
        if(size == 15){
            string length;
            while(size--){
                length += input[start++];
            }
            int len = stoi(length, nullptr, 2);
            input = input.substr(start);
            int curr_size = input.size();
            while (input.size() > (curr_size - len))
                values.push_back(parsePacket());
        }else{
            string numbers;
            while(size--){
                numbers += input[start++];
            }
            int count = stoi(numbers, nullptr, 2);
            input = input.substr(start);
            while(count--){
                values.push_back(parsePacket());
            }
        }
        return evaluate(values, stoi(type, nullptr, 2));

    }else{
        string num;
        while(start < input.size() && input[start] == '1'){
            num += input.substr(start+1, 4);
            start += 5;
        }
        num += input.substr(start+1, 4);
        start += 5;
        input = input.substr(start);
        return stoll(num, nullptr, 2);
    }
}

string getBinary(char &hex){
    switch(hex) {
        case '0' :
            return "0000";
        case '1' :
            return "0001";
        case '2' :
            return "0010";
        case '3' :
            return "0011";
        case '4' :
            return "0100";
        case '5' :
            return "0101";
        case '6' :
            return "0110";
        case '7' :
            return "0111";
        case '8' :
            return "1000";
        case '9' :
            return "1001";
        case 'A' :
            return "1010";
        case 'B' :
            return "1011";
        case 'C' :
            return "1100";
        case 'D' :
            return "1101";
        case 'E' :
            return "1110";
        case 'F' :
            return "1111";
    }
}

void solve(ifstream &fin){
    string line;
    getline(fin,line);
    for(char ch : line){
        input += getBinary(ch);
    }
    long long result = parsePacket();
    cout<<versions<<endl;
    cout<<result<<endl;
}

int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
    return 0;
}
