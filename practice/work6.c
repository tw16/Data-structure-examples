// date:2022年 07月 29日 星期五 09:08:43 CST
// author: A
// path: /mnt/hgfs/2206预科/03-数据结构/01-链表/work

/* 

4、设计一个商品信息管理系统（双向循环链表）
	（1）商品信息包含：编号、名称、类别、价格
	（2）能实现商品信息的增删查改
	（3）要求插入信息的时候，保持价格的从小到大的顺序

 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ESP 0.000001

struct goods
{
	char goodsname[20];	//名称
	int number;	//编号
	char class[20];	//类别
	float price;	//单价
};


typedef struct goods datatype;

//结构体节点设计
typedef struct node
{
	datatype data;	//数据：datatype是自定义的类型别名
	struct node *prev;	//前驱指针：存储前一个节点的地址
	struct node *next;	//后继指针：存储后一个节点的地址
}link_node, *link_list;	//link_node是struct node的类型别名， link_liststruct node*的类型别名

void sort_insert(link_list head, link_list node);

//初始化一条双向循环链表
//成功：返回头节点地址
//失败：返回NULL
static link_list list_init(void)
{
	link_list head = calloc(1, sizeof(link_node));
	if(head != NULL)
	{
		head->next = head;
		head->prev = head;
		
		return head;
	}
	return NULL;
}


// 创建一个节点
// data: 传入的数据
//成功：返回新节点地址
//失败：返回NULL
static link_list create_node(datatype data)
{
	link_list newnode = calloc(1, sizeof(link_node));
	if(newnode != NULL)
	{
		newnode->next = newnode;
		newnode->prev = newnode;
		newnode->data = data; //把数据存入新的节点数据域
		
		return newnode;
	}
	return NULL;
}


//从链表尾部添加一个节点
//head：链表头节点
//newnode：链表外节点
static void list_add_tail(link_list head, link_list newnode)
{
	newnode->next = head;
	newnode->prev = head->prev;
	head->prev->next = newnode;
	head->prev = newnode;
}


void goods_init(link_list head)
{
	struct goods a[5] = 
	{
		{.goodsname="apple", .number=1000, .class="fruit", .price=6.5},
		{.goodsname="banana", .number=1001, .class="fruit", .price=3.0},
		{.goodsname="grape", .number=1002, .class="fruit", .price=10.0},
		{.goodsname="salad", .number=1003, .class="flavour", .price=20.5},
		{.goodsname="salt", .number=1004, .class="flavour", .price=2.5}
	};
	
	int i;
	for(i=0; i<5; i++)
	{
		link_list newnode = create_node(a[i]);
		if(newnode == NULL)
		{
			printf("创建节点失败\n");
			continue;
		}
		
		sort_insert(head, newnode);
	}
}

//判断链表是否为空
//返回true，表示为空
//返回false，表示不为空
static bool list_empty(link_list head)
{
	return head->next == head ? true : false;
}

//后向遍历链表
//head：链表头节点
static void list_next_dispaly(link_list head)
{
	if( list_empty(head) )
	{
		printf("链表为空，没有可以遍历的节点\n");
		return ;
	}

	link_list tmp = head;
	
	printf("====================================================\n");
	printf("名称\t编号\t类别\t价格\n");	//打印一个表头
	while(tmp->next != head)
	{
		tmp = tmp->next;
		printf("%s\t%d\t%s\t%.2f￥\n", tmp->data.goodsname, tmp->data.number, tmp->data.class, tmp->data.price);
	}
	printf("----------------------------------------------------\n");
}


//查找一个节点
//head：链表头节点
//data：要查找的数据
//成功：返回找到的数据节点
//失败：返回NULL
static link_list find_node(link_list head, datatype data)
{
	link_list tmp = head;
	while(tmp->next != head)
	{
		tmp = tmp->next;
		if(tmp->data.number == data.number)
		{
			return tmp;
		}
	}
	return NULL;
}

//删除一个节点不释放
//head：链表头节点
//data：要删除的数据节点
//成功：返回脱离链表的数据节点
//失败：返回NULL
static link_list _delete_node(link_list head, datatype data)
{
	link_list fnode = find_node(head, data);
	if(fnode != NULL)
	{
		fnode->prev->next = fnode->next;
		fnode->next->prev = fnode->prev;
		fnode->prev = NULL;
		fnode->next = NULL;
		return fnode;
	}
	return NULL;
}


//删除一个节点并释放节点空间
//head：链表头节点
//data：要删除的数据节点
//成功：true，已删除释放该数据节点
//失败：false,没找到该数据节点
static bool delete_node(link_list head, datatype data)
{
	link_list del_node = _delete_node(head, data);
	if(del_node != NULL)
	{
		free(del_node);
		del_node = NULL;
		return true; //删除成功
	}
	return false; //删除失败
}

//从头部添加一个节点
//head：链表头节点
//newnode：链表外节点
static void list_add_head(link_list head, link_list newnode)
{
	newnode->prev = head;
	newnode->next = head->next;
	head->next->prev = newnode;
	head->next = newnode;	
}

void sort_insert(link_list head, link_list node)
{
	if( list_empty(head) )
	{
		list_add_tail(head, node);
		return ;
	}
	
	link_list tmp = head, ins = NULL;
	
	while(tmp->prev != head)
	{
		tmp = tmp->prev;
		if( tmp->data.price <= node->data.price )
		{
			list_add_head(tmp, node);
			return ;
		}
	}
	list_add_head(head, node);
}

bool add_goods(link_list head)
{
	datatype data;
	link_list tmp = NULL;
	
	printf("请输入新录入商品的信息\n");
	printf("----------------------------------------------------\n");
	printf("名称\t编号\t类别\t价格\n");	
	scanf("%s%d%s%f", data.goodsname, &data.number, data.class, &data.price);
	
	tmp = find_node(head, data);	//新录入商品是否已经存在
	if(tmp != NULL)
	{
		return false;
	}
	
	tmp = create_node(data);
	if(tmp == NULL)
	{
		return false;
	}
	
	sort_insert(head, tmp);	//去找到顺序插入
	return true;
}

void delete_goods(link_list head)
{
	datatype data;
	
	printf("请输入你要删除的商品编号\n");
	scanf("%d", &data.number);
	delete_node(head, data);
}

void find_goods(link_list head)
{
	datatype data;
	
	printf("请输入你要查找的商品编号\n");
	scanf("%d", &data.number);
	
	printf("----------------------------------------------------\n");
	link_list fnode = find_node(head, data);
	if(fnode != NULL)
	{	
		printf("%s\t%d\t%s\t%.2f￥\n", fnode->data.goodsname, fnode->data.number, fnode->data.class, fnode->data.price);
		getchar();
		getchar();
		return ;
	}
	
	printf("没找到该商品信息\n");
}


bool change_price(link_list head)
{
	datatype data;
	
	printf("请输入你要修改的商品编号\n");
	scanf("%d", &data.number);
	
	link_list fnode = find_node(head, data);
	if(fnode != NULL)
	{
		printf("请输入你要修改的商品新价格\n");
		scanf("%f", &fnode->data.price);
		return true;
	}
	return false;
}

 
int main(int argc, char *argv[])
{
	//1, 初始化一条链表
	link_list head = list_init();
	if(head == NULL)
	{
		printf("链表创建失败\n");
		return -1;
	}
	
	goods_init(head);
	
	int option;
	printf("进入商品管理系统....\n");
	while(1)
	{
		list_next_dispaly(head);
		printf("1.添加商品\t2.删除商品\n");
		printf("3.查找商品\t4.修改价格\n");
		printf("====================================================\n");
		
		// while(getchar() != '\n')
			// NULL;
		printf("\033[1;31;40m");
		scanf("%d", &option);
		printf("\033[0m");
		
		while(getchar() != '\n')
			NULL;
		
		switch(option)
		{
			case 1:
				add_goods(head);
				break;
			case 2:
				delete_goods(head);
				break;
			case 3:
				find_goods(head);
				break;
			case 4:
				change_price(head);
				break;
			default:
				printf("输入选项有误,没有对应的操作\n");
		}
	}
  
	return 0;
}
