// date:2022年 07月 29日 星期五 15:24:16 CST
// author: A
// path: /mnt/hgfs/2206预科/03-数据结构/01-链表/double_list

/* 

用链表存储若干自然数。比如输入一个整数10后：（双向循环链表）
	使得容器中存储： 1	2	3	4	5	6	7	8	9	10
	要求将其重排成： 1	3	5	7	9	10	8	6	4	2 （即奇数升序偶数降序）


 */



#include <stdio.h>
#include "double_list.h"


void rearrange(link_list head)
{
	link_list p = head, q;
	int flag = 1;
	
	while(p->prev != head)
	{
		p = p->prev;
		if(p->data%2 == 0 && flag == 0)
		{
			p->prev->next = p->next;
			p->next->prev = p->prev;
			list_add_tail(head, p);
			p = q;
		}
		else
		{
			q = p;
		}
		flag = 0;
	}
}
 
int main(int argc, char *argv[])
{
	//1, 初始化一条链表
	link_list head = list_init();
	
	//2, 初始化一些整数
	int i, n;
	printf("请输入整数n\n");
	scanf("%d", &n);
	
	for(i=1; i<=n; i++)
	{
		link_list newnode = create_node(i);
		
		list_add_tail(head, newnode);
	}
	
	list_next_dispaly(head);
	
	rearrange(head);
	list_next_dispaly(head);
	
  
	return 0;
}
