#include "iostream"
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

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
    int n,m,k;std::cin >> n >> m >> k;
    graph g(n+m);
    edge_adder adder(g);
    vertex_desc v_ps = boost::add_vertex(g);
    vertex_desc v_pt = boost::add_vertex(g);
    for(int i=0; i<m; i++){
        int s,t,c;std::cin >> s >> t >> c;
        adder.add_edge(s, n+i, 1, c);
        adder.add_edge(t, n+i, 1, c);
        adder.add_edge(n+i, v_pt, 1, 0);
    }
    for(int i=0; i<n; i++){
        adder.add_edge(v_ps, i, 1, 0);
    }
    vertex_desc v_s = boost::add_vertex(g);
    vertex_desc v_t = boost::add_vertex(g);
    adder.add_edge(v_s, v_ps, k, 0);
    adder.add_edge(v_pt, v_t, k, 0);
    boost::successive_shortest_path_nonnegative_weights(g, v_s, v_t);
    int cost = boost::find_flow_cost(g);
    out_edge_it e_begin, e_end;
    int s_flow = 0;
    boost::property_map<graph, boost::edge_capacity_t>::type c_map = boost::get(boost::edge_capacity, g);
    boost::property_map<graph, boost::edge_residual_capacity_t>::type rc_map = boost::get(boost::edge_residual_capacity, g);
    for(boost::tie(e_begin, e_end) = boost::out_edges(v_s, g); e_begin!=e_end; e_begin++){
        s_flow += c_map[*e_begin] - rc_map[*e_begin];
    }
    if(s_flow==k)std::cout << cost << "\n";
    else std::cout << "no\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}