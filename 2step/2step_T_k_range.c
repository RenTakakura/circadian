//2step model
//fraction of day ---> range of entrainment (FRP,t) 

#include <stdio.h>
#include <math.h>


int main(void){
  
  //def external force
  double fxa(double l,double xa,double xex){
    return  -1.0*  l *sin(xa - xex);
  }
  
  int step,k,i,j,maxstep =16000;
  double p,a,T,T0,T1,T2,T3,l,t, xa, xa0, va, va0, xex, kxa1, kxa2, kxa3, kxa4,dt = 1.0/500.0;

  
  //loop for fraction of day
  for(j=0;j<=10;j++){
    
    p=0.50+j*0.050;

    //open file
    FILE *fp;    
    char filename[100];    
    sprintf(filename,"tp%lfsun.txt",p);    
    fp = fopen(filename,"w");
    
    //loop for FRP
    for(i=0;i<=48;i++){
      
      a= i*1.0/24.0;
      
      xa =  M_PI*(2.0/3.0);
      va =  2.0*M_PI*(a);
      xex = 0.0;

      //loop for resetting strength
      for(k=0; k<=2000; k++){
	
	T=0.0;
	T0=0.0;
	T1=0.0;
	T2=0.0;
	T3=0.0;
	
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
	  
	  kxa1 =   fxa(l,xa,xex)*dt;
	  kxa2 =   fxa(l,xa + kxa1/2,xex)*dt;
	  kxa3 =   fxa(l,xa + kxa2/2,xex)*dt;
	  kxa4 =   fxa(l,xa + kxa3,xex)*dt;
	  xa =    xa + (kxa1 + 2*kxa2 + 2*kxa3 + kxa4)/6 + va*dt;
	  
	  if(sin(xa)*sin(xa0)<=0.0){
	    
	    T3=T2;
	    
	    T2=T1;
	    
	    T1=T0;
	    
	    T0=T;
	    
	    T=step*dt;
	    
	    if(T>10.0){
	      
	      if((T-T1 == 1.000)&&(T0-T2 == 1.000)&&(T1-T3 == 1.000)){
		
		fprintf(fp,"%d %lf %lf %lf\n",i,l ,step*dt, T-T1);
		
		break;
		
	      }
	      
	    }
	    
	  }
	  
	}
	
	
	if((T-T1 == 1.000) && (T0-T2 == 1.000) && (T1-T3 == 1.000)){
	  
	  break;
	  
	}
	
      }
      
    }
    
  }
  
  
}
