#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <climits>
void testcase() {
	int n,m;std::cin >> n >> m;
    std::vector<int> strengths(n);
    std::multiset<int, std::greater<int>> weights;
    int max_s = INT_MIN, max_w = INT_MIN;
    for(int i=0; i<n; i++){
        int s; std::cin >> s;
        strengths[i] = s;
        max_s = std::max(s, max_s);
    }
    for(int i=0; i<m; i++){
        int w;std::cin >> w;
        weights.insert(w); 
        max_w = std::max(w, max_w);
    }
    if(max_w > max_s){
        std::cout << "impossible\n";
        return;
    }
    std::sort(strengths.begin(), strengths.end(), std::greater<int>());
    int r = 0;
    while(!weights.empty()){
        r++;
        for(int i=0; i<n; i++){
            auto j = weights.lower_bound(strengths[i]);
            if(j==weights.end()){
                break;
            }else{
                weights.erase(j);
            }
        }
    }
    std::cout << 2*r+r-1 << "\n";
	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
