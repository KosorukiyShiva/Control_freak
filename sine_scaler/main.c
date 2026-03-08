#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int sine_table[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 5, 6, 6, 7, 7, 8, 9, 9, 10, 11, 12, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 35, 36, 37, 38, 39, 40, 42, 43, 44, 45, 46, 48, 49, 50, 51, 52, 54, 55, 56, 57, 58, 60, 61, 62, 63, 64, 65, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 86, 87, 88, 89, 90, 90, 91, 92, 92, 93, 93, 94, 95, 95, 96, 96, 96, 97, 97, 98, 98, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 98, 98, 98, 98, 97, 97, 96, 96, 96, 95, 95, 94, 94, 93, 92, 92, 91, 90, 90, 89, 88, 87, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 64, 63, 62, 61, 60, 59, 57, 56, 55, 54, 53, 51, 50, 49, 48, 47, 45, 44, 43, 42, 41, 39, 38, 37, 36, 35, 34, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 13, 12, 11, 10, 9, 9, 8, 7, 7, 6, 6, 5, 4, 4, 3, 3, 3, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
int sine_table_size = sizeof(sine_table)/sizeof(sine_table[0]);
int map[130];
  
#define duty 100

typedef struct node{
  int pos, count, childs_counts_left, childs_counts_right;
  struct node *mother;
  struct node *left;
  struct node *right
}Node;

typedef struct bin_tree{
  int seed;
  Node *seed_node ;
}BinTree;

void comp(int _duty,int size_of_table ,int table[]);
void plot(int sine_table[],int num_of_div);
void plot_3ph(int sine_table1[],int sine_table2[],int sine_table3[],int num_of_div);
int SLBinTreeInsert(BinTree* bt, int position);
void BinTreeInit(BinTree* bt); 
int mapmaker(int source_table[], int source_table_size, int* map);

int main(){
    // comp(duty, size, sine_table);
    int test = 9/2;
    

    // printf("%d", sine_table[130]);
    mapmaker(sine_table, sine_table_size,map);
    printf("%d \n", map[0]);
    printf("%d \n", map[1]);
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


void binary_comp(int _duty,int size_of_table ,int table[]){
  table_characteristic input_table;
  
  input_table.first_el = 0;
  input_table.end_el = size_of_table - 1;
  input_table.right_middle = _duty/2;
  input_table.left_middle = input_table.right_middle - 1;
  input_table.size_of_compressed_table= size_of_table;

}

int binary_map(int _duty, int size_of_table, int table[]){
  table_characteristic input_table;
  input_table.first_el = 0;
  input_table.end_el = size_of_table - 1;
  input_table.right_middle = _duty/2;
  input_table.left_middle = input_table.right_middle - 1;
  // input_table.size_of_compressed_table = ;

}

 
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




Node* CreateNode(int position,Node *mother){
  /*
  position - позиция в исходной таблице, основное значение
  
  */ 
  if(position < 0 ) return NULL;
  Node* Nu =(Node*)malloc(sizeof(Node));
  if(Nu == NULL) return NULL;
  Nu->pos = position;
  Nu->childs_counts_left = 0;
  Nu->childs_counts_right = 0;
  Nu->left = NULL;
  Nu->right = NULL;
  Nu->mother = mother;
} 

// int BinTreeInsert(BinTree *Bt, int position){
//   Node* transfer;
//   if(Bt -> seed_node == NULL){ // первый элемент, с заданием сид значения 
//     Bt->seed = position;
//     Bt->seed_node =CreateNode(position,NULL);
//     Bt->seed_node -> childs_counts_right = CreateNode(NULL,NULL);
//   }
//   else{
//     transfer = Bt->seed_node;
//     if(transfer->mother == NULL ){
//       transfer = transfer->childs_counts_left;
//     }
//     while(1){
//       if(transfer->childs_counts_left == transfer->childs_counts_right && transfer->left != NULL && transfer->right !=NULL){
//         transfer->childs_counts_left ++;
//         transfer = transfer->left; 
//       }
//       else if(transfer->childs_counts_left > transfer->childs_counts_right && transfer->left != NULL && transfer->right !=NULL){
//         transfer->childs_counts_right ++;
//         transfer = transfer->right;
//       }
//       if(transfer->childs_counts_left == 0 ||  transfer->childs_counts_right == 0){
//         break;
//       }
//     }
//     if(transfer->childs_counts_left == 0 && transfer->childs_counts_right == 0){
//       transfer->childs_counts_left ++;
//       transfer->left = CreateNode(position,transfer);
//     }
//     else if(transfer->childs_counts_left == 1 && transfer->childs_counts_right == 0){
//       transfer->childs_counts_right ++;
//       transfer->right = CreateNode(position, transfer);
//     }
//   }
// }

// int mapmaker(int source_table[], int source_table_size, int map[]){
//   BinTree* bt;
//   if(source_table[0] == source_table[source_table_size-1]){ // симетричные исходные сигналы 
//     map[0] = source_table[0];
//     map[1] = source_table[(source_table_size/2)-1];
//     if((source_table_size/4)%2 == 0) //для четного кол-ва элементов
//     {
//       BinTreeInsert(bt,source_table_size/4);
//       BinTreeInsert(bt,source_table_size/8);

//     }
//   }
// }
void BinTreeInit(BinTree* bt){
  bt->seed = 0;
  bt->seed_node = NULL;
}
int SLBinTreeInsert(BinTree* bt, int position){
  Node* transfer = bt->seed_node;
  if(bt->seed_node == NULL){
    bt->seed = position;
    bt->seed_node = CreateNode(position,NULL);
  }
  else 
  {
    while((transfer->pos > position ) || (transfer->pos < position )){
      if(transfer->pos > position && transfer->left != NULL){
        transfer = transfer->left;
        continue;;
      }
      if(transfer->pos < position && transfer->right != NULL){
        transfer = transfer->right;
        continue;;
      }
      if(transfer->pos > position && transfer->left == NULL){
        transfer->left = CreateNode(position, transfer);
        break;
      }
      if(transfer->pos < position && transfer->right == NULL){
        transfer->right = CreateNode(position, transfer);
        break;
      }
    }
  }
  
}
int mapmaker(int source_table[], int source_table_size, int* map){
  /*
  1. поиск серидины
  2. заполнение самой левой ветви пока эл-n не будет == 1 
  3. сдвигаем левую глобальную границу и выставляем локальное правое ограничение (глобальная левая граница это родитель. глобальная правая родитель родителя)
  4. ищем  среднее между глобальным левым и локальным правым двигаясь налево до эл-та с разницей от глобального минимума в 1
  5. повторить до заполенения 
  */
 BinTree* bt = (BinTree*) malloc(sizeof(BinTree));
 int locales[8]={0}; 
 int remainder = -1;
 int i = 0;
 int ll,rl;
 int middle;
 int transfer_mother, transfer_source, pos;
  if(source_table_size % 2 == 0){
    map[0] = 0;
    map[1] = (source_table_size/2)-1;
  }
  else if(source_table_size % 2 != 0){
    map[0] = 0;
    map[1] = source_table_size/2;
  }
  middle = map[1]/2;
  // locales[0] = middle;
  map[2] = middle;
  transfer_source = middle;

  // return 0;
  while(transfer_source >= 1){
    i++;
    rl = transfer_source;
    SLBinTreeInsert(bt,transfer_source);  
    locales[i-1] = transfer_source;
    transfer_source = transfer_source /2; 
    ll = transfer_source;
    // remainder ++;
  }
  printf("%d \n",map[0]);
  while(map[1]-ll >1){
    if(ll == 0){
      ll = 1;
      for(int i = 0; i <8; i++){
        if(locales[i+1] == 1){
          rl = locales[i];
          transfer_source = (ll + rl)/2;
          break;
        }
      }
    }
    while( ll != map[1]-1){
      if (transfer_source == 62){ //breakpoint trap
        printf("12");
      }
      SLBinTreeInsert(bt,transfer_source);
      if(transfer_source - ll == 1){
        ll = transfer_source;
      }
      if(transfer_source - ll > 1){
        rl = transfer_source;
        transfer_source = (rl + ll)/2;
        continue;
      }
      if(transfer_source - ll == 0 && rl - transfer_source != 1){
        transfer_source = (ll + rl)/2;
        ll = transfer_source;
        continue;
      }
      

      if(rl - transfer_source == 1){
        ll = rl ;
        for(int i = 0; i <8; i++){
        if(locales[i+1] == rl ){
          rl = locales[i];
          transfer_source = (ll + rl)/2;
          // SLBinTreeInsert(bt,transfer_source);
          // remainder --;
          if(ll == locales[1] && rl == locales[0]){
            locales[1] = (locales[0] + locales[1])/2;
            SLBinTreeInsert(bt,transfer_source);
            i = 1;
            while(transfer_source-1 >= ll){
              rl = transfer_source;
              locales[i] = rl;
              transfer_source = (rl + ll)/2;
              SLBinTreeInsert(bt,transfer_source);
              i++;
            }
            locales[i] = ll;
            printf("loc");
          }
          break;
        }
        else if((locales[i+1] < rl) && (locales[i] > rl) && ((locales[i]+locales[i+1])/2 > rl) ){
          ll = rl;
          rl = (locales[i]+locales[i+1])/2;
          transfer_source = (ll + rl)/2;
          // SLBinTreeInsert(bt,transfer_source);
          // remainder --;
          break;
        }
        else if((locales[i+1] < rl) && (locales[i] > rl) ){
          ll = rl;
          rl = locales[i];
          transfer_source = (ll + rl)/2;
          // remainder --;
          // SLBinTreeInsert(bt,transfer_source);
          break;
        }
      } 
      }
      
    }
  }

  /*
  1.находим первое знаение после сид значения и фиксируем его
  2.обход происходит по уровню, с очередностью сначала левые корни потом все правые на одном уровне 
  3. 

  */


}