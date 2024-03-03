#define _CRT_SECURE_NO_WARNINGS

//头文件
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include <conio.h> //getch()函数

//宏定义
#define SIZE 20
#define ACCOUNT_PASSWORD "beipiao_707770"  //账户及密码
#define LEN sizeof(struct book)//分配内存
#define LEN1 sizeof(struct reader)	//分配内存
#define ABC 'chaz'-'0'
/* 结构体定义 */

//图书信息
struct book {
	char name[SIZE];
	char author[SIZE];
	char publish[SIZE];
	int  amount;
	float price;
	struct book* next;
};
//借阅者信息
struct reader {
	char rname[SIZE];
	char bname[SIZE];
	char date[SIZE];
	int rnum;
	struct reader* next;
};

/*   函数声明    */ 

//初始化页面
void menu();
//选择系统
void SelectSystem();
//书籍数量
int NUM_BOOk();
//借书人信息
int NUM_READER();

//图书管理系统
void Library_System();
//新建图书信息
void New_Bulit();
//删除图书信息
void Delete();
//查询图书信息
void Inquire();
//浏览图书信息 （打印）
void Browse();
//返回上一级  
void Return(int i);

//借阅系统
void Lending_System();
//借书
void Lending();
//还书
void Repay();
//查询借书情况】
void Show_Lending();
//查询信息
void Show_Look();
//获取账户密码输入
//char* s_gets(char* st, int n);

/*   函数定义   */

/*char* s_gets(char* st, int n)
{
	char *ret_val;
	int i = 0;

	ret_val = fgets(st, n, stdin);

	if (ret_val) {
		while (st[i] != '\n' && st[i] != '\0')
			i++;
		if (st[i] == '\n')
			st[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	}

	return ret_val;
}*/
//书籍数量
int NUM_BOOK()
{
	FILE* fp;
	int txcl = 0, n;
	float tprice = 0;
	char tname[20] = { '\0' }, tauthor[20] = { '\0' }, tpublish[20] = { '\0' };
	fp = fopen("library.txt", "r");//打开文件
	for (n = 0; !feof(fp); n++)//逐个读文件
	fscanf(fp, "%s%s%s%d%f",  tname, tauthor, tpublish, &txcl, &tprice);
	n--;
	fclose(fp);//关闭文件

	return (n);//返回个数
}
//借书人信息
int  NUM_READER()
{
	FILE* fp;
	int ID = 0, n;
	char lname[SIZE] = { '\0' }, ldate[SIZE] = { '\0' }, lsname[SIZE] = { '\0' };
	fp = fopen("reader.txt", "r");//打开文件
	for (n = 0; !feof(fp); n++);//逐个打开文件
		fscanf(fp, "%d%s%s%s ", &ID, &lname, &ldate, &lsname);
	n--;
	fclose(fp);

	return (n);
}
//返回上一级
void Return(int i)
{
	switch (i) {
		case 1:SelectSystem();
			break;
		case 2:Lending_System();
			break;
	}
}
//新建图书信息
void New_Bulit()
{
	FILE* fp;
	char i=0;
	int amount = 0;
	float price = 0;
	char name[SIZE] = { '\0' }, author = { '\0' }, publish = { '\0' };

	system("cls");
	if ((fp = fopen("library.txt", "r")) == NULL)//打开图书馆文件，不存在此文件则新建
	{
		fp = fopen("library.txt", "w");
		fclose(fp);
	}
	fp = fopen("library.txt", "a");
	printf("\n请按以下格式输入图书信息:\n 书名 作者 出版社  进库量 单价");
	for (; i != 27;)//为了实现输入一次后按esc退出
	{
		printf("请输入：\n");
		scanf_s("%s%s%s%d%f",name, author, publish, &amount, &price);
		fprintf(fp, "%-9s%-14s%-16s%-7d%-8.2f\n", name, author, publish,amount, price);
		printf("继续输入请按回车，结束输入请按Esc\n");
		i = _getch();//暂停程序当i接收后继续下一条指令
		for (; i != 13 && i != 27;)//保证只能是CR和ESC才能退出循环,输入其他字符无用，暂停程序，按'CR'继续。
			i = _getch();
	}
	fclose(fp);
	printf("操作成功，按任意键返回上一级！\n");
	Library_System();
}
//删除图书信息
void Delete()
{
	struct book* head = NULL;
	struct book* p, * p1=NULL, * p2=NULL;
	int tmany = 0, n = 0, j, k;
	float tprice = 0;
	char  tnam[20] = { '\0' }, taut[20] = { '\0' }, tpub[20] = { '\0' }, tnum[20] = { '\0' };
	char jjnam[20] = { '\0' };
	char i;
	FILE* fp;
	if ((fp = fopen("library.txt", "r")) == NULL)//打开文件
	{
		system("cls");
		printf("\n记录文件不存在!按任意键返回");
		_getch();
		Return(1);
	}

	else//实现删除的功能
	{
		system("cls");
		printf("\n请输入你要删除的书名:");//输入删除图书书名
		scanf("%s", jjnam);
		printf("\n确认删除请回车，取消请按Esc\n");
		i = _getch();
		for (; i != 13 && i != 27;)
			i = _getch();
		if (i == 27)
			Return(1);
		fp = fopen("library.txt", "r");
		j = NUM_BOOK ();

		for (k = 0; k < j; k++)
		{
			fscanf(fp, "%s%s%s%d%f", tnam, taut, tpub, &tmany, &tprice);
			if (strcmp(jjnam, tnam))//比较名字，将不同名字的信息复制到链表
			{
				n++;//相同返回值为0不执行if语句继续循环，不同则执行直到将所有不同的书名建立成链表
				if (n == 1)//建立链表
				{
					p1 = p2 = (struct book*)malloc(LEN);
					head = p1;
				}
				else
				{
					p2->next = p1;
					p2 = p1;
					p1 = (struct book*)malloc(LEN);//新建链表
				}
				strcpy(p1->name, tnam);//复制书名
				strcpy(p1->author, taut);//复制作者名字
				strcpy(p1->publish, tpub);//复制出版社
				p1->amount = tmany;//复制数量
				p1->price = tprice;//复制单价
			}
		}
		if (n == 0)//如果图书只有一项且这一项刚好和要删除的相同
		{
			head = NULL;
		}
		else//建立链表的最后剩余一个储存空间，所以封底
		{
			p2->next = p1;
			p1->next = NULL;
			fclose(fp);
		}
	}

	fp = fopen("library.txt", "w");//清空文件，只写打开，然后关闭
	fclose(fp);
	fp = fopen("library.txt", "a");//追加文件
	p = head;

	for (; p != NULL;)//把链表内容覆盖到文件
	{
		fprintf(fp, "%-9s%-14s%-16s%-7d%-8.2f\n", p->name, p->author, p->publish,  p->amount, p->price);
		p = p->next;
	}
	fclose(fp);
	system("cls");
	printf("\n删除成功 \n按任意键返回上一层\n");
	_getch();//返回上一层
	Return(1);
}
//查询图书信息
void Inquire()
{
	 FILE *fp;
       int k=0,many=0,m=0,n=0;
	   float price=0;
       char  nam[20]={'\0'},aut[20]={'\0'},pub[20]={'\0'};
       char i;
       char chazhao[20]={'\0'};
       if ((fp=fopen("library.txt","r"))==NULL)//打开文件
       {
	       system ("cls");
           printf("\n记录文件不存在!按任意键返回");
  		   _getch();
		   Return(1);
       }
	   system("cls");
       printf("请输入书号,书名,作者或类别查询：\n");
       scanf("%s",chazhao);
       system ("cls");
       m=NUM_BOOK();

	   for (n=0;n<m;n++)
	   {
	    fscanf(fp,"%s%s%s%d%f",nam,aut,pub,&many,&price);
        if(!strcmp(chazhao,nam)||!strcmp(chazhao,aut))
        {
        	if(k==0)
            {
			  printf("查询结果:\n\n");
			  printf("书名\t\t作者\t\t出版社\t\t库存量\t单价\n");
            }
			printf("%-8s%-14s%-16s%-7d%-8.2f\n",nam,aut,pub,many,price);
            k++;
        }
       }
        if (k==0)//文件夹为空则输出无记录并返回上一层
        {
			system ("cls");
			printf("\n无符合记录!\n");
			_getch();
			Return(1);
		}
		fclose(fp);//查询结束
		_getch();
		Return(1);
}
//浏览图书信息
void Browse()
{
	FILE* fp;
	int n = 0;
	int k = 0, m = 0, many = 0;
	float price = 0;
	char  nam[20] = { '\0' }, aut[20] = { '\0' }, pub[20] = { '\0' };
	char i;
	if ((fp = fopen("library.txt", "r")) == NULL)//打开文件
	{
		system("cls");
		printf("\n记录文件不存在!按任意键返回");
		_getch();//返回
		Return(1);
	}
	n = NUM_BOOK();
	if (n == 0)
	{
		system("cls");
		printf("\n无任何记录!");
	}

	fp = fopen("library.txt", "r");//打开只读文件
	system("cls");
	printf("\t书名\t作者\t\t出版社\t\t库存量\t单价\n");

	for (m = 0; m < n; m++)//输出数据
	{
		fscanf(fp, "%s%s%s%d%f", nam, aut, pub, &many, &price);
		printf("%-14s%-16s%-18s%-7d%-8.2f\n",  nam, aut, pub, many, price);
	}
	fclose(fp);
	printf("\n按任意键返回\n");
	_getch();
	Return(1);
}


//借书
void Lending()
{
	FILE* fp, * fp3;
	struct book* head = NULL;
	struct book* p, * p1 = NULL, * p2 = NULL;
	int i, loop, k, n = 0, flag = 0, s = 0;
	int jnum = 0;
	int many = 0;
	float tprice = 0;
	char tname[20] = { '\0' }, tauthor[20] = { '\0' }, tchuban[20] = { '\0' }, 
		ttname[20] = { '\0' }, mingzi[20] = { '\0' }, riqi[20] = { '\0' }, zname[20] = { '\0' };
	char hit = 0;

	system("cls");
	if ((fp = fopen("library.txt", "r")) == NULL)
	{
		system("cls");
		printf("\n 图书馆无库存!按任意键退出!");
		_getch();
		exit(0);
	}
	else
	{
		printf("\n请输入借阅书名:\n请输入:");
		scanf("%s", zname);
		k = NUM_BOOK();//统计图书馆文件个数

		for (i = 0; i < k; i++)//先将图书信息建立链表，更改库存
		{
			fscanf(fp, "%s%s%s%d%f", tname, tauthor, tchuban, &many, &tprice);
			n++;
			if (n == 1)
			{
				p1 = p2 = (struct book*)malloc(LEN);
				head = p1;
			}
			else
			{
				p2->next = p1;
				p2 = p1;
				p1 = (struct book*)malloc(LEN);
			}
			strcpy(p1->name, tname);//复制书名
			strcpy(p1->author, tauthor);//复制作者
			strcpy(p1->publish, tchuban);//复制出版社
			p1->amount = many;//复制现存量
			p1->price = tprice;//复制单价
		}
		if (n == 0)
		head = NULL;
		else
		{
		p2->next = p1;
		p1->next = NULL;
		fclose(fp);
		}
	}
	p = head;

	for (; p != NULL;)
	{
		if (!(strcmp(p->name, zname)))//判断要借书的是否存在，标记等于1，存在库存减一
		{

			flag = 1;
			loop = p->amount;
			(p->amount)--;
		}
		p = p->next;
	}
	if (flag && (loop > 0))//存在被借的图书且现存量大于0，把库存量变化后的链表存入文件
	{

		fp = fopen("library.txt", "w");
		fclose(fp);
		fp = fopen("library.txt", "a");
		p = head;

		for (; p != NULL;)
		{
			fprintf(fp, "%-9s%-14s%-16s%-7d%-8.2f\n", p->name, p->author, p->publish, p->amount, p->price);
			p = p->next;
		}
		free(p);
		fclose(fp);

		if ((fp3 = fopen("reader.txt", "r")) == NULL)//建读者文件夹存入借书信息
		{
			fp3 = fopen("reader.txt", "w");//打开只读文件
			fclose(fp3);
		}
		fp3 = fopen("reader.txt", "a");

		printf("\n请按以下格式输入读者信息:\n 证号 姓名 借书日期 借书书名\n请输入:");//录入读者信息
		scanf("%d %s %s %s", &jnum, mingzi, riqi, zname);
		fprintf(fp3, "\n%-8d%-23s%-18s%-10s\n", jnum, mingzi, riqi, zname);
		fclose(fp3);
		printf("借书成功!请两个月内归还！！！按任意键返回\n");
		_getch();//返回
		Return(2);//调用借阅系统
	}
	else
	{
		if (flag != 0)
			printf("此书已被借完！按任意键返回！");
		else
			printf("查无此书！按任意键返回！");
		_getch();
		Return(2); //返回上一级
	}
}
//还书
void Repay()
{
	FILE* fp, * fp3;
	struct reader* head = NULL;
	struct reader* p, * p1=NULL, * p2=NULL;
	struct book* lhead1 = NULL;
	struct book* zp1, * lp1=NULL, * lp2=NULL;
	int txcl = 0, i;
	float tprice = 0;
	char tname[20] = { '\0' }, tauthor[20] = { '\0' },
		tpublish[20] = { '\0' }, ttname[20] = { '\0' };
	int ttzhenghao = 0, tzhenghao = 0, n = 0, k = 0, t = 0, flag = 0;
	char tmingzi[20] = { '\0' }, triqi[20] = { '\0' }, tzname[20] = { '\0' }, ttzname[20] = { '\0' };
	char hitkey = 0;
	system("cls");
	{
		if ((fp = fopen("reader.txt", "r")) == NULL)//不存在读者文件，则输出不能还书
		{
			system("cls");
			printf("\n 不存在借书者!按任意键退出!");
			_getch();
			system("cls");
			Return (2);
		}

		else
		{
			{
				printf("\n请输入读者证号和书名:\n请输入:");
				scanf("%d %s", &ttzhenghao, ttzname);//输入还书证号和书名
				k = NUM_READER();//获取读者文件夹信息个数
				for (i = 0; i < k; i++)//读取读者文件夹信息
				{
					fscanf(fp, "%d%s%s%s\n ", &tzhenghao, tmingzi, triqi, tzname);
					if ((ttzhenghao == tzhenghao) && !strcmp(ttzname, tzname))//如果证号书名存在，则标记为1
						flag = 1;
				}
				fclose(fp);
				fp = fopen("reader.txt", "r");//打开读者文件，删除借书信息
				if (flag)
				{
					for (i = 0; i < k; i++)//将读者文件复制到链表
					{
						fscanf(fp, "%d%s%s%s\n ", &tzhenghao, tmingzi, triqi, tzname);//读取文件信息
						if (!((ttzhenghao == tzhenghao) && !strcmp(ttzname, tzname)))
						{
							n++;
							if (n == 1)
							{
								p1 = p2 = (struct reader*)malloc(LEN1);//新建链表
								head = p1;
							}
							else
							{
								p2->next = p1;
								p2 = p1;
								p1 = (struct reader*)malloc(LEN1);//新建链表
							}
							p1->rnum = tzhenghao;//复制证号
							strcpy(p1->rname, tmingzi);//复制读者名字
							strcpy(p1->date, triqi);//复制日
							strcpy(p1->bname, tzname);//复制书名
						}
					}
					if (n == 0)
						head = NULL;
					else
					{
						p2->next = p1;
						p1->next = NULL;
						fclose(fp);
					}
					fp = fopen("reader.txt", "w");//清空读者文件
					fclose(fp);
					fp = fopen("reader.txt", "a");//追加信息
					p = head;
					for (; p != NULL;)//把链表内容覆盖读者文件
					{
						fprintf(fp, "\n%-8d%-23s%-18s%-10s\n", p->rnum, p->rname, p->date, p->bname);
						p = p->next;
					}
					free(p);
					fclose(fp);
				}
			}
		}
	}

	if (flag)//标记为1，即还书时更改库存
	{
		{
			{
				printf("确认还书请按回车!");
				for (; hitkey != 13 && hitkey != 27;)
					hitkey = _getch();
				if (hitkey == 13)
					printf("成功!按任意键返回!");
				n = 0; flag = 0;
				fp3 = fopen("library.txt", "r");//打开图书馆文件
				k = NUM_BOOK();//获取图书馆文件个数
				for (i = 0; i < k; i++)//将图书馆文件复制到链表
				{
					fscanf(fp3, "%s%s%d%f",tname, tauthor, &txcl, &tprice);//读取信息
					n++;
					if (n == 1)
					{
						lp1 = lp2 = (struct book*)malloc(LEN);//新建链表
						lhead1 = lp1;
					}
					else
					{
						lp2->next = lp1;
						lp2 = lp1;
						lp1 = (struct book*)malloc(LEN);//新建链表
					}
					
					strcpy(lp1->name, tname);//复制书名
					strcpy(lp1->author, tauthor);//复制作者
					strcpy(lp1->publish, tpublish);//复制出版社
					lp1->amount = txcl; //复制现存量
					lp1->price = tprice;//复制单价
				}
				if (n == 0)
				{
					lhead1 = NULL;
				}
				else
				{
					lp2->next = lp1;
					lp1->next = NULL;
					fclose(fp3);
				}
			}
		}
		zp1 = lhead1;
		for (; zp1 != NULL;)
		{
			if (!(strcmp(zp1->name, ttzname)))//寻找书名相同
				++(zp1->amount);//现存量加1
			zp1 = zp1->next;
		}
		fp3 = fopen("library.txt", "w");//清空图书馆文件
		fclose(fp);
		fp3 = fopen("library.txt", "a");//追加信息
		zp1 = lhead1;
		for (; zp1 != NULL;)//把链表内容覆盖图书馆文件
		{
			fprintf(fp3, "-9s%-14s%-16s%-7d%-8.2f\n",
				 zp1->name, zp1->author, zp1->publish, zp1->amount, zp1->price);
			zp1 = zp1->next;
		}
		fclose(fp3);
		_getch();//返回
		Return(2);//调用借阅系统
	}
	else
		printf("不存在此信息!按任意键返回!");
	_getch();//返回
	Return(2);//调用借阅系统
}
//查询借书情况
void Show_Lending()
{
	FILE* fp;
	int zhenghao = 0, xcl = 0, n = 0, i = 0, j = 0;
	char mingzi[20] = { '\0' }, riqi[20] = { '\0' }, zname[20] = { '\0' };
	if ((fp = fopen("reader.txt", "r")) == NULL)//打开读者文件夹
	{
		system("cls");
		printf("\n记录文件不存在!按任意键返回");
		_getch();
		Return (2);
	}
	n = NUM_READER();
	if (n == 0)
	{
		system("cls");
		printf("\n无任何记录!");
	}
	fp = fopen("reader.txt", "r");
	system("cls");
	printf("\n证号\t读者姓名\t\t借书日期\t书名\n");
	for (; !feof(fp);)//输出文件信息
	{
		fscanf(fp, "%d%s%s%s\n ", &zhenghao, mingzi, riqi, zname);
		printf("\n%-8d%-23s%-18s%-10s\n", zhenghao, mingzi, riqi, zname);
	}
	fclose(fp);
	printf("\n按任意键返回\n");
	_getch();//返回
	Return (2);//调用借阅系统
}
//查询信息
void Show_Look()
{
	FILE* fp;
	int jsnum = 0, k = 0, many = 0, m = 0, n = 0;

	char  jsnam[20] = { '\0' }, jstime[20] = { '\0' }, tsnam[20] = { '\0' };
	char i;
	char chaz[20] = { '\0' };
	if ((fp = fopen("reader.txt", "r")) == NULL)//打开文件
	{
		system("cls");
		printf("\n记录文件不存在!按任意键返回");
		_getch();
		Return(2);
	}
	system("cls");
	printf("请输入证号或姓名查询：\n");
	scanf("%s", chaz);
	system("cls");
	m = NUM_BOOK();
	for (n = 0; n < m; n++)
	{
		fscanf(fp, "%d%s%s%s", &jsnum, jsnam, jstime, tsnam);
		if (!strcmp(chaz, jsnam) || ((ABC) == jsnum))
		{
			if (k == 0)
			{
				printf("查询结果:\n\n");
				printf("\n证号\t读者姓名\t\t借书日期\t书名\n");
			}
			printf("\n%-8d%-23s%-18s%-10s\n", jsnum, jsnam, jstime, tsnam);
			k++;
		}
	}
	if (k == 0)//文件夹为空则输出无记录并返回上一层
	{
		system("cls");
		printf("\n无符合记录!\n");
		_getch();
		Return (2);
	}
	fclose(fp);//查询结束
	_getch();
	Return(2);
}
//选择系统
void SelectSystem()
{
	int m;
	printf("\n");
	printf("****************************************************\n");
	printf("*                       请选择                     *\n");
	printf("*        1. 图书信息系统       2. 借阅系统         *\n");
	printf("****************************************************\n");
	printf("\n");
	printf("请输入:->");

	scanf("%d", &m);
	switch (m)
	{
		//图书信息系统
		case 1: Library_System();
			break;
		//借阅系统
		case 2: Lending_System();
			break;
		//退出系统
		case 3:return;
			break;
		default:printf("输入有误，请重新输入!\n");
			break;
	}
}
//图书管理系统
void Library_System()
{
	int i;

	system("cls");

	printf("****************************************************\n");
	printf("*          1.新建  2.删除       3.查询              *\n");
	printf("*          4.浏览  5.返回上一级  6.结束              *\n");
	printf("****************************************************\n");
	printf("\n");
	printf("请输:->");

	scanf("%d", &i);

	switch (i) 
	{
		case 1:New_Bulit();
			break;
		case 2:Delete();
			break; 
		case 3:Inquire();
			break; 
		case 4:Browse();
			break; 
		case 5:Return(1);
			break;
		case 6:return 0;
			break;
	}
}
//借阅系统
void Lending_System()
{
	int i;

	printf("****************************************************\n");
	printf("*                 1.借书       2.还书               *\n");
	printf("*                 3.查询       4.浏览               *\n");
	printf("*                 5.返回上一级  6.结束               *\n");
	printf("****************************************************\n");
	printf("\n");
	printf("请输:->");

	scanf("%d", &i);

	switch (i)
	{
		case 1:Lending();
			break;
		case 2:Repay();
			break;
		case 3:Inquire();
			break;
		case 4:Browse();
			break;
		case 5:Return(1);
			break;
		case 6:return 0;
			break;
	default:printf("输入有误，重新输入！\n");
			break;
	}
}
//初始化页面
void menu()
{
	int i;
	char m[SIZE]; //账户及密码

	printf("****************************************************\n");
	printf("*              欢迎使用图书管理系统1.0             *\n");
	printf("*          1. 登录系统       2. 退出系统           *\n");
	printf("****************************************************\n");
	printf("\n");
	printf("请输:->");

	scanf("%d", &i);

	//登录 
	if (i == 1) {

		int ret_1; //比较结果

		//输入
		printf("输入账户及密码：");
		scanf("%s", m);
		//s_gets(m, SIZE);
	
		//判断是否正确  
		ret_1 = strcmp(m, ACCOUNT_PASSWORD);
		if (ret_1 == 0)
		{
			printf("登录成功！\n");
			system("cls");
			//选择系统
			SelectSystem();
		}	   
	}
	//退出
	else {
		return;
	} 
}

int main()
{
	system("color 1F");
	//初始化页面  账户登录
	menu();
	return 0;
}