#include<stdio.h>
#include<time.h>
#include<graphics.h>

//�����ȫ�ֱ���
int STACKSIZE = 5;//ͣ�������������
float price = 0.00055;//ÿ��ͣ���ļ۸�
int nUsersNum = 0;//ע����û���ţ���0��ʼ�� 
int nUsersFlag = 0;//�����ж��û��Ƿ��¼�ı�־����
int usersnum = 0;//�����¼���û����

//�궨��
#define USENUM 20000//����û���
#define STRLENGTH 30//�����û�������
#define NUMLENGTH 12//�������볤�� 

//�ṹ��
typedef struct node
{
	wchar_t plate[10];
	time_t start;
	time_t end;
}Car;//ÿ����
typedef struct Stack
{
	int top;
	Car* stack[6];
}SqStack;//ͣ������˳��ջ��
typedef struct qnode
{
	Car* data;
	struct qnode* next;
}QNode;
typedef struct Node
{
	QNode* front;
	QNode* rear;
	int num;
}LinkQueue;//����������У�
struct Users
{
	wchar_t szName[STRLENGTH];//�����û���
	wchar_t password1[NUMLENGTH];//�˻�����
	wchar_t password2[NUMLENGTH];//������������
	int nSerialNum;//�û����(��1��ʼ) 
}use[USENUM];//ÿ���û�

//���ص�ͼƬ
IMAGE welcome;
IMAGE welcome_button;
IMAGE startup;
IMAGE login;
IMAGE use_register;
IMAGE reset_password;
IMAGE park;
IMAGE parklot;
IMAGE parking;
IMAGE leaving;
IMAGE situation;
IMAGE users_exit;
IMAGE lot;
IMAGE cost;
IMAGE show;
//����������
void Welcome(FILE* fp, SqStack s, SqStack* temp, LinkQueue* q);
void SaveFile(FILE* fp);
void Select_MainMenu(FILE* fp, SqStack* s, SqStack* temp, LinkQueue* q);
void Login(FILE* fp);
void Register(FILE* fp);
void Reset_Password(FILE* fp);
void ParkingLot(FILE* fp, SqStack* s, SqStack* temp, LinkQueue* q);
SqStack* InitStack(SqStack* s);
int InitQueue(LinkQueue* Q);
void Parking(FILE* fp, SqStack* s, SqStack* temp, LinkQueue* q);
void Leaving(FILE* fp, SqStack* s, SqStack* temp, LinkQueue* q);
void Situation(FILE* fp, SqStack* s);
void Users_Exit(FILE* fp, SqStack* s, SqStack* temp, LinkQueue* q);

void Welcome(FILE* fp, SqStack* s, SqStack* temp, LinkQueue* q)
{
	loadimage(&welcome, L"C:/Users/Dragonborn/Desktop/Resources/welcome.png");
	putimage(0, 0, &welcome);//��ʾ��ӭ����
	//���������꽻��
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 739 && msg.x < 887 && msg.y > 395 && msg.y < 466)//������ض����򣬼�ENTER��ť��������
				{
					loadimage(&welcome_button, L"C:/Users/Dragonborn/Desktop/Resources/welcome_button.png");//���밴ťͼƬ
					putimage(0, 0, &welcome_button);//��ʾ��ťͼƬ
					Sleep(100);//��ʱ������CPUռ���ʣ������������Ч��
					Select_MainMenu(fp, s, temp, q);//����һ�����˵�ѡ���
				}
			}
		}
	}
}
void SaveFile(FILE* fp)//�����û���Ϣ
{
	fopen_s(&fp, "C:/Users/Dragonborn/Desktop/����/alldate.dat", "wb");
	//���ļ����ȫ�ֱ���
	fwrite(&nUsersNum, 4, 1, fp);
	fwrite(&nUsersFlag, 4, 1, fp);
	fwrite(&usersnum, 4, 1, fp);
	//����ṹ������
	for (int i = 0; i < nUsersNum; i++)
		fwrite(&use[i], sizeof(struct Users), 1, fp);
	fclose(fp);
}
void Select_MainMenu(FILE* fp, SqStack* s, SqStack* temp, LinkQueue* q)
{
	loadimage(&startup, L"C:/Users/Dragonborn/Desktop/Resources/startup.png");//�����ʼ����
	putimage(0, 0, &startup);//��ʾ��ʼ����
	MOUSEMSG msg;
	FlushMouseMsgBuffer();
	while (true)
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 138 && msg.x < 358 && msg.y > 191 && msg.y < 268)//�����"�û���¼"
					Login(fp);//�����û���¼����
				if (msg.x > 138 && msg.x < 358 && msg.y > 318 && msg.y < 398)//��������û�ע�ᡱ
					Register(fp);//�����û�ע�ắ��
				if (msg.x > 513 && msg.x < 736 && msg.y > 191 && msg.y < 268)//��������޸����롱
					Reset_Password(fp);//�����޸����뺯��
				if (msg.x > 513 && msg.x < 736 && msg.y > 318 && msg.y < 398)//�������ͣ��ϵͳ��
					ParkingLot(fp, s, temp, q);//����ͣ��������ϵͳ
			}
		}
	}
}
void Register(FILE* fp)
{
	loadimage(&use_register, L"C:/Users/Dragonborn/Desktop/Resources/use_register.png");
	putimage(0, 0, &use_register);
	int i;

	InputBox(use[nUsersNum].szName, 20, _T("�������û���"));//��ʾ�û������û���
	if (wcslen(use[nUsersNum].szName) < 2)
	{
		MessageBox(NULL, _T("�û���̫�̣�����������"), _T("�����˻�"), MB_ICONSTOP | MB_SETFOREGROUND);
	}
	else
	{
		//�����������û���Ϣ���е����ݣ��Ƚ���������û����Ƿ���ڣ�������ڣ�ϵͳ������ʾ
		for (i = 0; i < nUsersNum; i++)
		{
			if (wcscmp(use[i].szName, use[nUsersNum].szName) == 0)
			{
				MessageBox(NULL, _T("���û��Ѿ����ڣ�����������"), _T("�����˻�"), MB_ICONSTOP | MB_SETFOREGROUND | MB_OKCANCEL);//�����ʾ�������û�
				break;//����forѭ��
			}
		}
		if (i >= nUsersNum)//˵��û���ҵ��ظ����û��� 
		{
			do {
				InputBox(use[nUsersNum].password1, 10, _T("������6λ������"));//��ʾ�û���������
				InputBox(use[nUsersNum].password2, 10, _T("��ȷ������"));//��ʾ�û�ȷ������
				if (wcscmp(use[nUsersNum].password1, use[nUsersNum].password2) != 0)//�����������벻��� 
					MessageBox(NULL, _T("�������벻һ�£�����������"), _T("�����˻�"), MB_ICONSTOP | MB_SETFOREGROUND );
				else
				{
					MessageBox(NULL, _T("ע��ɹ���"), _T("�����˻�"), MB_SETFOREGROUND );
					nUsersNum++;//������һ����Ҫע����û��ı��
					use[nUsersNum - 1].nSerialNum = nUsersNum;//��һ 
					SaveFile(fp);//�����ļ����溯��
					break;
				}
			} while (1);
		}
	}
}

void Login(FILE* fp)
{
	loadimage(&login, L"C:/Users/Dragonborn/Desktop/Resources/login.png");
	putimage(0, 0, &login);
	/*�����û���*/
	int i;
	wchar_t username[STRLENGTH];//����һ����ʱ�洢�û������ַ����� 
	wchar_t password[NUMLENGTH];//����һ����ʱ�洢������ַ����� 
	do {
		InputBox(username, 10, _T("�������û���"));//��ʾ�û������û������������ʱ�洢�û������ַ�����
		for (i = 0; i < nUsersNum; i++)
			if (wcscmp(username, use[i].szName) == 0)//�ҵ��� 
			{
				usersnum = i;
				break;//����forѭ��
			}//��¼�����û�������Ӧ���û���ţ�����¼���û�����Ӧ�ı�� 

		if (i >= nUsersNum)//˵��û���ҵ���Ӧ�û��� 
		{
			MessageBox(NULL, _T("���û�������"), _T("��¼"), MB_ICONSTOP | MB_SETFOREGROUND );
			break;
		}
		else
		{
			do {
				InputBox(password, 10, _T("����������"));//��ʾ�û��������룬�������ʱ�洢������ַ�����
				if (wcscmp(password, use[usersnum].password1) == 0)//������� 
				{
					MessageBox(NULL, _T("��¼�ɹ���"), _T("��¼"), MB_SETFOREGROUND);
					nUsersFlag = 1;//�ɹ���¼ 
					break;
				}
				else
					MessageBox(NULL, _T("�������"), _T("��¼"), MB_ICONSTOP | MB_SETFOREGROUND );
			} while (1);
			break;
		}
	} while (1);
}

void Reset_Password(FILE* fp)
{
	loadimage(&reset_password, L"C:/Users/Dragonborn/Desktop/Resources/reset_password.png");//�����޸��������
	putimage(0, 0, &reset_password);
	int i;
	wchar_t username[STRLENGTH];//����һ����ʱ�洢�û������ַ����� 
	wchar_t password[NUMLENGTH];//����һ����ʱ�洢������ַ����� 
	wchar_t resetpassword[NUMLENGTH];//����һ����ʱ�洢�޸ĺ�������ַ����� 
	do {
		InputBox(username, 10, _T("�������û���"));//��ʾ�û������û������������ʱ�洢�û������ַ�����
		for (i = 0; i < nUsersNum; i++)
			if (wcscmp(username, use[i].szName) == 0)//�ҵ��� 
			{
				usersnum = i;
				break;
			}
		if (i >= nUsersNum)//˵��û���ҵ���Ӧ�û��� 
			MessageBox(NULL, _T("���û�������"), _T("�޸�����"), MB_ICONSTOP | MB_SETFOREGROUND );
		else
			break;//�ҵ��˴��û������˳������û�����ѭ���������޸�����ģ�� 
	} while (1);

	do {
		InputBox(password, 10, _T("������ԭʼ����"));
		if (wcscmp(password, use[usersnum].password1) == 0)//�������
		{
			InputBox(resetpassword, 10, _T("������ȷ��������6λ���޸�����"));
			wcscpy_s(use[usersnum].password1, resetpassword);//��ԭ�����Ϊ�޸ĺ������(wcscpy�൱��strcopy)
			MessageBox(NULL, _T("�޸�����ɹ���"), _T("�޸�����"), MB_SETFOREGROUND | MB_OKCANCEL);
			SaveFile(fp);//�����ļ����溯��
			break;//�˳��޸�����ģ�� 
		}
		else
			MessageBox(NULL, _T("�������"), _T("�޸�����"), MB_ICONSTOP | MB_SETFOREGROUND);
	} while (1);
}

void ParkingLot(FILE* fp, SqStack* s, SqStack* temp, LinkQueue* q)
{
	MOUSEMSG msg;//������������������Ϣ
	loadimage(&park, L"C:/Users/Dragonborn/Desktop/Resources/park.png");
	putimage(0, 0, &park);
	Sleep(100);

	if (nUsersFlag != 1)
		MessageBox(NULL, _T("δ��¼��"), _T("�û���¼"), MB_ICONSTOP | MB_SETFOREGROUND );
	else
	{
		loadimage(&parklot, L"C:/Users/Dragonborn/Desktop/Resources/parklot.png");
		putimage(0, 0, &parklot);
		FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
		while (true)
		{
			while (MouseHit())
			{
				msg = GetMouseMsg();
				if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
				{
					if (msg.x > 47 && msg.x < 206 && msg.y > 164 && msg.y < 231)//�����"��Ҫͣ��"
						Parking(fp, s, temp, q);
					if (msg.x > 47 && msg.x < 206 && msg.y > 254 && msg.y < 322)//���������Ҫ�뿪��
						Leaving(fp, s, temp, q);
					if (msg.x > 47 && msg.x < 206 && msg.y > 346 && msg.y < 414)//���������λ�����
						Situation(fp, s);
					if (msg.x > 47 && msg.x < 206 && msg.y > 436 && msg.y < 505)//��������˳���
						Users_Exit(fp, s, temp, q);
				}
			}
		}
	}
}

SqStack* InitStack(SqStack* s) //��ʼ��ջ
{
	int i;
	s->top = 0;
	return s;
}
int InitQueue(LinkQueue* q)
{
	q->front = (QNode*)malloc(sizeof(QNode));
	if (q->front != NULL)
	{
		q->front->next = NULL;
		q->rear = q->front;
		return 1;
	}
	else
		return -1;
}
void Parking(FILE* fp, SqStack* s, SqStack* temp, LinkQueue* q)
{
	wchar_t str[10];
	int result,i;
	int flag = 0;
	loadimage(&parking, L"C:/Users/Dragonborn/Desktop/Resources/parking.png");
	putimage(0, 0, &parking);
	Car* p;
	QNode* t;
	p = (Car*)malloc(sizeof(Car));
	if (s->top < STACKSIZE)
	{
		InputBox(p->plate, 10, _T("�����복�ƺ�"));
		for (i = 1; i <= s->top; i++)
		{
			if (wcscmp(s->stack[i]->plate, p->plate) == 0)
			{
				flag = 1;
				break;
			}
		}
		if (wcslen(p->plate) != 7 || flag == 1)
		{
			MessageBox(NULL, _T("���ƺŴ�������������"), _T("ͣ����ϵͳ"), MB_ICONSTOP | MB_SETFOREGROUND );
		}
		else
		{
			p->start=time(NULL);
			s->top++;
			loadimage(&lot, L"C:/Users/Dragonborn/Desktop/Resources/lot.png");
			putimage(0, 0, &lot);
			setbkmode(TRANSPARENT);
			settextcolor(COLORREF(RGB(0, 0, 0)));
			settextstyle(36, 0, _T("����"));
			swprintf_s(str, _T("%d"), s->top);
			outtextxy(468, 255, str);
			s->stack[s->top] = p;
		}
	}
	else
	{
		MessageBox(NULL, _T("����ͣ��λ"), _T("ͣ��������ϵͳ"), MB_ICONSTOP | MB_SETFOREGROUND );
		result = MessageBox(NULL, _T("���Ƿ�Ҫ�������ȴ�"), _T("ͣ��������ϵͳ"), MB_YESNO | MB_SETFOREGROUND);
		switch (result)
		{
		case IDYES:
			t = (QNode*)malloc(sizeof(QNode));
			InputBox(p->plate, 10, _T("�����복�ƺ�"));
			t->data = p;
			t->next = NULL;
			q->rear->next = t;
			q->rear = t;
			break;
		case IDNO:
			break;
		}


	}
}
void Leaving(FILE* fp, SqStack* s, SqStack* temp, LinkQueue* q)
{
	wchar_t str[20];
	loadimage(&leaving, L"C:/Users/Dragonborn/Desktop/Resources/leaving.png");
	putimage(0, 0, &leaving);
	int place = -1, i;
	Car* p, * t;
	QNode* node;
	if (s->top > 0)
	{
		while (1)
		{
			InputBox(str, 10, _T("�����복�ƺ�"));
			if (wcslen(str) != 7)
			{
				MessageBox(NULL, _T("���ƺŴ�������������"), _T("ͣ��������ϵͳ"), MB_ICONSTOP | MB_SETFOREGROUND );
				
			}
			for (i = 1; i <= s->top; i++)
			{
				if (wcscmp(str, s->stack[i]->plate) == 0)
				{
					place = i;
					break;
				}
			}
			if (place >= 1 && place <= s->top)
				break;
			else
			{
				MessageBox(NULL, _T("ͣ�������޸ó���"), _T("ͣ��������ϵͳ"), MB_ICONSTOP | MB_SETFOREGROUND);
				break;
				
			}
		}
		while (s->top > place && place != -1)//ǰ��ĳ���ʱ��ջ
		{
			temp->top++;
			temp->stack[temp->top] = s->stack[s->top];
			s->stack[s->top] = NULL;
			s->top--;
		}
		if (place >= 1 && place <= s->top)
		{
			p = s->stack[s->top];//p�ݴ�Ҫ�뿪�ĳ���
			s->stack[s->top] = NULL;//ɾ���뿪�ĳ�����Ϣ
			s->top--;
			p->end=time(NULL);
			loadimage(&cost, L"C:/Users/Dragonborn/Desktop/Resources/cost.png");
			putimage(0, 0, &cost);
			setbkmode(TRANSPARENT);
			settextcolor(COLORREF(RGB(255, 0, 0)));
			settextstyle(36, 0, _T("����"));
			swprintf_s(str, _T("%f"), price * difftime(p->end, p->start));
			outtextxy(521, 242, str);
			while (temp->top >= 1)//����ʱջ�����Ϣ�Ż�ͣ��ջ
			{
				s->top++;
				s->stack[s->top] = temp->stack[temp->top];
				temp->stack[temp->top] = NULL;
				temp->top--;
			}
			if (q->front != q->rear && s->top < STACKSIZE)//���뿪�󣬱���еĵ�һ��������
			{
				node = q->front->next;
				t = node->data;
				s->top++;
				q->front->next = node->next;
				if (node == q->rear)
					q->rear = q->front;
				s->stack[s->top] = t;
				free(node);
			}
		}
	}
}

void Situation(FILE* fp, SqStack* s)
{
	int  position_y1 = 195, position_y2 = 195;
	int i;
	wchar_t str[3];
	wchar_t str1[50], str2[50];
	loadimage(&show, L"C:/Users/Dragonborn/Desktop/Resources/show.png");
	putimage(0, 0, &show);
	if (s->top >= 0)
	{
		setbkmode(TRANSPARENT);
		settextcolor(COLORREF(RGB(0, 0, 0)));
		settextstyle(20, 0, _T("����"));
		for (i = 1; i <= s->top; i++)
		{
			position_y1 = position_y1 + 30;
			position_y2 = position_y2 + 30;
			swprintf_s(str, _T("%d"), i);
			outtextxy(410, position_y1, str);
			outtextxy(538, position_y2, s->stack[i]->plate);
		}
	}
}
void Users_Exit(FILE* fp, SqStack* s, SqStack* temp, LinkQueue* q)
{
	loadimage(&users_exit, L"C:/Users/Dragonborn/Desktop/Resources/exit.png");
	putimage(0, 0, &users_exit);
	nUsersFlag = 0;
	Select_MainMenu(fp, s, temp, q);
}

int main()
{
	FILE* fp;
	SqStack* s = (SqStack*)malloc(sizeof(SqStack));
	SqStack temp;
	LinkQueue q;
	InitQueue(&q);
	s = InitStack(s);
	InitStack(&temp);
	initgraph(961, 539);//���崰�ڴ�С
	fopen_s(&fp, "C:/Users/Dragonborn/Desktop/����/alldata.txt", "rb");
	Welcome(fp, s, &temp, &q);//����Welcome
	return 0;
}
