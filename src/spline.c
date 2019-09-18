#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "interpolazione.h"

Point *spline(Point *interp_points,int n,double *eval_points,int n_evalpoints)
{

    double h[n],l[n],z[n],u[n],A[n],c[n],b[n],d[n];
    

    for(int i= 0; i < n-1;i++)
         h[i] = interp_points[i + 1].x - interp_points[i].x;
    
    
    
    for(int i= 1;i < n - 1;i++)
        A[i]=(3/h[i]) * (interp_points[i+1].y - interp_points[i].y ) - (3/h[i-1]) * (interp_points[i].y - interp_points[i-1].y );
     
      
    l[0]=1;  
    u[0]=0;
    z[0]=0;
    
 
    for (int i = 1; i < n - 1; ++i) {
        l[i] = 2 * (interp_points[i + 1].x - interp_points[i - 1].x) - h[i - 1] * u[i - 1];
        u[i] = h[i] / l[i];
        z[i] = (A[i] - h[i - 1] * z[i - 1]) / l[i];
    }
     
    
    
    l[n]=1;  
    z[n]=0;
    c[n]=0;
    

    for (int j = n - 2; j >= 0; --j) {
        c[j] = z[j] - u[j] * c[j + 1];
        b[j] = (interp_points[j + 1].y - interp_points[j].y) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
        d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
    }

    Point *result = malloc(n_evalpoints * sizeof(Point));
    for(int i=0; i < n_evalpoints; i++)
    {
        for(int j=1; j < n;j++)
        {
        
            if( interp_points[j].x >= eval_points[i])
            {
                result[i].x=eval_points[i];
                result[i].y=(interp_points[j-1].y + b[j-1]*(eval_points[i] - interp_points[j-1].x) + c[j-1] * pow((eval_points[i]-interp_points[j-1].x),2) \
                + d[j-1] * pow((eval_points[i]-interp_points[j-1].x),3));
                break;
                
            }
       
        }
        
    }
    
    return result;
}


