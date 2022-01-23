///5
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/dijkstra_shortest_paths.hpp"
#include "boost/graph/push_relabel_max_flow.hpp"
#include "iostream"
#include "climits"

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
        boost::property<boost::edge_weight_t, int>> weighted_graph;
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
        boost::property<boost::edge_capacity_t, long,
                boost::property<boost::edge_residual_capacity_t, long,
                        boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
typedef std::vector<int> VI;
typedef std::vector<VI> VVI;
class edge_adder {
    graph &G;

public:
    explicit edge_adder(graph &G) : G(G) {}

    void add_edge(int from, int to, long capacity, bool is_directed) {
        auto c_map = boost::get(boost::edge_capacity, G);
        auto r_map = boost::get(boost::edge_reverse, G);
        const auto e = boost::add_edge(from, to, G).first;
        const auto rev_e = boost::add_edge(to, from, G).first;
        c_map[e] = capacity;
        c_map[rev_e] = is_directed ? 0 : capacity; // reverse edge has no capacity!
        r_map[e] = rev_e;
        r_map[rev_e] = e;
    }
};

void testcase() {
    int n,m,a,s,c,d;std::cin >> n >> m >> a >> s >> c >> d;
    weighted_graph wg(n);
    for(int i=0; i<m; i++){
        char w;
        int x,y,z; std::cin >> w >> x >> y >> z;
        if(w=='S'){
            boost::add_edge(x,y,z,wg);
        }else{
            boost::add_edge(x,y,z,wg);
            boost::add_edge(y,x,z,wg);
        }
    }
    VI agents(a);
    VI shelters(s);
    for(int i=0; i<a; i++)
        std::cin >> agents[i];
    for(int i=0; i<s; i++)
        std::cin >> shelters[i];
    VVI dis(a, VI(s));
    for(int i=0; i<a; i++){
        std::vector<int> tmp(n);
        boost::dijkstra_shortest_paths(wg, agents[i], boost::distance_map(boost::make_iterator_property_map(tmp.begin(), boost::get(boost::vertex_index, wg))));
        for(int j=0; j<s; j++){
            dis[i][j] = tmp[shelters[j]];
        }
    }
    int left = 0, right = INT_MAX;
    while(left < right){
        int pivot = (left+right)/2;
        graph g(a+c*s);
        edge_adder adder(g);
        vertex_desc v_source = boost::add_vertex(g);
        vertex_desc v_target = boost::add_vertex(g);
        for(int i=0; i<a; i++){
            for(int j=0; j<s; j++){
                for(int k=0; k<c; k++){
                    if(dis[i][j] != INT_MAX && dis[i][j]+(k+1)*d <= pivot)
                        adder.add_edge(i, a+k*s+j, 1, true);
                }
            }
            adder.add_edge(v_source, i, 1, true);
        }
        for(int j=0; j<s; j++)
            for(int k=0; k<c; k++)
                adder.add_edge(a+k*s+j, v_target, 1, true);
        long flow = boost::push_relabel_max_flow(g, v_source, v_target);
        if(flow==a)
            right = pivot;
        else
            left = pivot + 1;
    }
    std::cout << left << "\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}