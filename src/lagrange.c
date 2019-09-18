#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "interpolazione.h"


//Calcolo della componente prod(x_j - x_i)
double *denominatore(Point *points,int n)
{
    double *den= malloc(n * sizeof(double));
    for(int j=0; j < n; j++)
    {
        den[j]=1;
        for(int i=0;i < n;i++)
        {
            if(i != j)
                den[j]*=(points[j].x-points[i].x);
        }
    }
    return den;
}

double eval_point_lagrange(Point *interp_points, int n, double *den_coeff, double x)
{
    double prod=1;
    double sum=0;
    
    //Produttoria
    for(int i=0;i < n ; i++)
        prod *= (x-interp_points[i].x);
    
    // Sommatoria
    for(int j=0;j < n;j++)
        sum += interp_points[j].y / (den_coeff[j] * (x - interp_points[j].x));
        
    return sum * prod;
}


Point *lagrange(Point *interp_points, int n, double *eval_points,int n_evalpoints)
{
    double *den = denominatore(interp_points,n);
    Point *result = malloc(n_evalpoints * sizeof(Point));
    
    for(int i=0; i < n_evalpoints ; i++)
    {
        result[i].x=eval_points[i];
        result[i].y=eval_point_lagrange(interp_points,n,den,eval_points[i]);
    }
    
    free(den);
    return result;
    
}


