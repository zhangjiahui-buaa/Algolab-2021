#include "iostream"
#include "vector"
void testcase(){
    int n,k;std::cin >> n >> k;
    std::vector<int> card(n);
    for(int i=0; i<n; i++)
        std::cin >> card[i];
    int left =0, right = 0, sum=card[0];
    int result = INT_MAX, i = -1, j = -1;
    while(right < n){
        if(sum == k){
            std::cout << left << " " << right << "\n";
            return;
        }
        if(std::abs(sum-k) < result){
            result = std::abs(sum-k);
            i = left;
            j = right;
        }

        if(sum < k){
            right++;
            if(right ==n) break;
            sum += card[right];
        }else{
            sum -= card[left];
            left--;
            if(left > right){
                right++;
                if(right==n) break;
                sum += card[right];
            }
        }
    }
    std::cout << i << " " << j << "\n";
}
int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
