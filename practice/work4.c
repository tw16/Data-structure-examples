// date:2022年 07月 28日 星期四 19:01:49 CST
// author: A
// path: /mnt/hgfs/2206预科/03-数据结构/01-链表/work

/* 
3、用单链表初始化一个简单的学生信息管理系统，学生信息包含：姓名、学号、年龄、成绩
	（1）初始化至少5条信息
	（2）可以随时新增一条学生信息
	（3）可以随时通过学号删除一条学生的信息
	（4）通过学号和姓名查找学生成绩
	（5）通过学号找到学生信息并修改学生成绩

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PRINTF_LINE printf("=======================================================\n")

//学生信息结构体
typedef struct student
{
	char name[20];
	unsigned short num;
	unsigned short age;
	unsigned short score;
}datatype;

//链表节点设计
typedef struct node
{
	datatype data;	//数据域:自定义数据类型datatype
	struct node *next;	//指针域:指向下一个节点
}link_node, *link_list; //struct node  与  struct node *的别名


//初始化一条带头空链表
//无参数
//成功: 返回头节点
//失败: 返回NULL
static link_list list_init(void)
{
	link_list head = calloc(1, sizeof(link_node));	//分配空间初始化为0
	if(head != NULL)
	{
		head->next = head; //指向自己,自循环
		return head;
	}
	perror("calloc head failed");	//打印calloc()失败原因
	return NULL; 
}

//创建一个节点
//data: 节点存储的数据
//成功: 返回新节点
//失败: 返回NULL
static link_list create_node(datatype data)
{
	link_list newnode = calloc(1, sizeof(link_node));
	if(newnode != NULL)
	{
		newnode->next = newnode; //指向自己,自循环
		newnode->data = data; //存入数据	
		return newnode;
	}
	perror("calloc newnode failed");	//打印calloc()失败原因
	return NULL; 
}

//判断链表是否为空
//head: 链表头节点
//空链表: 返回true
//非空链表: 返回false
static bool list_empty(link_list head)
{
	return head->next == head ? true : false;
}

//在head节点后面插入newnode节点
//head: 链表中任意一个节点
//newnode: 链表外节点
static void list_add_head(link_list head, link_list newnode)
{
	newnode->next = head->next;
	head->next = newnode;
}

//在链表的最后一个节点后添加一个节点
//head: 链表头节点
//newnode: 链表外节点
static void list_add_tail(link_list head, link_list newnode)
{
	link_list tmp = head;
	while(tmp->next != head)
	{
		tmp = tmp->next;
	}
	tmp->next = newnode;
	newnode->next = head;
}

//删除一个节点不释放内存
// head: 链表头节点
// data: 要删除的数据
// 成功:返回已删除的节点
// 失败:返回NULL
static link_list _delete_node(link_list head, datatype data)
{
	link_list tmp = head, del_node;
	while(tmp->next != head)
	{	
		if(tmp->next->data.num == data.num)
		{
			del_node = tmp->next;	//del_node存储要删除的节点
			tmp->next = del_node->next;	//把del_node脱离链表
			del_node->next = del_node;	//del_node指向自己
			return del_node;	//返回已脱离链表未释放的节点del_node
		}
		tmp = tmp->next;
	}
	return NULL;	//没有找到该数据的节点
}


//删除节点并释放内存
// head: 链表头节点
// data: 要删除的数据
// 成功: 返回true
// 失败: 返回false
static bool delete_node(link_list head, datatype data)
{
	link_list del_node = _delete_node(head, data);
	if(del_node != NULL)
	{
		free(del_node); //释放已删除的节点
		return true;	//删除成功
	}
	return false;	//删除失败,没有该数据
}


// 查找一个节点
// head: 链表头节点
// data: 查找的数据
// 成功: 返回查找到的节点
// 失败: 返回NULL
static link_list find_node_num(link_list head, datatype data)
{
	link_list tmp = head;
	while(tmp->next != head)
	{	
		if(tmp->next->data.num == data.num)
		{
			return tmp->next;	//返回查找到的节点
		}
		tmp = tmp->next;
	}
	return NULL;	//没有找到该数据的节点
}

static link_list find_node_name(link_list head, datatype data)
{
	link_list tmp = head;
	while(tmp->next != head)
	{	
		if( !strcmp(tmp->next->data.name, data.name) )
		{
			return tmp->next;	//返回查找到的节点
		}
		tmp = tmp->next;
	}
	return NULL;	//没有找到该数据的节点
}



//遍历链表
// head: 链表头节点
static void list_dispaly(link_list head)
{
	if(list_empty(head))
	{
		printf("链表为空\n");
		return ;
	}
	link_list tmp = head;
	PRINTF_LINE;
	printf("姓名\t学号\t年龄\t成绩\n");
	while(tmp->next != head)
	{
		tmp = tmp->next;
		printf("%s\t%hu\t%hu\t%hu\n", tmp->data.name, tmp->data.num, tmp->data.age, tmp->data.score );
	}
	PRINTF_LINE;
}

//更新节点信息
// head: 链表头节点
// src_data: 要修改的数据
// dest_data: 修改的新数据
//成功:返回true
//失败:返回false
// static bool updata_node(link_list head, datatype src_data, datatype dest_data)
// {
	// link_list fnode = find_node(head, src_data);
	// if(fnode != NULL)
	// {
		// fnode->data = dest_data;
		// return true;
	// }
	// return false;
// }

//销毁链表
static void list_destroy(link_list *head)
{
	link_list tmp = *head;
	link_list des_node = NULL;
	while(tmp->next != *head)
	{
		des_node = tmp->next;
		tmp->next = des_node->next;
		free(des_node);
	}
	free(*head);
	*head = NULL;
}

void init_student_info(link_list head)
{
	datatype a[5] = 
	{
		{.name = "lhl", .num = 1001, .age = 20, .score = 90},
		{.name = "zt", .num = 1002, .age = 21, .score = 94},
		{.name = "wym", .num = 1003, .age = 22, .score = 93},
		{.name = "hyk", .num = 1004, .age = 22, .score = 92},
		{.name = "ljy", .num = 1005, .age = 21, .score = 99}
	};
	
	//初始化5条学生信息
	int i;
	for(i=0; i<5; i++)
	{
		link_list newnode = create_node(a[i]);
		if(newnode == NULL)
		{
			printf("节点创建失败\n");
			continue;
		}
		list_add_tail(head, newnode);
	}
}

//添加一个学生信息 
void add_student_info(link_list head)
{
	datatype data;
	printf("请添加一个学生信息\n");
	printf("姓名\t学号\t年龄\t成绩\n");
	scanf("%s%hu%hu%hu", data.name, &data.num, &data.age, &data.score);
	
	link_list newnode = create_node(data);
	list_add_tail(head, newnode);
}


//删除一个学生信息
void num_delete_info(link_list head)
{
	datatype data;
	printf("请输入要删除的学生学号\n");
	scanf("%hu", &data.num);
	delete_node(head, data);
}

void find_info(link_list head)
{
	link_list fnode = NULL;
	int ch;
	datatype data;
	
	printf("输入1. 学号查找	2.姓名查找\n");
	scanf("%d", &ch);
	if(ch == 1)
	{
		printf("请输入要查询的学号\n");
		scanf("%hu", &data.num);
		fnode = find_node_num(head, data);
		printf("%s\t%hu\t%hu\t%hu\n", fnode->data.name, fnode->data.num, fnode->data.age, fnode->data.score );
	}
	else if(ch == 2)
	{
		printf("请输入要查询的姓名\n");
		scanf("%s", data.name);
		fnode = find_node_name(head, data);
		printf("%s\t%hu\t%hu\t%hu\n", fnode->data.name, fnode->data.num, fnode->data.age, fnode->data.score );
	}
	else
	{
		printf("输入无效选项\n");
		return ;
	}	
}

void change_info(link_list head)
{
	datatype data;
	printf("请输入要修改的学生学号\n");
	scanf("%hu", &data.num);
	link_list fnode = find_node_num(head, data);
	
	printf("请输入要修改的成绩\n");
	scanf("%hu", &data.score);
	fnode->data.score = data.score;
}
 
int main(int argc, char *argv[])
{
	//初始化链表
	link_list head = list_init();
	if(head == NULL)
	{
		printf("链表初始化失败\n");
		return -1;
	}
	
	//初始化5条学生信息
	init_student_info(head);
	// list_dispaly(head);
	int n;
	while(1)
	{
		list_dispaly(head);
		printf("\033[1;31;40m1. 添加学生信息\n\033[m");
		printf("2. 删除学生信息\n");
		printf("3. 查找学生信息\n");
		printf("4. 修改学生信息\n");
		
		scanf("%d", &n);
		switch(n)
		{
			case 1:
				add_student_info(head);
				break;
			case 2:
				num_delete_info(head);
				break;
			case 3:
				find_info(head);
				break;
			case 4:
				change_info(head);
				break;
			default:
				printf("输入无效选项\n");
		}
		
	}
  
	return 0;
}
