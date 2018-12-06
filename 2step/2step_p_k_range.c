//2step model
//range of entrainment
//relaative frequency --->entrainment range (fraction of day, resetting strength)

#include <stdio.h>
#include <math.h>


int main(void){

  //def external force
  double fxa(double l,double xa,double xex){
    return  -1.0*  l * sin(xa - xex);
  }
  
  int step,k,i,j,cnt,maxstep =50000;
  double p,a,T,T0,T1,l,t, xa, xa0, va, va0, xex, kxa1, kxa2, kxa3, kxa4, dt = 1.0/1000.0;
  
  //loop for relative frequency
  for(j=0;j<=5;j++){
    
    a=1.0+0.10*j;
    
    FILE *fp;    
    char filename[100];
    sprintf(filename,"suna%lf.txt",a);
    fp = fopen(filename,"w");
    
    //loop for fraction of day
    for(i=0;i<=50;i++){
      
      cnt=0;
      
      p=0.50+0.010*i;
      
      xa =  M_PI*(2.0/3.0);
      va =  2.0*M_PI*(a);
      xex = 0.0;

      //lpp for resetting strength
      for(k=0; k<=1000; k++){
	
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
	  
	  if(sin(xa)*sin(xa0)<=0.0){
	    
	    T1=T0;
	    
	    T0=T;
	    
	    T=step*dt;
	    
	    if(T>30.0){
	      
	      if(T-T1<0.990){
		
		break;
		
	      }
	      
	      else{
		
		if(T-T1>1.010){
		  
		  break;
		  
		}
		
		else{
		  
		  fprintf(fp,"%lf %lf %lf\n",p,l,T-T1);
		  
		  
		  cnt=1;
		  
		  break;
		  
		}
	      }
	      
	    }
	    
	  }
	  
	  
	  
	}
	
      }
    }
  }
}

