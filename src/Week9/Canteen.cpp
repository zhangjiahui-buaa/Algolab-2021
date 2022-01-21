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
    int n;std::cin >> n;
    graph g(n);
    edge_adder adder(g);
    vertex_desc v_source = boost::add_vertex(g);
    vertex_desc v_target = boost::add_vertex(g);
    int shift = 20;
    int number = 0;
    for(int i=0; i<n; i++){
        int a,c;std::cin >> a >> c;
        adder.add_edge(v_source, i, a, c);
    }
    for(int i=0; i<n; i++){
        int s,p;std::cin >> s >> p;
        adder.add_edge(i, v_target, s, -p+shift);
        number += s;
    }
    for(int i=0; i<n-1; i++){
        int v,e;std::cin >> v >> e;
        adder.add_edge(i,i+1, v, e);
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
    if(s_flow == number) std::cout << "possible ";
    else std::cout << "impossible ";
    std::cout << s_flow << " " << -cost + s_flow * shift << "\n";
  return;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t;
  std::cin >> t;
  for (int i = 0; i < t; ++i)
    testcase();
}
