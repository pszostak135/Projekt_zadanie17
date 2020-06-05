#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "winbgi2.h"
#include "rk4.h"

double g=9.81;

void rhs_fun(double t, double *X, double *F,double p, double a, double b)
{
	F[0]= X[1];
	F[1]= -p*b/2*b-p*X[1]*X[1]/2-p*b*X[1]-p*a*X[1]*X[2]-p/2*a*a*X[2]*X[2]+p*a*b*X[2];
	F[2]= X[3];
	F[3]= -g-p*X[3]*abs(X[3])/2;
}

void main()
{
	double h=0.01,a,b,gest=1.2,C,S,m;
	double X[4];
	double X1[4];
	X[0]=0; //x0
	X[1]=0; //vx0
	X[2]=0; //y0
	
    printf("Podaj predkosc poczatkowa [m/s]:");
	scanf("%lf", &X[3]);
    printf("\n mase kulki [kg]: ");
	scanf("%lf", &m);
	printf("\n ppowierzchnie odniesienia [m^2]: ");
	scanf("%lf", &S);
	printf("\n wspolczynnik oporu powietrza: ");
	scanf("%lf", &C);
	printf("\n stale a i b ze wzoru v=ay+b (a>0, b>0) opisujacego rozklad predkosci wiatru \n a= ");
	scanf("%lf", &a);
	printf("\n b= ");
    scanf("%lf", &b);   

	double p=gest*S*C/m; //p to parametr ³¹czacy kilka sta³ych upraszczaj¹cy zapis
	
	graphics(800,800);
	scale(0,-12,2,12);
	X1[2]=0; //do warunku zakoñczenia pêtli 

		for(double i=0;X1[2]>=0;i+=h)
	{
		vrk4(0,X, h, 4, rhs_fun, X1,p,a,b);
		X[0]=X1[0];
		X[1]=X1[1];
		X[2]=X1[2];
		X[3]=X1[3];
				
		//point(X1[0],X1[2]);// wykres trajektorii y(x)
		//point(i,X1[0]); // x(t)
		//point(i,X1[1]); // vx(t)
		//point(i,X1[2]); // y(t)
		point(i,X1[3]); //vy(t)
		//printf( "%.2lf\t  %.2lf\n ",  i,X1[3] );
	}
		
	wait();
}