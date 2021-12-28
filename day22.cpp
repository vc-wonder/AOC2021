#include "main.h"
#include <thread>

vector<int> X,Y,Z;
struct cube{
    int xs,xe,ys,ye,zs,ze;
    bool on;
    cube(int xs,int xe,int ys,int ye,int zs,int ze,bool on):
            xs(xs),xe(xe),ys(ys),ye(ye),zs(zs),ze(ze),on(on){}
};
vector<cube> all_cubes;
vector<vector<vector<int>>> on_cubes;

void updateOnCubes(){
    for(auto &ele : all_cubes){
        int xs,xe,ys,ye,zs,ze;
        xs = distance(X.begin(), lower_bound(X.begin(), X.end(), ele.xs));
        xe = distance(X.begin(),lower_bound(X.begin(), X.end(), ele.xe+1));
        ys = distance(Y.begin(),lower_bound(Y.begin(), Y.end(), ele.ys));
        ye = distance(Y.begin(), lower_bound(Y.begin(), Y.end(), ele.ye+1));
        zs = distance(Z.begin(), lower_bound(Z.begin(), Z.end(), ele.zs));
        ze = distance(Z.begin(), lower_bound(Z.begin(), Z.end(), ele.ze+1));
        for(int i = xs; i < xe; i++) {
            for (int j = ys; j < ye; j++) {
                for (int k = zs; k < ze; k++) {
                    on_cubes[i][j][k] = ele.on;
                }
            }
        }
    }
}
void part1(){
    set<tuple<int,int,int>> cubes;
    for(auto &ele : all_cubes){
        int xs=ele.xs,xe=ele.xe,ys=ele.ys,ye=ele.ye,zs=ele.zs,ze=ele.ze;
        for(int i = max(-50,xs); i <= min(50,xe); i++){
            for(int j = max(-50,ys); j <= min(50,ye); j++){
                for(int k = max(-50,zs); k <= min(50,ze); k++){
                    if(ele.on) cubes.insert({i,j,k});
                    else{
                        cubes.erase({i,j,k});
                    }
                }
            }
        }
    }
    cout<<cubes.size()<<endl;
}
void part2(){
    on_cubes.resize(X.size(), vector<vector<int>>(Y.size(), vector<int>(Z.size())));
    updateOnCubes();
    long long total = 0;
    for(int i = 0; i < X.size()-1; i++) {
        for (int j = 0; j < Y.size()-1; j++) {
            for (int k = 0; k < Z.size()-1; k++) {
                if(on_cubes[i][j][k]){
                    long long dx = X[i+1] - X[i];
                    long long dy = Y[j+1] - Y[j];
                    long long dz = Z[k+1] - Z[k];
                    total += dx * dy * dz;
                }
            }
        }
    }
    cout<<total<<endl;
}

void solve(ifstream &fin) {
    for(string line; getline(fin,line);) {
        vector<string> input = splitOnString(line, " ");
        vector<string> values = splitOnString(input[1], ",");
        vector<string> x = splitOnString(values[0],"..");
        int xs = stoi(splitOnString(x[0],"=")[1]);
        int xe = stoi(x[1]);
        X.push_back(xs);X.push_back(xe+1);
        vector<string> y = splitOnString(values[1],"..");
        int ys = stoi(splitOnString(y[0],"=")[1]);
        int ye = stoi(y[1]);
        Y.push_back(ys);Y.push_back(ye+1);
        vector<string> z = splitOnString(values[2],"..");
        int zs = stoi(splitOnString(z[0],"=")[1]);
        int ze = stoi(z[1]);
        Z.push_back(zs);Z.push_back(ze+1);
        all_cubes.push_back(cube(xs,xe,ys,ye,zs,ze,input[0] == "on"));
    }
    sort(X.begin(), X.end()); sort(Y.begin(), Y.end()); sort(Z.begin(), Z.end());
    part1();
    part2();
}

int main() {
    ifstream fin("input");
    solve(fin);
    fin.close();
    return 0;
}
