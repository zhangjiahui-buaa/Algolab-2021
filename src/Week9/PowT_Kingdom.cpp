///1
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/push_relabel_max_flow.hpp"
#include "iostream"
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
        boost::property<boost::edge_capacity_t, long,
                boost::property<boost::edge_residual_capacity_t, long,
                        boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
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
    int l,p;std::cin >> l >> p;
    graph g(l);
    edge_adder adder(g);
    vertex_desc v_source = boost::add_vertex(g);
    vertex_desc v_target = boost::add_vertex(g);
    long demand = 0;
    for(int i=0; i<l; i++){
        int g,d;std::cin >> g >> d;
        adder.add_edge(v_source, i, g, true);
        adder.add_edge(i, v_target, d, true);
        demand += d;
    }
    for(int i=0; i<p; i++){
        int f,t,minc,maxc;std::cin >> f >> t >> minc >> maxc;
        adder.add_edge(v_source, t, minc, true);
        adder.add_edge(f, v_target, minc, true);
        demand += minc;
        adder.add_edge(f,t,maxc-minc,true);
    }
    long flow = boost::push_relabel_max_flow(g,v_source, v_target);
    if(flow==demand)
        std::cout << "yes\n";
    else
        std::cout << "no\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}