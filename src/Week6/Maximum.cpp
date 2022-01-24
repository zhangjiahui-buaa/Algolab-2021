#include "iostream"
#include "CGAL/QP_functions.h"
#include "CGAL/QP_models.h"
#include "CGAL/Gmpz.h"
typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
long ceil_to_double(const CGAL::Quotient<ET>& x){
    double a = std::ceil(CGAL::to_double(x));
    while(a<x) a++;
    while(a-1>=x) a--;
    return (long)a;
}

void testcase(int p, int a, int b){
    if(p==1){
        Program lp(CGAL::SMALLER, true, 0, false, 0);
        const int X = 0, Y = 1;
        lp.set_a(X,0,1); lp.set_a(Y,0,1); lp.set_b(0,4);
        lp.set_a(X,1,4); lp.set_a(Y,1,2); lp.set_b(1,a*b);
        lp.set_a(X,2,-1); lp.set_a(Y,2,1); lp.set_b(2,1);
        lp.set_c(X,a);lp.set_c(Y,-b);

        Solution s = CGAL::solve_linear_program(lp, ET());
        if(s.is_infeasible()) std::cout << "no\n";
        else if(s.is_unbounded()) std::cout << "unbounded\n";
        else std::cout << -ceil_to_double(s.objective_value()) << "\n";
    }else if(p==2){
        Program lp(CGAL::LARGER, false,0,true, 0);
        const int X = 0, Y = 1, Z =2 ;
        lp.set_a(X,0,1); lp.set_a(Y,0,1); lp.set_b(0,-4);
        lp.set_a(X,1,4); lp.set_a(Y,1,2); lp.set_a(Z,1,1); lp.set_b(1,-a*b);
        lp.set_a(X,2,-1); lp.set_a(Y,2,1); lp.set_b(2,-1);
        lp.set_c(X,a); lp.set_c(Y,b); lp.set_c(Z,1);
        Solution s = CGAL::solve_linear_program(lp, ET());
        if(s.is_infeasible()) std::cout << "no\n";
        else if(s.is_unbounded()) std::cout << "unbounded\n";
        else std::cout << ceil_to_double(s.objective_value()) << "\n";
    }else{
        return;
    }
}

int main(){
    std::cout << std::fixed << std::setprecision(0);
    int a,b,c;std::cin >> a;
    while(a!=0){
        std::cin >> b >> c;
        testcase(a,b,c);
        std::cin >> a;
    }
}