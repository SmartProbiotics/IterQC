#include "kplex.h"
#include <string>
using namespace std;
#define LEN_LIMIT (1 << 10)
char filename[LEN_LIMIT];

void check_graph(Graph *g)
{
    cout << "Check Graph: " << "N Anno:" << g->n << "  M Anno:" << g->m << endl;
    long long n = g->n, m = g->m;
    if (n * (n - 1) < m)
    {
        cout << n * (n - 1) << endl;
        cout << "Graph Error!" << endl;
        exit(1);
    }

    bool *st = new bool[n];
    ui *pstart = g->pstart, *edges = g->edge_to;
    memset(st, 0, sizeof(bool) * n);
    for (int i = 0; i < n; i++)
    {
        vector<int> neig;
        for (int j = g->pstart[i]; j < g->pstart[i + 1]; j++)
        {
            int v = edges[j];
            // cout<<"("<<i<<","<<v<<"),"<<endl;
            if (v < 0 || v >= n)
            {
                delete[] st;
                cout << "Graph Error! Wrong vertice id" << endl;
                exit(1);
            }
            if (st[v])
            {
                delete[] st;
                cout << "Graph Error! Multiple edges" << endl;
                exit(1);
            }
            if (v == i)
            {
                delete[] st;
                cout << "Graph Error! Self Loop" << endl;
                exit(1);
            }
            st[v] = true;
            neig.push_back(v);
            m--;
        }
        for (auto &v : neig)
            st[v] = false;
    }
    delete[] st;
    if (m)
    {
        cout << "Graph Error!not true edge count" << endl;
        cout << "M announced - True count =" << m << endl;
        exit(1);
    }
    cout << "Check : Correct Graph" << endl;
}
Graph *graph, *new_graph;

void shrink_graph(MiniGraph &mini_g, int d_limit)
{
    int n = mini_g.n;
    ui *degree = new ui[n], *peel_sequence = new ui[n];
    int *h = mini_g.h, *ne = mini_g.ne, *e = mini_g.e;
    ListLinearHeap *heap = new ListLinearHeap(n, n - 1);
    for (ui i = 0; i < n; i++)
    {
        degree[i] = mini_g.get_deg(i);
        assert(degree[i] < n);
    }

    for (ui i = 0; i < n; i++)
        peel_sequence[i] = i;
    heap->init(n, n - 1, peel_sequence, degree);
    for (ui i = 0; i < n; i++)
    {
        ui u, key;
        heap->pop_min(u, key);
        if (key >= d_limit)
            break;
        peel_sequence[i] = u;
        for (int j = h[u]; j != -1; j = ne[j])
            heap->decrement(e[j], 1);
        mini_g.delete_node(u);
    }

    delete heap;
    delete[] degree;
    delete[] peel_sequence;

    // start refresh graph
    int new_n = mini_g.n, new_m = mini_g.m;
    if (new_graph != nullptr)
        delete new_graph;
    new_graph = new Graph();
    ui *pstart = new ui[new_n + 1], *edges = new ui[new_m], *deg = new ui[new_n];
    ui pstart_idx = 0, edges_idx = 0;

    int *id_map = new int[n], idx = 0;
    memset(id_map, -1, n * sizeof(int));
    vector<int> vset;
    for (int i = 0; i < n; i++)
        if (!mini_g.is_del(i))
            deg[idx] = mini_g.get_deg(i), vset.push_back(i), id_map[i] = idx++;
    pstart[0] = 0;
    for (int i = 1; i <= new_n; i++)
        pstart[i] = pstart[i - 1] + deg[i - 1];
    for (int i = 0; i < new_n; i++)
    {
        int u = vset[i];
        int pre = edges_idx;
        assert(!mini_g.is_del(u));
        for (int j = h[u]; j != -1; j = ne[j])
        {
            int v = id_map[e[j]];
            assert(!mini_g.is_del(e[j]));
            edges[edges_idx++] = v;
        }
        assert(edges_idx - pre == deg[i]);
    }
    delete graph;
    graph = new Graph();
    graph->init_with_basic(new_n, new_m, deg, pstart, edges);
    delete[] id_map;
    delete[] pstart;
    delete[] edges;
    delete[] deg;
}

int main(int argc, char *argv[])
{
    printf("\n-----------------------------------------------------------------------------------------\n");

    file_path = string(argv[1]);
    cout << file_path << endl;
    gama = atof(argv[2]);

    cout << "gama: " << gama << endl;
    if (gama < 0.5)
    {
        cout << "error! gamma must >=0.5" << endl;
        exit(1);
    }
    double alpha = 1 - gama;
    graph = new Graph();
    graph->readFromFile(file_path);
    // If you are not sure whether the graph input is valid, please let the following row check it.
    // check_graph(graph);
    long long s1 = clock();

    cout << filename << " n:" << graph->n << " m:" << graph->m << endl;
    SuperUB_Extractor se;
    se.init(file_path, gama);

    long long start = clock();
    int lb, n = graph->n, k;
    bool need_iteration = true;
#ifndef NO_PRE_PROC
    se.get_quasi_bound(lb, n);
    cout << "Extract UB:" << (double)(clock() - start) / CLOCKS_PER_SEC << "s UB value:" << n << " LB value:" << lb << endl;

    k = 1 + alpha * (n - 1);
    start = clock();
    MiniGraph mini_g;
    assert(graph->edge_to != nullptr);
    mini_g.init(graph->n, graph->m, graph->pstart, graph->edge_to);
    int pre_graph_n = graph->n, pre_graph_m = graph->m;
    if (lb > 0)
        shrink_graph(mini_g, my_floor((lb - 1) * gama) + 1);
    cout << "Prunning graph:" << endl
         << "new n:" << mini_g.n << " " << "new m:" << mini_g.m << endl;
    printf("Prunning N:%.2f%  M:%.2f%\n", 100 * (double)(pre_graph_n - mini_g.n) / pre_graph_n, 100 * (double)(pre_graph_m - mini_g.m) / pre_graph_m);
    cout << "Shrink graph Cost:" << (double)(clock() - start) / CLOCKS_PER_SEC << endl;
    n = min(max(mini_g.n, lb), n);
    need_iteration = (mini_g.n != 0 && mini_g.n > lb);
#endif
    start = clock();
    if (need_iteration)
    {
        k = my_floor(1 + alpha * (n - 1));
        while (1)
        {
            int UB = n;
            std::cout << "UB: " << std::left << std::setw(6) << UB << " ";
            std::cout << "K: " << std::left << std::setw(6) << k << " ";
            bool is_bad_instance = true;
            int pre_n = n;
            n = search(graph, k, gama, n, is_bad_instance);
            std::cout << "N: " << std::left << std::setw(6) << n << " ";
            if (k == my_floor(alpha * (n - 1) + 1) && !is_bad_instance)
                break;
            k = my_floor(alpha * (n - 1) + 1);
            puts("");
        }
    }
    cout << "Final Iteration Cost:" << (double)(clock() - start) / CLOCKS_PER_SEC << endl;
    // vector<int> res;
    // for(auto v:solution) res.push_back(v);
    delete graph;
    cout << "Running Time: " << (double)(clock() - s1) / CLOCKS_PER_SEC << "s" << endl;
    cout << "res: " << n << endl;
    // for(auto v:solution) cout<<v<<" ";
    // cout<<endl;
    printf("-----------------------------------------------------------------------------------------\n\n");
}
// n-1-core=alpha*(n-1)
// gama*n=core-alpha+1
// n=(core-alpha+1)/gama=core/gama+1
