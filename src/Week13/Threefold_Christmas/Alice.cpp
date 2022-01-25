#include "vector"
#include "iostream"

void testcase() {
    int k;std::cin >> k;
    std::vector<std::vector<int>> values(k);
    std::vector<std::vector<int>> dp(k);
    for(int i=0; i<k; i++){
        for(int j=0; j<=i; j++){
            int v;std::cin >> v;
            values[i].push_back(v);
            dp[i].push_back(0);
        }
    }
    int result = INT_MIN;
    for(int i=k-1; i>=0; i--){
        for(int j=0; j<=i; j++){
            dp[i][j] += values[i][j];
            if(i+1 < k)
                dp[i][j] += dp[i+1][j] + dp[i+1][j+1];
            if(i+2 < k)
                dp[i][j] -= dp[i+2][j+1];
            result = std::max(result, dp[i][j]);
        }
    }
    std::cout << result << "\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}