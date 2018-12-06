//unbalance model
//relative frequency(=const), fraction of day, resetting strength---> phase

#include <stdio.h>

#include <math.h>

#define l     -1.89000

//def external force
double fxa(double xa,double xex){
  return    l * sin(xa - xex);
}


int main(void){
  
  
  int step, maxstep =480000;
  double T, T0, xa, xa0, va, va0, vex0, xex0, xex, vex, kxa1, kxa2, kxa3, kxa4, t, p = 0.550, dt = 5.0/8640.0;

  //open file
  FILE *fp;
  char filename[100];
  sprintf(filename,"p%lfw1.3.txt",p);  
  fp = fopen(filename,"w");

  //initialize
  xa =  M_PI*(1.0/3.0);
  va =  2.0*M_PI*(1.30);
  xex = 0.0;
  
  
  //time development
  for(step=0; step<maxstep; step++){
    
    xa0 = xa;
    
    xex0 = xex;
    
    t=tan(M_PI*(1.0-p));
    
    xex=2*atan(1.0/sqrt(1.0+t*t)-sqrt(t*t/(1.0+t*t))/tan(M_PI*(dt*step-p)));
    
    //RungeKutta
    kxa1 =   fxa(xa,xex)*dt;
    kxa2 =   fxa(xa + kxa1/2,xex)*dt;
    kxa3 =   fxa(xa + kxa2/2,xex)*dt;
    kxa4 =   fxa(xa + kxa3,xex)*dt;
    xa =    xa + (kxa1 + 2*kxa2 + 2*kxa3 + kxa4)/6 + va*dt;
    
    va0  =   (xa - xa0 )/dt;
    
    vex0 =   (xex - xex0)/dt;
    
    if(step>320000){
      
      fprintf(fp,"%lf %lf %lf %lf %lf\n", step*dt,sin(xex),sin(xa),va0 - vex0,sin(xa-xex));
      
    }
    
    
    
    
    
  }
  
}
