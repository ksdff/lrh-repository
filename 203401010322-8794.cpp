#include"stdio.h"
#include"stdlib.h"
#include"string.h"

typedef struct student
{
	int ID;//学号
	char name[10];//姓名
	char sex[10];//性别
	int houseid;//宿舍号
	char professor[20];//专业
	char Class[10];//班级	
	struct student* prior;
    struct student* next;
}*stu,Stu;//学生信息

stu creat_head()
{
    stu head;
    head = (stu)malloc(sizeof(Stu));
    head->prior = NULL;
    head->next = NULL;
    return head;
}//初始化头结点

int user_choose()
{ 
    printf("||                     该系统包含以下功能                       ||\n");
    printf("||                          请选择!                             ||\n");
    printf("||            0--END    (结束)    1--entry  (输入)              ||\n");
    printf("||            2--modify (修改)    3-insert  (添加)              ||\n");
    printf("||            4--delete (删除)    5--search (查找与显示)        ||\n");
    printf("||                                                              ||\n");
    printf("                          your choose:");
    int choose;
    scanf("%d", &choose);
    return choose;
}//用户选择界面

void sc(stu p)
{
    printf("||             请根据提示输入学生信息!               ||\n");
    printf("                     学号:");
    scanf("%d", &p->ID);
    printf("                     姓名:");
    scanf("%s", p->name);
    printf("                     性别："); 
	scanf("%s", p->sex); 
    printf("                     寝室号:");
	scanf("%d",&p->houseid);
	printf("                     专业:");
	scanf("%s", p->professor);
	printf("                     班级:");
	scanf("%s", p->Class);  
}//用户界面输入


void pr(stu p)
{
    printf("||                   学生信息:                       ||\n");
	printf("学号:%d\n",p->ID);
    printf("姓名:%s\n",p->name);
	printf("性别:%s\n",p->sex); 
	printf("宿舍号:%d\n",p->houseid);
	printf("专业:%s\n",p->professor);
	printf("班级:%s\n",p->Class);
}//用户界面输出

void new_list(stu head)
{
    stu p, q;
    p = head;
    int a;
    do
    {
        q = (stu)malloc(sizeof(Stu));
        sc(q);
        p->next = q;
        q->prior = p;
        p = q;
        p->next = NULL;
        printf("                        继续输入? 1/0  ");
        scanf("%d", &a);
    } while (a == 1);
}//建立新的数据链表

int read_file(stu head)
{
    stu p = head, q;
    FILE* fp;
    if ((fp = fopen("student.txt", "r")) == NULL) return 0;
    else
    {
        fp = fopen("student.txt", "r");
        while (!feof(fp))
        {
            q = (stu)malloc(sizeof(Stu));
    		fscanf(fp, "%d", &p->ID);
    		fscanf(fp, "%s", p->name);
			fscanf(fp, "%s", p->sex);
			fscanf(fp, "%d", &p->houseid);
			fscanf(fp, "%s", p->professor);
			fscanf(fp, "%s", p->Class);
            p->next = q;
            q->prior = p;
            q->next = NULL;
            p = q;
        }
        p->next = NULL;
        fclose(fp);
        return 1;
    }
}//读取文件中的数据

void save_file(stu head)
{
    stu p = head;
    FILE* fp;
    fp = fopen("student.txt", "wb+");
    while (p->next != NULL)
    {
        p = p->next;
        	fprintf(fp, "%d ", p->ID);
    		fprintf(fp, "%s ", p->name);
			fprintf(fp, "%s ", p->sex);
			fprintf(fp, "%d ", p->houseid);
			fprintf(fp, "%s ", p->professor);
			fprintf(fp, "%s ", p->Class);
       		fprintf(fp, "\n");
        	fprintf(fp, "\n");
    }
    fclose(fp);
}//把内存中的数据保存到文件

stu search_key(stu head)
{
    stu p = head;
    int choose;
    printf("可根据以下关键词查询学生信息，请选择:\nNO:1--学号\nNO:2--姓名\nNO:3--宿舍号\n");
    scanf("%d", &choose);
    if (choose == 1)
    {
        int a;
        printf("输入要查询学生的学号:");
        scanf("%d", &a);
        while (p->next != NULL)
        {
            p = p->next;
            if (a == p->ID)
                return p;//查询成功返回指针
        }
        if (p->next == NULL)
            return NULL;//查询失败返回空
    }
    else if (choose == 2)
    {
        char b[80];
        printf("输入要查询学生的姓名:");
        scanf("%s", b);
        while (p->next != NULL)
        {
            p = p->next;
            if (!strcmp(b, p->name))
                return p;
        }
        if (p->next == NULL)
            return NULL;
    }
	else if(choose == 3)
	{
		int c;
		printf("输入要查询学生的房间号:");
		scanf("%d",&c);
		while(p->next != NULL)
		{
			p = p->next;
			if(c == p->houseid)
			  return p;
		}
		if (p->next == NULL)
            return NULL;
	}
}//用关键词语查询信息

void search_list(stu head)
{
    stu p = head, q;
    int choose;
    printf("        你可以选择以下两种方式!         \n");
    printf("  1--显示所有信息!  2--关键词查找部分信息!  \n");
    printf("你的选择：");
    scanf("%d", &choose);
    if (choose == 1)
    {
        printf("所有学生信息如下： \n");
        int a = 1;
        while (p->next != NULL)
        {
            p = p->next;
            printf("                            (%d)                                  \n", a++);
            pr(p);
        }//打印链表
    }
    else if (choose == 2)
    {
        q = search_key(head);//接收关键词语查询信息返回的指针
        if (q != NULL)
        {
            printf("你所查找的信息如下:\n");
            pr(q);
        }
        else if (q == NULL) printf("未找到相关信息\n");
    }
}//查询信息

void modify_list(stu head)
{
    stu q = head, p;
    printf("请输入你要修改的信息关键词!\n");
    p = search_key(q);
    printf("你将要修改的数据\n");
    pr(p);
    printf("你想要修改那条信息?\n");
    printf("1--学号\n2--姓名\n3--性别\n4--房间号\n5--专业\n6--班级\n请选择: ");
    int a;
    scanf("%d", &a);
    printf("输入新的数据:");
    switch (a)
    {
    case 1:scanf("%d", &p->ID); break;
    case 2:scanf("%s", p->name); break;
	case 3:scanf("%s", p->sex); break;
	case 4:scanf("%d", &p->houseid); break;
	case 5:scanf("%s", p->professor); break;
	case 6:scanf("%s", p->Class); break;
    }
}//修改信息

void delete_list(stu head)
{
    stu p = head, q;
    printf("请输入你要删除数据的关键词!\n");
    q = search_key(p);
    if (q == NULL) printf("未找到相关信息\n");
    else if (q != NULL)
    {
        printf("你将要删除的数据\n");
        pr(q);
        printf("确定删除输入1，否则输入0  ");
        int a;
        scanf("%d", &a);
        if (a == 1)
        {
            if (q->next != NULL)
            {
                q->prior->next = q->next;
                q->next->prior = q->prior;
                free(q);
            }
            else
            {
                q->prior->next = q->next;
                q->prior = NULL;
                free(q);
            }
        }
    }

}//删除信息

void insert_list(stu head)
{
    stu p = head, q, l;
    printf("请输入你希望添加数据节点关键词!\n");
    q = search_key(p);
    if (q == NULL) printf("未找到相关信息\n");
    else if (q != NULL)
    {
        printf("输入你要插入的数据:\n");
        pr(q);
        printf("添加在前面输1，添加在后面输0  ");
        int a;
        scanf("%d", &a);
        if (a == 1)
        {
            if (q->next != NULL)
            {
                l = (stu)malloc(sizeof(Stu));
                sc(l);
                l->next = q->next;
                l->prior = q;
                q->next->prior = l;
                q->next = l;
            }//非最后一个的添加
            else
            {
                l = (stu)malloc(sizeof(Stu));
                sc(l);
                q->next = l;
                l->prior = q;
                l->next = NULL;
            }//最后一个的添加
        }//添加后面
        else if (a == 0)
        {
            l = (stu)malloc(sizeof(Stu));
            sc(l);
            l->prior = q->prior;
            l->next = q;
            q->prior->next = l;
            q->prior = l;
        }//添加前面
    }
}//插入信息

int free_list(stu head)
{
    stu p = head;
    int choose;
    printf("               你将开始输入信息!                              \n");
    printf("               你是否要销毁之前的数据!                        \n");
    printf("                 输入1确定，输入0取消  ");
    scanf("%d", &choose);
    if (choose == 1)
    {
        p->next->prior = NULL;
        p->next = NULL;
        printf("你的数据已经销毁!\n");
        return 1;
    }
    else if (choose == 0) return 0;
}//销毁链表

void save_list2(stu head)
{
    stu p;
    for (p = head; p->next != NULL; p = p->next)
    {}
    new_list(p);
}

int main()
{
    stu head;
    head = creat_head();
    printf("==================================================================\n");
    printf("||                           Hello!                             ||\n");
    printf("||     This program is collecting the info of the works!        ||\n");
    printf("==================================================================\n");
    int choose, i = 0;
    i = read_file(head);//检测是否存在文件,如果存在则读取进内存
    while (1)//循环让用户选择功能
    {
        choose = user_choose();
        switch (choose)
        {
        case 1:if (i == 0)
        {
            new_list(head);
            save_file(head);
            i = 1;
            break;
        } 
              else if (i == 1) 
        {
            int a;
            a = free_list(head);
            if (a == 0) {
                save_list2(head);
                save_file(head);
                break;
            }
            else if (a == 1)
            {
                new_list(head);
                save_file(head);
                break;
            }
        }
        case 2:if (i == 0)
        {
            printf("请先输入数据再进行该操作\n");
            break;
        }
              else
        {
            modify_list(head);
            save_file(head);
            break;
        }//修改数据
        case 3:if (i == 0)
        {
            printf("请先输入数据再进行该操作\n");
            break;
        }
              else
        {
            insert_list(head);
            save_file(head);
            break;
        }//插入操作
        case 4:if (i == 0)
        {
            printf("请先输入数据再进行该操作\n");
            break;
        }
              else
        {
            delete_list(head);
            save_file(head);
            break;
        }//删除操作
        case 5:if (i == 0)
        {
            printf("请先输入数据再进行该操作\n");
            break;
        }
              else
        {
            search_list(head);
            save_file(head);
            break;
        }//查找操作
        case 0:exit(0);//退出程序
        }
    }
    return 0;
}//主程序 