class MiniGraph
{
public:
    int n,init_n,m;
    int* h,*ne,*e,*pe;
    bool* node_is_del;
    int* deg;
    int idx=0;
    void add(int u,int v){
        if(h[u]!=-1) pe[h[u]]=idx;
        ne[idx]=h[u];e[idx]=v;h[u]=idx++;
        if(h[v]!=-1) pe[h[v]]=idx;
        ne[idx]=h[v];e[idx]=u;h[v]=idx++;
        deg[u]++;deg[v]++;
    }
    void init(int n_,int m_,ui* pstart,ui* edges){
        int* pt=(int*) pstart,*et=(int*)edges;
        assert(pt!=nullptr&&et!=nullptr);
        init(n_,m_,pt,et);
    }
    void init(int n_,int m_,int *pstart,int* edges){
        //m (a,b) (b,a) all counts
        idx=0;assert(pstart!=nullptr&&edges!=nullptr);
        init_n=n=n_,m=m_;
        h=new int[n];
        deg=new int[n];
        ne=new int[m];
        e=new int[m];
        pe=new int[m];
        node_is_del=new bool[n];
        memset(deg,0,n*sizeof(int));
        memset(h,-1,n*sizeof (int));
        memset(node_is_del,0,n*sizeof(bool));
        memset(ne,-1,m*sizeof (int));
        memset(e,-1,m*sizeof (int));
        memset(pe,-1,m*sizeof (int));
        for(int i=0;i<n;i++){
            for(int j=pstart[i];j<pstart[i+1];j++){
                int v=edges[j];
                if(v<i) continue;
                add(i,v);
            }
        }
    }

    void inline delete_edge(int edge){
        if(pe[edge]!=-1)//pe[j] ->j ->ne[j]
        {
            ne[pe[edge]]=ne[edge];
            if(ne[edge]!=-1) pe[ne[edge]]=pe[edge];
        }
        else{
            int u=e[edge^1];//h[u]==j
            h[u]=ne[edge];
            if(ne[edge]!=-1) pe[ne[edge]] = -1;
        }
    }

    void delete_node(int v){
        assert(v>=0&&v<init_n);
        assert(!node_is_del[v]);
        m-=deg[v]*2;
        for(int i=h[v];i!=-1;i=ne[i]){ //remove edge
            int j=i^1;
            delete_edge(i);
            delete_edge(j);
            int u=e[i];
#ifndef NDEBUG
            for(int k=h[v];k!=-1;k=ne[k]) assert(e[k]!=u);
            for(int k=h[u];k!=-1;k=ne[k]) assert(e[k]!=v);
            assert(!node_is_del[u]);
#endif
            deg[u]--;
        }
        deg[v]=0;
        n--;
        node_is_del[v]=true;
        h[v]=-1;
    }

    int inline get_deg(int v){return deg[v];}
    bool inline is_del(int v){return node_is_del[v];}

    ~MiniGraph(){
        if(h!=nullptr){
            delete[] h;
            h=nullptr;
        }
        
        if(ne!=nullptr){
            delete[] ne;
            ne=nullptr;
        }
        
        if(e!=nullptr){
            delete[] e;
            e=nullptr;
        }

        if(pe!=nullptr){
            delete[] pe;
            pe=nullptr;
        }

        if(node_is_del!=nullptr){
            delete[] node_is_del;
            node_is_del=nullptr;
        }

        if(deg!=nullptr){
            delete[] deg;
            deg=nullptr;
        }
    }
};