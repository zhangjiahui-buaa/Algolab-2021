#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

void testcase() {
	int n;std::cin >> n;
    int a[n];
    int sum[n];
    int result = 0;
    int n_even = 0;
    int n_odd = 0;
    for(int i=0; i<n; i++){
        int x;
        std::cin >> x;
        a[i] = x;
        sum[i] = i==0 ? x : sum[i-1] + x;  
        if(sum[i] % 2 == 0){
            result += 1 + n_even++;
        }else{
            result += n_odd++;
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
