#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "interpolazione.h"

//Funzione generatrice di punti (x0,fun(x0))...(x_n-1,fun(x_n-1))
Point *gen_point(double (*fun)(double),int a,int b, int n)
{
  
    Point *points =malloc(n * sizeof(Point));
    
    for(int i=0;i<n;i++)
     {
      points[i].x= (a + (((double)(i) * (double)(b-a)) / (n-1)));
      points[i].y=fun(points[i].x);
     }
     
     return points;
    
}

//Funzione generatrice di n punti compresi nell'intervallo [a,bs]
double *linspace(int a,int b, int n)
{

    double *x =malloc(n * sizeof(Point));
    
    for(int i=0;i<n;i++)
     {
      x[i]= (a + (((double)(i) * (double)(b-a)) / (n-1)));
     }
     
    return x;
    
}

