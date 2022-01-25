#include "iostream"
#include "vector"
#include "unordered_map"
typedef std::vector<int> VI;
int dp(int start, std::unordered_map<int, std::vector<int>>& adj, VI& memo){
    if(memo[start]==-1){
        int result = 0;
        int total = 0;
        for(int i=0; i<adj[start].size(); i++){
            total += dp(adj[start][i], adj, memo);
        }
        result = std::max(result, total);
        for(int i=0; i<adj[start].size(); i++){
            int tmp = 1;
            int idx = adj[start][i];
            for(int j=0; j<adj[idx].size(); j++){
                tmp += dp(adj[idx][j], adj, memo);
            }
            result = std::max(result, tmp + total - dp(idx, adj, memo));
        }
        memo[start] = result;
    }
    return memo[start];
}
void testcase() {
    int n,m;std::cin >> n >> m;
    std::unordered_map<int, std::vector<int>> adj;
    for(int i=0; i<m; i++){
        int u,v;std::cin >> u >> v;
        u--;v--;
        adj[u].push_back(v);
    }
    VI memo(n,-1);
    std::cout << dp(0, adj, memo) << "\n";
	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}