#include <stdio.h>
#include <math.h>

int sine_table[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 5, 6, 6, 7, 7, 8, 9, 9, 10, 11, 12, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 35, 36, 37, 38, 39, 40, 42, 43, 44, 45, 46, 48, 49, 50, 51, 52, 54, 55, 56, 57, 58, 60, 61, 62, 63, 64, 65, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 86, 87, 88, 89, 90, 90, 91, 92, 92, 93, 93, 94, 95, 95, 96, 96, 96, 97, 97, 98, 98, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 98, 98, 98, 98, 97, 97, 96, 96, 96, 95, 95, 94, 94, 93, 92, 92, 91, 90, 90, 89, 88, 87, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 64, 63, 62, 61, 60, 59, 57, 56, 55, 54, 53, 51, 50, 49, 48, 47, 45, 44, 43, 42, 41, 39, 38, 37, 36, 35, 34, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 13, 12, 11, 10, 9, 9, 8, 7, 7, 6, 6, 5, 4, 4, 3, 3, 3, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
int size = sizeof(sine_table)/sizeof(sine_table[0]);
#define duty 0


void comp(int _duty,int size_of_table ,int table[]);
void plot(int sine_table[],int num_of_div);
void plot_3ph(int sine_table1[],int sine_table2[],int sine_table3[],int num_of_div);
int main(){
    comp(duty, size, sine_table);
    return 0;
}
typedef struct table_characteristic
{
    int first_el;
    int right_middle;
    int left_middle;
    int end_el;
    int size_of_compressed_table;
    int half_size_of_compressed_table;
    float division;
} table_characteristic;



void comp(int _duty,int size_of_table ,int table[]){
    table_characteristic input_table;
    input_table.first_el = 0;
    // input_table.right_middle = _duty/2;
    // input_table.left_middle = input_table.right_middle - 1;
    input_table.end_el = size_of_table-1;
    input_table.size_of_compressed_table =4 + 28*2 + 2*(100-_duty);
    input_table.half_size_of_compressed_table = input_table.size_of_compressed_table/2;
    input_table.division = (float)size_of_table/input_table.size_of_compressed_table;
    int o_t = (float)(input_table.size_of_compressed_table/3);
    int t_t = (float)(2*input_table.size_of_compressed_table/3);


    int first_compressed_table[input_table.size_of_compressed_table];
    int second_compressed_table[input_table.size_of_compressed_table];
    int third_compressed_table[input_table.size_of_compressed_table];
    first_compressed_table[0] = first_compressed_table[size_of_table-1] = 0;
    // first_compressed_table[input_table.left_middle] = first_compressed_table[input_table.right_middle] = 99;
    printf("%d\n",first_compressed_table[0]);
    for (int i = 1; i < input_table.size_of_compressed_table; i++)
    {
        first_compressed_table[i] = sine_table[(int)roundf(i*input_table.division)];
        printf("%d\n",first_compressed_table[(int)roundf(i*input_table.division)]);
    }
    for (int i = 0; i < input_table.size_of_compressed_table; i++)
    {
        if(o_t+i<input_table.size_of_compressed_table){
            second_compressed_table[i] = first_compressed_table[o_t+i];
        }
        else{
            second_compressed_table[i] = first_compressed_table[(o_t+i)-input_table.size_of_compressed_table ];
        }
        
    }
    for (int i = 0; i < input_table.size_of_compressed_table; i++)
    {
        if(t_t+i<input_table.size_of_compressed_table){
            third_compressed_table[i] = first_compressed_table[t_t+i];
        }
        else{
            third_compressed_table[i] = first_compressed_table[(t_t+i)-input_table.size_of_compressed_table ];
        }
        
    }
    
    
    plot(first_compressed_table,input_table.size_of_compressed_table);
    plot(second_compressed_table,input_table.size_of_compressed_table);
    plot(third_compressed_table,input_table.size_of_compressed_table);
    plot_3ph(first_compressed_table,second_compressed_table,third_compressed_table,input_table.size_of_compressed_table);
}

void plot(int sine_table[],int num_of_div){
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
void plot_3ph(int sine_table1[],int sine_table2[],int sine_table3[],int num_of_div){
    printf("\n");
    for (int i = 0; i < num_of_div; i++)
    {
        for (int k = 99; k >= 0; k-=1)
        {
          if (sine_table1[i]>k)
          {
            printf("#");
          }
          if(sine_table[i] ==0 && k==0){
            printf("|");
          }

        }
        printf("\n");
        for (int k = 99; k >= 0; k-=1)
        {
          if (sine_table2[i]>k)
          {
            printf("O");
          }
          if(sine_table[i] ==0 && k==0){
            printf("I");
          }

        }
        printf("\n");
        for (int k = 99; k >= 0; k-=1)
        {
          if (sine_table3[i]>k)
          {
            printf("H");
          }
          if(sine_table[i] ==0 && k==0){
            printf("J");
          }

        }
        printf("\n");
    }
}