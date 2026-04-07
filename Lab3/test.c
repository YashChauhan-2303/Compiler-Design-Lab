#include<stdio.h>
#incude<stdlib.h>
int main(){
int i;
/* This is the test input
You maybe asked to modify*/
char msg[]="Done";
int d = 1;
for(i=1; i<=10; i++){       //Loop
if(i%2==0 && !d){               //Decision
printf("%d is Even\n",i);

} else {
printf("%d is Odd\n",i);
d-=1;
}
}
printf("%s",msg);
return 0;
}