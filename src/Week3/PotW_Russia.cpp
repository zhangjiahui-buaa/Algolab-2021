#include "vector"
#include "iostream"

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

int f(int start, int end, int people, VI& values, VVI& memo){
    if(memo[start][end] == -1){
        if(end-start+1 <= people){
            memo[start][end] = std::max(values[start], values[end]);
        }else{
            int re1 = 0, re2 = 0;
            for(int i=0; i<end-start-people+1; i++){
                re1 = std::min(re1, values[start] + f(start + i + 1, end- people + i + 1, people, values, memo));
                re2 = std::min(re2, values[end] + f(start+i, end-people+i, people, values, memo));
            }
            memo[start][end] = std::max(re1, re2);
        }
    }
    return memo[start][end];
}
void testcase() {
    int n,m,k; std::cin >> n >> m >> k;
    VI values(n);
    for(int i=0; i<n; i++)
        std::cin >> values[i];
    if(n<k+1)
        std::cout << 0 << "\n";
    else{
        int re = INT_MAX;
        VVI memo(n-1, VI(n-1, -1));
        for(int i=0; i<k+1; i++){
            re = std::min(re, f(0, n-k-1, m, values, memo));
        }
        std::cout << re << "\n";
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