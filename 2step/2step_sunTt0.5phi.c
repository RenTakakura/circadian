//2step
//FRP ---> (resetting strength, period)

#include <stdio.h>
#include <math.h>

//def function
  double fxa(double l,double xa,double xex){
  return  -1.0*  l *sin(xa - xex);
  }

int main(void){

  

  //def variables  
  int k, i, j, step, maxstep =8000;
  double p,a,T,T0,T1,l,t, xa, xa0, va, va0, xex, kxa1, kxa2, kxa3, kxa4, dt = 1.0/500.0;

  //def fraction of day
  p=0.50;

  //loop for FRP
  for(i=12;i<=12;i++){

    a= i*1.0/24.0;

    //open file
    FILE *fp;
    char filename[100];
    sprintf(filename,"sunT%dt0.5phi.txt",i);
    fp = fopen(filename,"w");

    
    
    //initialize
    xa =  M_PI*(2.0/3.0);
    va =  2.0*M_PI*(a);
    xex = 0.0;

    //loop for resetting strength
    for(k=0; k<=2000; k++){
      
      T=0.0;
      T0=0.0;
      T1=0.0;
      
      l=0.010*k;

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
	
	if(((step-1)*dt-0.5)*(step*dt-0.5)<=0.0){
	  
        
	  
	  T1=T0;

	  T0=T;
	  
	  T=step*dt;
	  
	  if(T>6.0){
	    
	    fprintf(fp,"%lf %lf\n",l,sin(xa));
	    
	  }
	  
	}

      }
      
    }
    
  }
}
