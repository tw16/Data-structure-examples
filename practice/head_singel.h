#ifndef _HEAD_SINGEL_H_
#define _HEAD_SINGEL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//如果没有定义这个宏，就默认数据域为int型
#ifndef DATATYPE
typedef int datatype;
#endif


//设计节点
struct node
{
	datatype data;
	struct node *next;
};


//初始化一条带头结点的空链表
//成功返回头节点地址
//
static struct node *init_list(void)
{
	struct node *head = malloc(sizeof(struct node)); // 分配给节点空间
	if(NULL == head)	//返回为NULL，失败
	{
		perror("malloc head failed");
		return NULL;
	}
	
	head->next = NULL;	
	
	return head;	//返回头节点的地址
}

//创建一个新节点
//传入一个datatype的数据
static struct node *create_node(datatype i)
{
	struct node *newnode = malloc(sizeof(struct node));
	if(NULL == newnode)	//返回为NULL，失败
	{
		perror("malloc newnode failed");
		return NULL;
	}
	
	newnode->data = i;   //存储数据
	newnode->next = NULL;
	
	return newnode; //返回新创建的节点的地址
}


//从尾巴上插入一个节点
//head：链表头
//newnode：新节点
static void inster_tial(struct node *head, struct node *newnode)
{
	struct node *tmp = head;
	
	while(tmp->next != NULL)
	{
		tmp = tmp->next; //如果tmp下一个节点不为空，就把下一个节点地址给tmp
	}
	
	tmp->next = newnode;
	
	return ;
}


//从头节点（任意节点）后面插入一个节点
static void inster_head(struct node *head, struct node *newnode)
{
	//把头节点的原来的下一个节点存到新节点的next里面
	newnode->next = head->next;
	
	//把细节点存到头节点的next里面
	head->next = newnode;
	
	return ;
}


//按数据查找
//返回值位查找到的数据的前一个节点
static struct node *find_node(struct node *head, datatype find_data)
{
	//遍历链表的每个节点
	while(head->next != NULL)
	{
		if(head->next->data == find_data)
			return head;
		head = head->next;	//如果当前节点数据没有比对成功，就比对下一个
	}
	
	return NULL; //没有找到节点
}

//删除一个节点
//dest_node：要删除的前一个节点
static struct node *delete_node(struct node *dest_node, struct node *del_node)
{
	dest_node->next = del_node->next;
	del_node->next = NULL;
	
	return del_node;
}

//移动一个节点到某个节点后面
//dest_node：是要插入的位置的前一个节点
//src_node：要移动的节点的前一个节点
//src_node->next：要移动的那个节点
static void move_node(struct node *dest_node, struct node *src_node)
{
	struct node * del_node = delete_node(src_node, src_node->next);
	
	//插入到目标位置的后面
	inster_head(dest_node, del_node);
}

//遍历所有节点
static void dispaly_list(struct node *head)
{
	struct node *tmp = head;
	
	while(tmp->next != NULL)
	{
		printf("%d->", tmp->next->data);
		tmp = tmp->next;
	}
	printf("\n");
	
	return ;
}

//判断空链表
static bool empty_list(struct node *head)
{
	if(head->next == NULL)
		return true;
	
	return false;
}


//释放单个节点
static void free_node(struct node **fnode)
{
	free(*fnode);	//释放已删除的节点空间
	*fnode = NULL;	//给指向这片空间的指针指向空
}

#endif