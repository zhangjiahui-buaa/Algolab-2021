#include "CGAL/QP_functions.h"
#include "CGAL/QP_models.h"
#include "CGAL/Gmpz.h"
#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "CGAL/Delaunay_triangulation_2.h"
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
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
    std::vector<Point> pts;
    int cons = 0;
    for(int i=0; i<n; i++){
        int x,y,s,a;std::cin >> x >> y >> s >> a;
        warehouse.push_back({x,y,s,a,0,-1});
        pts.push_back(Point(x,y));
        for(int j=0; j<m; j++){
            lp.set_a(i*m+j, cons, 1);
        }
        lp.set_b(cons++, s);
    }
    std::vector<stad_type> stadium;
    for(int i=0; i<m; i++){
        int x,y,d,u;std::cin >> x >> y >> d >> u;
        stadium.push_back({x,y,d,u,0,-1});
        pts.push_back(Point(x,y));
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
        lp.set_b(cons++, 100*u);
    }

    Triangulation t;
    t.insert(pts.begin(), pts.end());
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
        contour.push_back({x,y,r});
    }
    std::vector<contour_type> r_contour;
    for(int i=0; i<c; i++){
        Point con(contour[i].x,contour[i].y);
        Point pt = t.nearest_vertex(con)->point();
        if(CGAL::squared_distance(pt,con) < (long)contour[i].r * (long)contour[i].r)
            r_contour.push_back(contour[i]);
    }
    std::vector<bool> in(r_contour.size(), false);
    std::vector<std::vector<int>> lines(n,std::vector<int>(m,0));
    for(int i=0; i<n; i++){
        for(int j=0;j<r_contour.size(); j++){
            long r = r_contour[j].r;
            Point con(r_contour[j].x, r_contour[j].y);
            Point pt(warehouse[i].x, warehouse[i].y);
            if(CGAL::squared_distance(con,pt) < r*r)
                in[j] = true;
        }

        for(int k=0;k<m;k++){
            std::vector<bool> s_in(r_contour.size(), false);
            for(int j=0;j<r_contour.size(); j++){
                long r = r_contour[j].r;
                Point con(r_contour[j].x, r_contour[j].y);
                Point pt(stadium[k].x, stadium[k].y);
                if(CGAL::squared_distance(con,pt) < r*r)
                    s_in[j] = true;
            }
            for(int j=0;j<in.size();j++){
                if(in[j] != s_in[j])
                lines[i][k]++;
            }
        }

        for(int j=0; j<m; j++){
            lp.set_c(i*m+j, line[i][j]-100*rev[i][j]);
        }
    }
    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_infeasible()) std::cout << "RIOT!\n";
    else std::cout << (int)std::floor(-CGAL::to_double(s.objective_value())/100) << "\n";

	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
