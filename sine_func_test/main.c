#include <stdio.h>
#include <math.h>
short sine_table[500];
float max =0;
#define num_of_div 260
int per_num_div = num_of_div/2;

void plot(short sine_table[]){
    printf("\n");
    for (int i = 0; i < num_of_div; i++)
    {
        for (int k = 99; k >= 0; k-=1)
        {
          if (sine_table[i]>k)
          {
            printf("#");
          }
          if(sine_table[i] ==0 && k==0){
            printf("|");
          }

        }
        printf("\n");
    
    }
}

int main(){
    for(int i = 1; i <num_of_div+1; i++){
       sine_table[i-1]=((1-(2+cosl(((i)*3.14)/per_num_div)+cosl(((i-1)*3.14)/per_num_div))/4)*100); 
       printf("%d, ",sine_table[i-1]);
    }
    plot(sine_table);
    
    return 0;
}

