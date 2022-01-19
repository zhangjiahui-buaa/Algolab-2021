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
  int m,n,k,c;std::cin >> m >> n >> k >> c;
    graph g(2*m*n);
    edge_adder adder(g);
    vertex_desc v_source = boost::add_vertex(g);
    vertex_desc v_target = boost::add_vertex(g);
    for(int i=0; i<k; i++){
        int column, row; std::cin >> column >> row;
        adder.add_edge(v_source, row * m + column, 1, true);
    }
    int offset = m*n;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            int idx = i*m + j;
            int out_ways = (i==0 || i==n-1) + (j==0 || j==m-1);
            if(out_ways > 0){
                adder.add_edge(idx+offset, v_target, out_ways, true);
            }

            adder.add_edge(idx, idx+offset, c, true);

            if(i>0){
                adder.add_edge(idx+offset, (i-1)*m+j, 1, true);
                adder.add_edge((i-1)*m+j+offset, idx, 1, true);
            }

            if(j>0){
                adder.add_edge(idx+offset, i*m+j-1, 1, true);
                adder.add_edge(i*m+j-1+offset, idx, 1, true);
            }
        }
    }
    long flow = boost::push_relabel_max_flow(g, v_source, v_target);
    std::cout << flow << "\n";

  return;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t;
  std::cin >> t;
  for (int i = 0; i < t; ++i)
    testcase();
}
