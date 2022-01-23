#include <iostream>
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/push_relabel_max_flow.hpp"
#include "vector"
#include "map"
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
        boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::edge_descriptor edge_desc;
typedef traits::edge_descriptor edge_desc;
typedef traits::vertex_descriptor vertex_desc;
class edge_adder {
    graph &G;
public:
    explicit edge_adder(graph &G) : G(G) {}
    void add_edge(int from, int to, long capacity) {
        auto c_map = boost::get(boost::edge_capacity, G);
        auto r_map = boost::get(boost::edge_reverse, G);
        const auto e = boost::add_edge(from, to, G).first;
        const auto rev_e = boost::add_edge(to, from, G).first;
        c_map[e] = capacity;
        c_map[rev_e] = 0; // reverse edge has no capacity!
        r_map[e] = rev_e;
        r_map[rev_e] = e;
    } };

void testcase(){
    int n,m; std::cin >> n >> m;
    graph G(n);
    vertex_desc v_source=boost::add_vertex(G);
    vertex_desc v_end = boost::add_vertex(G);
    edge_adder adder(G);
    long in=0;
    for (int t=0; t<n; t++){
        int bt; std::cin >> bt;
        if(bt<0){
            adder.add_edge(t, v_end, -bt);
        }else{
            adder.add_edge(v_source, t, bt);
            in+=bt;
        }
    }
    for(int t=0; t<m;t++){
        int i,j,dij; std::cin >> i >> j >> dij;
        adder.add_edge(i,j,dij);
    }
    long flow = boost::push_relabel_max_flow(G,v_source,v_end);
    std::cout << ((flow<in)?"yes":"no")<< "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t;std::cin >> t;
    for(int i=0; i<t;i++){
        testcase();
    }
}   