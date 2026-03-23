#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

int sine_table[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 5, 6, 6, 7, 7, 8, 9, 9, 10, 11, 12, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 35, 36, 37, 38, 39, 40, 42, 43, 44, 45, 46, 48, 49, 50, 51, 52, 54, 55, 56, 57, 58, 60, 61, 62, 63, 64, 65, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 86, 87, 88, 89, 90, 90, 91, 92, 92, 93, 93, 94, 95, 95, 96, 96, 96, 97, 97, 98, 98, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 98, 98, 98, 98, 97, 97, 96, 96, 96, 95, 95, 94, 94, 93, 92, 92, 91, 90, 90, 89, 88, 87, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 64, 63, 62, 61, 60, 59, 57, 56, 55, 54, 53, 51, 50, 49, 48, 47, 45, 44, 43, 42, 41, 39, 38, 37, 36, 35, 34, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 13, 12, 11, 10, 9, 9, 8, 7, 7, 6, 6, 5, 4, 4, 3, 3, 3, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
int sine_table_size = sizeof(sine_table)/sizeof(sine_table[0]);
int map[130];
int map1[130];

uint8_t PWM_ch1[260]={0};
  
// #define duty 100

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
int MapMaker(int source_table[], int source_table_size, int* map);


uint16_t SIZE  = 0; // size for pwm_dma_start length
uint16_t SIGNAL_SIZE = sizeof(sine_table)/sizeof(sine_table[0]);
uint16_t MAP_SIZE = sizeof(map)/sizeof(map[0]);

uint8_t  sort_signal( int* map, uint8_t duty, uint8_t* PWM_ch1);
uint8_t mirror_signal(uint16_t SIZE, uint8_t* PWM_ch1);

int main(){
    // comp(duty, size, sine_table);
    int test = 9/2;
    

    // printf("%d", sine_table[130]);
    MapMaker(sine_table, sine_table_size,map);
    sort_signal(map,127,PWM_ch1);
    mirror_signal(SIZE, PWM_ch1);
    // printf("%d \n", map[0]);
    printf(" \n");
    plot((int*)PWM_ch1,(int) SIZE );
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

int SearchNode(BinTree* bt, int position, char side){
  Node* transfer = bt->seed_node;
  switch (side)
  {
  case 'l':
    while(transfer->pos != position ){
      if(position <= transfer->pos && transfer->left != NULL || transfer->pos == bt->seed ){
        transfer = transfer->left;
        continue;
      }
      if(position >= transfer->pos && transfer->right != NULL){
        transfer = transfer->right;
        continue;
      }
      
    }
    if(transfer->left == NULL){
      return 0;
    }    
    return transfer->left->pos;
    break;
  case 'r':
    while(transfer->pos != position ){
      if(position <= transfer->pos && transfer->left != NULL || transfer->pos == bt->seed ){
        transfer = transfer->left;
        continue;
      }
      if(position >= transfer->pos && transfer->right != NULL){
        transfer = transfer->right;
        continue;
      }
    }
    if(transfer->right == NULL){
      return 0;
    } 
    return transfer->right->pos;
    break;
  default:
    break;
  }
}


int MapMaker(int source_table[], int source_table_size, int* map){
  /*
  1. поиск серидины
  2. заполнение самой левой ветви пока эл-n не будет == 1 
  3. сдвигаем левую глобальную границу и выставляем локальное правое ограничение (глобальная левая граница это родитель. глобальная правая родитель родителя)
  4. ищем  среднее между глобальным левым и локальным правым двигаясь налево до эл-та с разницей от глобального минимума в 1
  5. повторить до заполенения 
  */
 BinTree* bt = (BinTree*) malloc(sizeof(BinTree));
 int locales[8] = {0}; 
 int frame_1[64] = {0};
 int frame_2[64] = {0};
 int remainder = -1;
 int i = 0;
 int j = 0;
 int k = 6;
 int deep = -1;
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
    deep++;
    rl = transfer_source;
    SLBinTreeInsert(bt,transfer_source);  
    locales[i-1] = transfer_source;
    transfer_source = transfer_source /2; 
    ll = transfer_source;
    // remainder ++;
  }
  // printf("%d \n",map[0]);
  while(map[1]-ll >1){
    if(ll == 0){
      ll = 1;
      for(int i = 0; i <8; i++){
        if(locales[i+1] == 1){
          rl = locales[i];
          transfer_source = (ll + rl)/2;
          // deep++;
          break;
        }
      }
    }
    while( ll != map[2]){
      // if (transfer_source == 20){ //breakpoint trap
      //   // printf("12");
      // }
      SLBinTreeInsert(bt,transfer_source);
      if(transfer_source - ll == 1 ){
        ll = transfer_source;
        locales[deep] = transfer_source;
      }
      if(transfer_source - ll > 1){
        rl = transfer_source;
        transfer_source = (rl + ll)/2;
        for(int i = 0; i < deep; i++){
          if(transfer_source < locales[i] && transfer_source > locales[i+1]){
            locales[i+1] = transfer_source;
            break;
          }
        }
        continue;
      }
      if(transfer_source - ll == 0 && rl - transfer_source != 1){
        transfer_source = (ll + rl)/2;
        ll = transfer_source;
        continue;
      }
      




      if(rl - transfer_source == 1){
        ll=rl;
        for(int i =0; i < 8; i++){
          if(locales[i+1] == rl ){
            rl = locales[i];
            locales[deep] = ll;
            transfer_source = (ll + rl)/2;
            for(int i = 0; i < deep; i++){
              if(transfer_source < locales[i] && transfer_source > locales[i+1]){
                locales[i+1] = transfer_source;
                break;
              }
              if(transfer_source - ll == 1){
                break;
              }
            }
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
            }
            break;
          }
        }
      }
      
    }
    break;
  }
  i = 0;
  // printf("chayka");
  /*
  1.находим первое знаение после сид значения и фиксируем его
  2.обход происходит по уровню, с очередностью сначала левые корни потом все правые на одном уровне 
  3. 
  
  */
  frame_1[0] = bt->seed_node->left->left->pos;
  frame_1[1] = bt->seed_node->left->right->pos;
  map[3] = bt->seed_node->left->pos;
  map[4] = frame_1[0];
  map[5] = frame_1[1];
  printf(" %d, ", map[0]);
  printf(" %d, ", map[1]);
  printf(" %d, ", map[2]);
  printf(" %d, ", map[3]);
  printf(" %d, ", map[4]);
  printf(" %d, ", map[5]);
  while(map[bt->seed + 1] == 0){
    while(frame_1[i] != 0){
      frame_2[i] = SearchNode(bt,frame_1[i],'l');
      i++;
    }
    if (i == 0){
      return 0;
    }
    while(j != i ){
      frame_2[i+j] = SearchNode(bt,frame_1[j],'r');
      j++;
    }
    i = j = 0;
    while(frame_2[i] != 0){
      map[k] = frame_2[i];
      k++;
      map[k] = frame_2[i]+map[2]; 
      printf("%d, %d, ",map[k-1], map[k]);
      k++;
      i++;
    }
    i = 0;
    while(frame_2[i] != 0){
      // if (frame_2[i] = 21){
      //   printf("sas");
      // }
      frame_1[i] = SearchNode(bt, frame_2[i],'l');
      i++;
    }
    if (i == 0){
      return 0;
    }
    while(j != i){
      frame_1[i+j] = SearchNode(bt,frame_2[j],'r');
      j++;
    }
    i = j = 0;
    while (frame_1[i] != 0){
      map[k] = frame_1[i];
      k++;
      map[k] = frame_1[i]+map[2]; 
      printf("%d, %d, ",map[k-1], map[k]);
      // printf("%d, ", map[k]);
      i++;
      k++;
    }
    i = 0;
  }
  map[k]= map[2]+map[2];
  printf("%d, ",map[k]);
  k++;
  map[k]= map[3]+map[2];
  printf("%d, ",map[k]);
  k++;
  map[k]= map[4]+map[2];
  printf("%d, ",map[k]);
  k++;
  map[k]= map[5]+map[2];
  printf("%d, ",map[k]);
  k++;

}





 
 typedef enum {
	 OFF,
//	 SMLL_FRC,
//	 BG_FRC,
	 ON
 }duty_subrange;

duty_subrange st_sbr = OFF;
uint8_t  sort_signal( int* map, uint8_t duty, uint8_t* PWM_ch1){
  /*
  1. range of duty = 0-128    error code: 1

	  */
	 uint8_t swap_val1 = 0;
	 if(duty > 128){
		 st_sbr = OFF;
		 SIZE = 0;
		 return 1;
	 }
	 if(duty == 0){
		 st_sbr = OFF;
	 }
//	 else if (duty != 0 && duty <=40) {
//		st_sbr = SMLL_FRC;
//	}
//	 else if(duty > 40 && duty <= 100){
//		 st_sbr = BG_FRC;
//	 }
	 else if (duty > 0 && duty <= 256) {
		st_sbr = ON;
	}

	 PWM_ch1[0] = sine_table[map[0]];
	 switch (st_sbr) {
		case OFF:
			SIZE = 0;
			break;
		case ON:
			SIZE = SIGNAL_SIZE - duty*2;
			for (int i = 0 ; i < SIZE/2; i++ ){
				if(i == 0){
					PWM_ch1[0] = sine_table[0];
					swap_val1 = map[1];
					continue;
				}
				for(int k = 0; k < SIZE/2; k++){
					if(map[k] > PWM_ch1[i-1] && map[k] < swap_val1){
						swap_val1 = map[k];
					}
				}
        PWM_ch1[i] = swap_val1 ;
        swap_val1 = map[1];
			}
      for (int i = 0; i < SIZE/2; i++ ){
        PWM_ch1[i] = (uint8_t) sine_table[PWM_ch1[i]];
      }
			break;
		default:
			break;
	}
 };

 uint8_t mirror_signal(uint16_t SIZE, uint8_t* PWM_ch1){
  for(int i = 0; i < SIZE/2; i++){
    PWM_ch1[i+SIZE/2] = PWM_ch1[SIZE/2 -(1 + i)];
  }
  return 0;
 }