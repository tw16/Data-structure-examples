// date:2022年 07月 27日 星期三 14:05:57 CST
// author: A
// path: /mnt/hgfs/2206预科/03-数据结构/01-链表/singel_list


/* 

据说着名犹太历史学家 Josephus有过以下的故事：在罗马人占领乔塔帕特后，犹太人与Josephus及他的朋友
躲到一个洞中，族人决定宁愿死也不要被敌人到，于是决定了一个自杀方式，所有人排成一个圆圈，由第1个
人 开始报数，每报数到第3人该人就必须自杀，然后再由下一个重新报数，直到所有人都自杀身亡为止。
然而Josephus 和他的朋友并不想遵从，Josephus要他的朋友先假装遵从，他将朋友与自己安排在两个特殊
的位置，于是逃过了这场死亡游戏。现在求输入总人数n，请问最后活下来的两个人是哪两个位置上的人。
（单向循环链表）

 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int datatype;

typedef struct node
{
	datatype data;
	struct node *next;
}link_node, *link_list;  


//初始化一条不带头结点空链表
link_list init_list(void)
{
	link_list head = NULL;
	
	return head;
}

//创建一个节点,节点next初始化必须要求自己指向自己
link_list create_node(datatype data)
{
	//给新节点分配空间,初始化传入的数据
	link_list newnode = calloc(1, sizeof(link_node));
	if(newnode == NULL)
	{
		perror("链表初始化失败\n");
		return NULL;
	}
	
	newnode->data = data;	//初始化数据
	newnode->next = newnode;	//自己指向自己
	
	return newnode; //返回新节点的空间基地址
}

//判断链表是否为空
bool empty_list(link_list head)
{
	if(head == NULL)
		return true;
	return false;
}

//从尾巴上插入一个节点
void insert_tail(link_list *head, link_list newnode)
{
	if( empty_list(*head) )
	{
		*head = newnode; //链表为空,指向让头指针指向第一个节点
		return ;
	}
		
	link_list tmp = *head;
	
	//判断是否等于头,如果不等于说明还没有最后一个节点
	while(tmp->next != *head)
	{
		tmp = tmp->next;
	}
	
	tmp->next = newnode;
	newnode->next = *head;
}

//遍历链表
void dispaly_list(link_list head)
{
	if( empty_list(head) )
	{
		printf("链表为空,没有数据可以遍历\n");
		return ;
	}
	
	link_list tmp = head;
	
	//判断是否等于头,如果不等于说明还没有最后一个节点
	do{
		printf("%d->", tmp->data);
		tmp = tmp->next;
	}while(tmp != head);
	printf("\n");
}

//数到第3个杀掉他
link_list kill3(link_list head)
{
	link_list prev = head->next;	//指向被杀的前一个人
	link_list delete = head->next->next;	//指向被杀的人
	
	while(delete->next->next != delete)
	{
		prev->next = delete->next; //prev->next指向被杀的人的下一个人
		delete->next = NULL; //先给他一枪
		free(delete);	//毁尸灭迹(释放已删除节点的空间)
		prev = prev->next->next;	//下一个要杀的人的前一个节点
		delete = prev->next;	//下一个被杀的人
	}
	
	return delete;
} 
 
 
int main(int argc, char *argv[])
{
	// 1,初始化带头结点循环链表
	link_list head = init_list();
	if(head != NULL)
	{
		printf("链表创建失败\n");
		return -1;
	}
	
	//2, 初始化一些整数
	int i, n;
	
	printf("请输入整数n\n");
	scanf("%d", &n);
	
	for(i=1; i<=n; i++)
	{
		//2.1 创建节点
		link_list newnode = create_node(i);
		if(NULL == newnode)
		{
			printf("节点创建失败\n");
			continue;
		}
		
		//2.2 插入新的节点到尾巴
		insert_tail(&head, newnode);
	}
	
	//3,遍历链表
	dispaly_list(head);
	
	//数3杀1游戏开始
	link_list ser1 = kill3(head);
	printf("两个幸存者是:ser1 = %d, ser2 = %d\n", ser1->data, ser1->next->data);
  
	return 0;
}
