#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "interpolazione.h"



double *vandermonde(Point *points, int n)
{
    //output
    double *coeffpolinomio= malloc(n * sizeof(double));
    //matrice A - Vandermonde
    double **a= (double **) malloc(n*sizeof(double *));
    //1 x0 x0^2 .... x0^n
    //. .   .   .... .
    //. .   .   .... .
    //1 xn xn^2 .... xn^n
    
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
        for (j=1; j < n ;j++)
        {
            a[i][j] =pow(points[i].x, (double)j);
        }
        a[i][j] = points[i].y;
    }
    
    for (int i=0;i < n-1;i++)
    {
        //Cerco il massimo in questa colonna
        double maxE=abs(a[i][i]);
        int maxRow= i;
        for (int k=i+1 ; k< n;k++)
        {
            if( abs(a[k][i]) > maxE)
            {
                maxE=abs(a[k][i]);
                maxRow=k;
            }
        }
        
        //scambio la riga massima con la riga corrente
        for(int k=i;k <= n;k++)
        {
            double tmp = a[maxRow] [k];
            a[maxRow][k]=a[i][k];
            a[i][k] =tmp;
        }
        
        //mosse di gauss
        for (int k=i+1; k < n;k++)
        {
            double c = - a[k][i] / a[i][i];
            for (int j=i; j <= n; j++)
            {
                if (i==j)
                    a[k][j] = 0;
                else
                    a[k][j] += c * a[i][j];
            }
        }
        
    
    
      
    }
    
    //risolvo sistema triangolare
    for(int i = n-1 ; i >= 0; i--)
    {
        coeffpolinomio[i]=a[i][n] / a[i][i];
        for(int k = i - 1;k>=0;k--)
        {
            a[k][n] -= a[k][i] * coeffpolinomio[i];
        }
        
    }
    
    //Pulizia
    for (int i=0; i < n;i++)
    {
      free(a[i]);
    }
    free(a);
    
    
    return coeffpolinomio;
    
    

}