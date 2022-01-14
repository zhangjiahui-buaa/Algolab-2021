#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <climits>
using VI = std::vector<int>;
using VVI = std::vector<VI>;
int f(VVI& adj, int start, int n, int* memo){
    if(memo[start]==-1){
        if(start == n-1)
            memo[start] = 0;
        else if(std::find(adj[start].begin(), adj[start].end(), n-1)!= adj[start].end())
            memo[start] = 1;
        else{
            int result = INT_MAX;
            for(int i=0; i<adj[start].size(); i++){
                int cur = adj[start][i];
                int tmp = 0;
                for(int j=0; j<adj[cur].size(); j++){
                    tmp = std::max(tmp, 1+ f(adj, adj[cur][j], n, memo));
                }
                result = std::min(result, 1+tmp);
            }
            memo[start] = result;
        }
    }
    return memo[start];
}
void testcase() {
    int n,m;std::cin >> n >> m;
    int r,b;std::cin >> r >> b;
    r--;b--;
    int dp[n];
    VVI adj(n, VI());
    for(int i=0; i<m; i++){
        int u,v;std::cin >> u >> v;
        u--;v--;
        adj[u].push_back(v);
    }
    for(int i =0;i<n;i++)
        dp[i] = -1;
    f(adj, r,n,dp);
    if(dp[b]==-1)
        f(adj,b,n,dp);
    if(dp[r] < dp[b])
        std::cout << 0;
    else if(dp[r] > dp[b])
        std::cout << 1;
    else{
        if(dp[r] % 2 !=0)
            std::cout << 0;
        else 
            std::cout << 1;
    }
    std::cout << "\n";

	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
