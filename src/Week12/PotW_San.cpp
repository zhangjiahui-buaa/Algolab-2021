///2
#include "iostream"
#include "vector"
#include "map"
long f(int k, int start, std::vector<std::map<int,long>>& adj, std::vector<std::vector<long>>& memo){
    if(memo[k][start]==-1){
        if(k==0)
            memo[k][start] = 0;
        else if(adj[start].empty())
            memo[k][start] = f(k, 0, adj, memo);
        else{
            for(auto nei : adj[start])
                memo[k][start] = std::max(memo[k][start], nei.second + f(k-1, nei.first, adj, memo));
        }
    }
    return memo[k][start];
}
void testcase() {
    long n,m,x,k;std::cin >> n >> m >> x >> k;
    std::vector<std::map<int,long>> adj(n);
    for(int i=0; i<m; i++){
        int u,v,c;std::cin >> u >> v >> c;
        adj[u][v] = std::max(adj[u][v], (long)c);
    }
    std::vector<std::vector<long>> memo(k+1, std::vector<long>(n, -1));
    if(f(k,0,adj,memo) < x)
        std::cout << "Impossible\n";
    else{
        int left = 0, right =k;
        while(left < right){
            int pivot = (left+right)/2;
            if(f(pivot, 0, adj, memo) < x)
                left = pivot + 1;
            else
                right = pivot;
        }
        std::cout << left << "\n";
    }
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}