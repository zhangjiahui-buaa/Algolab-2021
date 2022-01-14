#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
using VI = std::vector<int>;
using VVI = std::vector<VI>;

int nf(int start, int m, int n, VVI& memo, int* length, int* defence){
    if(memo[start][m] == -1){
        if(m==0)
            memo[start][m] = 0;
        else if(start == n){
            memo[start][m] = -2;
        }else{
            if(length[start] == 0){
                memo[start][m] = nf(start+1, m, n, memo, length, defence);
            }else{
                memo[start+length[start]][m-1] = nf(start+length[start], m-1, n, memo, length, defence);
                memo[start+1][m] = nf(start+1, m, n , memo, length, defence);
                if(memo[start+length[start]][m-1]!= -2)
                    memo[start][m] = std::max(memo[start+length[start]][m-1] + length[start], memo[start+1][m]);
                else
                    memo[start][m] = memo[start+1][m];
            }
        }
    }
    return memo[start][m];
}
void testcase() {
	int n,m,k;std::cin >> n >> m >> k;
    int defence[n];
    int length[n];
    for(int i=0; i<n; i++){
        int v;std::cin >> v;
        defence[i] = v;
        length[i] = 0;
    }
    int left = 0, right = left+1, sum = defence[left];
	while(left < n && right<=n){
        if(sum==k){
            length[left] = right-left;
            sum -= defence[left];
            left++;
            if(right==left){
                right++;
                sum = defence[left];
            } 
        }else if(sum < k){
            sum += defence[right];
            right++;
        }else{
            sum -= defence[left];
            left++;
            if(right==left){
                right++;
                sum = defence[left];
            } 
        }
    }
    VVI memo(n+1, VI(m+1,-1));
    nf(0,m,n,memo,length,defence);
    if(memo[0][m]==-2)
        std::cout << "fail\n";
    else 
        std::cout << memo[0][m] << "\n";
    return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
