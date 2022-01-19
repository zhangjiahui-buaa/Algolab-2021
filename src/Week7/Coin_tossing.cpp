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
    int n,m;std::cin >> n >> m;
    graph g(n);
    edge_adder adder(g);
    std::vector<int> pts(n,0);
    vertex_desc v_source = boost::add_vertex(g);
    vertex_desc v_target = boost::add_vertex(g);
    long matches = 0;
    for(int i=0; i<m; i++){
        int a,b,c; std::cin >> a >> b >> c;
        if(c==1)
            pts[a] += 1;
        else if(c==2)
            pts[b] += 1;
        else{
            matches++;
            vertex_desc v_match = boost::add_vertex(g);
            adder.add_edge(v_source, v_match, 1, true);
            adder.add_edge(v_match, a, 1, true);
            adder.add_edge(v_match, b, 1, true);
        }
    }
    for(int i=0; i<n; i++){
        int score; std::cin >> score;
        pts[i] = score - pts[i];
    }
    long demands = 0;
    for(int i=0; i<n; i++){
        if(pts[i] < 0){
            std::cout << "no\n";
            return;
        }else{
            adder.add_edge(i, v_target, pts[i], true);
            demands += pts[i];
        }
    }
    long flow = boost::push_relabel_max_flow(g, v_source, v_target);
    std::cout << ((flow==demands && flow==matches) ? "yes\n" : "no\n");
  return;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t;
  std::cin >> t;
  for (int i = 0; i < t; ++i)
    testcase();
}
