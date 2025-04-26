#include<stdio.h>
#include<graphics.h>
#include<malloc.h>
#include<string.h>
#include<conio.h>
#include<windows.h>

#include<mmsystem.h>
#pragma comment(lib,"WINMM.LIB")

/*#define Wideth 1000
#define High 550*/

IMAGE bkImage;
IMAGE bkImage2;
IMAGE add;
IMAGE modify;
IMAGE search;
IMAGE print;
IMAGE login;

struct student//数据
{
	char name[20];
	char num[10];
	char score[10];

};

typedef  struct Node//结点
{
	struct student data;//结点的数据域
	struct Node* next;//结点的指针域

}NODE, *LPNODE;//LPNODE为指向结构体NODE的指针类型


//创建表头
LPNODE createList()
{
	//创建、初始化过程
	LPNODE headNode = (LPNODE)malloc(sizeof(NODE));//申请一块动态内存，并返回这块内存的地址

	headNode->next = NULL;//指针初始化指向空，指针域置空
	return headNode;
}



//创建结点
LPNODE createNode(struct student data)
{
	struct Node*  node = (struct Node*)malloc(sizeof(struct Node));
	node->data = data;
	node->next = NULL;
	return node;
}

//创建一个链表
LPNODE list = createList();//创建表，存储数据信息




//=========================================录入、插入====================================

//插入结点:表头插入法:插入链表newNode，插入的数据：data
void insertNodeByHead(struct Node *list, struct student data)
{
	//插入前首先创建插入的结点
	struct Node* newNode = createNode(data);
	newNode->next = list->next;
	list->next = newNode;
}



void printexcel()//画表格框
{
	for (int i = 0; i < 2; i++)//画信息框
	{
		setlinecolor(RED);//红色
		rectangle(430, 180+i*40,910,220+i*40 );
	}
}


//学生管理系统的录入信息
void addStudentInfo(LPNODE list)
{
	struct student data;
	
		printexcel();
	//划线line
		line(590, 180, 590, 260);
		line(750,180,750, 260);
	//填字
		settextstyle(20, 0, "consolas");	//consolas字体
		outtextxy(450, 190, "姓名");
		outtextxy(610, 190, "学号");
		outtextxy(776, 190, "得分");

	//弹出框outsetxy

		Sleep(200);
	InputBox(data.name, 10, "请输入name:");
	outtextxy(450, 230, data.name);

	InputBox(data.num, 10, "请输入num:");
	outtextxy(620, 230, data.num);

	InputBox(data.score, 10, "请输入score:");
	outtextxy(786, 230, data.score);

	insertNodeByHead(list, data);
	outtextxy(610, 290, "loading...");
	Sleep(500);
	outtextxy(610, 320, "保存成功");
	Sleep(500);
}






//=========================================查找==========================================


//查找:按学号查找
LPNODE searchNodeByNum(LPNODE list, char *searchNum)
{
	LPNODE p = list;
	LPNODE pNext = p->next;
	while (pNext != NULL && strcmp(pNext->data.num, searchNum))			//strcmp(str1,str2)比较两个字符串 若str1==str2，则返回零
	{
		p = pNext;
		pNext = p->next;
	}
	if(pNext != NULL)
		return pNext;	
	return NULL;
	
}


void searchInfoByNum()//查找
{
	printexcel();

	char searchNum[20] = "";
	outtextxy(450, 190, "请输入要查找的学号：");
	int s = 0;
	int ch;
	int startX = 720;
		//不等于不换行
	while ((ch = _getch()) != 13)
	{
		outtextxy(startX, 190, ch);//对用户输入的数字打印
		startX += 13;
		searchNum[s++] = ch;
	}
		//字符到字符串的处理  主要'\0';
	searchNum[s] = '\0';

	if (searchNodeByNum(list, searchNum) ==NULL)
	{
		outtextxy(550, 290, "查无此人");
			//按回车回到主菜单
		outtextxy(470, 320, "按下Enter键返回主菜单");
		while ((ch = _getch()) != 13);//获取的键不等于回车键，让他一直死循环
		return;
	}
	else
	{
		outtextxy(450, 230, "姓名：");
		outtextxy(520, 230, searchNodeByNum(list, searchNum)->data.name);
		outtextxy(610, 230, "学号：");
		outtextxy(680, 230, searchNodeByNum(list, searchNum)->data.num);
		outtextxy(776, 230, "分数：");
		outtextxy(846, 230, searchNodeByNum(list, searchNum)->data.score);

			//按回车回到主菜单
		outtextxy(610, 320, "按下Enter键回到主菜单");
		while ((ch = _getch()) != 13);
		return;
	}

}

//==========================================修改==============================================

void judgeuseKeyHit(char *searchNum);//函数，判断鼠标点击位置，进行信息修改


void modifyInfoByHit()//修改
{
//	struct student data;

	printexcel();

	char searchNum[20] = "";
	outtextxy(450, 150, "请输入要修改的学号:");
	int s = 0;
	int ch;
	int startX = 720;
		//不等于不换行
	while ((ch = _getch()) != 13)
	{
		outtextxy(startX, 150, ch);//对用户输入的数字打印
		startX += 13;
		searchNum[s++] = ch;
	}
		//字符到字符串的处理  主要'\0';
	searchNum[s] = '\0';
	if (searchNodeByNum(list, searchNum) ==NULL)
	{
		outtextxy(550, 290, "查无此人");
			//按回车回到主菜单

		outtextxy(470, 320, "按下Enter键返回主菜单");
		while ((ch = _getch()) != 13);//获取的键不等于回车键，则一直死循环
		return;
	}
	else
	{
		outtextxy(430, 230, "姓名：");
		outtextxy(500, 230, searchNodeByNum(list, searchNum)->data.name);
		outtextxy(610, 230, "学号：");
		outtextxy(680, 230, searchNodeByNum(list, searchNum)->data.num);
		outtextxy(776, 230, "分数：");
		outtextxy(846, 230, searchNodeByNum(list, searchNum)->data.score);


		line(590, 220, 590, 260);
		line(750,220,750, 260);
		outtextxy(450, 190, "请点击要修改的信息：");

		judgeuseKeyHit(searchNum);//判断用户鼠标的信息，修改后return

		outtextxy(610, 290, "loading...");
		Sleep(500);
		outtextxy(610, 320, "修改成功");
					
		outtextxy(570, 350, "按下Enter键回到主菜单");
		while ((ch = _getch()) != 13);	//按回车回到主菜单
		return;
	
	}

}


void judgeuseKeyHit(char *searchNum)//判断鼠标点击位置，进行信息修改
{
//	int ch;
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
			case WM_LBUTTONDOWN://左键点击指定区域
				if(m.x > 440 && m.x <580 && m.y>230 && m.y < 250)
				{
					InputBox(searchNodeByNum(list, searchNum)->data.name, 10, "请输入修改后的name:");
				}
				else if(m.x > 590 && m.x <740 && m.y>230 && m.y < 250)
				{
					InputBox(searchNodeByNum(list, searchNum)->data.num, 10, "请输入修改后的num:");			
				}
				else if(m.x > 750 && m.x <910 && m.y>230 && m.y < 250)
				{
					InputBox(searchNodeByNum(list, searchNum)->data.score, 10, "请输入修改后的score:");
				}
					
			return;	//退出函数

		}
		
	}

}






//==========================================删除======================================================

//删除信息
int deleteNodeByNum(LPNODE list,char* searchNum)
{
	LPNODE p = list;
	LPNODE pNext = p->next;
	while (pNext != NULL && strcmp(pNext->data.num, searchNum))
	{
		p = pNext;
		pNext = p->next;
	}
	if (pNext == NULL)
		return 0;
	else
	{
		p->next = pNext->next;
		free(pNext);
		return 1;
	}
}

void deleteInfoByNum()
{
	printexcel();//画表格

	char searchNum[20] = " ";
	outtextxy(450, 190, "请输入要删除的学号:");
	int w = 0;
	char ch;	
	int startX = 720;

	while ((ch = _getch()) != 13)
	{
		outtextxy(startX, 190, ch);
		startX += 13;
		searchNum[w++] = ch;
	}
	//字符到字符串的处理  主要'\0';
	searchNum[w] = '\0';


	if (searchNodeByNum(list, searchNum) != NULL)
	{
		deleteNodeByNum(list, searchNum);

		//按回车回到主菜单
		outtextxy(610, 320, "删除成功！");
		outtextxy(570, 350, "按下Enter键回到主菜单");

		while ((ch = _getch()) != 13);
		return;		
	}
	else
	{
	outtextxy(550, 290, "查无此人");
			//按回车回到主菜单

		outtextxy(470, 320, "按下Enter键返回主菜单");
		while ((ch = _getch()) != 13);
		return;
	}
}


//======================================浏览====================================
void printStudentInfo(LPNODE list)
{
	int ch;

	if (list->next == NULL)
	{
		settextcolor(RED);
		outtextxy(550, 250, "暂无信息，请添加");
		//按回车键回到主菜单
		outtextxy(510, 290,"按下Enter键返回主菜单");
		while ((ch = _getch()) != 13);
		return;
	}
	else
	{
		fillrectangle(430, 160, 910, 480);
		for (int i = 0;i < 8; i++)
		{
			setlinecolor(RED);
			rectangle(430, 160+i*40,910,200+i*40 );
		}

		line(590, 160, 590, 480);
		line(750,160, 750, 480);
		outtextxy(450, 170, "姓名:");
		outtextxy(613, 170, "学号:");
		outtextxy(776, 170, "分数:");
		int excelWidth = 0;
		LPNODE p = list->next;
		while (p)
		{
			outtextxy(450, 210 + excelWidth, p->data.name);
			outtextxy(610, 210 + excelWidth, p->data.num);
			outtextxy(776, 210 + excelWidth, p->data.score);
			p=p->next;
			excelWidth += 40;
		}
		outtextxy(100, 450, "按下Enter键后回到主菜单");
		while ((ch = _getch()) != 13);
			return;
	}
}


//=======================================保存==============================================

void save()
{
	FILE *fp;
	LPNODE pr = list->next;
	if((fp = fopen("student.txt","w")) == NULL)
	{
			outtextxy(470, 320, "can not open file\n");
		
		return;
	}

	while(pr)
	{

		fwrite(pr,sizeof(Node),1,fp);
		pr=pr->next;

	}
	outtextxy(460, 225, "保存成功");
	
	fclose(fp);

}




//=======================================载入==============================================


void load()
{
	FILE *fp;
	LPNODE p;
	LPNODE pr;
	pr=list;


	if((fp = fopen("student.txt","r")) == NULL)
	{
		outtextxy(470, 320, "can not open file\n");
		Sleep(200);
	return ;
	}

	while(!feof(fp))
	{
		p=(Node *)malloc(sizeof(Node)); 
		outtextxy(470, 225, "载入中...\n");
			Sleep(200);
		if(!p)
		{
			outtextxy(470, 280, "memory malloc fail\n");
			Sleep(200);
			return;
		}

		if(fread(p,sizeof(Node),1,fp)!=1)

		break;
		else
		{
			if (list == NULL)
			{
				list = p;
				pr = p;
				pr->next = NULL;
			}
			else
			{
				pr->next = p;
				pr = p;
				pr->next = NULL;
			}

		}
		
	}
	outtextxy(460, 265, "载入成功\n");
	fclose(fp);
	Sleep(200);

}



//===================================登录界面=============================

void Login()//登录
{
	char account[20]="";

	loadimage(&login, _T("IMAGE"), _T("LoginInterface"),1000, 550);

	putimage(0, 0, &login);

	setbkmode(TRANSPARENT);//设置字体透明



	settextstyle(18, 0, "华文楷体");//说明，字
	setcolor(BLUE);
	outtextxy(755 , 190, "登录说明：");
	outtextxy(755 , 210, "鼠标点账号");
	outtextxy(755 , 230, "输好账号后点回车");
	outtextxy(755 , 250, "输好密码后点回车");//说明



	settextstyle(15, 0, "consoals");
	setcolor(WHITE);
	outtextxy(450, 455, "2018年10月\n");

	settextstyle(20, 0, "consoals");



	MOUSEMSG m;
	while (1)
	{
		int i= 0;
		int ch;//用户的输入
		int startX = 333;//画字的x坐标
	//	outtextxy(400 ,375,"点这里->");

		m = GetMouseMsg();
		switch (m.uMsg)
		{		
			case WM_LBUTTONDOWN://左键点击指定区域

				PlaySound("res/鼠标1.wav", NULL, SND_SYNC | SND_FILENAME | SND_ASYNC);

				if(m.x > 325 && m.x <660 && m.y>210 && m.y < 250)//输账号
				{	
					setcolor(WHITE);
					rectangle(330 ,212 ,660 , 250);
					fillrectangle(330 ,212 ,660 , 250);//画白框

					setcolor(BLACK);
					outtextxy(startX, 224, "|");//画黑色光标
				
					while (i<15)//输入不得超过15
					{					
						setcolor(WHITE);
						Sleep(90);
						outtextxy(startX, 224, "|");//覆盖黑色的光标

						setcolor(BLACK);
						if((ch = _getch()) == 13)//用户输入回车则return，退出函数
						{
								PlaySound("res/鼠标1.wav", NULL, SND_SYNC | SND_FILENAME | SND_ASYNC);

							account[i] = '\0';						
							return;
						}
							PlaySound("res/鼠标1.wav", NULL, SND_SYNC | SND_FILENAME | SND_ASYNC);

						outtextxy(startX, 224, ch);//打印用户输入

						startX += 13;
						account[i++] = ch;//移动x坐标，继续打印下个用户输入

						outtextxy(startX, 224, "|");//显示黑色光标						
					}
					setcolor(RED);//超过长度报警
					outtextxy(666, 224, "输入不得超过15个字符！");
					Sleep(1600);
					closegraph();

				}					
		}
		
	}
}


void Login2()//登录
{
	char password[20]="";

	setcolor(WHITE);//画白框
	rectangle(330 ,290 ,660 , 330);
	fillrectangle(330 ,290 ,660 ,330);

	MOUSEMSG m;
	while (1)
	{
		int i= 0;
		int ch;//用户的输入
		int startX = 333;

		m = GetMouseMsg();
		
		
		setbkmode(TRANSPARENT);
		settextstyle(20, 0, "consoals");
		setcolor(BLACK);
		while (i<15)
		{
			if((ch = _getch()) == 13)//用户输入回车则return，退出函数
			{
					PlaySound("res/鼠标1.wav", NULL, SND_SYNC | SND_FILENAME | SND_ASYNC);
				password[i] = '\0';
				return;
			}
			outtextxy(startX, 300, ch);//打印用户输入
				PlaySound("res/鼠标1.wav", NULL, SND_SYNC | SND_FILENAME | SND_ASYNC);
			Sleep(150);

			setcolor(WHITE);//画白框隐藏用户输入,用*处理密码
			rectangle(startX, 300,startX+10, 330);
			fillrectangle(startX, 300,startX+10, 330);
			setcolor(BLACK);
			outtextxy(startX, 300, "*");

			startX += 13;
			password[i++] = ch;	
		}
		setcolor(RED);
		outtextxy(666, 300, "输入不得超过15个字符！");
		Sleep(1500);
		closegraph();
	
	}
}




//===============================================================================================

//菜单窗口
void studentSystemWindow()
{
	//缩放的方式加载图片

	loadimage(&bkImage, _T("IMAGE"), _T("bkimage"),1000, 550);
	loadimage(&bkImage2, _T("IMAGE"), _T("blank"),1000, 550);
	loadimage(&add, _T("IMAGE"), _T("add"),1000, 550);
	loadimage(&search, _T("IMAGE"), _T("search"),1000, 550);
	loadimage(&modify, _T("IMAGE"), _T("modify"),1000, 550);
	loadimage(&print, _T("IMAGE"), _T("print"),1000, 550);


	putimage(0, 0, &bkImage);
	setbkmode(TRANSPARENT);
	setcolor(WHITE);
	settextstyle(20, 0, "consolas");//consolas字体
	outtextxy(460, 455, "2018年10月\n");

	settextcolor(RGB(0, 0, 255));

	
//	settextstyle(25, 0, "华文楷体");

}

//用户处理...按键+鼠标



void userKeyDown()
{
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
			case WM_LBUTTONDOWN:

				setcolor(BLUE);
				if (m.x > 60 && m.x < 120 && m.y>200 && m.y < 250 )
				{
					
					rectangle(40,185,140,285);
					//录入信息
						Sleep(300);
					putimage(0, 0, &add);
					addStudentInfo(list);
					
				}
				else if (m.x > 180 && m.x < 250 && m.y>200 && m.y < 250)
				{
					rectangle(165,185,270,285);
					//查找信息	
					Sleep(300);
				
					putimage(0, 0, &search);
					searchInfoByNum();			
				}
				else if (m.x > 300 && m.x < 380 && m.y>200 && m.y < 250)
				{
					//修改消息
					rectangle(290,185,400,285);
					Sleep(300);
					putimage(0, 0, &modify);
					modifyInfoByHit();
								
				}
				else if (m.x > 440 && m.x <510 && m.y>200 && m.y < 250)
				{
					//删除消息
					rectangle(420,185,530,285);
						Sleep(300);
					putimage(0, 0, &bkImage2);
					deleteInfoByNum();				
				}
				else if (m.x >  570 && m.x <640 && m.y>200 && m.y < 250)
				{
					//浏览信息
				
					rectangle(545,185,660,285);
					Sleep(300);
					putimage(0, 0, &print);
					printStudentInfo(list);			
				}
				else if (m.x > 700 && m.x < 770 && m.y>200 && m.y < 250)
				{
					//保存信息
					setcolor(BLUE);
					rectangle(675,185,790,285);
					Sleep(300);
					putimage(0, 0, &bkImage2);	
					save();
				}
				else if (m.x > 830 && m.x < 900 && m.y>200 && m.y < 250)
				{
					//载入信息			
					rectangle(810,185,910,285);
					Sleep(300);
					putimage(0, 0, &bkImage2);	
					
					load();
				}

				Sleep(300);
				studentSystemWindow();	
				
				break;

			default:
				break;
		}
	}
}