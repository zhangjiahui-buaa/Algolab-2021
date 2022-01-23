#include "boost/pending/disjoint_sets.hpp"
#include "iostream"
#include "vector"
#include "climits"
struct edge_type{
    int from;
    int to;
    int cost;
};
int cost(std::vector<edge_type>& edges, int ignore, int n, std::vector<int>& MST){
    boost::disjoint_sets_with_storage<> uf(n);
    int result = 0;
    for(int i=0; i<edges.size(); i++){
        if(i==ignore)
            continue;
        int c1 = uf.find_set(edges[i].from);
        int c2 = uf.find_set(edges[i].to);

        if(c1!=c2){
            uf.link(c1,c2);
            MST.push_back(i);
            result += edges[i].cost;
        }
        if(MST.size()==n-1)
            break;
    }
    return result;
}
void testcase() {
    int n,i;std::cin >> n >> i;
    std::vector<edge_type> edges;
    for(int j=0; j<n-1;j++){
        for(int k=1; k<=n-j-1; k++){
            int c;std::cin >> c;
            edges.push_back({j,j+k,c});
        }
    }
    std::sort(edges.begin(), edges.end(), [](edge_type& e1, edge_type& e2){
        return e1.cost < e2.cost;
    });
    std::vector<int> MST;
    int minc = cost(edges, -1, n, MST);
    int result = INT_MAX;
    for(int ig: MST){
        std::vector<int> tmp;
        int curc = cost(edges, ig, n, tmp);

            result = std::min(result, curc);
    }
    std::cout << result << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}