#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct xx{
	char bh[100];
	char mc[100];
	char lyr[100];
	char bm[100];
	char sl[100];
	char sj[100];
	char jg[100];
};       //规定一个结构体包括设备编号、设备名称等数据
typedef struct xx xx;
int main(){
	int i,j=0,z=0;
	xx stu[100];
	FILE *fp1;
	if((fp1=fopen("设备信息.txt","r+"))==NULL)
	{
		printf("can't open this file.\n");
		exit(0);
	}//导入文本信息
	 printf("请输入所需功能前的编号：\n");
	 printf("1.信息浏览\n");
	 printf("2.设备查询\n");
	 printf("3.设备更新\n");
	 printf("4.设备删除\n");
	 printf("5.设备排序(按价格)\n");
	 printf("6.退出程序\n");//对所需实现的功能进行分组 
	 while(fscanf(fp1,"%s %s %s %s %s %s %s",stu[j].bh,stu[j].mc,
	 stu[j].lyr,stu[j].bm,
	 stu[j].sl,stu[j].sj,
	 stu[j].jg)==7)
	 j++;
	 while(scanf("%d",&i)==1 && i!=6){
	 int flag=0;	
	 
	 switch(i){
	 
	 case 1:
	 	printf("编号      名称      领用人      部门        数量                时间        价格\n");
	 	for(int count=0;count<j;count++){
		 
	 	printf("%s %10s %10s %10s %10s %20s %10s\n",
		 stu[count].bh,
		 stu[count].mc,
		 stu[count].lyr,
		 stu[count].bm,
		 stu[count].sl,
		 stu[count].sj,
		 stu[count].jg);
	}
	     printf("请再次输入所需功能前的编号：\n");
	     printf("1.信息浏览\n");
	 printf("2.设备查询\n");
	 printf("3.设备更新\n");
	 printf("4.设备删除\n");
	 printf("5.设备排序(按价格)\n");
	 printf("6.退出程序\n");
	 	break;
	 	
	case 2:
		char a[100];
		printf("请输入你要查询的编号或名称:\n"); 
		scanf("%s",a);
		getchar();
		for(int h=0;h<j;h++){
			if(strcmp(a,stu[h].mc)==0 || strcmp(a,stu[h].bh)==0 ){
				printf("编号      名称      领用人      部门        数量                时间        价格\n");
				printf("%s %10s %10s %10s %10s %20s %10s\n",
		        stu[h].bh,
		        stu[h].mc,
		        stu[h].lyr,
		        stu[h].bm,
		        stu[h].sl,
		        stu[h].sj,
		        stu[h].jg);
		        flag=1;
				}
			}
			if(flag==0){
				printf("对应的编号或名称不存在\n");
			}
			printf("请再次输入所需功能前的编号：\n");
			printf("1.信息浏览\n");
	 printf("2.设备查询\n");
	 printf("3.设备更新\n");
	 printf("4.设备删除\n");
	 printf("5.设备排序(按价格)\n");
	 printf("6.退出程序\n");
			break;
			
	case 3:
	xx st;
	printf("请输入你要添加的设备信息（每个信息之间添加一空格）:\n");
	printf("编号      名称      领用人      部门        数量                时间        价格\n");
	scanf("%s %s %s %s %s %s %s",st.bh,
	st.mc,
	st.lyr,
	st.bm,
	st.sl,
	st.sj,
	st.jg);
	for(int h=0;h<j;h++){
			if(strcmp(st.mc,stu[h].mc)==0 || strcmp(st.bh,stu[h].bh)==0 ){
				printf("输入的设备编号或名称已存在，无法更新\n");
				flag=1;
			}
		}
	if(flag==0){
	fprintf(fp1,"%s %s %s %s %s %s %s\n",
	st.bh,
	st.mc,
	st.lyr,
	st.bm,
	st.sl,
	st.sj,
	st.jg); 
	printf("新的设备信息已添加完毕\n");
	 }
	printf("请再次输入所需功能前的编号：\n");
	printf("1.信息浏览\n");
	 printf("2.设备查询\n");
	 printf("3.设备更新\n");
	 printf("4.设备删除\n");
	 printf("5.设备排序(按价格)\n");
	 printf("6.退出程序\n");
	break;
		
	case 4:
		printf("请输入想要删除的设备的编号或名称：\n");
		FILE *fp2;
		if((fp2=fopen("设备信息1.txt","w+"))==NULL)
	{
		printf("can't open this file.\n");
		exit(0);
	    }
	    char b[100];
	    scanf("%s",b);
		getchar();
		for(int i=0;i<j;i++){
			if(strcmp(b,stu[i].mc)!=0 && strcmp(b,stu[i].bh)!=0 ){
				fprintf(fp2,"%s %s %s %s %s %s %s\n",
				stu[i].bh,
	            stu[i].mc,
	            stu[i].lyr,
	            stu[i].bm,
	            stu[i].sl,
	            stu[i].sj,
	            stu[i].jg); 
			}
			else
			flag=1;
		}
		if(flag==0){
			printf("未找到想要删除的相关设备\n");
			remove("设备信息1.txt");
		}
		else{
		
		fclose(fp1);
		fclose(fp2);
		remove("设备信息.txt");  
        rename("设备信息1.txt", "设备信息.txt");  
        printf("您以成功删除相应信息\n");
    }
        printf("请再次输入所需功能前的编号：\n");
        printf("1.信息浏览\n");
	 printf("2.设备查询\n");
	 printf("3.设备更新\n");
	 printf("4.设备删除\n");
	 printf("5.设备排序(按价格)\n");
	 printf("6.退出程序\n");
        break;
        
    case 5:
    	FILE *fp3;
		if((fp3=fopen("设备信息2.txt","w+"))==NULL)
	{
		printf("can't open this file.\n");
		exit(0);
	    }
	    for(int x=0;x<j-1;x++){
	    	for(int y=x+1;y<j;y++){
	    		if(atoi(stu[x].jg)<atoi(stu[y].jg)){
	    			xx st;
	    			st=stu[y];
	    			stu[y]=stu[x];
	    			stu[x]=st;
				}
			}
		}
		while(z<j){
			fprintf(fp3,"%s %s %s %s %s %s %s\n",
				stu[z].bh,
	            stu[z].mc,
	            stu[z].lyr,
	            stu[z].bm,
	            stu[z].sl,
	            stu[z].sj,
	            stu[z].jg); 
	            z++;
		}
		fclose(fp1);
		fclose(fp3);
		remove("设备信息.txt");  
        rename("设备信息2.txt", "设备信息.txt"); 
        printf("您以成功将数据按价格进行排序（由大到小）\n");
        printf("请再次输入所需功能前的编号：\n");
        printf("1.信息浏览\n");
	 printf("2.设备查询\n");
	 printf("3.设备更新\n");
	 printf("4.设备删除\n");
	 printf("5.设备排序(按价格)\n");
	 printf("6.退出程序\n");
        break;
    	
	    
	default:
		printf("您输入的数字无效\n"); 
		printf("请再次输入所需功能前的编号：\n");
		break;
	}
}
	 fclose(fp1);
     printf("感谢您的使用，程序已关闭\n");
	 return 0;
} 
