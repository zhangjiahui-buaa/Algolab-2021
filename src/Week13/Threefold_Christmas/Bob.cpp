#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/dijkstra_shortest_paths.hpp"
#include "iostream"
#include "vector"
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, int>> Graph;
typedef boost::graph_traits<Graph> Traits;

void testcase() {
    int k;std::cin >> k;
    Graph g((k+1)*k);
    int half = ((k+1)*k)/2;
    std::vector<std::vector<int>> values(k);
    for(int i=0; i<k; i++){
        for(int j=0; j<=i; j++){
            int v;std::cin >> v;
            int idx = j + (i*(i+1))/2;
            values[i].push_back(v);
            boost::add_edge(idx, idx +  half, v, g);
            int adj_idx;
            if(i-1>=0){
                if(j-1>=0){
                    adj_idx = j-1 + (i*(i-1))/2;
                    boost::add_edge(idx + half, adj_idx, 0, g);
                }
                if(j<=i-1){
                    adj_idx = j + (i*(i-1))/2;
                    boost::add_edge(idx + half, adj_idx, 0, g);
                }
            }
            if(i+1<k){
                adj_idx = j + ((i+1)*(i+2))/2;
                boost::add_edge(idx + half, adj_idx, 0, g);
                adj_idx = j + 1 + ((i+1)*(i+2))/2;
                boost::add_edge(idx + half, adj_idx, 0, g);

            }
            if(j-1>=0){
                boost::add_edge(idx + half, idx - 1, 0, g);
            }
            if(j+1<=i){
                boost::add_edge(idx + half, idx + 1, 0, g);
            }
        }
    }
    std::vector<int> map1((k+1)*k);
    std::vector<int> map2((k+1)*k);
    std::vector<int> map3((k+1)*k);

    boost::dijkstra_shortest_paths(g, (k*(k-1))/2 ,boost::distance_map(&map1[0]));
    boost::dijkstra_shortest_paths(g, (k*(k-1))/2 + k - 1,boost::distance_map(&map2[0]));
    boost::dijkstra_shortest_paths(g, 0, boost::distance_map(&map3[0]));

    int result  = INT_MAX;
    for(int i=0; i<k; i++){
        for(int j=0; j<=i; j++){
            int idx = j + (i*(i+1))/2 + half;
            result = std::min(result, map1[idx] + map2[idx] + map3[idx] - 2*values[i][j]);
        }
    }
    std::cout << result << "\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}