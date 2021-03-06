//celestial model
//fraction of day, relative frequency --->(resetting strength, period)

#include <stdio.h>
#include <math.h>


int main(void){
  
  //def external force
  double fxa(double l,double xa,double xex){
    return  -1.0 *  l *cos((xex/2.0)-M_PI/4.0)* sin(xa - xex);
  }
  
  int step,k,i,j,maxstep=10000;
  double p,a,T,T0,T1,l,t, xa, xa0, va, va0, xex, kxa1, kxa2, kxa3, kxa4, dt = 1.0/400.0;

  //loop for fraction of day
  for(i=0;i<=100;i++){
    
    p=0.010*i;

    //loop for relative frequency
    for(j=0;j<=5;j++){
      
      a=1.0+0.10*j;

      //open file
      FILE *fp;      
      char filename[100];      
      sprintf(filename,"p%lfsura%lf.txt",p,a);      
      fp = fopen(filename,"w");
      
      xa =  M_PI*(2.0/3.0);
      va =  2.0*M_PI*(a);
      xex = 0.0;

      //loop for resetting strength
      for(k=0; k<=400; k++){
	
	T=0.0;
	T0=0.0;
	T1=0.0;
	
	l=0.050*k;

	//time development
	for(step=0; step<maxstep; step++){
	  
	  xa0 = xa;
	  
	  t=dt*step;
	  
	  if(fmod(t,1.0)<=p){
	    
	    xex  = M_PI/2.0;
	    
	  }else{
	    
	    xex  =3.0* M_PI/2.0;
	    
	  }

	  //RungeKutta
	  kxa1 =   fxa(l,xa,xex)*dt;
	  kxa2 =   fxa(l,xa + kxa1/2,xex)*dt;
	  kxa3 =   fxa(l,xa + kxa2/2,xex)*dt;
	  kxa4 =   fxa(l,xa + kxa3,xex)*dt;
	  xa =    xa + (kxa1 + 2*kxa2 + 2*kxa3 + kxa4)/6 + va*dt;
	  
	  if(sin(xa)*sin(xa0)<=0.0){
	    
	    
	    
	    T1=T0;
	    
	    T0=T;
	    
	    T=step*dt;
	    
	    if(T>5.0){
	      
	      fprintf(fp,"%lf %lf %lf %lf \n",l ,step*dt, T, T-T1);
	      
	    }
	    
	  }
	  
	}
	
      }
    }
  }
}
