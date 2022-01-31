#include "iostream"
#include "vector"
#include "map"
#include "climits"
void testcase(){
	int N,M;std::cin >> N >> M;
	std::vector<int> target(M);
	for(int i=0; i<M; i++)
		std::cin >> target[i];
	std::vector<std::vector<int>> mat(N, std::vector<int>(2*M));
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			std::cin >> mat[i][2*j] >> mat[i][2*j+1];
		}
	}
	std::map<std::vector<int>, int> memo;
	for(int i=0; i< 1 << (N/2); i++){
		std::vector<int> room(M, 0);
		int num = 0;
		for(int j=0; j<N/2; j++){
			bool flip = 1<< j & i;
			if(flip) num++;
			for(int k=0; k<M; k++){
				room[k] += flip ? mat[j][2*k+1] : mat[j][2*k];
			}
		}

		if(memo.find(room) == memo.end())
			memo.insert({room, num});
		else
			memo[room] = std::min(memo[room], num);
	}
	int result = INT_MAX;
	for(int i=0; i< 1<< (N-N/2); i++){
		std::vector<int> rest(target);
		int num = 0;
		for(int j=0; j<N-N/2; j++){
			bool flip = 1<< j & i;
			if(flip) num++;
			for(int k=0; k<M; k++)
				rest[k] -= flip ? mat[j+N/2][2*k+1] : mat[j+N/2][2*k];
		}
		if(memo.find(rest)!=memo.end()){
			result = std::min(result, num + memo[rest]);
		}
	}
	if(result==INT_MAX)
		std::cout << "impossible\n";
	else std::cout << result;
}
int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}