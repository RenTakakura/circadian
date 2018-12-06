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
  int cnt,ppp,k, i, j, step, maxstep =50000;
  double p,a,T,T0,T1,l,t, xa, xa0, va, va0, xex, kxa1, kxa2, kxa3, kxa4, dt = 1.0/500.0;

  //def fraction of day
  for(ppp=80;ppp<=90;ppp++){
    
    //open file
    FILE *fp;
    char filename[100];
    sprintf(filename,"pisunregionp%d.txt",ppp);
    fp = fopen(filename,"w");

    p=0.01*ppp;

  //loop for FRP
  for(i=1;i<=32;i++){

    a= i*1.0/24.0;


    
    //initialize
    xa =  M_PI*(3.0/3.0);
    va =  2.0*M_PI*(a);
    xex = 0.0;

    //loop for resetting strength
    for(k=0; k<=500; k++){
      
      T=0.0;
      T0=0.0;
      T1=0.0;
      
      l=0.10*k;

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
	
	if(sin(xa)*sin(xa0)<=0.0 && xa>xa0){
	  
        
	  
	  T1=T0;

	  T0=T;
	  
	  T=step*dt;
	  
	  if(T>10.0){

      if(fabs(T-T1-1)<0.0005){

        cnt++;

        if(cnt>5){

        fprintf(fp,"%lf %d \n", l, i);

        break;


        }
	    
	  }else{

      cnt=0;

    }
	  
	}

      }
      
    }
    
  }
  }
  }
}
