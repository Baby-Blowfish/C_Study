#include<stdio.h>

int main(void)
{
  int a;
  int age;
  double height;
  char grade;
  char name[20];

  // scanf("%d",&a);
  // printf("input value : %d\n",a);

  // printf("input age and height : ");
  // scanf("%d %lf",&age, &height);
  // printf("age is %d and height is %.1lf\n",age,height);

  printf("input score : ");
  scanf("%c",&grade);
  printf("input name : ");
  scanf("%s",name);
  printf("score is %c and name is %s\n",grade,name);

  return 0;
}