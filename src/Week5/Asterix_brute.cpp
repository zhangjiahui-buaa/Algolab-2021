#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <climits>
struct move_type{
    long distance;
    long time;
};
struct aggregated{
    int number_of_moves;
    long total_distance;
    long total_time;
};
bool valid_potion(std::vector<aggregated>& one, std::vector<aggregated>& two, long D, long T, long potion){
    std::vector<aggregated> new_one;
    long previous_distance = -1;
    for(int i=0; i<one.size(); i++){
        if(one[i].total_distance + one[i].number_of_moves * potion > previous_distance){
            new_one.push_back({one[i].number_of_moves, one[i].total_distance + one[i].number_of_moves * potion,one[i].total_time });
            previous_distance = one[i].total_distance + one[i].number_of_moves * potion;
        }
    }
    for(int i=0; i<two.size(); i++){
        int left = 0, right = new_one.size()-1;
        while(left<right){
            int pivot = (left+right)/2+1;
            if(two[i].total_time + new_one[pivot].total_time < T)
                left = pivot;
            else
                right = pivot-1;
        }
        if(two[i].total_distance + two[i].number_of_moves * potion + new_one[right].total_distance >= D)
            return true;
    }
    return false;
}
void split(std::vector<move_type>& actual, std::vector<aggregated>& result, long T){
    int n = actual.size();
    for(int i=0; i< 1 << n; i++){
        int number = 0;
        long total_time = 0;
        long total_distance = 0;
        for(int j=0; j<n; j++){
            if(i& 1<< j){
                number++;
                total_distance += actual[j].distance;
                total_time += actual[j].time;
            }
        }
        if(total_time < T){
            result.push_back({number, total_distance, total_time});
        }
    }
}
void testcase() {
    int n,m;
    long D,T;
    std::cin >> n >> m >> D >> T;
    std::vector<move_type> moves_one, moves_two;
    std::vector<long> power(m+1,0);
    for(int i=0; i<n; i++){
        long d,t;std::cin >> d >> t;
        if(i<n/2)
            moves_one.push_back({d,t});
        else
            moves_two.push_back({d,t});
    }
    for(int i=1; i<=m; i++){
        std::cin >> power[i];
    }
    std::vector<aggregated> one, two;
    split(moves_one, one, T);
    split(moves_two, two, T);
    std::sort(one.begin(), one.end(), [](aggregated& a1, aggregated& a2){
        return a1.total_time < a2.total_time;
    });
    long left = 0, right = m;
    if(!valid_potion(one,two, D,T,power[m])){
        std::cout << "Panoramix captured\n";
        return;
    }
    while(left < right){
        long pivot = (left+right)/2;
        if(valid_potion(one,two, D,T,power[pivot]))
            right = pivot;
        else 
            left = pivot + 1;
    }
    std::cout << left << "\n";
	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
