#ifndef _HEAD_SINGEL_H_
#define _HEAD_SINGEL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//���û�ж�������꣬��Ĭ��������Ϊint��
#ifndef DATATYPE
typedef int datatype;
#endif


//��ƽڵ�
struct node
{
	datatype data;
	struct node *next;
};


//��ʼ��һ����ͷ���Ŀ�����
//�ɹ�����ͷ�ڵ��ַ
//
static struct node *init_list(void)
{
	struct node *head = malloc(sizeof(struct node)); // ������ڵ�ռ�
	if(NULL == head)	//����ΪNULL��ʧ��
	{
		perror("malloc head failed");
		return NULL;
	}
	
	head->next = NULL;	
	
	return head;	//����ͷ�ڵ�ĵ�ַ
}

//����һ���½ڵ�
//����һ��datatype������
static struct node *create_node(datatype i)
{
	struct node *newnode = malloc(sizeof(struct node));
	if(NULL == newnode)	//����ΪNULL��ʧ��
	{
		perror("malloc newnode failed");
		return NULL;
	}
	
	newnode->data = i;   //�洢����
	newnode->next = NULL;
	
	return newnode; //�����´����Ľڵ�ĵ�ַ
}


//��β���ϲ���һ���ڵ�
//head������ͷ
//newnode���½ڵ�
static void inster_tial(struct node *head, struct node *newnode)
{
	struct node *tmp = head;
	
	while(tmp->next != NULL)
	{
		tmp = tmp->next; //���tmp��һ���ڵ㲻Ϊ�գ��Ͱ���һ���ڵ��ַ��tmp
	}
	
	tmp->next = newnode;
	
	return ;
}


//��ͷ�ڵ㣨����ڵ㣩�������һ���ڵ�
static void inster_head(struct node *head, struct node *newnode)
{
	//��ͷ�ڵ��ԭ������һ���ڵ�浽�½ڵ��next����
	newnode->next = head->next;
	
	//��ϸ�ڵ�浽ͷ�ڵ��next����
	head->next = newnode;
	
	return ;
}


//�����ݲ���
//����ֵλ���ҵ������ݵ�ǰһ���ڵ�
static struct node *find_node(struct node *head, datatype find_data)
{
	//���������ÿ���ڵ�
	while(head->next != NULL)
	{
		if(head->next->data == find_data)
			return head;
		head = head->next;	//�����ǰ�ڵ�����û�бȶԳɹ����ͱȶ���һ��
	}
	
	return NULL; //û���ҵ��ڵ�
}

//ɾ��һ���ڵ�
//dest_node��Ҫɾ����ǰһ���ڵ�
static struct node *delete_node(struct node *dest_node, struct node *del_node)
{
	dest_node->next = del_node->next;
	del_node->next = NULL;
	
	return del_node;
}

//�ƶ�һ���ڵ㵽ĳ���ڵ����
//dest_node����Ҫ�����λ�õ�ǰһ���ڵ�
//src_node��Ҫ�ƶ��Ľڵ��ǰһ���ڵ�
//src_node->next��Ҫ�ƶ����Ǹ��ڵ�
static void move_node(struct node *dest_node, struct node *src_node)
{
	struct node * del_node = delete_node(src_node, src_node->next);
	
	//���뵽Ŀ��λ�õĺ���
	inster_head(dest_node, del_node);
}

//�������нڵ�
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

//�жϿ�����
static bool empty_list(struct node *head)
{
	if(head->next == NULL)
		return true;
	
	return false;
}


//�ͷŵ����ڵ�
static void free_node(struct node **fnode)
{
	free(*fnode);	//�ͷ���ɾ���Ľڵ�ռ�
	*fnode = NULL;	//��ָ����Ƭ�ռ��ָ��ָ���
}

#endif