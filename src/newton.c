#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "interpolazione.h"


double product(Point *p, int i, int j)
{
    double res=1;
    for (int k=0;k < j; k++)
    {
        res=res * (p[i].x - p[k].x);
    }
    return res;
}


double *newton(Point *points, int n)
{
    //output
    double *coeffpolinomio= malloc(n * sizeof(double));
    
    //matrice A - Newton
    double **a= (double **) malloc(n*sizeof(double *));

    //Allocazione in memoria & prima riga 
    for (int i=0; i < n;i++)
    {
        a[i] = (double *) malloc((n+1)*sizeof(double));
        a[i][0] = 1;
    }
    
    //Costruzione matrice
    for (int i=0; i < n ;i++)
    {
        int j;
        for (j=1; j < i+1 ;j++)
        {
            
            a[i][j] =product(points,i,j);
        }
        a[i][n] = points[i].y;
    }
    
    //Stampa matrice  
    printf("Matrice\n");
    for(int i=0;i<n;i++)
    {
        int j;
        for(j=0;j<i+1;j++)
           {
               printf("%lf ",a[i][j]);
           }
            printf("|%lf ",a[i][n]);
            printf("\n");
    }
    

    //risolvo sistema triangolare
    for(int i = 0 ; i < n; i++)
    {
        coeffpolinomio[i]=a[i][n] / a[i][i];
        for(int k = i + 1;k<n;k++)
        {
            a[k][n] -= a[k][i] * coeffpolinomio[i];
        }
    }
    
    return coeffpolinomio;
    
}


//Calcolo della componente prod(x_j - x_i)
double *prod(Point *points,int n,double x)
{
    double *den= malloc(n * sizeof(double));
    for(int j=1; j < n; j++)
    {
        den[j]=1;
        for(int i=0;i < j;i++)
                den[j]*=(x-points[i].x);
        
    }
    return den;
}


double eval(Point *interp_points,int n,double x,double * coeffpolinomio)
{
    double *coeff = prod(interp_points,n,x);
    double sum = coeffpolinomio[0];
    for (int i=0 ;i< n;i++)
        sum+=coeffpolinomio[i] *coeff[i];
    
    free(coeff);
    return sum;
}

Point *eval_point_newton(Point *interp_points, int n, double *eval_points,int n_evalpoints)
{
    double *coeffpolinomio = newton(interp_points,n);
    Point *result = malloc(n_evalpoints * sizeof(Point));
    for(int i=0; i < n_evalpoints; i++)
    {
        result[i].x = eval_points[i];
        result[i].y = eval(interp_points,n,eval_points[i],coeffpolinomio);
        
    }
    
    free(coeffpolinomio);
    return result;
}
