// date:2022年 07月 29日 星期五 09:08:43 CST
// author: A
// path: /mnt/hgfs/2206预科/03-数据结构/01-链表/work

#ifndef _DOUBLE_LIST_H_
#define _DOUBLE_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#ifndef DATATYPE
typedef int datatype;
#endif


//结构体节点设计
typedef struct node
{
	datatype data;	//数据：datatype是自定义的类型别名
	struct node *prev;	//前驱指针：存储前一个节点的地址
	struct node *next;	//后继指针：存储后一个节点的地址
}link_node, *link_list;	//link_node是struct node的类型别名， link_liststruct node*的类型别名


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
	printf("后向：");
	link_list tmp = head;
	while(tmp->next != head)
	{
		tmp = tmp->next;
		printf("%d->", tmp->data);
	}
	printf("\n");
}

//前向遍历链表
//head：链表头节点
static void list_prev_dispaly(link_list head)
{
	if( list_empty(head) )
	{
		printf("链表为空，没有可以遍历的节点\n");
		return ;
	}
	printf("前向：");
	link_list tmp = head;
	while(tmp->prev != head)
	{
		tmp = tmp->prev;
		printf("%d->", tmp->data);
	}
	printf("\n");
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
		if(tmp->data == data)
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

//移动一个src_data节点到dest_data数据节点后面
//head：链表头节点
//src_data：要移动的数据节点
//dest_data：数据节点移动的位置在dets_data数据节点后面
//成功：返回true
//失败：返回false
static bool move_node(link_list head, datatype src_data, datatype dest_data)
{
	link_list src_node = _delete_node(head, src_data);
	link_list dest_node = find_node(head, dest_data);
	if(src_node != NULL && dest_node != NULL)
	{
		list_add_head(dest_node, src_node);
		return true;
	}
	return false;
}


//更新节点数据
//head：链表头节点
//src_data：原始数据
//dest_data：要修改的新数据
//成功：返回true
//失败：返回false
static bool updata_node(link_list head, datatype src_data, datatype dest_data)
{
	link_list fnode = find_node(head, src_data);
	if(fnode != NULL)
	{
		fnode->data = dest_data;
		return true;
	}
	return false;
}


//销毁链表
//head：链表头节点
static void list_distory(link_list *head)
{
	if( list_empty(*head) )
	{
		free(*head);
		*head = NULL;
		return ;
	}
	
	link_list tmp = *head;
	link_list dis_node = NULL;
	while(tmp->next != *head)
	{
		dis_node = tmp->next;
		tmp->next = dis_node->next;
		free(dis_node);
	}
	free(*head);
	*head = NULL;
}



#endif