///1
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/push_relabel_max_flow.hpp"
#include "iostream"
#include "vector"
#include "string"
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
	int h,w;std::cin >> h >> w;
	int base = 'Z' - 'A' + 1;
    std::vector<int> frequency_char(base, 0);
    std::vector<int> frequency_piece(base*base, 0);
    graph g(base * base + base);
    edge_adder adder(g);
    vertex_desc v_source = boost::add_vertex(g);
    vertex_desc v_target = boost::add_vertex(g);
    std::string note; std::cin >> note;
    for(int i=0; i<note.size(); i++){
        frequency_char[note[i] - 'A']++;
    }
    for(int i=0; i<base; i++){
        adder.add_edge(i + base*base, v_target, frequency_char[i], true);
    }
    std::vector<std::string> front;
    for(int i=0; i<h; i++){
        std::string s; std::cin >> s;
        front.push_back(s);
    }
    for(int i=0; i<h; i++){
        std::string s; std::cin >> s;
        for(int j=0; j<w; j++){
            int idx = (s[j]-'A')*base + front[i][w-j-1]-'A';
            frequency_piece[idx]++;
        }
    }
    for(int i=0; i<base*base; i++){
        adder.add_edge(v_source, i, frequency_piece[i], true);
        adder.add_edge(i, i%base+base*base, frequency_piece[i], true);
        adder.add_edge(i, i/base+base*base, frequency_piece[i], true);
    }
    long flow = boost::push_relabel_max_flow(g, v_source, v_target);
    std::cout << ((flow==note.size()) ? "Yes\n" : "No\n");
    return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
