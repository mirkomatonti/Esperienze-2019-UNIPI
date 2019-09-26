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

void test(int a,int b,int n,int nxi)
{

    Point *equi_points =gen_point(rounge,a,b,n);
    Point *chb_points =chebyshev(rounge,a,b,n);
    double *int_vande = vandermonde(equi_points,n);
    
    fprintf(stdout,"Coefficienti ottenuti:\n");
    for(int i=0;i<n;i++)
    {
        if(int_vande[i] >= 0 )
            printf("+%.10fx^%d ",int_vande[i],i);
        else
            printf("%.10fx^%d ",int_vande[i],i);
    }
    fprintf(stdout,"\n");    
    double *xi = linspace(-5,5,nxi);
    Point *int_newton = newton(equi_points,n,xi,nxi);
    Point *int_lag = lagrange(equi_points,n,xi,nxi);
    Point *int_lag_cheb = lagrange(chb_points,n,xi,nxi);
    Point *int_spline = spline(equi_points,n,xi,nxi);

    fprintf(stdout,"Plot delle funzioni in formato .png\n");
    

    
    char newton_string[50];
    sprintf(newton_string,"Newton-%d nodi",n);
    char lagrange_string[50];
    sprintf(lagrange_string,"Lagrange-%d nodi",n);
    char lagrange_cheb_string[50];
    sprintf(lagrange_cheb_string,"Lagrange-Cheb-%d nodi",n);
    char spline_string[50];
    sprintf(spline_string,"Spline-%d nodi",n);
    
    plot(newton_string,int_newton,nxi);
    plot(lagrange_string,int_lag,nxi);
    plot(lagrange_cheb_string,int_lag_cheb,nxi);
    plot(spline_string,int_spline,nxi);
    
    
    //pulizia
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
    test(-5,5,5,100);
    test(-5,5,11,100);
    test(-5,5,15,100);

    return 0;
} 