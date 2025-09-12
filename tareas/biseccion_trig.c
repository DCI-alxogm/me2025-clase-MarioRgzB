#include <stdio.h>
#include <math.h>

float f(float x);

int main(){
    float Err_max=0.0001;
    float a=3,b=5,k,fk,Eapr,Err,kold=INFINITY;
    int n=0;
    float delta_x,error_teorico;
    
    do {
        n++;
        k=(a+b)/2;
        fk=f(k);
        
        if(fk*f(a)<0) {
            b=k;
        } else {
            a=k;
        }
        
        delta_x=b-a;
        error_teorico=delta_x/pow(2, n);
        Eapr=k-kold;
        Err=fabs(Eapr/k);
        kold=k;
        
        char cumple[4];
        if (fabs(Err-error_teorico)<0.00001) {
            sprintf(cumple, "Sí");
        } else {
            sprintf(cumple, "No");
        }
        
        printf("%d\t %f \t %f \t %f \t %f \t %f \t %f \t %s\n", 
               n,k,fk,Eapr,Err,delta_x,error_teorico,cumple);
        
    } while (Err>Err_max);
    
    printf("\nRaiz encontrada: %f después de %d iteraciones\n",k,n);
    printf("Error final: %f\n",Err);
    printf("Error teórico final: %f\n",error_teorico);
    
    return 0;
}

float f(float x) {
    return sin(10*x)-cos(3*x);
}