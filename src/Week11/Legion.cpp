#include "CGAL/QP_functions.h"
#include "CGAL/QP_models.h"
#include "CGAL/Gmpz.h"
#include "iostream"

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
void testcase() {
    long x,y,n;std::cin >> x >> y >> n;
    Program lp(CGAL::SMALLER, false, 0, false, 0);
    const int X = 0, Y = 1, Z = 2;
    int cons = 0;
    for(int i=0; i<n; i++){
        long a,b,c,v;std::cin >> a >> b >> c >> v;
        long tmp = std::sqrt(a*a+b*b) * v;
        if(a*x + b*y + c >=0){
            lp.set_a(X, cons, -a);
            lp.set_a(Y, cons, -b);
            lp.set_b(cons++, c);
            
            lp.set_a(X, cons, -a);
            lp.set_a(Y, cons, -b);
            lp.set_a(Z, cons, tmp);
            lp.set_b(cons++, c);
        }else{
            lp.set_a(X, cons, a);
            lp.set_a(Y, cons, b);
            lp.set_b(cons++, -c);
            
            lp.set_a(X, cons, a);
            lp.set_a(Y, cons, b);
            lp.set_a(Z, cons, tmp);
            lp.set_b(cons++, -c);
        }
    }
    lp.set_c(Z,-1);
    Solution s = CGAL::solve_linear_program(lp, ET());
    std::cout << std::floor(-CGAL::to_double(s.objective_value())) << "\n";
	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}