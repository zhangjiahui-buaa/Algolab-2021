#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/max_cardinality_matching.hpp"
#include "iostream"
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
typedef boost::graph_traits<Graph> Traits;
typedef Traits::vertex_descriptor vertex_desc;
void testcase() {
    int n,m;std::cin >> n >> m;
    Graph g(2*n);
    for(int i=0; i<m; i++){
        int s,t;std::cin >> s >> t;
        boost::add_edge(n+s, t, g);
    }
    std::vector<vertex_desc> mate(2*n);
    boost::edmonds_maximum_cardinality_matching(g, boost::make_iterator_property_map(mate.begin(), boost::get(boost::vertex_index, g)));
    int ms = boost::matching_size(g, boost::make_iterator_property_map(mate.begin(), boost::get(boost::vertex_index, g)));
    std::cout << ms << "\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}