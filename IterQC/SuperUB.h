#include "Graph.h"
#include "Branch.h"
#include "ListLinearHeap.h"
#include "MiniGraph.h"

class SuperUB_Extractor{
public:
    ui* peel_sequence;
    bool gama_type=false;
    double gama=0;
    ui* pstart,*edges;
    int n,m;
    void get_quasi_bound(int& lb,int& ub){
        ui* degree = new ui[n];
        char *vis = new char[n];
        ListLinearHeap *heap = new ListLinearHeap(n, n-1);
        for(ui i = 0;i < n;i ++){
            degree[i] = pstart[i+1] - pstart[i];
        }
        
        memset(vis, 0, sizeof(char)*n);
        for(ui i = 0;i < n;i ++) peel_sequence[i] = i;

        ui idx = n,UB=0,max_core=0;
        heap->init(n, n-1, peel_sequence, degree);
        for(ui i = 0;i < n;i ++) {
            ui u, key;
            heap->pop_min(u, key);
            max_core=max(max_core,key);
            //if(key>=1+my_ceil(gama*(n-i-1))&&idx==n) idx=i;
            if(key>=my_ceil(gama*(n-i-1))&&idx==n) idx=i;
            UB=max((int)UB,1+my_ceil(max_core/gama));
            peel_sequence[i] = u;
            vis[u] = 1;
            for(ui j = pstart[u];j < pstart[u+1];j ++) if(vis[edges[j]] == 0) {
                heap->decrement(edges[j], 1);
            }
        }
        cout<<"Max Core:"<<max_core<<endl;
        //for(int i=0;i<idx;i++) mini_g.delete_node(peel_sequence[i]);        
        delete heap;
        delete[] vis;
        delete[] degree;
        lb=n-idx;
        ub=UB;
    }

    void init(string file_path,double gama_){
        gama_type=true;
        gama=gama_;
        if(pstart==nullptr){
            Graph* g=new Graph();
            g->readFromFile(file_path);
            n=g->n;m=g->m;
            peel_sequence=new ui[n];
            pstart=new ui[n+1];
            edges=new ui[m];
            memcpy(pstart,g->pstart,(n+1)*sizeof(int));
            memcpy(edges,g->edge_to,m*sizeof(int));
            delete g;
        }
    }
    ~SuperUB_Extractor(){
        delete[] peel_sequence;
        delete[] pstart;
        delete[] edges;
    }
};