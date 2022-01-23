#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <climits>
typedef std::vector<int>  VI;
typedef std::vector<VI> VVI;
typedef std::vector<VVI> VVVI;
int f(int x1, int y1, int x2, VVI& mat, VVVI& memo){
    if(memo[x1][y1][x2]==-1){
        int y2 = x1+y1-x2;
        int result = x1==x2 ? mat[x1][y1] : mat[x1][y1] + mat[x2][y2];
        int tmp = 0;
        if(x1+1< mat.size() && x2+1<mat.size()){
            tmp = std::max(tmp,f(x1+1, y1, x2+1, mat, memo));
        }
        if(x1+1<mat.size() && y2+1<mat.size()){
            tmp = std::max(tmp, f(x1+1, y1, x2, mat,memo));
        }
        if(y1+1<mat.size() && x2+1<mat.size()){
            tmp = std::max(tmp, f(x1, y1+1, x2+1, mat, memo));
        }
        if(y1+1<mat.size() && y2+1<mat.size()){
            tmp = std::max(tmp, f(x1, y1+1, x2, mat, memo));
        }
        result += tmp;
        memo[x1][y1][x2] = result;
    }
    return memo[x1][y1][x2];
}
void testcase() {
    int n;std::cin >> n;
    VVI mat(n, VI(n));
    for(int i=0; i<n; i++){
        for(int j=0; j<n ;j++){
            std::cin >> mat[i][j];       
        }
    }
    VVVI memo(n, VVI(n, VI(n,-1)));
    std::cout << f(0,0,0,mat, memo) << "\n";
	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
