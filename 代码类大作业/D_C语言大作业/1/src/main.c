#include <stdio.h>
#include <stdlib.h>
struct count
{
    int numbers[2];
};
typedef struct count count;
void plus()
{
    count ct;
    FILE *fp1,*fp2;
    int sum;
    fp1=fopen("./src/in.txt","r");
    if(!fp1)
    {
        exit(-1);
    }
    fp2=fopen("./src/out.txt","w");
    if(!fp2)
    {
        exit(-1);
    }
    if (fscanf(fp1, "%d %d", &ct.numbers[0], &ct.numbers[1]) != 2) {
        fclose(fp1);
        fclose(fp2);
        exit(-1);
    }

    sum = ct.numbers[0] + ct.numbers[1];

    fprintf(fp2, "%d", sum);

    fclose(fp1);
    fclose(fp2);
}
int main()
{
    plus();
    return 0;
}