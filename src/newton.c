#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "interpolazione.h"



double ** divided_difference(Point * interp_points,int n)
{
    double **mdd= (double **) malloc(n*sizeof(double *));
   
    //set prima colonna f(x0),f(x1).....f(xn-1)
    for (int i=0; i < n;i++)
    {
        mdd[i] = (double *) malloc((n+1)*sizeof(double));
        mdd[i][0]=interp_points[i].y;
    }
    
    //matrice delle differenze divise
    for(int j=1; j < n;j++)
        for (int k = 1;k <= j; k++)
            mdd[j][k]= ((mdd[j][k-1] -  mdd[j-1][k-1]) / (interp_points[j].x -interp_points[j-k].x));
        
   return mdd;
}


//Valutazione polinomio in x con metodo di Horner
double eval_point_newton(Point * interp_points,int n,double ** mdd,double x)
{
    double result = mdd[n-1][n-1];  
  
    for (int i=n-2; i>=0; i--) 
        result = (result*(x - interp_points[i].x) + mdd[i][i]); 
  
    return result;
}



Point *newton(Point *interp_points, int n, double *eval_points,int n_evalpoints)
{
    double **mdd = divided_difference(interp_points,n);
    Point *result = malloc(n_evalpoints * sizeof(Point));
    for(int i=0; i < n_evalpoints; i++)
    {
        result[i].x = eval_points[i];
        result[i].y = eval_point_newton(interp_points,n,mdd,eval_points[i]);
        
    }
    
    //pulizia
    for (int i=0; i < n;i++)
    {
        free(mdd[i]);
    }
    free(mdd);
    return result;
}