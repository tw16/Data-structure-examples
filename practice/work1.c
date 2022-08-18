// date:2022年 07月 28日 星期四 16:20:24 CST
// author: A
// path: /mnt/hgfs/2206预科/03-数据结构/01-链表/work
//1、实现头插法，输入一个正整数，实现元素的头插，输入小于等于0的数字结束插入，显示链表的所有节点数据

#include <stdio.h>
#include "singel_list.h"
 
int main(int argc, char *argv[])
{
	//1, 初始化一条链表
	link_list head = list_init();
	if(head == NULL)
	{
		printf("链表创建失败\n");
		return -1;
	}
	
	//2, 输入数据
	int n;
	printf("输入整数, 创建节点插入链表\n输入负数,结束输入遍历链表\n");
	for(; ;)
	{
		scanf("%d", &n);
		if(n <= 0)
		{
			break;
		}
		link_list newnode = create_node(n);
		if(newnode == NULL)
		{
			printf("节点创建失败\n");
			continue;
		}
		
		list_add_head(head, newnode);
	}
	
	list_dispaly(head);
  
	return 0;
}
