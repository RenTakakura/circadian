//2step model
//FRP -->(k,fraction of longer(shorter) period)

#include <stdio.h>
#include <math.h>


int main(void){
  
  //def external force  
  double fxa(double l,double xa,double xex){
    return  -1.0*  l *sin(xa - xex);
    
  }
  
  int step,k,i,j,m,n,q,r, maxstep =25000;
  double p,a,T,T0,T1,l,t, xa, xa0, va, va0, xex, kxa1, kxa2, kxa3, kxa4,S,  dt = 1.0/500.0;
  int A[10];
  int SUM;
  
  
  p=0.50;

  //loop for FRP
  for(r=1;r<=32;r++){
    
    a = r*1.0/24.0;
    
    FILE *fp;    
    char filename[100];
    sprintf(filename,"frsunT%dsc.txt",r);    
    fp = fopen(filename,"w");

    //loop gor resetting strength
    for(k=0; k<=1200; k++){
      
      l = k*0.010;

      //initialize
      xa =  M_PI*(2.0/3.0);
      va =  2.0*M_PI*(a);
      xex = 0.0;
      
      T=0.0;
      T0=0.0;
      T1=0.0;
      
      SUM = 0;
      
      for(n=0;n<=1;n++){
	
	A[n]=0;
	
      }
      
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
	
	if( (sin(xa)*sin(xa0)<=0.0)&&(step*dt>10.0) ){
	  
	  T1=T0;
	  
	  T0=T;
	  
	  T=step*dt;
	  
	  for(j=0;j<=1;j++){
	    
	    if(( j*0.50+0.250  <= T-T1) && (T-T1 <= j*0.50+0.750)){
	      
	      A[j]++;	
	      
	      break;
	      
	    }
	    
	  }		  
	}
	
      }
      
      for(q=0;q<=1;q++){
	
	SUM +=  A[q];
	
      }
      
      fprintf(fp,"%lf %lf %lf \n", l , (A[0]*1.0)/(SUM*1.0) , (A[1]*1.0)/(SUM*1.0) );
      
    }
    
  }	  
}


