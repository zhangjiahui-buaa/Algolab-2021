#include "iostream"
#include "vector"
#include "map"
#include "climits"
typedef std::vector<int> VI;
typedef std::vector<VI> VVI;
typedef std::vector<VVI> VVVI; 
int mm = 1024*1024*256;
int f(int start, bool father, bool self, VI& price, VVVI& memo, std::map<int, std::vector<int>>& adj){
    if(self==0 && father==0 && adj[start].empty()){
        return mm;
    }
    if(memo[start][father][self]==mm){
        int result = mm;
        int tmp = 0;
        if(self){
            tmp += price[start];
            for(int child : adj[start])
                tmp += std::min(f(child, self, 0, price, memo, adj), f(child, self, 1, price, memo, adj));
            result = std::min(result, tmp);
        }else{
            if(father){
                for(int child : adj[start]){
                    tmp += std::min(f(child, self, 0, price, memo, adj), f(child, self, 1, price, memo, adj));
                }
                result = std::min(result, tmp);
            }else{
                int min_diff = mm;
                for(int child: adj[start]){
                    tmp += std::min(f(child, self, 0, price, memo, adj), f(child, self, 1, price, memo, adj));
                    min_diff = std::min(min_diff,  f(child, self, 1, price, memo, adj) - std::min(f(child, self, 0, price, memo, adj), f(child, self, 1, price, memo, adj)));
                }
                tmp += min_diff;
                result = std::min(result, tmp);
            }
        }
        memo[start][father][self] = std::min(result, (int)mm);
    }
    return memo[start][father][self];
}
int nf(int start, int status, VI& prices, VVI& memo,std::map<int, std::vector<int>>& adj){
    if(memo[start][status] == -1){
        if(adj[start].empty()){
            if(status == 0) memo[start][status] = prices[start];
            else if(status == 1) memo[start][status] = INT_MAX;
            else memo[start][status] = 0;
        }else{
            if(status==0){
                memo[start][status] = prices[start];
                for(int child : adj[start]){
                    memo[start][status] += std::min(std::min(nf(child, 0, prices, memo, adj),
                                                    nf(child, 1, prices, memo, adj)),nf(child, 2, prices, memo, adj));
                }
            }else if(status == 1){
                int min_diff = INT_MAX;
                int sum = 0;
                for(int child : adj[start]){
                    sum += std::min(nf(child, 0, prices, memo, adj), nf(child, 1 , prices, memo, adj));
                    if(nf(child, 0, prices, memo, adj) - std::min(nf(child, 0, prices, memo, adj), nf(child, 1 , prices, memo, adj)) < min_diff){
                        min_diff = nf(child, 0, prices, memo, adj) - std::min(nf(child, 0, prices, memo, adj), nf(child, 1 , prices, memo, adj));
                    }
                }
                memo[start][status] = sum + min_diff;
            }else{
                memo[start][status] = 0;
                for(int child : adj[start]){
                    if(nf(child, 1, prices, memo, adj)==INT_MAX){
                        memo[start][status] = INT_MAX;
                        break;    
                    }
                    memo[start][status] += nf(child, 1, prices, memo, adj);
                }
            }
        }
    }
    return memo[start][status];
}
void testcase() {
    int n;std::cin >> n;
	std::ios_base::sync_with_stdio(false);
    std::map<int, std::vector<int>> adj;
    for(int i=0; i<n-1; i++){
        int u,v;std::cin >> u >> v;
        adj[u].push_back(v);
    }
    std::vector<int> price(n);
    for(int i=0; i<n; i++)
        std::cin >> price[i];
    VVI memo(n, VI(3, -1));
    std:cout << std::min(nf(0,0,price, memo, adj), nf(0,1,price, memo,adj)) << "\n";
    //VVVI memo(n,VVI(2,VI(2,mm)));
    //std::cout << std::min(f(0, 0, 0, price, memo, adj), f(0, 0, 1, price, memo, adj)) << "\n";
    
	return;
}

int main() {

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
