
#include "tinyexpr.h"
#include <stdio.h>
#include <math.h>
double solution(te_expr *n, double *x, double a, double b, double e){
    *x = a;
    double f_a = te_eval(n);
    *x = b;
    double f_b = te_eval(n);
    int step = 1;
	 /* Inputs */
	 /* Calculating Functional Value */
 	double f0, f1, f2, c;
	f0 = f_a;
	f1 = f_b;
	 /* Checking whether given guesses brackets the root or not. */
	 if( f0 * f1 > 0.0)
	 {
		  printf("Incorrect Initial Guesses.\n");
		  return 0;
	 }
   /* Implementing Bisection Method */
    printf("\nStep\t\ta\t\tb\t\tc\t\tf(c)\n");
	 do
	 {
		  c = (a + b)/2;
		  *x = c;
		  double f_c = te_eval(n);
          f2 = f_c;
		  printf("%d\t\t%f\t%f\t%f\t%f\n",step, a, b, c, f2);
		  if( f0 * f2 < 0.0)
		  {
			   b = c;
			   f1 = f2;
		  }
		  else
		  {
			   a = c;
			   f0 = f2;
		  }
		  step = step + 1;
	 }
	 while(fabs(a-b)/2>e);
	 c = (a + b)/2;
	 printf("%d\t\t%f\t%f\t%f\n",step, a, b, c);
	 printf("\nRoot is: %f", c);
	 getch();
}
int main()
{
    char equation[50];
	printf("Please enter your equation\n");
	scanf("%s",equation);
	double a, b, e;
	printf("Enter the input value of the interval(a,b)\n");
	printf("Please enter a, b\n");
	scanf("%lf %lf",&a,&b);
	printf("Please enter tolerence\n");
	scanf("%lf",&e);


	double x;
	te_variable vars[] = {"x", &x};
	int err;
    te_expr *n = te_compile(equation, vars, 1, &err);
    if ( n) {
		/* The variables can be changed here, and eval can be called as many
	     * times as you like. This is fairly efficient because the parsing has
	     * already been done. */
	     solution(n, &x, a, b, e);
	     te_free(n);
        }
    else {
	    /* Show the user where the error is at. */
		printf("\t%*s^\nError near here", err-1, "");
        }





 return 0;
}
