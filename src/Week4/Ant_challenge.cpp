#include "boost/graph/adjacency_list.hpp"
#include "iostream"
#include "boost/graph/dijkstra_shortest_paths.hpp"
#include "queue"
typedef boost::adjacency_list<boost::vecS,
        boost::vecS,
        boost::undirectedS,
        boost::no_property,
        boost::property<boost::edge_weight_t,int>> Graph;
typedef boost::graph_traits<Graph> Traits;
typedef Traits::vertex_descriptor vertex_desc;
typedef Traits::edge_descriptor edge_desc;
typedef Traits::out_edge_iterator out_edge_it;
struct ele{
    edge_desc edge;
    int weight;
};
void bfs(Graph& g_specie, Graph& g_forest, vertex_desc start){
    auto cmp = [](ele& e1, ele& e2){
        return e1.weight > e2.weight;
    };
    std::priority_queue<ele, std::vector<ele>, decltype(cmp)> pq(cmp);
    boost::property_map<Graph, boost::edge_weight_t>::type weight_map = boost::get(boost::edge_weight, g_specie);
    std::vector<bool> visited(boost::num_vertices(g_specie), false);
    visited[start] = true;
    int find = 1;
    out_edge_it it_begin, it_end;
    for(boost::tie(it_begin, it_end) = boost::out_edges(start, g_specie); it_begin!=it_end; it_begin++){
        pq.push({*it_begin, weight_map[*it_begin]});
    }
    while(!pq.empty()){
        auto top = pq.top(); pq.pop();
        vertex_desc v1 = boost::source(top.edge, g_specie), v2 = boost::target(top.edge, g_specie);
        int weight = top.weight;
        if(visited[v1] && visited[v2]) continue;

        vertex_desc v = visited[v1] ? v2 : v1;
        visited[v] = true;
        boost::add_edge(v1,v2,weight,g_forest);
        find++;
        if(find==visited.size()) break;
        for(boost::tie(it_begin, it_end) = boost::out_edges(v, g_specie); it_begin != it_end; it_begin++){
            if(!visited[boost::target(*it_begin, g_specie)])
                pq.push({*it_begin, weight_map[*it_begin]});
        }
    }
}
void testcase() {
    int n,e,s,a,b;std::cin >> n >> e >> s >> a >> b;
    std::vector<Graph> gs(s, Graph(n));
    for(int i=0; i<e; i++){
        int u,v;std::cin >> u >> v;
        for(int j=0; j<s; j++){
            int w;std::cin >> w;
            boost::add_edge(u,v,w,gs[j]);
        }
    }
    Graph forest(n);
    for(int i=0; i<s; i++){
        int h;std::cin >> h;
        bfs(gs[i],forest, h);
    }
    std::vector<int> distance_map(n);
    boost::dijkstra_shortest_paths(forest, a, boost::distance_map(boost::make_iterator_property_map(distance_map.begin(), boost::get(boost::vertex_index, forest))));
    std::cout << distance_map[b] << "\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
