#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>
 
using namespace std;//�ռ���
 
 
int total=1;//�����ȫ�ֱ��������ڿ�������
 
typedef struct ElemType
{
    char name[8];//����
    int account;//�˻�
    char password[6];//���루�޶�6λ����
    float money;//Ǯ��
}ElemType;
 
typedef struct lnode
{
    ElemType data;//ָ��ṹ��
    struct lnode *next;
}LINK;
 
void InitList(LINK *&L)/*��ʼ����*/
{
    L=(LINK *)malloc (sizeof(LINK));
    L->next=NULL;
}
void InsertList(LINK *&L)/*����*/
{
    LINK *s;
    s=(LINK*)malloc(sizeof(LINK));//��̬���ٿռ�
    printf("��������Ҫ����������:");
    scanf("%s",s->data.name);
    s->data.account=10001000+total++;//�����ʼ�ʺ�
    printf("\n�㿪�����˺�Ϊ:%d\n",s->data.account);
    printf("���������˺ŵ�����:");
    scanf("%s",s->data.password);
    s->data.money=0.00;//��ʼ���˻����
    s->next=NULL;
    if(L->next==NULL)
        L->next=s;
    else
    {
        s->next=L->next;
        L->next=s;
    }
    printf("�����ɹ���\n");
}
void DeleteList(LINK *&L)/*����*/
{
    LINK *p=L,*q;
    char pass[6];
    int s;
    printf("��������Ҫ�������˺�:");
    scanf("%d",&s);
    printf("��������˺ŵ�����:");
    scanf("%s",pass);
    while(p->next!=NULL)
    {
        if(p->next->data.account==s)
            break;
        p=p->next;
    }
    if(p->next!=NULL)
    {
        while(strcmp(p->next->data.password,pass)!=0)//�ַ����Ƚϣ�������֤�����Ƿ���ȷ
        {
            printf("�������!����������:");
            scanf("%s",pass);
        }
        q=p->next;
        p->next=q->next;
        free(q);
        printf("�˺������ɹ���\n");
    }
    else printf("����Ҫ�����ĵ��˺Ų�����(�����Ѿ�����)��\n");
}
void PrintList(LINK*L)
{
    LINK *p=L->next;
    while (p!=NULL)
    {
        printf("%s\t",p->data.name);
        printf("%d\t%s\t%.2f\n",p->data.account,p->data.password,p->data.money);
        p=p->next;
    }
}
void Deposit(LINK *&L,LINK *p)
{
    int cq;
    float mn;
    while(1)
    if(p!=NULL)
    {
        printf("��ѡ����(1)��ȡ��(2)����ѯ���(3)���˳��˺�(4)��\n(�����������ڵ�����,���������ַ�Ĭ��Ϊȡ��):\n");
		printf("���-----------------1\n");
		printf("ȡ��-----------------2\n");
		printf("��ѯ���-------------3\n");
		printf("�˳��˺�-------------4\n");
        scanf("%d",&cq);
        if(cq==1)
        {
            printf("��������Ĵ����:");
            scanf("%f",&mn);
            p->data.money=p->data.money+mn;//���
            printf("���ɹ�!\n");
			time_t timep;
            struct tm *p;
            time (&timep);
            p=gmtime(&timep);
			printf("����ʱ��Ϊ%dʱ",p->tm_hour);
			printf("%d��",p->tm_min); /*��ȡ��ǰ��*/
            printf("%d��\n",p->tm_sec); /*��ȡ��ǰ��*/
            

        }
        else if(cq==3)
        {
        printf("���˻������Ϊ:%.2f\n",p->data.money);
        }
        else if(cq==4)
        {
            printf("�˺��˳��ɹ���\n");
            return;
        }
        else
        {
            printf("���������ȡ����:");
            FH:        scanf("%f",&mn);
            if((p->data.money-mn)>=0)
            {
                p->data.money=p->data.money-mn;//ȡ��
                printf("ȡ��ɹ�!\n");
            }
            else
            {
                printf("ȡ��ʧ��!\n");
                printf("���˻��ϵĽ���!����˻����Ϊ:%.2fRMB\n",p->data.money);
                printf("��������ʵ�ȡ����:");
                goto FH;
            }
        }
    }
}
void Search(LINK *L)
{
    LINK *p=L->next;
    int acc;
    char pass[6];
    printf("��������Ҫ��¼���˺�:");
    scanf("%d",&acc);
    printf("�������������:");
    scanf("%s",pass);
    while(p!=NULL)
    {
        if(p->data.account==acc)
        break;
        p=p->next;
    }//ɨ���˻�
    if(p==NULL)
        printf("�����ڸ��˻�\n");
    else
    {
        if(strcmp(p->data.password,pass)==0)
            printf("�˺ŵ�¼�ɹ���\n");//��֤����
        else
        {
            while(strcmp(p->data.password,pass)!=0)
            {
                char pa;
                printf("�������\n");
                printf("�Ƿ���������(�ǣ������������)��(�񣬴Ӽ���������N or n):");
                scanf("\n%c",&pa);
                if(pa=='n'||pa=='N')
                {system ("cls");return;}
                printf("\n�����������������:");
                scanf("%s",pass);
            }
        }
        Deposit(L,p);
    }
}
void save(LINK *L)
{
    FILE *fp;
    fp=fopen("Account","w");  //¼���ļ�
    LINK *p=L->next;
    while(p!=NULL)
    {
        if(fwrite(p,sizeof(struct lnode),1,fp)!=1)
            printf("file write error\n");
        p=p->next;
    }
    fclose(fp);
}
void Print(LINK *&L)
{
    FILE *fp;
    LINK *p,*s;
    if((fp=fopen("Account","r"))==NULL)
    {
        printf("can not open.\n");
        return; //����ʧ��ʱ��ֱ�ӷ��غ��� ����Ҫ�˳�
    }
    else
    {
        printf("���ݼ��سɹ�.....\n");
    }
    s=(LINK*)malloc(sizeof(LINK));s->next=NULL;
    for(;fread(s,sizeof(struct lnode),1,fp)!=0; )
    {
        total++;//���ڼ�¼�˺ŵģ������˺Ų��ظ�
        if(L->next==NULL)
        {
            L->next=s;
            p=s;
            p->next=s->next;
        }
        else
        {
            p->next=s;
            p=s;
            p->next=s->next;
        }
        s=(LINK*)malloc(sizeof(LINK));s->next=NULL;
 
    }
    fclose(fp);
 
}
void menu()
{
    printf("************��ӭ������ڴ�����Ŀ����***********\n");
    printf("        1.����������\n");
    printf("        2.����������\n");
    printf("        3.�������˺Ŵ�ȡ�\n");
    printf("        4.���ز˵���\n");
    printf("        5.�鿴���д����˻���Ϣ��\n");
    printf("        6.�˳���Ŀ����\n");
    printf("***********************************************\n");
}

void choice()//���ܷ���
{
    LINK *L;
    InitList(L);
    Print(L);                    //��һ�δ�����ʱ����Ҫ��
    // �˴������Ƿ��һ�ζ���ȡ�ļ� �����Ƿ��ж�������ν �оͶ��� û������Ҫ����¼��
    while(1)
    {
        menu();  //�������һ��֮����Ҫ������ʾ�˵�
        char xunhan,ch;
        printf("��ѡ������Ҫ�Ĺ���:");
        scanf("%c",&xunhan);
        if(xunhan=='6')
            break;
        system ("cls");
        switch(xunhan)
        {
            case '1':InsertList(L);ch=getchar();break;
            case '2':DeleteList(L);ch=getchar();break;
            case '3':Search(L);ch=getchar();break;
            case '4':menu();ch=getchar();break;
            case '5':PrintList(L);ch=getchar();break;
            default:printf("�������!������ѡ���ܡ�\n");break;
        }
        save(L);  //�����ļ�
 
}
}

	int main(){

    choice();
    return 0;
	}
