#define _CRT_SECURE_NO_WARNINGS

//ͷ�ļ�
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include <conio.h> //getch()����

//�궨��
#define SIZE 20
#define ACCOUNT_PASSWORD "beipiao_707770"  //�˻�������
#define LEN sizeof(struct book)//�����ڴ�
#define LEN1 sizeof(struct reader)	//�����ڴ�
#define ABC 'chaz'-'0'
/* �ṹ�嶨�� */

//ͼ����Ϣ
struct book {
	char name[SIZE];
	char author[SIZE];
	char publish[SIZE];
	int  amount;
	float price;
	struct book* next;
};
//��������Ϣ
struct reader {
	char rname[SIZE];
	char bname[SIZE];
	char date[SIZE];
	int rnum;
	struct reader* next;
};

/*   ��������    */ 

//��ʼ��ҳ��
void menu();
//ѡ��ϵͳ
void SelectSystem();
//�鼮����
int NUM_BOOk();
//��������Ϣ
int NUM_READER();

//ͼ�����ϵͳ
void Library_System();
//�½�ͼ����Ϣ
void New_Bulit();
//ɾ��ͼ����Ϣ
void Delete();
//��ѯͼ����Ϣ
void Inquire();
//���ͼ����Ϣ ����ӡ��
void Browse();
//������һ��  
void Return(int i);

//����ϵͳ
void Lending_System();
//����
void Lending();
//����
void Repay();
//��ѯ���������
void Show_Lending();
//��ѯ��Ϣ
void Show_Look();
//��ȡ�˻���������
//char* s_gets(char* st, int n);

/*   ��������   */

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
//�鼮����
int NUM_BOOK()
{
	FILE* fp;
	int txcl = 0, n;
	float tprice = 0;
	char tname[20] = { '\0' }, tauthor[20] = { '\0' }, tpublish[20] = { '\0' };
	fp = fopen("library.txt", "r");//���ļ�
	for (n = 0; !feof(fp); n++)//������ļ�
	fscanf(fp, "%s%s%s%d%f",  tname, tauthor, tpublish, &txcl, &tprice);
	n--;
	fclose(fp);//�ر��ļ�

	return (n);//���ظ���
}
//��������Ϣ
int  NUM_READER()
{
	FILE* fp;
	int ID = 0, n;
	char lname[SIZE] = { '\0' }, ldate[SIZE] = { '\0' }, lsname[SIZE] = { '\0' };
	fp = fopen("reader.txt", "r");//���ļ�
	for (n = 0; !feof(fp); n++);//������ļ�
		fscanf(fp, "%d%s%s%s ", &ID, &lname, &ldate, &lsname);
	n--;
	fclose(fp);

	return (n);
}
//������һ��
void Return(int i)
{
	switch (i) {
		case 1:SelectSystem();
			break;
		case 2:Lending_System();
			break;
	}
}
//�½�ͼ����Ϣ
void New_Bulit()
{
	FILE* fp;
	char i=0;
	int amount = 0;
	float price = 0;
	char name[SIZE] = { '\0' }, author = { '\0' }, publish = { '\0' };

	system("cls");
	if ((fp = fopen("library.txt", "r")) == NULL)//��ͼ����ļ��������ڴ��ļ����½�
	{
		fp = fopen("library.txt", "w");
		fclose(fp);
	}
	fp = fopen("library.txt", "a");
	printf("\n�밴���¸�ʽ����ͼ����Ϣ:\n ���� ���� ������  ������ ����");
	for (; i != 27;)//Ϊ��ʵ������һ�κ�esc�˳�
	{
		printf("�����룺\n");
		scanf_s("%s%s%s%d%f",name, author, publish, &amount, &price);
		fprintf(fp, "%-9s%-14s%-16s%-7d%-8.2f\n", name, author, publish,amount, price);
		printf("���������밴�س������������밴Esc\n");
		i = _getch();//��ͣ����i���պ������һ��ָ��
		for (; i != 13 && i != 27;)//��ֻ֤����CR��ESC�����˳�ѭ��,���������ַ����ã���ͣ���򣬰�'CR'������
			i = _getch();
	}
	fclose(fp);
	printf("�����ɹ����������������һ����\n");
	Library_System();
}
//ɾ��ͼ����Ϣ
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
	if ((fp = fopen("library.txt", "r")) == NULL)//���ļ�
	{
		system("cls");
		printf("\n��¼�ļ�������!�����������");
		_getch();
		Return(1);
	}

	else//ʵ��ɾ���Ĺ���
	{
		system("cls");
		printf("\n��������Ҫɾ��������:");//����ɾ��ͼ������
		scanf("%s", jjnam);
		printf("\nȷ��ɾ����س���ȡ���밴Esc\n");
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
			if (strcmp(jjnam, tnam))//�Ƚ����֣�����ͬ���ֵ���Ϣ���Ƶ�����
			{
				n++;//��ͬ����ֵΪ0��ִ��if������ѭ������ͬ��ִ��ֱ�������в�ͬ����������������
				if (n == 1)//��������
				{
					p1 = p2 = (struct book*)malloc(LEN);
					head = p1;
				}
				else
				{
					p2->next = p1;
					p2 = p1;
					p1 = (struct book*)malloc(LEN);//�½�����
				}
				strcpy(p1->name, tnam);//��������
				strcpy(p1->author, taut);//������������
				strcpy(p1->publish, tpub);//���Ƴ�����
				p1->amount = tmany;//��������
				p1->price = tprice;//���Ƶ���
			}
		}
		if (n == 0)//���ͼ��ֻ��һ������һ��պú�Ҫɾ������ͬ
		{
			head = NULL;
		}
		else//������������ʣ��һ������ռ䣬���Է��
		{
			p2->next = p1;
			p1->next = NULL;
			fclose(fp);
		}
	}

	fp = fopen("library.txt", "w");//����ļ���ֻд�򿪣�Ȼ��ر�
	fclose(fp);
	fp = fopen("library.txt", "a");//׷���ļ�
	p = head;

	for (; p != NULL;)//���������ݸ��ǵ��ļ�
	{
		fprintf(fp, "%-9s%-14s%-16s%-7d%-8.2f\n", p->name, p->author, p->publish,  p->amount, p->price);
		p = p->next;
	}
	fclose(fp);
	system("cls");
	printf("\nɾ���ɹ� \n�������������һ��\n");
	_getch();//������һ��
	Return(1);
}
//��ѯͼ����Ϣ
void Inquire()
{
	 FILE *fp;
       int k=0,many=0,m=0,n=0;
	   float price=0;
       char  nam[20]={'\0'},aut[20]={'\0'},pub[20]={'\0'};
       char i;
       char chazhao[20]={'\0'};
       if ((fp=fopen("library.txt","r"))==NULL)//���ļ�
       {
	       system ("cls");
           printf("\n��¼�ļ�������!�����������");
  		   _getch();
		   Return(1);
       }
	   system("cls");
       printf("���������,����,���߻�����ѯ��\n");
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
			  printf("��ѯ���:\n\n");
			  printf("����\t\t����\t\t������\t\t�����\t����\n");
            }
			printf("%-8s%-14s%-16s%-7d%-8.2f\n",nam,aut,pub,many,price);
            k++;
        }
       }
        if (k==0)//�ļ���Ϊ��������޼�¼��������һ��
        {
			system ("cls");
			printf("\n�޷��ϼ�¼!\n");
			_getch();
			Return(1);
		}
		fclose(fp);//��ѯ����
		_getch();
		Return(1);
}
//���ͼ����Ϣ
void Browse()
{
	FILE* fp;
	int n = 0;
	int k = 0, m = 0, many = 0;
	float price = 0;
	char  nam[20] = { '\0' }, aut[20] = { '\0' }, pub[20] = { '\0' };
	char i;
	if ((fp = fopen("library.txt", "r")) == NULL)//���ļ�
	{
		system("cls");
		printf("\n��¼�ļ�������!�����������");
		_getch();//����
		Return(1);
	}
	n = NUM_BOOK();
	if (n == 0)
	{
		system("cls");
		printf("\n���κμ�¼!");
	}

	fp = fopen("library.txt", "r");//��ֻ���ļ�
	system("cls");
	printf("\t����\t����\t\t������\t\t�����\t����\n");

	for (m = 0; m < n; m++)//�������
	{
		fscanf(fp, "%s%s%s%d%f", nam, aut, pub, &many, &price);
		printf("%-14s%-16s%-18s%-7d%-8.2f\n",  nam, aut, pub, many, price);
	}
	fclose(fp);
	printf("\n�����������\n");
	_getch();
	Return(1);
}


//����
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
		printf("\n ͼ����޿��!��������˳�!");
		_getch();
		exit(0);
	}
	else
	{
		printf("\n�������������:\n������:");
		scanf("%s", zname);
		k = NUM_BOOK();//ͳ��ͼ����ļ�����

		for (i = 0; i < k; i++)//�Ƚ�ͼ����Ϣ�����������Ŀ��
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
			strcpy(p1->name, tname);//��������
			strcpy(p1->author, tauthor);//��������
			strcpy(p1->publish, tchuban);//���Ƴ�����
			p1->amount = many;//�����ִ���
			p1->price = tprice;//���Ƶ���
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
		if (!(strcmp(p->name, zname)))//�ж�Ҫ������Ƿ���ڣ���ǵ���1�����ڿ���һ
		{

			flag = 1;
			loop = p->amount;
			(p->amount)--;
		}
		p = p->next;
	}
	if (flag && (loop > 0))//���ڱ����ͼ�����ִ�������0���ѿ�����仯�����������ļ�
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

		if ((fp3 = fopen("reader.txt", "r")) == NULL)//�������ļ��д��������Ϣ
		{
			fp3 = fopen("reader.txt", "w");//��ֻ���ļ�
			fclose(fp3);
		}
		fp3 = fopen("reader.txt", "a");

		printf("\n�밴���¸�ʽ���������Ϣ:\n ֤�� ���� �������� ��������\n������:");//¼�������Ϣ
		scanf("%d %s %s %s", &jnum, mingzi, riqi, zname);
		fprintf(fp3, "\n%-8d%-23s%-18s%-10s\n", jnum, mingzi, riqi, zname);
		fclose(fp3);
		printf("����ɹ�!���������ڹ黹�����������������\n");
		_getch();//����
		Return(2);//���ý���ϵͳ
	}
	else
	{
		if (flag != 0)
			printf("�����ѱ����꣡����������أ�");
		else
			printf("���޴��飡����������أ�");
		_getch();
		Return(2); //������һ��
	}
}
//����
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
		if ((fp = fopen("reader.txt", "r")) == NULL)//�����ڶ����ļ�����������ܻ���
		{
			system("cls");
			printf("\n �����ڽ�����!��������˳�!");
			_getch();
			system("cls");
			Return (2);
		}

		else
		{
			{
				printf("\n���������֤�ź�����:\n������:");
				scanf("%d %s", &ttzhenghao, ttzname);//���뻹��֤�ź�����
				k = NUM_READER();//��ȡ�����ļ�����Ϣ����
				for (i = 0; i < k; i++)//��ȡ�����ļ�����Ϣ
				{
					fscanf(fp, "%d%s%s%s\n ", &tzhenghao, tmingzi, triqi, tzname);
					if ((ttzhenghao == tzhenghao) && !strcmp(ttzname, tzname))//���֤���������ڣ�����Ϊ1
						flag = 1;
				}
				fclose(fp);
				fp = fopen("reader.txt", "r");//�򿪶����ļ���ɾ��������Ϣ
				if (flag)
				{
					for (i = 0; i < k; i++)//�������ļ����Ƶ�����
					{
						fscanf(fp, "%d%s%s%s\n ", &tzhenghao, tmingzi, triqi, tzname);//��ȡ�ļ���Ϣ
						if (!((ttzhenghao == tzhenghao) && !strcmp(ttzname, tzname)))
						{
							n++;
							if (n == 1)
							{
								p1 = p2 = (struct reader*)malloc(LEN1);//�½�����
								head = p1;
							}
							else
							{
								p2->next = p1;
								p2 = p1;
								p1 = (struct reader*)malloc(LEN1);//�½�����
							}
							p1->rnum = tzhenghao;//����֤��
							strcpy(p1->rname, tmingzi);//���ƶ�������
							strcpy(p1->date, triqi);//������
							strcpy(p1->bname, tzname);//��������
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
					fp = fopen("reader.txt", "w");//��ն����ļ�
					fclose(fp);
					fp = fopen("reader.txt", "a");//׷����Ϣ
					p = head;
					for (; p != NULL;)//���������ݸ��Ƕ����ļ�
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

	if (flag)//���Ϊ1��������ʱ���Ŀ��
	{
		{
			{
				printf("ȷ�ϻ����밴�س�!");
				for (; hitkey != 13 && hitkey != 27;)
					hitkey = _getch();
				if (hitkey == 13)
					printf("�ɹ�!�����������!");
				n = 0; flag = 0;
				fp3 = fopen("library.txt", "r");//��ͼ����ļ�
				k = NUM_BOOK();//��ȡͼ����ļ�����
				for (i = 0; i < k; i++)//��ͼ����ļ����Ƶ�����
				{
					fscanf(fp3, "%s%s%d%f",tname, tauthor, &txcl, &tprice);//��ȡ��Ϣ
					n++;
					if (n == 1)
					{
						lp1 = lp2 = (struct book*)malloc(LEN);//�½�����
						lhead1 = lp1;
					}
					else
					{
						lp2->next = lp1;
						lp2 = lp1;
						lp1 = (struct book*)malloc(LEN);//�½�����
					}
					
					strcpy(lp1->name, tname);//��������
					strcpy(lp1->author, tauthor);//��������
					strcpy(lp1->publish, tpublish);//���Ƴ�����
					lp1->amount = txcl; //�����ִ���
					lp1->price = tprice;//���Ƶ���
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
			if (!(strcmp(zp1->name, ttzname)))//Ѱ��������ͬ
				++(zp1->amount);//�ִ�����1
			zp1 = zp1->next;
		}
		fp3 = fopen("library.txt", "w");//���ͼ����ļ�
		fclose(fp);
		fp3 = fopen("library.txt", "a");//׷����Ϣ
		zp1 = lhead1;
		for (; zp1 != NULL;)//���������ݸ���ͼ����ļ�
		{
			fprintf(fp3, "-9s%-14s%-16s%-7d%-8.2f\n",
				 zp1->name, zp1->author, zp1->publish, zp1->amount, zp1->price);
			zp1 = zp1->next;
		}
		fclose(fp3);
		_getch();//����
		Return(2);//���ý���ϵͳ
	}
	else
		printf("�����ڴ���Ϣ!�����������!");
	_getch();//����
	Return(2);//���ý���ϵͳ
}
//��ѯ�������
void Show_Lending()
{
	FILE* fp;
	int zhenghao = 0, xcl = 0, n = 0, i = 0, j = 0;
	char mingzi[20] = { '\0' }, riqi[20] = { '\0' }, zname[20] = { '\0' };
	if ((fp = fopen("reader.txt", "r")) == NULL)//�򿪶����ļ���
	{
		system("cls");
		printf("\n��¼�ļ�������!�����������");
		_getch();
		Return (2);
	}
	n = NUM_READER();
	if (n == 0)
	{
		system("cls");
		printf("\n���κμ�¼!");
	}
	fp = fopen("reader.txt", "r");
	system("cls");
	printf("\n֤��\t��������\t\t��������\t����\n");
	for (; !feof(fp);)//����ļ���Ϣ
	{
		fscanf(fp, "%d%s%s%s\n ", &zhenghao, mingzi, riqi, zname);
		printf("\n%-8d%-23s%-18s%-10s\n", zhenghao, mingzi, riqi, zname);
	}
	fclose(fp);
	printf("\n�����������\n");
	_getch();//����
	Return (2);//���ý���ϵͳ
}
//��ѯ��Ϣ
void Show_Look()
{
	FILE* fp;
	int jsnum = 0, k = 0, many = 0, m = 0, n = 0;

	char  jsnam[20] = { '\0' }, jstime[20] = { '\0' }, tsnam[20] = { '\0' };
	char i;
	char chaz[20] = { '\0' };
	if ((fp = fopen("reader.txt", "r")) == NULL)//���ļ�
	{
		system("cls");
		printf("\n��¼�ļ�������!�����������");
		_getch();
		Return(2);
	}
	system("cls");
	printf("������֤�Ż�������ѯ��\n");
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
				printf("��ѯ���:\n\n");
				printf("\n֤��\t��������\t\t��������\t����\n");
			}
			printf("\n%-8d%-23s%-18s%-10s\n", jsnum, jsnam, jstime, tsnam);
			k++;
		}
	}
	if (k == 0)//�ļ���Ϊ��������޼�¼��������һ��
	{
		system("cls");
		printf("\n�޷��ϼ�¼!\n");
		_getch();
		Return (2);
	}
	fclose(fp);//��ѯ����
	_getch();
	Return(2);
}
//ѡ��ϵͳ
void SelectSystem()
{
	int m;
	printf("\n");
	printf("****************************************************\n");
	printf("*                       ��ѡ��                     *\n");
	printf("*        1. ͼ����Ϣϵͳ       2. ����ϵͳ         *\n");
	printf("****************************************************\n");
	printf("\n");
	printf("������:->");

	scanf("%d", &m);
	switch (m)
	{
		//ͼ����Ϣϵͳ
		case 1: Library_System();
			break;
		//����ϵͳ
		case 2: Lending_System();
			break;
		//�˳�ϵͳ
		case 3:return;
			break;
		default:printf("������������������!\n");
			break;
	}
}
//ͼ�����ϵͳ
void Library_System()
{
	int i;

	system("cls");

	printf("****************************************************\n");
	printf("*          1.�½�  2.ɾ��       3.��ѯ              *\n");
	printf("*          4.���  5.������һ��  6.����              *\n");
	printf("****************************************************\n");
	printf("\n");
	printf("����:->");

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
//����ϵͳ
void Lending_System()
{
	int i;

	printf("****************************************************\n");
	printf("*                 1.����       2.����               *\n");
	printf("*                 3.��ѯ       4.���               *\n");
	printf("*                 5.������һ��  6.����               *\n");
	printf("****************************************************\n");
	printf("\n");
	printf("����:->");

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
	default:printf("���������������룡\n");
			break;
	}
}
//��ʼ��ҳ��
void menu()
{
	int i;
	char m[SIZE]; //�˻�������

	printf("****************************************************\n");
	printf("*              ��ӭʹ��ͼ�����ϵͳ1.0             *\n");
	printf("*          1. ��¼ϵͳ       2. �˳�ϵͳ           *\n");
	printf("****************************************************\n");
	printf("\n");
	printf("����:->");

	scanf("%d", &i);

	//��¼ 
	if (i == 1) {

		int ret_1; //�ȽϽ��

		//����
		printf("�����˻������룺");
		scanf("%s", m);
		//s_gets(m, SIZE);
	
		//�ж��Ƿ���ȷ  
		ret_1 = strcmp(m, ACCOUNT_PASSWORD);
		if (ret_1 == 0)
		{
			printf("��¼�ɹ���\n");
			system("cls");
			//ѡ��ϵͳ
			SelectSystem();
		}	   
	}
	//�˳�
	else {
		return;
	} 
}

int main()
{
	system("color 1F");
	//��ʼ��ҳ��  �˻���¼
	menu();
	return 0;
}