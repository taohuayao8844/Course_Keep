#include<stdio.h>
#include<time.h>
#include<graphics.h>

//定义的全局变量
int STACKSIZE = 5;//停车场的最大容量
float price = 0.00055;//每秒停车的价格
int nUsersNum = 0;//注册的用户编号（从0开始） 
int nUsersFlag = 0;//定义判断用户是否登录的标志变量
int usersnum = 0;//定义登录的用户编号

//宏定义
#define USENUM 20000//最大用户数
#define STRLENGTH 30//定义用户名长度
#define NUMLENGTH 12//定义密码长度 

//结构体
typedef struct node
{
	wchar_t plate[10];
	time_t start;
	time_t end;
}Car;//每辆车
typedef struct Stack
{
	int top;
	Car* stack[6];
}SqStack;//停车场（顺序栈）
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
}LinkQueue;//便道（链队列）
struct Users
{
	wchar_t szName[STRLENGTH];//定义用户名
	wchar_t password1[NUMLENGTH];//账户密码
	wchar_t password2[NUMLENGTH];//二次输入密码
	int nSerialNum;//用户序号(从1开始) 
}use[USENUM];//每名用户

//加载的图片
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
//函数的声明
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
	putimage(0, 0, &welcome);//显示欢迎界面
	//下面进行鼠标交互
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 739 && msg.x < 887 && msg.y > 395 && msg.y < 466)//鼠标点击特定区域，即ENTER按钮所在区域
				{
					loadimage(&welcome_button, L"C:/Users/Dragonborn/Desktop/Resources/welcome_button.png");//导入按钮图片
					putimage(0, 0, &welcome_button);//显示按钮图片
					Sleep(100);//延时，降低CPU占用率，并且做到点击效果
					Select_MainMenu(fp, s, temp, q);//调用一级主菜单选项函数
				}
			}
		}
	}
}
void SaveFile(FILE* fp)//保存用户信息
{
	fopen_s(&fp, "C:/Users/Dragonborn/Desktop/测试/alldate.dat", "wb");
	//向文件输出全局变量
	fwrite(&nUsersNum, 4, 1, fp);
	fwrite(&nUsersFlag, 4, 1, fp);
	fwrite(&usersnum, 4, 1, fp);
	//输出结构体数据
	for (int i = 0; i < nUsersNum; i++)
		fwrite(&use[i], sizeof(struct Users), 1, fp);
	fclose(fp);
}
void Select_MainMenu(FILE* fp, SqStack* s, SqStack* temp, LinkQueue* q)
{
	loadimage(&startup, L"C:/Users/Dragonborn/Desktop/Resources/startup.png");//导入初始界面
	putimage(0, 0, &startup);//显示初始界面
	MOUSEMSG msg;
	FlushMouseMsgBuffer();
	while (true)
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 138 && msg.x < 358 && msg.y > 191 && msg.y < 268)//鼠标点击"用户登录"
					Login(fp);//调用用户登录函数
				if (msg.x > 138 && msg.x < 358 && msg.y > 318 && msg.y < 398)//鼠标点击“用户注册”
					Register(fp);//调用用户注册函数
				if (msg.x > 513 && msg.x < 736 && msg.y > 191 && msg.y < 268)//鼠标点击“修改密码”
					Reset_Password(fp);//调用修改密码函数
				if (msg.x > 513 && msg.x < 736 && msg.y > 318 && msg.y < 398)//鼠标点击“停车系统”
					ParkingLot(fp, s, temp, q);//进入停车场管理系统
			}
		}
	}
}
void Register(FILE* fp)
{
	loadimage(&use_register, L"C:/Users/Dragonborn/Desktop/Resources/use_register.png");
	putimage(0, 0, &use_register);
	int i;

	InputBox(use[nUsersNum].szName, 20, _T("请输入用户名"));//提示用户输入用户名
	if (wcslen(use[nUsersNum].szName) < 2)
	{
		MessageBox(NULL, _T("用户名太短，请重新输入"), _T("创建账户"), MB_ICONSTOP | MB_SETFOREGROUND);
	}
	else
	{
		//接下来查找用户信息表中的内容，比较新输入的用户名是否存在，如果存在，系统给出提示
		for (i = 0; i < nUsersNum; i++)
		{
			if (wcscmp(use[i].szName, use[nUsersNum].szName) == 0)
			{
				MessageBox(NULL, _T("该用户已经存在，请重新输入"), _T("创建账户"), MB_ICONSTOP | MB_SETFOREGROUND | MB_OKCANCEL);//输出提示，提醒用户
				break;//跳出for循环
			}
		}
		if (i >= nUsersNum)//说明没有找到重复的用户名 
		{
			do {
				InputBox(use[nUsersNum].password1, 10, _T("请设置6位数密码"));//提示用户输入密码
				InputBox(use[nUsersNum].password2, 10, _T("请确认密码"));//提示用户确认密码
				if (wcscmp(use[nUsersNum].password1, use[nUsersNum].password2) != 0)//两次输入密码不相等 
					MessageBox(NULL, _T("两次输入不一致，请重新输入"), _T("创建账户"), MB_ICONSTOP | MB_SETFOREGROUND );
				else
				{
					MessageBox(NULL, _T("注册成功！"), _T("创建账户"), MB_SETFOREGROUND );
					nUsersNum++;//代表下一个将要注册的用户的编号
					use[nUsersNum - 1].nSerialNum = nUsersNum;//加一 
					SaveFile(fp);//调用文件保存函数
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
	/*输入用户名*/
	int i;
	wchar_t username[STRLENGTH];//定义一个临时存储用户名的字符数组 
	wchar_t password[NUMLENGTH];//定义一个临时存储密码的字符数组 
	do {
		InputBox(username, 10, _T("请输入用户名"));//提示用户输入用户名，输入给临时存储用户名的字符数组
		for (i = 0; i < nUsersNum; i++)
			if (wcscmp(username, use[i].szName) == 0)//找到了 
			{
				usersnum = i;
				break;//跳出for循环
			}//记录输入用户名所对应的用户编号，即登录的用户所对应的编号 

		if (i >= nUsersNum)//说明没有找到对应用户名 
		{
			MessageBox(NULL, _T("该用户不存在"), _T("登录"), MB_ICONSTOP | MB_SETFOREGROUND );
			break;
		}
		else
		{
			do {
				InputBox(password, 10, _T("请输入密码"));//提示用户输入密码，输入给临时存储密码的字符数组
				if (wcscmp(password, use[usersnum].password1) == 0)//密码符合 
				{
					MessageBox(NULL, _T("登录成功！"), _T("登录"), MB_SETFOREGROUND);
					nUsersFlag = 1;//成功登录 
					break;
				}
				else
					MessageBox(NULL, _T("密码错误"), _T("登录"), MB_ICONSTOP | MB_SETFOREGROUND );
			} while (1);
			break;
		}
	} while (1);
}

void Reset_Password(FILE* fp)
{
	loadimage(&reset_password, L"C:/Users/Dragonborn/Desktop/Resources/reset_password.png");//进入修改密码界面
	putimage(0, 0, &reset_password);
	int i;
	wchar_t username[STRLENGTH];//定义一个临时存储用户名的字符数组 
	wchar_t password[NUMLENGTH];//定义一个临时存储密码的字符数组 
	wchar_t resetpassword[NUMLENGTH];//定义一个临时存储修改后密码的字符数组 
	do {
		InputBox(username, 10, _T("请输入用户名"));//提示用户输入用户名，输入给临时存储用户名的字符数组
		for (i = 0; i < nUsersNum; i++)
			if (wcscmp(username, use[i].szName) == 0)//找到了 
			{
				usersnum = i;
				break;
			}
		if (i >= nUsersNum)//说明没有找到对应用户名 
			MessageBox(NULL, _T("该用户不存在"), _T("修改密码"), MB_ICONSTOP | MB_SETFOREGROUND );
		else
			break;//找到了此用户名，退出输入用户名的循环，进入修改密码模块 
	} while (1);

	do {
		InputBox(password, 10, _T("请输入原始密码"));
		if (wcscmp(password, use[usersnum].password1) == 0)//密码符合
		{
			InputBox(resetpassword, 10, _T("密码正确，请输入6位数修改密码"));
			wcscpy_s(use[usersnum].password1, resetpassword);//将原密码改为修改后的密码(wcscpy相当于strcopy)
			MessageBox(NULL, _T("修改密码成功！"), _T("修改密码"), MB_SETFOREGROUND | MB_OKCANCEL);
			SaveFile(fp);//调用文件保存函数
			break;//退出修改密码模块 
		}
		else
			MessageBox(NULL, _T("密码错误"), _T("修改密码"), MB_ICONSTOP | MB_SETFOREGROUND);
	} while (1);
}

void ParkingLot(FILE* fp, SqStack* s, SqStack* temp, LinkQueue* q)
{
	MOUSEMSG msg;//定义变量，保存鼠标消息
	loadimage(&park, L"C:/Users/Dragonborn/Desktop/Resources/park.png");
	putimage(0, 0, &park);
	Sleep(100);

	if (nUsersFlag != 1)
		MessageBox(NULL, _T("未登录！"), _T("用户登录"), MB_ICONSTOP | MB_SETFOREGROUND );
	else
	{
		loadimage(&parklot, L"C:/Users/Dragonborn/Desktop/Resources/parklot.png");
		putimage(0, 0, &parklot);
		FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
		while (true)
		{
			while (MouseHit())
			{
				msg = GetMouseMsg();
				if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
				{
					if (msg.x > 47 && msg.x < 206 && msg.y > 164 && msg.y < 231)//鼠标点击"我要停车"
						Parking(fp, s, temp, q);
					if (msg.x > 47 && msg.x < 206 && msg.y > 254 && msg.y < 322)//鼠标点击“我要离开”
						Leaving(fp, s, temp, q);
					if (msg.x > 47 && msg.x < 206 && msg.y > 346 && msg.y < 414)//鼠标点击“车位情况”
						Situation(fp, s);
					if (msg.x > 47 && msg.x < 206 && msg.y > 436 && msg.y < 505)//鼠标点击“退出”
						Users_Exit(fp, s, temp, q);
				}
			}
		}
	}
}

SqStack* InitStack(SqStack* s) //初始化栈
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
		InputBox(p->plate, 10, _T("请输入车牌号"));
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
			MessageBox(NULL, _T("车牌号错误，请重新输入"), _T("停车场系统"), MB_ICONSTOP | MB_SETFOREGROUND );
		}
		else
		{
			p->start=time(NULL);
			s->top++;
			loadimage(&lot, L"C:/Users/Dragonborn/Desktop/Resources/lot.png");
			putimage(0, 0, &lot);
			setbkmode(TRANSPARENT);
			settextcolor(COLORREF(RGB(0, 0, 0)));
			settextstyle(36, 0, _T("楷体"));
			swprintf_s(str, _T("%d"), s->top);
			outtextxy(468, 255, str);
			s->stack[s->top] = p;
		}
	}
	else
	{
		MessageBox(NULL, _T("暂无停车位"), _T("停车场管理系统"), MB_ICONSTOP | MB_SETFOREGROUND );
		result = MessageBox(NULL, _T("您是否要进入便道等待"), _T("停车场管理系统"), MB_YESNO | MB_SETFOREGROUND);
		switch (result)
		{
		case IDYES:
			t = (QNode*)malloc(sizeof(QNode));
			InputBox(p->plate, 10, _T("请输入车牌号"));
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
			InputBox(str, 10, _T("请输入车牌号"));
			if (wcslen(str) != 7)
			{
				MessageBox(NULL, _T("车牌号错误！请重新输入"), _T("停车场管理系统"), MB_ICONSTOP | MB_SETFOREGROUND );
				
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
				MessageBox(NULL, _T("停车场中无该车辆"), _T("停车场管理系统"), MB_ICONSTOP | MB_SETFOREGROUND);
				break;
				
			}
		}
		while (s->top > place && place != -1)//前面的车暂时出栈
		{
			temp->top++;
			temp->stack[temp->top] = s->stack[s->top];
			s->stack[s->top] = NULL;
			s->top--;
		}
		if (place >= 1 && place <= s->top)
		{
			p = s->stack[s->top];//p暂存要离开的车，
			s->stack[s->top] = NULL;//删除离开的车的信息
			s->top--;
			p->end=time(NULL);
			loadimage(&cost, L"C:/Users/Dragonborn/Desktop/Resources/cost.png");
			putimage(0, 0, &cost);
			setbkmode(TRANSPARENT);
			settextcolor(COLORREF(RGB(255, 0, 0)));
			settextstyle(36, 0, _T("楷体"));
			swprintf_s(str, _T("%f"), price * difftime(p->end, p->start));
			outtextxy(521, 242, str);
			while (temp->top >= 1)//把临时栈里的信息放回停车栈
			{
				s->top++;
				s->stack[s->top] = temp->stack[temp->top];
				temp->stack[temp->top] = NULL;
				temp->top--;
			}
			if (q->front != q->rear && s->top < STACKSIZE)//车离开后，便道中的第一辆车进入
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
		settextstyle(20, 0, _T("楷体"));
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
	initgraph(961, 539);//定义窗口大小
	fopen_s(&fp, "C:/Users/Dragonborn/Desktop/测试/alldata.txt", "rb");
	Welcome(fp, s, &temp, &q);//调用Welcome
	return 0;
}
