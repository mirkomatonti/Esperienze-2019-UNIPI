#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "interpolazione.h"


//Generatore di nodi di Chebyshev
Point *chebyshev(double (*fun)(double),int a, int b, int n)
{
    Point *points =malloc(n * sizeof(Point));
    
    double alpha=(b-a)/2;
    double beta = (a+b)/2;
    
    for(int i=0; i < n;i++)
    {
        points[i].x = (beta-alpha*cos((2*(i)+1)*M_PI/(2*n)));
        points[i].y=fun(points[i].x);
    }
    return points;
}