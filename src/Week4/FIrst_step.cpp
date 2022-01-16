#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/dijkstra_shortest_paths.hpp"
#include "boost/graph/kruskal_min_spanning_tree.hpp"
#include "iostream"
typedef boost::adjacency_list<boost::vecS,
                                boost::vecS,
                                boost::undirectedS,
                                boost::no_property,
                                boost::property<boost::edge_weight_t, int>> Graph;
typedef boost::graph_traits<Graph> Traits;
typedef Traits::edge_descriptor Edge_descriptor;
typedef boost::property_map<Graph, boost::edge_weight_t>::type Weight_map;
typedef Traits::vertex_descriptor Vertex_descriptor;
int minimum_spanning_value(Graph& g){
    std::vector<Edge_descriptor> tree(boost::num_edges(g));
    boost::kruskal_minimum_spanning_tree(g, tree.begin());
    Weight_map weights = boost::get(boost::edge_weight, g);
    int result = 0;
    for(auto it = tree.begin(); it!=tree.end(); it++){
        result += weights[*it];
    }
    return result;
}

int furtherest_vertex(Graph& g, Vertex_descriptor v){
    std::vector<int> distance(boost::num_vertices(g));
    std::vector<Vertex_descriptor> pred(boost::num_vertices(g));
    boost::dijkstra_shortest_paths(g,v,
                boost::distance_map(
                boost::make_iterator_property_map(
                    distance.begin(), boost::get(boost::vertex_index,g))
                ).predecessor_map(boost::make_iterator_property_map(
                    pred.begin(), boost::get(boost::vertex_index, g)))
                );
    return *std::max_element(distance.begin(), distance.end());
    
}
void testcase() {
	int n,m;std::cin >> n >> m;
    Graph g(n);
    for(int i=0; i<m; i++){
        int from, to, weight;std::cin >> from >> to >> weight;
        boost::add_edge(from, to, weight, g);
    }
    std::cout << minimum_spanning_value(g) << " " << furtherest_vertex(g,0) << "\n";
	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}


