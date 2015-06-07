#include<stdio.h>
int main()
{
int f1,f2,fs,m;
float i1,i2,is,cm;
printf("enter first distance\n");
scanf("%d%f",&f1,&i1);

printf("enter second distance\n");
scanf("%d%f",&f2,&i2);
is=i1+i2;
fs=f1+f2;
if(is>=12)
{
fs++;
is-=12;
}
cm=(is+fs*12)*2.54;
m=cm/100;
cm=cm-m*100;
printf("distance in %dmetres %fcentimetres",m,cm);
return 0;
}
