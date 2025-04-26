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

struct student//����
{
	char name[20];
	char num[10];
	char score[10];

};

typedef  struct Node//���
{
	struct student data;//����������
	struct Node* next;//����ָ����

}NODE, *LPNODE;//LPNODEΪָ��ṹ��NODE��ָ������


//������ͷ
LPNODE createList()
{
	//��������ʼ������
	LPNODE headNode = (LPNODE)malloc(sizeof(NODE));//����һ�鶯̬�ڴ棬����������ڴ�ĵ�ַ

	headNode->next = NULL;//ָ���ʼ��ָ��գ�ָ�����ÿ�
	return headNode;
}



//�������
LPNODE createNode(struct student data)
{
	struct Node*  node = (struct Node*)malloc(sizeof(struct Node));
	node->data = data;
	node->next = NULL;
	return node;
}

//����һ������
LPNODE list = createList();//�������洢������Ϣ




//=========================================¼�롢����====================================

//������:��ͷ���뷨:��������newNode����������ݣ�data
void insertNodeByHead(struct Node *list, struct student data)
{
	//����ǰ���ȴ�������Ľ��
	struct Node* newNode = createNode(data);
	newNode->next = list->next;
	list->next = newNode;
}



void printexcel()//������
{
	for (int i = 0; i < 2; i++)//����Ϣ��
	{
		setlinecolor(RED);//��ɫ
		rectangle(430, 180+i*40,910,220+i*40 );
	}
}


//ѧ������ϵͳ��¼����Ϣ
void addStudentInfo(LPNODE list)
{
	struct student data;
	
		printexcel();
	//����line
		line(590, 180, 590, 260);
		line(750,180,750, 260);
	//����
		settextstyle(20, 0, "consolas");	//consolas����
		outtextxy(450, 190, "����");
		outtextxy(610, 190, "ѧ��");
		outtextxy(776, 190, "�÷�");

	//������outsetxy

		Sleep(200);
	InputBox(data.name, 10, "������name:");
	outtextxy(450, 230, data.name);

	InputBox(data.num, 10, "������num:");
	outtextxy(620, 230, data.num);

	InputBox(data.score, 10, "������score:");
	outtextxy(786, 230, data.score);

	insertNodeByHead(list, data);
	outtextxy(610, 290, "loading...");
	Sleep(500);
	outtextxy(610, 320, "����ɹ�");
	Sleep(500);
}






//=========================================����==========================================


//����:��ѧ�Ų���
LPNODE searchNodeByNum(LPNODE list, char *searchNum)
{
	LPNODE p = list;
	LPNODE pNext = p->next;
	while (pNext != NULL && strcmp(pNext->data.num, searchNum))			//strcmp(str1,str2)�Ƚ������ַ��� ��str1==str2���򷵻���
	{
		p = pNext;
		pNext = p->next;
	}
	if(pNext != NULL)
		return pNext;	
	return NULL;
	
}


void searchInfoByNum()//����
{
	printexcel();

	char searchNum[20] = "";
	outtextxy(450, 190, "������Ҫ���ҵ�ѧ�ţ�");
	int s = 0;
	int ch;
	int startX = 720;
		//�����ڲ�����
	while ((ch = _getch()) != 13)
	{
		outtextxy(startX, 190, ch);//���û���������ִ�ӡ
		startX += 13;
		searchNum[s++] = ch;
	}
		//�ַ����ַ����Ĵ���  ��Ҫ'\0';
	searchNum[s] = '\0';

	if (searchNodeByNum(list, searchNum) ==NULL)
	{
		outtextxy(550, 290, "���޴���");
			//���س��ص����˵�
		outtextxy(470, 320, "����Enter���������˵�");
		while ((ch = _getch()) != 13);//��ȡ�ļ������ڻس���������һֱ��ѭ��
		return;
	}
	else
	{
		outtextxy(450, 230, "������");
		outtextxy(520, 230, searchNodeByNum(list, searchNum)->data.name);
		outtextxy(610, 230, "ѧ�ţ�");
		outtextxy(680, 230, searchNodeByNum(list, searchNum)->data.num);
		outtextxy(776, 230, "������");
		outtextxy(846, 230, searchNodeByNum(list, searchNum)->data.score);

			//���س��ص����˵�
		outtextxy(610, 320, "����Enter���ص����˵�");
		while ((ch = _getch()) != 13);
		return;
	}

}

//==========================================�޸�==============================================

void judgeuseKeyHit(char *searchNum);//�������ж������λ�ã�������Ϣ�޸�


void modifyInfoByHit()//�޸�
{
//	struct student data;

	printexcel();

	char searchNum[20] = "";
	outtextxy(450, 150, "������Ҫ�޸ĵ�ѧ��:");
	int s = 0;
	int ch;
	int startX = 720;
		//�����ڲ�����
	while ((ch = _getch()) != 13)
	{
		outtextxy(startX, 150, ch);//���û���������ִ�ӡ
		startX += 13;
		searchNum[s++] = ch;
	}
		//�ַ����ַ����Ĵ���  ��Ҫ'\0';
	searchNum[s] = '\0';
	if (searchNodeByNum(list, searchNum) ==NULL)
	{
		outtextxy(550, 290, "���޴���");
			//���س��ص����˵�

		outtextxy(470, 320, "����Enter���������˵�");
		while ((ch = _getch()) != 13);//��ȡ�ļ������ڻس�������һֱ��ѭ��
		return;
	}
	else
	{
		outtextxy(430, 230, "������");
		outtextxy(500, 230, searchNodeByNum(list, searchNum)->data.name);
		outtextxy(610, 230, "ѧ�ţ�");
		outtextxy(680, 230, searchNodeByNum(list, searchNum)->data.num);
		outtextxy(776, 230, "������");
		outtextxy(846, 230, searchNodeByNum(list, searchNum)->data.score);


		line(590, 220, 590, 260);
		line(750,220,750, 260);
		outtextxy(450, 190, "����Ҫ�޸ĵ���Ϣ��");

		judgeuseKeyHit(searchNum);//�ж��û�������Ϣ���޸ĺ�return

		outtextxy(610, 290, "loading...");
		Sleep(500);
		outtextxy(610, 320, "�޸ĳɹ�");
					
		outtextxy(570, 350, "����Enter���ص����˵�");
		while ((ch = _getch()) != 13);	//���س��ص����˵�
		return;
	
	}

}


void judgeuseKeyHit(char *searchNum)//�ж������λ�ã�������Ϣ�޸�
{
//	int ch;
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
			case WM_LBUTTONDOWN://������ָ������
				if(m.x > 440 && m.x <580 && m.y>230 && m.y < 250)
				{
					InputBox(searchNodeByNum(list, searchNum)->data.name, 10, "�������޸ĺ��name:");
				}
				else if(m.x > 590 && m.x <740 && m.y>230 && m.y < 250)
				{
					InputBox(searchNodeByNum(list, searchNum)->data.num, 10, "�������޸ĺ��num:");			
				}
				else if(m.x > 750 && m.x <910 && m.y>230 && m.y < 250)
				{
					InputBox(searchNodeByNum(list, searchNum)->data.score, 10, "�������޸ĺ��score:");
				}
					
			return;	//�˳�����

		}
		
	}

}






//==========================================ɾ��======================================================

//ɾ����Ϣ
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
	printexcel();//�����

	char searchNum[20] = " ";
	outtextxy(450, 190, "������Ҫɾ����ѧ��:");
	int w = 0;
	char ch;	
	int startX = 720;

	while ((ch = _getch()) != 13)
	{
		outtextxy(startX, 190, ch);
		startX += 13;
		searchNum[w++] = ch;
	}
	//�ַ����ַ����Ĵ���  ��Ҫ'\0';
	searchNum[w] = '\0';


	if (searchNodeByNum(list, searchNum) != NULL)
	{
		deleteNodeByNum(list, searchNum);

		//���س��ص����˵�
		outtextxy(610, 320, "ɾ���ɹ���");
		outtextxy(570, 350, "����Enter���ص����˵�");

		while ((ch = _getch()) != 13);
		return;		
	}
	else
	{
	outtextxy(550, 290, "���޴���");
			//���س��ص����˵�

		outtextxy(470, 320, "����Enter���������˵�");
		while ((ch = _getch()) != 13);
		return;
	}
}


//======================================���====================================
void printStudentInfo(LPNODE list)
{
	int ch;

	if (list->next == NULL)
	{
		settextcolor(RED);
		outtextxy(550, 250, "������Ϣ�������");
		//���س����ص����˵�
		outtextxy(510, 290,"����Enter���������˵�");
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
		outtextxy(450, 170, "����:");
		outtextxy(613, 170, "ѧ��:");
		outtextxy(776, 170, "����:");
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
		outtextxy(100, 450, "����Enter����ص����˵�");
		while ((ch = _getch()) != 13);
			return;
	}
}


//=======================================����==============================================

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
	outtextxy(460, 225, "����ɹ�");
	
	fclose(fp);

}




//=======================================����==============================================


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
		outtextxy(470, 225, "������...\n");
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
	outtextxy(460, 265, "����ɹ�\n");
	fclose(fp);
	Sleep(200);

}



//===================================��¼����=============================

void Login()//��¼
{
	char account[20]="";

	loadimage(&login, _T("IMAGE"), _T("LoginInterface"),1000, 550);

	putimage(0, 0, &login);

	setbkmode(TRANSPARENT);//��������͸��



	settextstyle(18, 0, "���Ŀ���");//˵������
	setcolor(BLUE);
	outtextxy(755 , 190, "��¼˵����");
	outtextxy(755 , 210, "�����˺�");
	outtextxy(755 , 230, "����˺ź��س�");
	outtextxy(755 , 250, "���������س�");//˵��



	settextstyle(15, 0, "consoals");
	setcolor(WHITE);
	outtextxy(450, 455, "2018��10��\n");

	settextstyle(20, 0, "consoals");



	MOUSEMSG m;
	while (1)
	{
		int i= 0;
		int ch;//�û�������
		int startX = 333;//���ֵ�x����
	//	outtextxy(400 ,375,"������->");

		m = GetMouseMsg();
		switch (m.uMsg)
		{		
			case WM_LBUTTONDOWN://������ָ������

				PlaySound("res/���1.wav", NULL, SND_SYNC | SND_FILENAME | SND_ASYNC);

				if(m.x > 325 && m.x <660 && m.y>210 && m.y < 250)//���˺�
				{	
					setcolor(WHITE);
					rectangle(330 ,212 ,660 , 250);
					fillrectangle(330 ,212 ,660 , 250);//���׿�

					setcolor(BLACK);
					outtextxy(startX, 224, "|");//����ɫ���
				
					while (i<15)//���벻�ó���15
					{					
						setcolor(WHITE);
						Sleep(90);
						outtextxy(startX, 224, "|");//���Ǻ�ɫ�Ĺ��

						setcolor(BLACK);
						if((ch = _getch()) == 13)//�û�����س���return���˳�����
						{
								PlaySound("res/���1.wav", NULL, SND_SYNC | SND_FILENAME | SND_ASYNC);

							account[i] = '\0';						
							return;
						}
							PlaySound("res/���1.wav", NULL, SND_SYNC | SND_FILENAME | SND_ASYNC);

						outtextxy(startX, 224, ch);//��ӡ�û�����

						startX += 13;
						account[i++] = ch;//�ƶ�x���꣬������ӡ�¸��û�����

						outtextxy(startX, 224, "|");//��ʾ��ɫ���						
					}
					setcolor(RED);//�������ȱ���
					outtextxy(666, 224, "���벻�ó���15���ַ���");
					Sleep(1600);
					closegraph();

				}					
		}
		
	}
}


void Login2()//��¼
{
	char password[20]="";

	setcolor(WHITE);//���׿�
	rectangle(330 ,290 ,660 , 330);
	fillrectangle(330 ,290 ,660 ,330);

	MOUSEMSG m;
	while (1)
	{
		int i= 0;
		int ch;//�û�������
		int startX = 333;

		m = GetMouseMsg();
		
		
		setbkmode(TRANSPARENT);
		settextstyle(20, 0, "consoals");
		setcolor(BLACK);
		while (i<15)
		{
			if((ch = _getch()) == 13)//�û�����س���return���˳�����
			{
					PlaySound("res/���1.wav", NULL, SND_SYNC | SND_FILENAME | SND_ASYNC);
				password[i] = '\0';
				return;
			}
			outtextxy(startX, 300, ch);//��ӡ�û�����
				PlaySound("res/���1.wav", NULL, SND_SYNC | SND_FILENAME | SND_ASYNC);
			Sleep(150);

			setcolor(WHITE);//���׿������û�����,��*��������
			rectangle(startX, 300,startX+10, 330);
			fillrectangle(startX, 300,startX+10, 330);
			setcolor(BLACK);
			outtextxy(startX, 300, "*");

			startX += 13;
			password[i++] = ch;	
		}
		setcolor(RED);
		outtextxy(666, 300, "���벻�ó���15���ַ���");
		Sleep(1500);
		closegraph();
	
	}
}




//===============================================================================================

//�˵�����
void studentSystemWindow()
{
	//���ŵķ�ʽ����ͼƬ

	loadimage(&bkImage, _T("IMAGE"), _T("bkimage"),1000, 550);
	loadimage(&bkImage2, _T("IMAGE"), _T("blank"),1000, 550);
	loadimage(&add, _T("IMAGE"), _T("add"),1000, 550);
	loadimage(&search, _T("IMAGE"), _T("search"),1000, 550);
	loadimage(&modify, _T("IMAGE"), _T("modify"),1000, 550);
	loadimage(&print, _T("IMAGE"), _T("print"),1000, 550);


	putimage(0, 0, &bkImage);
	setbkmode(TRANSPARENT);
	setcolor(WHITE);
	settextstyle(20, 0, "consolas");//consolas����
	outtextxy(460, 455, "2018��10��\n");

	settextcolor(RGB(0, 0, 255));

	
//	settextstyle(25, 0, "���Ŀ���");

}

//�û�����...����+���



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
					//¼����Ϣ
						Sleep(300);
					putimage(0, 0, &add);
					addStudentInfo(list);
					
				}
				else if (m.x > 180 && m.x < 250 && m.y>200 && m.y < 250)
				{
					rectangle(165,185,270,285);
					//������Ϣ	
					Sleep(300);
				
					putimage(0, 0, &search);
					searchInfoByNum();			
				}
				else if (m.x > 300 && m.x < 380 && m.y>200 && m.y < 250)
				{
					//�޸���Ϣ
					rectangle(290,185,400,285);
					Sleep(300);
					putimage(0, 0, &modify);
					modifyInfoByHit();
								
				}
				else if (m.x > 440 && m.x <510 && m.y>200 && m.y < 250)
				{
					//ɾ����Ϣ
					rectangle(420,185,530,285);
						Sleep(300);
					putimage(0, 0, &bkImage2);
					deleteInfoByNum();				
				}
				else if (m.x >  570 && m.x <640 && m.y>200 && m.y < 250)
				{
					//�����Ϣ
				
					rectangle(545,185,660,285);
					Sleep(300);
					putimage(0, 0, &print);
					printStudentInfo(list);			
				}
				else if (m.x > 700 && m.x < 770 && m.y>200 && m.y < 250)
				{
					//������Ϣ
					setcolor(BLUE);
					rectangle(675,185,790,285);
					Sleep(300);
					putimage(0, 0, &bkImage2);	
					save();
				}
				else if (m.x > 830 && m.x < 900 && m.y>200 && m.y < 250)
				{
					//������Ϣ			
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