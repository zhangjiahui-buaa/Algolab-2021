///4
#include "CGAL/QP_functions.h"
#include "CGAL/QP_models.h"
#include "iostream"
#include "vector"
#include "CGAL/Gmpz.h"
typedef long IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
struct pt{
    int x;
    int y;
};
void testcase() {
    long n,m,h,w;std::cin >> n >> m >> h >> w;
    std::vector<pt> new_pts;
    for(int i=0; i<n; i++){
        int x,y;std::cin >> x >> y;
        new_pts.push_back({x,y});
    }
    std::vector<pt> old_pts;
    for(int i=0; i<m; i++){
        int x,y;std::cin >> x >> y;
        old_pts.push_back({x,y});
    }
    Program lp(CGAL::SMALLER, true, 1, false, 0);
    int cons = 0;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            int dx = std::abs(new_pts[i].x - new_pts[j].x);
            int dy = std::abs(new_pts[i].y - new_pts[j].y);
            lp.set_a(i, cons, w*h);
            lp.set_a(j, cons, w*h);
            lp.set_b(cons++, std::max(2*h*dx, 2*w*dy));
        }
    }
    for(int i=0; i<n; i++){
        long limit = LONG_MAX;
        for(int j=0; j<m; j++){
            int dx = std::abs(new_pts[i].x - old_pts[j].x);
            int dy = std::abs(new_pts[i].y - old_pts[j].y);
            limit = std::min(limit, std::max(2*h*dx, 2*w*dy) - h*w);
        }
        lp.set_a(i, cons, h*w);
        lp.set_b(cons++, limit);
        lp.set_c(i, -2*w-2*h);
    }

    Solution s = CGAL::solve_linear_program(lp, ET());
    std::cout << std::ceil(CGAL::to_double(-s.objective_value())) << "\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout << std::fixed << std::setprecision(0);
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}