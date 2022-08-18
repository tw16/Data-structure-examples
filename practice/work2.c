// date:2022年 07月 28日 星期四 16:28:52 CST
// author: A
// path: /mnt/hgfs/2206预科/03-数据结构/01-链表/work

/* 

2、单链表操作，实现输入整数，做以下操作：
	（1）如果输入的是正整数，就将元素添加进去，如果有相同值的元素就不添加
	（2）如果输入的是负整数，就将该值的绝对值，从链表中删除，如果不存在请提示
	（3）如果输入的是0，则显示当前链表所有元素的值

 */

#include <stdio.h>
#include "singel.h"
 
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
	printf("请按规则输入数据\n");
	for(; ;)
	{
		scanf("%d", &n);
		if(n < 0)
		{
			if( !delete_node(head, -n) )
				printf("没有该数据\n");
		}
		else if(n > 0)
		{
			if( find_node(head, n) != NULL )
				continue;
			link_list newnode = create_node(n);
			if(newnode == NULL)
			{
				printf("节点创建失败\n");
				continue;
			}
			list_add_head(head, newnode);
		}
		else
			list_dispaly(head);
	}
  
	return 0;
}