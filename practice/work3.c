// date:2022年 07月 27日 星期三 09:10:58 CST
// author: A
// path: /mnt/hgfs/2206预科/03-数据结构/01-链表/singel_list
#include <stdio.h>
#include "head_singel.h"

/* 

建立一个包含若干整数的单向链表，然后通过某些算法，将其中的数据翻转。（单向链表）

 */

void reversal(struct node *head);

// struct A
// {
	// int a;
	// char b;
// };

// #define DATATYPE
// typedef char datatype;
// typedef struct A datatype;
 
 
int main(int argc, char *argv[])
{
	//1、初始化一条链表
	struct node *head = init_list();
	if(head == NULL)
	{
		printf("链表初始化失败\n");
		return -1;
	}
	
	// 2、插入一些自然数
	int i, n;
	printf("请输入一个整数n\n");
	scanf("%d", &n);
	
	//插入1~n个整数,每一个整数作为一个节点
	for(i=1; i<=n; i++)
	{
		struct node *newnode = create_node(i);
		if(NULL == newnode)
		{
			printf("节点创建失败\n");
			continue;
		}
		
		//插入链表新节点到尾巴上
		inster_tial(head, newnode);
	}
	
	//遍历链表
	dispaly_list(head);
	
	//反转
	reversal(head);
	dispaly_list(head);
	
  
	return 0;
}

//反转
void reversal(struct node *head)
{
	//p：链表断开后第一个节点的指针
	struct node *p = head->next, *q=NULL;
	head->next = NULL; //链表断开
	
	//遍历p到最后一个节点结束，p是要被移动的节点
	while(p->next != NULL)
	{
		q = p->next;  //记录p的下一个节点
		// p->next = NULL;
		p->next = head->next; //把头节点的下一个存在新节点
		head->next = p;	//插入到头节点后面
		p = q;
	}
	p->next = head->next;  //p退出循环的那次节点
	head->next = p;
}
