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
    of.open(fileName.c_str(),ios::out);

    
    int n,m;cin>>n>>m;
    of<<n<<" "<<m<<endl;
    getchar();
    for(int i=0;i<n;i++){
        int v;cin>>v;
        char c=getchar();
        while(c!='\r'&&c!='\n'){
            int u=-1;
            cin>>u;
            if(u>v)
                of<<v<<" "<<u<<endl;
            c=getchar();
        }
    }

    of.close();
}