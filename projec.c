#define WELCOME_MESSAGE "                 ---WELCOME TO *HIGHHIlL* *RESTAURANT* --- \n\n"
// #define N 5

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include<unistd.h>
#define PASS 7693
#define MOVE_CURSOR_BACK() printf("\033[D") 
#define CLEAR_CURRENT_CHAR() printf("\033[K") 

char name1[90] = "WELCOME_TO *HIGHHILL*_*RESTAURANT* MANAGEMNET_SYSTEM CREATED_BY_TEAM_7 ";
int order_manage();
int create_order();
int billing();
void print_order(int a); 
void splash();
bool admin_verify();

struct orderlist{

    char custumer_name[20];
    int  order_item[5];
    int item_price[5];
    time_t order_id;
    int total_price;
    int item_qui[5];
    char status[10];
    int a;
};
struct orderlist ol1;
char items[6][15]={"tea","coffee","burger","pizza","sandwich","Biryani"};
int price[6]={10,20,30,60,40,150};
int main (){


splash();
if(admin_verify()==true){
order_manage();

}
else{

    printf("\n\nerror :   !!!!!! Invalid Pin  !!!!");
}



    return 0;
}

int order_manage(){
    system("cls");
int k;
printf("%s \n",WELCOME_MESSAGE);
printf("1.Book a New Order\n2.billing\n3.Exit\n");
printf("Select an Option : ");
scanf("%d",&k);
if(k==1){
    create_order();
}else if(k==2){
    billing();

}else if(k==3){
    return 0;
    
} 
    else{
  printf("You Have Enter An Wrong Choice .\n");
  Sleep(3000);
  order_manage();

}


}

int create_order(){
     system("cls");
     printf("%s \n",WELCOME_MESSAGE);
     printf("Enter Custumer name : ");
     scanf("%s",ol1.custumer_name);
     system("cls");
     printf("%s \n",WELCOME_MESSAGE);
     
  int l=1;
  int i;
    for( i=0;l;i++){
        system("cls");
        printf("%s \n",WELCOME_MESSAGE);
        printf("Enter item id (1-6) of selected item \n");
    for(int j=0;j<6;j++){
        printf("%d.%s   ",(j+1),items[j]);

    }
    printf("\nenter item : ");
    scanf("%d",&ol1.order_item[i]);
    if(ol1.order_item[i]>6 || ol1.order_item[i]<1){
       
        i=i-1;
        continue;
    }
    printf("enter item quantity : ");
    scanf("%d",&ol1.item_qui[i]);
    printf("Do you want add more item (y/n) : ");
    char c[2];
    scanf("%s",&c);
    if(c[0]=='y'){
        continue;
    }else{
        break;
    }


    }
    time_t times =time(NULL);
    ol1.order_id=times;
    int sum=0;
    for(int k=0;k<=i;k++){
        ol1.item_price[k]=price[(ol1.order_item[k]-1)]*ol1.item_qui[k];
        sum=sum+ ol1.item_price[k];
    }
  ol1.total_price=sum;
  FILE *fp;
  char filename[50];
  sprintf(filename,"./orders/%ld_%s.txt",ol1.order_id,ol1.custumer_name);
  fp =fopen(filename,"w");
  if (fp == NULL) {
        printf("Error opening fp\n");
        return 1;
    }
    
	
    fprintf(fp, "Customer Name: %s\n",ol1.custumer_name);
    fprintf(fp, "order id : %d\n",ol1.order_id);
    fprintf(fp,"item     quantity  per/price subtotal \n");
    for(int y=0;y<=i;y++){
         fprintf(fp,"%d.%s  :      %d         %d         %d\n",(y+1),items[(ol1.order_item[y]-1)],ol1.item_qui[y],price[(ol1.order_item[y]-1)],ol1.item_price[y]);
         fprintf(fp,"-------------------------------------\n");
    }


    
    fprintf(fp, "Total Price: %d\n", ol1.total_price);
    fprintf(fp, "Status: %s\n", "sucess");
    char *aman =ctime(&ol1.order_id);
    fprintf(fp, "Date : %s",aman);

	fprintf(fp,"\n\n     ...... thanks you for visit......");

   
    fclose(fp);
    ol1.a=i;
    FILE *fp1;
  char filename1[50];
  sprintf(filename1,"./bino/%ld.dat",ol1.order_id);
  fp1 =fopen(filename1,"wb");
  if (fp1 == NULL) {
        printf("Error opening fp\n");
        return 1;
    }
   fwrite(&ol1,sizeof(struct orderlist),1,fp1);
   fclose(fp1);

 print_order(i);
 printf("\nGo to main menu (y/n) :");
char c11[2];
    scanf("%s",&c11);
    if(c11[0]=='y'){
        order_manage();
    }
     
}
void print_order(int a){
    system("cls");

printf("        ..........Order Receipt.........\n\n");
printf("Order id : %d \nCustumer name : %s\n....Order Items...\nitem     quantity  per/price subtotal \n",ol1.order_id,ol1.custumer_name);
for(int i=0;i<=a;i++){
    
    printf("%s        %d          %d         %d\n",items[(ol1.order_item[i]-1)],ol1.item_qui[i],price[(ol1.order_item[i]-1)],ol1.item_price[i]);
    printf("-------------------------------------\n");
}

printf(" \nTotal : %d\nStatus : success",ol1.total_price);

// printf("\n\n     ...... thanks you for visit......");



}






int billing(){
system("cls");
printf("%s",WELCOME_MESSAGE);
printf("enter Order_id :");
time_t orderida;
scanf("%d",&orderida);
FILE *fp2;
char filename2[50];
sprintf(filename2,"./bino/%ld.dat",orderida);
fp2 =fopen(filename2,"rb");
if(fp2==NULL){
    printf("order id %d not exist ",orderida);
    Sleep(3000);
    order_manage();
}
fread(&ol1,sizeof(struct orderlist),1,fp2);
fclose(fp2);
print_order(ol1.a);
printf("\n\nDo Want To Print Order : %d (y/n) :",orderida);
char c[2];
    scanf("%s",&c);
    char filename3[50];
    if(c[0]=='y'){
        sprintf(filename3,"xdg-open ./orders/%ld_%s.txt",orderida,ol1.custumer_name);
        // system(filename3);
       system(filename3);
        
    }
    
    else{
       printf("\nGo to main menu (y/n) :");
char c[2];
    scanf("%s",&c);
    if(c[0]=='y'){
        order_manage();
    }

    }





}

void splash(){



 


int k=0;


    system("cls");
   printf("\n\n\n\n                              ");
  for(int i=0;i<strlen(name1);i++){
    char c=name1[i];
    Sleep(120);
    putchar(c);
    if (c==' '){
        for(int p=i;p>=k;p--){
            Sleep(120);
    MOVE_CURSOR_BACK();
    CLEAR_CURRENT_CHAR();
    if(p==k){
        k=i;
        system("color 0");

    }
    }
    
    }
   





  }

system("cls");
printf("\n\n\n                         %.52s",name1);
sleep(5);
system("cls");
  
}
bool admin_verify(){

int k;

int p=1,o=0;
for(int i=0;p;i++){
system("cls");
printf("%s \n",WELCOME_MESSAGE);
printf("Max wrong attempt (%d)/(3)",o);
printf("\nEnter Pin : ");
scanf("%d",&k);


if(k==PASS){
    p=0;
    return true;
}
if(o==3){
    printf("No more attempt remain . try again");
    p=0;
    return false;
}

o++;
}



    return false;


}





