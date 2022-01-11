#include "iostream"
#include "vector"
using VI = std::vector<int>;
using VVI = std::vector<VI>;
void testcase(){
    int n;std::cin >> n;
    int mat[n][n];
    VVI partial_sum(n+1, VI(n+1, 0));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int x;std::cin >> x;
            mat[i][j] = x;
            partial_sum[i+1][j+1] = partial_sum[i+1][j] + mat[i][j] + partial_sum[i][j+1] - partial_sum[i][j];
        }
    }
    VI row_sum(n, 0);
    int result = 0;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<=n; j++){
            int n_odd = 0;
            int n_even = 0;
            for(int k=0; k<n; k++){
                row_sum[k] = partial_sum[j][k+1] - partial_sum[i][k+1];
                
                if(row_sum[k] % 2==0){
                    result += n_even;
                    result += 1;
                    n_even++;    
                }
                else{
                    result += n_odd;
                    n_odd++;
                }
            }
        }
    }
    std::cout << result << "\n";

    
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t;std::cin >> t;
    for(int i=0; i<t; i++){
        testcase();
    }
}