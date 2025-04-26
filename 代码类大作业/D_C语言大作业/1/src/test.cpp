#include <stdio.h>
#include <stdlib.h>
struct student
{
 char name[20];
 int score[4];
};
typedef struct student student;
void count()
{
 student st;
 FILE *fp1,*fp2;
 int i=0;
 float sum1=0,sum2=0,sum3=0,sum4=0,sum5=0;
 fp1=fopen("./src/zy.dat","rb");
 if(!fp1)
 {
  printf("cann't create file\n");
  exit(0);
 }
 fp2=fopen("./src/result.dat","wb");
 if(!fp2)
 {
  printf("cann't create file\n");
  exit(0);
 }
 while(fread(&st,sizeof(student),1,fp1)==1)
 {
  sum1+=st.score[0];
  sum2+=st.score[1];
  sum3+=st.score[2];
  sum4+=st.score[3];
  i++;
 }
 sum1/=(i*25);
 sum2/=(i*25);
 sum3/=(i*25);
 sum4/=(i*25);
 fprintf(fp2,"%f %f %f %f ",sum1,sum2,sum3,sum4);
 fclose(fp1);
 fclose(fp2);
}
int main()
{
 count(); 
 return 0; 
}