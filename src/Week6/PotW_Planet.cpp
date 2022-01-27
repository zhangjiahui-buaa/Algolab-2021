///4
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/dijkstra_shortest_paths.hpp"
#include "iostream"
#include "vector"
#include "boost/graph/strong_components.hpp"
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, int>> Graph;
typedef boost::graph_traits<Graph> Traits;

void testcase() {
    int n,m,k,T;std::cin >> n >> m >> k >>T;
    Graph g(n);
    Graph g_r(n);
    std::vector<int> tele(T);
    for(int i=0; i<T; i++){
        std::cin >> tele[i];
    }
    for(int i=0; i<m; i++){
        int u,v,c;std::cin >> u >> v >> c;
        boost::add_edge(u,v,2* c,g);
        boost::add_edge(v,u,2* c,g_r);
    }
    std::vector<int> con_map(n);
    int noc = boost::strong_components(g, boost::make_iterator_property_map(con_map.begin(), boost::get(boost::vertex_index, g)));
    std::vector<int> nt(noc,0);
    for(int i=0; i<noc; i++)
        boost::add_vertex(g_r);
    for(int i=0; i<T; i++){
        nt[con_map[tele[i]]]++;
    }
    for(int i=0; i<T; i++){
        int con = con_map[tele[i]];
        boost::add_edge(tele[i], n+con, nt[con]-1 , g_r);
        boost::add_edge(n+con, tele[i], nt[con]-1 , g_r);
    }
    std::vector<int> dis_map(n+noc);
    boost::dijkstra_shortest_paths(g_r, n-1, boost::distance_map(&dis_map[0]));
    int result = INT_MAX;
    for(int i=0; i<k; i++){
        result = std::min(result, dis_map[i]);
    }
    if(result == INT_MAX || result/2 >= 1000000)
        std::cout << "no\n";
    else
        std::cout << result/2 << "\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}