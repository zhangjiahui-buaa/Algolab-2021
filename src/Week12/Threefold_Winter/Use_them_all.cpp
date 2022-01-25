#include "CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h"
#include "CGAL/Delaunay_triangulation_2.h"
#include "vector"
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;

void testcase() {
    int n;std::cin >> n;
    std::vector<K::Point_2> pts;
    for(int i=0; i<n; i++){
        int x,y;std::cin >>x >> y;
        pts.push_back(K::Point_2(x,y));
    }
    Triangulation t;
    t.insert(pts.begin(), pts.end());
    K::FT result = LONG_MAX;
    for(auto e = t.finite_edges_begin(); e!=t.finite_edges_end(); e++){
        result = std::min(result, t.segment(e).squared_length());
    }
    std::cout << std::floor(CGAL::to_double(CGAL::sqrt(result/4))) << "\n";
	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
