#include "main.h"

void solve(ifstream &fin, bool part2){
    string input1, arrow, input2;
    map<pair<int,int>,int> counts;
    set<pair<int,int>> points;
    while(fin>>input1 && fin>>arrow && fin>> input2){
        int i = input1.find_first_of(',');
        int x1 = stoi(input1.substr(0, i));
        int y1 = stoi(input1.substr(i+1));
        i = input2.find_first_of(',');
        int x2 = stoi(input2.substr(0, i));
        int y2 = stoi(input2.substr(i+1));
        //cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;

        if(x1==x2){
            for(int i = min(y1,y2); i<=max(y2,y1);i++){
                auto key = make_pair(x1,i);
                counts[key]++;
                if(counts[key] == 2) {
                    points.insert(key);
                }
            }
        }
        else if(y1==y2){
            for(int i = min(x1,x2); i<=max(x1,x2);i++){
                auto key = make_pair(i,y1);
                counts[key]++;
                if(counts[key] == 2){
                    points.insert(key);
                }
            }
        }else if(part2){
            if(y2<y1){
                swap(x1,x2);
                swap(y1,y2);
            }
            for(int y = y1;y <= y2;y++){
                int x = x2 < x1? x1-(y-y1): x1+(y-y1);
                auto key = make_pair(x,y);
                counts[key]++;
                if(counts[key] == 2){
                    points.insert(key);
                }
            }
        }

    }
    cout<<points.size()<<endl;
}

int main() {
    ifstream fin1("input"), fin2("input");
    solve(fin1, false);
    solve(fin2, true);
    fin1.close();
    fin2.close();
    return 0;
}
