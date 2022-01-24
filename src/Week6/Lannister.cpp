//
// Created by 张佳辉 on 2021/11/3.
//

#include "CGAL/QP_functions.h"
#include "CGAL/QP_models.h"
#include "CGAL/Gmpz.h"
#include "iostream"
#include "vector"

typedef long IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> LP;
typedef CGAL::Quadratic_program_solution<ET> Solution;
struct position{
    IT x;
    IT y;
};
typedef std::vector<position> VS;

void testcase(){
    long n,m,s;std::cin >> n >> m >> s;
    VS noble, common;
    for(int i=0; i<n; i++){
        int x,y;std::cin >> x >> y;
        noble.push_back(position({x,y}));
        //std::cout << noble[0].x << noble[0].y;
    }
    for(int i=0; i<m; i++){
        int x,y;std::cin >> x >> y;
        common.push_back(position({x,y}));
    }
    LP lp(CGAL::SMALLER, false,0 , false,0);
    const int P=0, Q=1, K=2, B=3, Z=4;
    int constraint = 0;
    // two canal must cross at a right angle
    lp.set_a(P,0,1); lp.set_a(K, 0, 1); lp.set_b(0, 0);
    lp.set_a(P, 1, -1); lp.set_a(K, 1, -1); lp.set_b(1, 0);
    constraint += 2;
    // cersei's constraint
    for(int i=0; i<n; i++){
        lp.set_a(P, constraint, -noble[i].y); lp.set_a(Q, constraint, -1); lp.set_b(constraint, -noble[i].x);
        constraint++;
    }
    for(int i=0; i<m; i++){
        lp.set_a(P,constraint, common[i].y); lp.set_a(Q, constraint, 1); lp.set_b(constraint, common[i].x);
        constraint++;
    }
    Solution s_cersei = CGAL::solve_linear_program(lp, ET());
    if(s_cersei.is_infeasible()){std::cout << "Yuck!\n"; return;}
    // Tywin's constraint
    if(s != -1){
        IT p_coeff = 0, extra_b = 0;
        for(int i=0; i<n; i++){
            p_coeff += noble[i].y;
            extra_b += noble[i].x;
        }
        for(int i=0; i<m; i++){
            p_coeff -= common[i].y;
            extra_b -= common[i].x;
        }
        lp.set_a(P, constraint, p_coeff); lp.set_a(Q, constraint, n-m); lp.set_b(constraint, s+extra_b);
        constraint++;
        Solution s_tywin = CGAL::solve_linear_program(lp, ET());
        if(s_tywin.is_infeasible()){std::cout << "Bankrupt!\n"; return;}
    }
    // extra procedure to convert into LP
    for(int i=0; i<n; i++){
        lp.set_a(K, constraint, noble[i].x); lp.set_a(B, constraint, 1); lp.set_a(Z, constraint, -1); lp.set_b(constraint,noble[i].y);
        constraint++;
    }
    for(int i=0; i<n; i++){
        lp.set_a(K, constraint, -noble[i].x); lp.set_a(B, constraint, -1); lp.set_a(Z, constraint, -1); lp.set_b(constraint,-noble[i].y);
        constraint++;
    }
    for(int i=0; i<m; i++){
        lp.set_a(K, constraint, common[i].x); lp.set_a(B, constraint, 1); lp.set_a(Z, constraint, -1); lp.set_b(constraint,common[i].y);
        constraint++;
    }
    for(int i=0; i<m; i++){
        lp.set_a(K, constraint, -common[i].x); lp.set_a(B, constraint, -1); lp.set_a(Z, constraint, -1); lp.set_b(constraint,-common[i].y);
        constraint++;
    }
    // objective function
    lp.set_c(Z,1);


    // Solve it!
    Solution solution = CGAL::solve_linear_program(lp, ET());
    std::cout << std::ceil(CGAL::to_double(solution.objective_value())) << "\n";
}
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    int t;std::cin >> t;
    for(int i=0; i<t; i++){
        testcase();
    }
}