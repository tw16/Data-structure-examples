// date:2022年 08月 01日 星期一 09:37:51 CST
// author: A
// path: /mnt/hgfs/2206预科/03-数据结构/01-链表/kernel_list
#include <stdio.h>
#include <stdlib.h>
#include "kernel_list.h"


/* 

研读内核代码，用Linux内核链表重做第7题（内核链表）

 */

//节点设计
struct node
{
	int data;
	struct list_head list;
};


//初始化链表、
struct node *list_init(void)
{
	struct node* head = calloc(1, sizeof(struct node));

	INIT_LIST_HEAD(&head->list);
	return head;
}

//创建新节点
struct node *create_node(int data)
{
	struct node* head = calloc(1, sizeof(struct node));
	
	INIT_LIST_HEAD(&head->list);
	head->data = data;
	return head;
}

//奇偶排序
void ox_sort(struct node *head)
{
	struct list_head *pos = NULL, *n = NULL;
	struct node *tmp = NULL;
	int flag = 0;
	//向前找偶数移动到链表末尾
	list_for_each_prev_safe(pos, n, &head->list)
	{
		tmp = list_entry(pos, struct node, list);
		if(tmp->data % 2 == 0 && flag != 0)
			list_move_tail(pos, &head->list);
		
		flag = 1;
	}

	// 向后遍历打印整理后的结果
	list_for_each(pos, &head->list)
	{
		tmp = list_entry(pos, struct node, list);

		printf("%d->", tmp->data);
	}
	printf("\n");
}

 
int main(int argc, char *argv[])
{
	//1，初始化一条链表
	struct node *head = list_init();
	
	int i;
	for(i=1; i<=10; i++)
	{
		struct node* newnode = create_node(i);
		
		list_add_tail(&newnode->list, &head->list);
	}
	
	ox_sort(head);
  
	return 0;
}
