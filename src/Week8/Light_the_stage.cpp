#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "CGAL/Delaunay_triangulation_2.h"
#include "iostream"
#include "vector"
#include "climits"
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;

void testcase() {
    int m,n;std::cin >> m >> n;
    std::vector<std::pair<Point, long>> people;
    std::vector<Point> pts;
    for(int i=0; i<m; i++){
        int x,y;
        long r;
        std::cin >> x >> y >> r;
        people.emplace_back(std::make_pair(Point(x,y), r));
    }
    long h;std::cin >> h;
    for(int i=0; i<n; i++){
        int x,y;std::cin >> x >>y;
        pts.emplace_back(Point(x,y));
    }
    Triangulation t;
    t.insert(pts.begin(), pts.end());
    std::vector<int> result;
    for(int i=0; i<m; i++){
        Point pt = t.nearest_vertex(people[i].first)->point();
        if(CGAL::squared_distance(people[i].first, pt) >= (people[i].second+h)*(people[i].second+h))
            result.push_back(i);
    }
    if(result.empty()){
        int last_lamp = -1;
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                if(CGAL::squared_distance(pts[j], people[i].first) < (people[i].second+h)*(people[i].second+h)){
                    if(j==last_lamp){
                        result.push_back(i);
                    }else if(j>last_lamp){
                        result.clear();
                        result.push_back(i);
                        last_lamp = j;
                    }
                    break;
                }
            }
        }
    }
    std::sort(result.begin(), result.end());
    for(int i: result)
        std::cout << i << " ";
    std::cout << "\n";
	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
