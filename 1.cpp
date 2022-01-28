#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>
 
using namespace std;//空间名
 
 
int total=1;//定义的全局变量，用于开户所需
 
typedef struct ElemType
{
    char name[8];//姓名
    int account;//账户
    char password[6];//密码（限定6位数）
    float money;//钱款
}ElemType;
 
typedef struct lnode
{
    ElemType data;//指向结构体
    struct lnode *next;
}LINK;
 
void InitList(LINK *&L)/*初始化表*/
{
    L=(LINK *)malloc (sizeof(LINK));
    L->next=NULL;
}
void InsertList(LINK *&L)/*开户*/
{
    LINK *s;
    s=(LINK*)malloc(sizeof(LINK));//动态开辟空间
    printf("请输入你要开户的姓名:");
    scanf("%s",s->data.name);
    s->data.account=10001000+total++;//分配初始帐号
    printf("\n你开户的账号为:%d\n",s->data.account);
    printf("请输入你账号的密码:");
    scanf("%s",s->data.password);
    s->data.money=0.00;//初始化账户余额
    s->next=NULL;
    if(L->next==NULL)
        L->next=s;
    else
    {
        s->next=L->next;
        L->next=s;
    }
    printf("开户成功。\n");
}
void DeleteList(LINK *&L)/*销户*/
{
    LINK *p=L,*q;
    char pass[6];
    int s;
    printf("请输入你要销户的账号:");
    scanf("%d",&s);
    printf("请输入该账号的密码:");
    scanf("%s",pass);
    while(p->next!=NULL)
    {
        if(p->next->data.account==s)
            break;
        p=p->next;
    }
    if(p->next!=NULL)
    {
        while(strcmp(p->next->data.password,pass)!=0)//字符串比较，用于验证密码是否正确
        {
            printf("密码错误!请重新输入:");
            scanf("%s",pass);
        }
        q=p->next;
        p->next=q->next;
        free(q);
        printf("账号销户成功。\n");
    }
    else printf("你所要销户的的账号不存在(或者已经销户)。\n");
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
        printf("请选择存款(1)、取款(2)、查询余额(3)、退出账号(4)。\n(请输入括号内的数字,输入其它字符默认为取款):\n");
		printf("存款-----------------1\n");
		printf("取款-----------------2\n");
		printf("查询余额-------------3\n");
		printf("退出账号-------------4\n");
        scanf("%d",&cq);
        if(cq==1)
        {
            printf("请输入你的存款金额:");
            scanf("%f",&mn);
            p->data.money=p->data.money+mn;//存款
            printf("存款成功!\n");
			time_t timep;
            struct tm *p;
            time (&timep);
            p=gmtime(&timep);
			printf("交易时间为%d时",p->tm_hour);
			printf("%d分",p->tm_min); /*获取当前分*/
            printf("%d秒\n",p->tm_sec); /*获取当前秒*/
            

        }
        else if(cq==3)
        {
        printf("你账户的余额为:%.2f\n",p->data.money);
        }
        else if(cq==4)
        {
            printf("账号退出成功。\n");
            return;
        }
        else
        {
            printf("请输入你的取款金额:");
            FH:        scanf("%f",&mn);
            if((p->data.money-mn)>=0)
            {
                p->data.money=p->data.money-mn;//取款
                printf("取款成功!\n");
            }
            else
            {
                printf("取款失败!\n");
                printf("你账户上的金额不足!你的账户余额为:%.2fRMB\n",p->data.money);
                printf("请输入合适的取款金额:");
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
    printf("请输入你要登录的账号:");
    scanf("%d",&acc);
    printf("请输入你的密码:");
    scanf("%s",pass);
    while(p!=NULL)
    {
        if(p->data.account==acc)
        break;
        p=p->next;
    }//扫描账户
    if(p==NULL)
        printf("不存在该账户\n");
    else
    {
        if(strcmp(p->data.password,pass)==0)
            printf("账号登录成功。\n");//验证密码
        else
        {
            while(strcmp(p->data.password,pass)!=0)
            {
                char pa;
                printf("密码错误\n");
                printf("是否重新输入(是，就输入任意键)、(否，从键盘上输入N or n):");
                scanf("\n%c",&pa);
                if(pa=='n'||pa=='N')
                {system ("cls");return;}
                printf("\n请重新输入你的密码:");
                scanf("%s",pass);
            }
        }
        Deposit(L,p);
    }
}
void save(LINK *L)
{
    FILE *fp;
    fp=fopen("Account","w");  //录入文件
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
        return; //加载失败时，直接返回函数 不需要退出
    }
    else
    {
        printf("数据加载成功.....\n");
    }
    s=(LINK*)malloc(sizeof(LINK));s->next=NULL;
    for(;fread(s,sizeof(struct lnode),1,fp)!=0; )
    {
        total++;//用于记录账号的，以致账号不重复
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
    printf("************欢迎进入活期储蓄账目管理***********\n");
    printf("        1.储户开户。\n");
    printf("        2.储户销户。\n");
    printf("        3.储户的账号存款、取款。\n");
    printf("        4.返回菜单。\n");
    printf("        5.查看所有储蓄账户信息。\n");
    printf("        6.退出账目管理。\n");
    printf("***********************************************\n");
}

void choice()//汇总方法
{
    LINK *L;
    InitList(L);
    Print(L);                    //第一次创建的时候，需要屏
    // 此处不管是否第一次都读取文件 至于是否有东西无所谓 有就读入 没人则需要重新录入
    while(1)
    {
        menu();  //操作完成一次之后需要重新显示菜单
        char xunhan,ch;
        printf("请选择你需要的功能:");
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
            default:printf("输入错误!请重新选择功能。\n");break;
        }
        save(L);  //更新文件
 
}
}

	int main(){

    choice();
    return 0;
	}
