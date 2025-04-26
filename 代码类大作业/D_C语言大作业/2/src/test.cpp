#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *fp1,*fp2;
	if((fp1=fopen("./src/in.txt","r"))==NULL)
	{
		printf("fail file.\n");
		exit(0);
	}
	if((fp2=fopen("./src/out.txt","w"))==NULL)
	{
		printf("fail creat.\n");
		exit(0);
	}
	int st,a,i = 0,j;
	while(fscanf(fp1,"%d",&st)==1)
	{
		if(st==2)
		{
			i++;
			continue;
		}
		int f=1;
		for(j=2;j*j<=st;j++)
		{
			if(st%j==0)
			{
				f=0;
				break;
			}
		}
		if(f)
			i++;
	}
	fclose(fp1);
	fprintf(fp2,"%d",i);
	fclose(fp2);
	return 0;
}
