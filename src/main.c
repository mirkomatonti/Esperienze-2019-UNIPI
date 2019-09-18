#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //api posix   
#include <sys/types.h> 
#include <sys/stat.h> 
#include "math.h"
#include "interpolazione.h" 



double rounge(double x)
{
  return (1/(1+(x*x)));
}


void plot(char *name,Point *points,int n)
{
      
    mkdir("plot", 0777);
    FILE *f = popen("gnuplot", "w");

    fprintf(f,
    "set term png; "
    "set output 'plot/%s.png'\n"
    "set style line 1 lt 1 lw 6 \n"
    "set xlabel 'x' \n"
    "set ylabel 'y'\n"
    "set border 3 \n"
    "set xtics nomirror \n"
    "set ytics nomirror \n"
    "plot 1/(1+x**2) lt rgb 'red'  , '-' lt rgb 'blue'  title '%s' w linespoint \n",name,name);



    for (int i=0; i< n; i++)
      fprintf(f, "%g %g\n", points[i].x, points[i].y);
    
    fclose(f);
    
}


void test1()
{
    int a= -5; int b= 5;
    int n= 5; int nxi=100;
    
    
    Point *equi_points =gen_point(rounge,a,b,n);
    
    double *int_vande = vandermonde(equi_points,n);
    
    printf("Coefficienti ottenuti:\n");
    for(int i=0;i<n;i++)
    {
        if(int_vande[i] >= 0 )
            printf("+%.10fx^%d ",int_vande[i],i);
        else
            printf("%.10fx^%d ",int_vande[i],i);
    }
    
    double *xi = linspace(-5,5,nxi);
    double *int_newton = newton(equi_points,n);
    Point *int_lag = lagrange(equi_points,n,xi,nxi);
    Point *int_spline = spline(equi_points,n,xi,nxi);
    
    plot("lagrange-equi-5",int_lag,nxi);
    plot("spline-5",int_spline,nxi);
    
    free(equi_points);
    free(int_vande);
    free(xi);
    free(int_newton);
    free(int_lag);
    free(int_spline);
    
}
void test(int a,int b,int n,int nxi)
{

    Point *equi_points =gen_point(rounge,a,b,n);
    Point *chb_points =chebyshev(rounge,a,b,n);
    double *int_vande = vandermonde(equi_points,n);
    
    printf("Coefficienti ottenuti:\n");
    for(int i=0;i<n;i++)
    {
        if(int_vande[i] >= 0 )
            printf("+%.10fx^%d ",int_vande[i],i);
        else
            printf("%.10fx^%d ",int_vande[i],i);
    }
    
    double *xi = linspace(-5,5,nxi);
    double *int_newton = eval_point_newton(equi_points,n,xi,nxi);
    Point *int_lag = lagrange(equi_points,n,xi,nxi);
    Point *int_lag_cheb = lagrange(chb_points,n,xi,nxi);
    Point *int_spline = spline(equi_points,n,xi,nxi);
    

    plot("newton",int_newton,nxi);
    plot("lagrange",int_lag,nxi);
    plot("lagrange-cheb",int_lag_cheb,nxi);
    plot("spline",int_spline,nxi);
    
    
    free(equi_points);
    free(chb_points);
    free(int_vande);
    free(xi);
    free(int_newton);
    free(int_lag);
    free(int_lag_cheb);
    free(int_spline);
    
    
}

int main()
{
    
    test(-5,5,15,100);
    /*
    int a= -5;
    int b= 5;
    int n= 11;
    
    Point *equi_points =gen_point(rounge,a,b,n);
    Point *chb_points =chebyshev(rounge,a,b,n);
    
      

    double *inter1 = newton(equi_points,n);
    double *inter2 = vandermonde(equi_points,n);
    
    
    for(int i=0;i<n;i++)
    {
        if(inter1[i] >= 0 )
            printf("+%.10fx^%d ",inter1[i],i);
        else
            printf("%.10fx^%d ",inter1[i],i);
    }
    
    
    printf("\n");
    for(int i=0;i<n;i++)
    {
        if(inter1[i] > 0 )
            printf("+%.10fx^%d ",inter2[i],i);
        else
            printf("%.10fx^%d ",inter2[i],i);
    }


    double *xi = linspace(-5,5,100);
   // Point *res = lagrange(equi_points,n,xi,100);
 //   plot("laxg",res,100);
    
    

    Point *res2 = spline(equi_points,n,xi,100);
    plot("spline3",res2,100);
    */
    return 0;
} 