//处理点的坐标从1开始（都怪real world graphs）处理后下标从0开始 ./C-\>A grpah save_directory

#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
int main(int argc,char* argv[]){
    ofstream of;
    string fileName = string(argv[1]);
    freopen(fileName.c_str(),"r",stdin);
    int idx=0;
    for(int i=fileName.size()-1;i>=0;i--){
        if(fileName[i]=='/'){
            idx=i+1;
            break;
        }
    }
    
    fileName=string(argv[2])+"/"+fileName.substr(idx);
    cout<<fileName<<endl;
    freopen(fileName.c_str(),"w",stdout);

    string p;cin>>p;string edges;cin>>edges;
    
    int n,m;cin>>n>>m;
    vector<vector<int>> e(n+10);
    vector<set<int>> st(n+10);
    cout<<n<<" "<<m<<endl;
    int dec=0;
    for(int i=0;i<m;i++){
        char c;cin>>c;
        int v,u;cin>>u>>v;
        if(i==0)
            dec=(u!=0&&v!=0);
        if(!st[v-dec].count(u-dec)){
            e[v-dec].push_back(u-dec);
            st[v-dec].insert(u-dec);
        }        
        if(!st[u-dec].count(v-dec)){
            e[u-dec].push_back(v-dec);
            st[u-dec].insert(v-dec);
        }
    }

    for(int i=0;i<n;i++){
        cout<<i<<(0==e[i].size()?"":" ");
        for(int j=0;j<e[i].size();j++){
            cout<<e[i][j]<<(j==e[i].size()-1?"":" ");
        }
        cout<<endl;
    }
    of.close();
}