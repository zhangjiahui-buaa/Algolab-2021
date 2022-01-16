#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/biconnected_components.hpp"

/*typedef boost::adjacency_list<boost::vecS,
                              boost::vecS,
                              boost::undirectedS,
                              boost::no_property,
                              boost::property<boost::edge_name_t,int>> Graph;
                              */
                              
typedef boost::adjacency_list<boost::vecS,
                              boost::vecS,
                              boost::undirectedS,
                              boost::no_property,
                              boost::property<boost::edge_index_t,int>> Graph;                 

typedef boost::graph_traits<Graph> Traits;
typedef Traits::edge_descriptor Edge_desc;
typedef Traits::edge_iterator Edge_it;
void testcase(){
    int n,m; std::cin  >> n >> m;
    Graph g(n);
    for(int i=0; i<m; i++){
        int u,v;std::cin >> u >> v;
        boost::add_edge(u,v,i,g);
    }
    //boost::property_map<Graph, boost::edge_name_t>::type component = boost::get(boost::edge_name, g);
    boost::property_map<Graph, boost::edge_index_t>::type index_map = boost::get(boost::edge_index, g);
    std::vector<int> component_2(boost::num_edges(g));
    //std::size_t num = boost::biconnected_components(g, component);
    std::size_t num = boost::biconnected_components(g, boost::make_iterator_property_map(component_2.begin(), boost::get(boost::edge_index, g)));
    std::vector<int> nec(num,0);
    for(int i=0; i<component_2.size(); i++){
        nec[component_2[i]]++;
    }
    Edge_it it_begin, it_end;

    /*for(boost::tie(it_begin, it_end) = boost::edges(g); it_begin!=it_end; it_begin++){
        nec[component[*it_begin]]++;
    }*/

    std::vector<std::pair<int,int>> result;
    /*for(boost::tie(it_begin, it_end) = boost::edges(g); it_begin!=it_end; it_begin++){
        if(nec[component[*it_begin]] == 1){
            int u = boost::source(*it_begin,g);
            int v = boost::target(*it_begin,g);
            result.push_back(std::make_pair(std::min(u,v), std::max(u,v)));
        }
    }*/
    for(boost::tie(it_begin, it_end) = boost::edges(g); it_begin!=it_end; it_begin++){
        if(nec[component_2[index_map[*it_begin]]] == 1){
            int u = boost::source(*it_begin,g);
            int v = boost::target(*it_begin,g);
            result.push_back(std::make_pair(std::min(u,v), std::max(u,v)));
        }
    }
    std::sort(result.begin(), result.end(), [](std::pair<int,int>& o1, std::pair<int,int>&o2){
        return (o1.first < o2.first) || (o1.first==o2.first && o1.second < o2.second);
    });
    std::cout << result.size() << "\n";
    for(std::pair<int,int>& p : result){
        std::cout << p.first << " " << p.second << "\n";
    }
}
int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}