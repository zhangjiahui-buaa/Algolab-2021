#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/max_cardinality_matching.hpp"
#include "iostream"
#include "string"
#include "algorithm"
typedef boost::adjacency_list<boost::vecS,
                              boost::vecS,
                              boost::undirectedS> Graph;
typedef boost::graph_traits<Graph> Traits;
typedef std::vector<std::string> interests;
int common(interests& o1, interests& o2){
    int i1 = 0, i2 = 0;
    int result = 0;
    while(i1 < o1.size() && i2 < o2.size()){
        if(o1[i1] == o2[i2]){
            result++;
            i1++;
            i2++;
        }else if(o1[i1] < o2[i2])
            i1++;
        else
            i2++;
    }
    return result;
}
void testcase(){
    int n,c,f;std::cin >> n >> c >> f;
    Graph g(n);
    std::vector<interests> students(n);
    for(int i=0; i<n; i++){
        for(int j=0; j<c; j++){
            std::string s;std::cin >> s;
            students[i].push_back(s);
        }
        std::sort(students[i].begin(), students[i].end());
    }
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(common(students[i], students[j]) > f)
                boost::add_edge(i,j,g);
        }
    }
    std::vector<Traits::vertex_descriptor> mate(n);
    boost::edmonds_maximum_cardinality_matching(g, boost::make_iterator_property_map(mate.begin(), boost::get(boost::vertex_index, g)));
    int ms = boost::matching_size(g, boost::make_iterator_property_map(mate.begin(), boost::get(boost::vertex_index, g)));
    std::cout << (ms * 2 == n) ? "not optimal\n" : "optimal\n"; 

}
int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
                        