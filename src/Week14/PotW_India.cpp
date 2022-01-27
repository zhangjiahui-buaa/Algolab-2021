///4
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
int cost(int pivot, graph& g, int k, int a, edge_adder& adder){
    vertex_desc v_source = boost::add_vertex(g);
    vertex_desc v_target = boost::add_vertex(g);
    adder.add_edge(v_source, k, pivot, 0);
    adder.add_edge(a, v_target, pivot, 0);
    boost::successive_shortest_path_nonnegative_weights(g, v_source, v_target);
    return boost::find_flow_cost(g);
}
void testcase() {
    int c,G,b,k,a;std::cin >> c >> G >> b >> k >> a;
    graph g(c);
    edge_adder adder(g);
    for(int i=0; i<G; i++){
        int x,y,d,e;std::cin >> x >> y >> d >> e;
        adder.add_edge(x,y,e,d);
    }
    vertex_desc v_source = boost::add_vertex(g);
    vertex_desc v_target = boost::add_vertex(g);
    adder.add_edge(v_source, k, INT_MAX, 0);
    adder.add_edge(a, v_target, INT_MAX, 0);
    int right = boost::push_relabel_max_flow(g, v_source, v_target);
    int left = 0;
    while(left < right){
        int pivot = (left+right)/2 + 1;
        if(cost(pivot, g, k, a, adder) <= b)
            left = pivot;
        else
            right = pivot - 1;
    }
    std::cout << right << "\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}