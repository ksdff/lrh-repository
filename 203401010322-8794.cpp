#include"stdio.h"
#include"stdlib.h"
#include"string.h"

typedef struct student
{
	int ID;//ѧ��
	char name[10];//����
	char sex[10];//�Ա�
	int houseid;//�����
	char professor[20];//רҵ
	char Class[10];//�༶	
	struct student* prior;
    struct student* next;
}*stu,Stu;//ѧ����Ϣ

stu creat_head()
{
    stu head;
    head = (stu)malloc(sizeof(Stu));
    head->prior = NULL;
    head->next = NULL;
    return head;
}//��ʼ��ͷ���

int user_choose()
{ 
    printf("||                     ��ϵͳ�������¹���                       ||\n");
    printf("||                          ��ѡ��!                             ||\n");
    printf("||            0--END    (����)    1--entry  (����)              ||\n");
    printf("||            2--modify (�޸�)    3-insert  (���)              ||\n");
    printf("||            4--delete (ɾ��)    5--search (��������ʾ)        ||\n");
    printf("||                                                              ||\n");
    printf("                          your choose:");
    int choose;
    scanf("%d", &choose);
    return choose;
}//�û�ѡ�����

void sc(stu p)
{
    printf("||             �������ʾ����ѧ����Ϣ!               ||\n");
    printf("                     ѧ��:");
    scanf("%d", &p->ID);
    printf("                     ����:");
    scanf("%s", p->name);
    printf("                     �Ա�"); 
	scanf("%s", p->sex); 
    printf("                     ���Һ�:");
	scanf("%d",&p->houseid);
	printf("                     רҵ:");
	scanf("%s", p->professor);
	printf("                     �༶:");
	scanf("%s", p->Class);  
}//�û���������


void pr(stu p)
{
    printf("||                   ѧ����Ϣ:                       ||\n");
	printf("ѧ��:%d\n",p->ID);
    printf("����:%s\n",p->name);
	printf("�Ա�:%s\n",p->sex); 
	printf("�����:%d\n",p->houseid);
	printf("רҵ:%s\n",p->professor);
	printf("�༶:%s\n",p->Class);
}//�û��������

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
        printf("                        ��������? 1/0  ");
        scanf("%d", &a);
    } while (a == 1);
}//�����µ���������

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
}//��ȡ�ļ��е�����

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
}//���ڴ��е����ݱ��浽�ļ�

stu search_key(stu head)
{
    stu p = head;
    int choose;
    printf("�ɸ������¹ؼ��ʲ�ѯѧ����Ϣ����ѡ��:\nNO:1--ѧ��\nNO:2--����\nNO:3--�����\n");
    scanf("%d", &choose);
    if (choose == 1)
    {
        int a;
        printf("����Ҫ��ѯѧ����ѧ��:");
        scanf("%d", &a);
        while (p->next != NULL)
        {
            p = p->next;
            if (a == p->ID)
                return p;//��ѯ�ɹ�����ָ��
        }
        if (p->next == NULL)
            return NULL;//��ѯʧ�ܷ��ؿ�
    }
    else if (choose == 2)
    {
        char b[80];
        printf("����Ҫ��ѯѧ��������:");
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
		printf("����Ҫ��ѯѧ���ķ����:");
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
}//�ùؼ������ѯ��Ϣ

void search_list(stu head)
{
    stu p = head, q;
    int choose;
    printf("        �����ѡ���������ַ�ʽ!         \n");
    printf("  1--��ʾ������Ϣ!  2--�ؼ��ʲ��Ҳ�����Ϣ!  \n");
    printf("���ѡ��");
    scanf("%d", &choose);
    if (choose == 1)
    {
        printf("����ѧ����Ϣ���£� \n");
        int a = 1;
        while (p->next != NULL)
        {
            p = p->next;
            printf("                            (%d)                                  \n", a++);
            pr(p);
        }//��ӡ����
    }
    else if (choose == 2)
    {
        q = search_key(head);//���չؼ������ѯ��Ϣ���ص�ָ��
        if (q != NULL)
        {
            printf("�������ҵ���Ϣ����:\n");
            pr(q);
        }
        else if (q == NULL) printf("δ�ҵ������Ϣ\n");
    }
}//��ѯ��Ϣ

void modify_list(stu head)
{
    stu q = head, p;
    printf("��������Ҫ�޸ĵ���Ϣ�ؼ���!\n");
    p = search_key(q);
    printf("�㽫Ҫ�޸ĵ�����\n");
    pr(p);
    printf("����Ҫ�޸�������Ϣ?\n");
    printf("1--ѧ��\n2--����\n3--�Ա�\n4--�����\n5--רҵ\n6--�༶\n��ѡ��: ");
    int a;
    scanf("%d", &a);
    printf("�����µ�����:");
    switch (a)
    {
    case 1:scanf("%d", &p->ID); break;
    case 2:scanf("%s", p->name); break;
	case 3:scanf("%s", p->sex); break;
	case 4:scanf("%d", &p->houseid); break;
	case 5:scanf("%s", p->professor); break;
	case 6:scanf("%s", p->Class); break;
    }
}//�޸���Ϣ

void delete_list(stu head)
{
    stu p = head, q;
    printf("��������Ҫɾ�����ݵĹؼ���!\n");
    q = search_key(p);
    if (q == NULL) printf("δ�ҵ������Ϣ\n");
    else if (q != NULL)
    {
        printf("�㽫Ҫɾ��������\n");
        pr(q);
        printf("ȷ��ɾ������1����������0  ");
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

}//ɾ����Ϣ

void insert_list(stu head)
{
    stu p = head, q, l;
    printf("��������ϣ��������ݽڵ�ؼ���!\n");
    q = search_key(p);
    if (q == NULL) printf("δ�ҵ������Ϣ\n");
    else if (q != NULL)
    {
        printf("������Ҫ���������:\n");
        pr(q);
        printf("�����ǰ����1������ں�����0  ");
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
            }//�����һ�������
            else
            {
                l = (stu)malloc(sizeof(Stu));
                sc(l);
                q->next = l;
                l->prior = q;
                l->next = NULL;
            }//���һ�������
        }//��Ӻ���
        else if (a == 0)
        {
            l = (stu)malloc(sizeof(Stu));
            sc(l);
            l->prior = q->prior;
            l->next = q;
            q->prior->next = l;
            q->prior = l;
        }//���ǰ��
    }
}//������Ϣ

int free_list(stu head)
{
    stu p = head;
    int choose;
    printf("               �㽫��ʼ������Ϣ!                              \n");
    printf("               ���Ƿ�Ҫ����֮ǰ������!                        \n");
    printf("                 ����1ȷ��������0ȡ��  ");
    scanf("%d", &choose);
    if (choose == 1)
    {
        p->next->prior = NULL;
        p->next = NULL;
        printf("��������Ѿ�����!\n");
        return 1;
    }
    else if (choose == 0) return 0;
}//��������

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
    i = read_file(head);//����Ƿ�����ļ�,����������ȡ���ڴ�
    while (1)//ѭ�����û�ѡ����
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
            printf("�������������ٽ��иò���\n");
            break;
        }
              else
        {
            modify_list(head);
            save_file(head);
            break;
        }//�޸�����
        case 3:if (i == 0)
        {
            printf("�������������ٽ��иò���\n");
            break;
        }
              else
        {
            insert_list(head);
            save_file(head);
            break;
        }//�������
        case 4:if (i == 0)
        {
            printf("�������������ٽ��иò���\n");
            break;
        }
              else
        {
            delete_list(head);
            save_file(head);
            break;
        }//ɾ������
        case 5:if (i == 0)
        {
            printf("�������������ٽ��иò���\n");
            break;
        }
              else
        {
            search_list(head);
            save_file(head);
            break;
        }//���Ҳ���
        case 0:exit(0);//�˳�����
        }
    }
    return 0;
}//������ 