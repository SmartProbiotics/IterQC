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
    string s;
    getline(cin,s);
    getline(cin,s);
    
    int n,m;cin>>n;
    cin>>n>>m;
    int m_cnt=0;
    vector<pair<int,int>> e;
    for(int i=0;i<m;i++){
        string s;
        getline(cin,s);
        stringstream ss(s);
        int v,u;ss>>u>>v;
        if(v!=u)
        e.push_back(make_pair(v,u));
    }
    cout<<"p edge "<<n<<" "<<e.size()<<endl;
    for(auto p:e)
        cout<<"e "<<p.first<<" "<<p.second<<endl;
    
    of.close();
}