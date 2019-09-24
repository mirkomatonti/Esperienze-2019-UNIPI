#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "interpolazione.h"
//Algoritmo seguito : https://fac.ksu.edu.sa/sites/default/files/numerical_analysis_9th.pdf


//Ricerca binaria modificata per cercare indice
int search_index(Point *lst,double a,double b,double x)
{
    if( b >= a)
    {
        int md = a + (b-a) / 2;
        
        if(lst[md].x == x)
            return md;
        
        if (x < lst[md +1].x && x > lst[md].x)
        {
            return md;
        }
        
        if(x < lst[md].x )
            return search_index(lst,a,md -1,x);
        
        return search_index(lst,md +1,b,x);
    }
}

Point *spline(Point *interp_points,int n,double *eval_points,int n_evalpoints)
{

    double h[n],l[n],z[n],u[n],A[n],c[n],b[n],d[n];
    
    for(int i= 0; i < n-1;i++)
         h[i] = interp_points[i + 1].x - interp_points[i].x;
    
    
    for(int i= 1;i < n - 1;i++)
        A[i]=(3/h[i]) * (interp_points[i+1].y - interp_points[i].y ) - (3/h[i-1]) * (interp_points[i].y - interp_points[i-1].y );
     
    //A[0,0]  
    l[0]=1;
    u[0]=0;
    //b[0]
    z[0]=0;
    
  
    //L non diagonali l[i,i-1] = h[i-1]  
    //l diag l[i,i] = a[i,i] - l[i,i-1] * u[i-1,i]  
    //u[i,i+1] = a[i,i+1] / l[i,i]  
    
    
    //Lz=b
    for (int i = 1; i < n - 1; ++i) {
        l[i] = 2 * (interp_points[i + 1].x - interp_points[i - 1].x) - h[i - 1] * u[i - 1];
        u[i] = h[i] / l[i];
        z[i] = (A[i] - h[i - 1] * z[i - 1]) / l[i];
    }
     
    z[n-1]=0;
    c[n-1]=0;
    
    // Uc = z e calcolo coeff b,d
    for (int j = n - 2; j >= 0; --j) {
        c[j] = z[j] - u[j] * c[j + 1];
        b[j] = ((interp_points[j + 1].y - interp_points[j].y) / h[j]) - (h[j] * (c[j + 1] + 2 * c[j]) / 3);
        d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
    }
    
    
    //Valutazione punti
    Point *result = malloc(n_evalpoints * sizeof(Point));
    for(int i=0; i < n_evalpoints; i++)
    {
        int k = search_index(interp_points,0,n-1,eval_points[i]);
        result[i].x=eval_points[i];
        result[i].y =(interp_points[k].y + b[k]*(eval_points[i] - interp_points[k].x) + c[k] * pow((eval_points[i]-interp_points[k].x),2) \
                + d[k] * pow((eval_points[i]-interp_points[k].x),3));
        
    }
    
    return result;
}



