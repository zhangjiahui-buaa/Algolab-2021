#include "iostream"
#include "vector"
#include "algorithm"
struct boat_type{
    int length;
    int ring;
    boat_type(int l, int r): length(l), ring(r){}
};
void testcase() {
	int n;std::cin >> n;
    std::vector<boat_type> boats;
    for(int i=0; i<n; i++){
        int l,r;std::cin >> l >> r;
        boats.push_back(boat_type(l,r));
    }
    std::sort(boats.begin(), boats.end(), [](boat_type& b1, boat_type& b2){
        return b1.ring < b2.ring;
    });
    int left_limit = INT_MIN, i=0, count = 0;
    while(i<n){
        if(boats[i].ring < left_limit){
            i++;
            continue;
        }
        int smallest_right = INT_MAX;
        int result_j;
        for(int j=i; j<n; j++){
            if(boats[j].ring > smallest_right){
                break;
            }
            if(smallest_right > std::max(boats[j].ring, left_limit + boats[j].length)){
                result_j = j;
                smallest_right = std::max(boats[j].ring, left_limit + boats[j].length);
            }
        }
        i = result_j + 1;
        count++;
        left_limit = smallest_right;
    }
    std::cout << count << "\n";
	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
