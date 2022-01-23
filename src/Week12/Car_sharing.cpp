///4
#include "iostream"
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include "map"
#include "vector"
// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
        boost::property<boost::edge_capacity_t, long,
                boost::property<boost::edge_residual_capacity_t, long,
                        boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs
typedef boost::graph_traits<graph>::vertex_descriptor           vertex_desc;
typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

// Custom edge adder class
class edge_adder {
    graph &G;

public:
    explicit edge_adder(graph &G) : G(G) {}
    void add_edge(int from, int to, long capacity, long cost) {
        auto c_map = boost::get(boost::edge_capacity, G);
        auto r_map = boost::get(boost::edge_reverse, G);
        auto w_map = boost::get(boost::edge_weight, G); // new!
        const edge_desc e = boost::add_edge(from, to, G).first;
        const edge_desc rev_e = boost::add_edge(to, from, G).first;
        c_map[e] = capacity;
        c_map[rev_e] = 0; // reverse edge has no capacity!
        r_map[e] = rev_e;
        r_map[rev_e] = e;
        w_map[e] = cost;   // new assign cost
        w_map[rev_e] = -cost;   // new negative cost
    }
};

void testcase() {
    int N,S;std::cin >> N >> S;
    int ST=0,FT=100000, MAXP = 100;
    std::vector<std::map<int, vertex_desc>> vertex_map(S);
    std::vector<int> initial(S);
    graph g;
    edge_adder adder(g);
    for(int i=0; i<S; i++){
        std::cin >> initial[i];
        vertex_desc vst = boost::add_vertex(g);
        vertex_map[i].insert(std::make_pair(ST, vst));
        vertex_desc vft = boost::add_vertex(g);
        vertex_map[i].insert(std::make_pair(FT, vft));
    }
    for(int i=0; i<N; i++){
        int s,t,d,a,p;std::cin >> s >> t >> d >> a >> p;
        s--; t--;
        if(vertex_map[s].find(d) == vertex_map[s].end()){
            vertex_desc v = boost::add_vertex(g);
            vertex_map[s].insert(std::make_pair(d,v));
        }
        if(vertex_map[t].find(a) == vertex_map[t].end()){
            vertex_desc v = boost::add_vertex(g);
            vertex_map[t].insert(std::make_pair(a,v));
        }
        adder.add_edge(vertex_map[s][d], vertex_map[t][a], 1, -p + MAXP * (a-d));
    }
    vertex_desc v_source = boost::add_vertex(g);
    vertex_desc v_target = boost::add_vertex(g);
    for(int i=0; i<S; i++){
        adder.add_edge(v_source,vertex_map[i][ST], initial[i], 0);
        auto it = vertex_map[i].begin();
        auto it_next = vertex_map[i].begin(); it_next++;
        while(it_next != vertex_map[i].end()){
            adder.add_edge(it->second, it_next->second, INT_MAX, MAXP * (it_next->first - it->first));
            it++; it_next++;
        }
        adder.add_edge(vertex_map[i][FT], v_target, INT_MAX, 0);
    }
    boost::successive_shortest_path_nonnegative_weights(g, v_source, v_target);
    int cost = boost::find_flow_cost(g);
    boost::property_map<graph, boost::edge_capacity_t>::type c_map = boost::get(boost::edge_capacity, g);
    auto rc_map = boost::get(boost::edge_residual_capacity, g);
    int s_flow = 0;
    out_edge_it e, eend;
    for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source,g), g); e != eend; ++e) {
        s_flow += c_map[*e] - rc_map[*e];
    }
    std::cout << -cost + s_flow * FT * MAXP << "\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}