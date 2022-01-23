#include "CGAL/Quadratic_functions.h"
#include "CGAL/Quadratic_models.h"
#include "CGAL/Gmpz.h"
#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

struct ware_type{
    int x;
    int y;
    int supply;
    int alco;
    int contour_num;
    int closest_contour;
};
struct stad_type{
    int x;
    int y;
    int demand;
    int upper;
    int contour_num;
    int closest_contour;
};
struct contour_type{
    int x;
    int y;
    int r;
};
void testcase() {
    int n,m,c; std::cin >> n >> m >> c;
    Program lp(CGAL::SMALLER, true, 0, false, 0);
    std::vector<ware_type> warehouse;
    int cons = 0;
    for(int i=0; i<n; i++){
        int x,y,s,a;std::cin >> x >> y >> s >> a;
        warehouse.emplace_back({x,y,s,a,0,-1});
        for(int j=0; j<m; j++){
            lp.set_a(i*m+j, cons, 1);
        }
        lp.set_b(cons++, s);
    }
    std::vector<stad_type> stadium;
    for(int i=0; i<m; i++){
        int x,y,d,u;std::cin >> x >> y >> d >> u;
        stadium.emplace_back({x,y,d,u,0,-1});
        for(int j=0; j<n; j++){
            lp.set_a(j*m+i, cons, 1);
        }
        lp.set_b(cons++, d);
        for(int j=0; j<n; j++){
            lp.set_a(j*m+i, cons, -1);
        }
        lp.set_b(cons++, -d);
        for(int j=0; j<n; j++){
            lp.set_a(j*m+i, cons, warehouse[j].alco);
        }
        lp.set_b(cons++, u);
    }
    std::vector<std::vector<int>> rev(n);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            int w;std::cin >> w;
            rev[i].push_back(w);
        }
    }
    std::vector<contour_type> contour;
    for(int i=0; i<c; i++){
        int x,y,r;std::cin >> x >> y >> r;
        contour.emplace_back({x,y,r});
        for(int j=0; j<n; j++){
            long dis = CGAL::squared_distance(Point(x,y), Point(warehouse[j].x, warehouse[j].y)); 
            if(dis < (long)r*(long)r){
                warehouse[j].contour_num++;
                int tmp = warehouse[j].closest_contour; 
                if(tmp == -1 || (r < contour[tmp].r && CGAL::squared_distance(Point(x,y), Point(contour[tmp].x, contour[tmp].y)) < (long)contour[tmp].r * (long)contour[tmp].r))
                    warehouse[j].cloest_contour = i;
            }
        }
        for(int j=0; j<m; j++){
            long dis = CGAL::squared_distance(Point(x,y), Point(stadium[j].x, stadium[j].y)); 
            if(dis < (long)r*(long)r){
                stadium[j].contour_num++;
                int tmp = stadium[j].closest_contour; 
                if(tmp == -1 || (r < contour[tmp].r && CGAL::squared_distance(Point(x,y), Point(contour[tmp].x, contour[tmp].y)) < (long)contour[tmp].r * (long)contour[tmp].r))
                    stadium[j].cloest_contour = i;
            }
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            long dis = CGAL::squared_distance(Point(contour[warehouse[i]].x, contour[warehouse[i]].y), Point(contour[stadium[j]].x, contour[stadium[j]].y));
            long r1 = contour[warehouse[i]].r;
            long r2 = contour[stadium[j]].r;
            int num;
            if(dis >= (r1+r2)*(r1+r2)){
                num = warehouse[i].contour_num + stadium[j].contour_num;
            }else{
                num = std::max(warehouse[i].contour_num, stadium[j].contour_num) - std::min(warehouse[i].contour_num, stadium[j].contour_num);
            }
            lp.set_c(i*m+j, num - 100*rev[i][j]);
        }
    }
    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_infeasible()) std::cout << "RIOT!\n";
    else std::cout << std::floor(-CGAL::to_double(s.objective_value())/100) << "\n";

	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
