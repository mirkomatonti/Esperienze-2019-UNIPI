#ifndef INTERPOLAZIONE_H_
#define INTERPOLAZIONE_H_

#define M_PI 3.14159265358979323846
#define M_E	2.71828182845904523536


typedef struct{
    double x;
    double y;
}Point;


extern double *vandermonde(Point *points, int n);

extern Point *newton(Point *interp_points, int n, double *eval_points,int n_evalpoints);

extern Point *lagrange(Point *interp_points, int n, double *eval_points,int n_evalpoints);

extern Point *spline(Point *interp_points,int n,double *eval_points,int n_evalpoints);

extern Point *chebyshev(double (*fun)(double),int a, int b, int n);

extern Point *gen_point(double (*fun)(double),int a,int b, int n);

extern double *linspace(int a,int b, int n);




#endif /* INTERPOLAZIONE_H_ */