#include <stdio.h>
#include <stdlib.h>

typedef int elemtype;

typedef struct node {
	elemtype data;
	struct node* next;
}node;

//初始化链表
node* initList()
{
	node* head = (node*)malloc(sizeof(node));
	if (head == NULL)
	{
		printf("分配失败\n");
		free(head);
		return NULL;
	}
	head->next = NULL;
	head->data = 0;
	return head;
}

//初始化节点
node* init_node(elemtype e)
{
	node* n = (node*)malloc(sizeof(node));
	if (n == NULL)
	{
		printf("分配失败\n");
		free(n);
		return NULL;
	}
	n->data = e;
	n->next = NULL;
	return n;
}

//头插法
int insertHead(node* head, elemtype e)
{
	node* n = (node*)malloc(sizeof(node));
	if (n == NULL) {
		printf("分配失败\n");
		free(n);
		return 0;
	}
	n->data = e;
	n->next = head->next;
	head->next = n;
	return 1;
}

//遍历
void list_node(node* head)
{
	if (head->next == NULL)
	{
		printf("没有元素，无法遍历\n");
		return;
	}
	node* tempt = head->next;
	while (tempt != NULL) {
		printf("%d ", tempt->data);
		tempt = tempt->next;
	}
	printf("\n");
}

//获取尾部结点
node* get_tail(node* head)
{
	node* p = head;
	while (p->next != NULL) {
		p = p->next;
	}
	return p;
}

//尾插法
node* insertTail(node* tail, elemtype e)
{
	node* p = (node*)malloc(sizeof(node));
	if (p == NULL) {
		printf("内存分配失败\n");
		free(p);
		return NULL;
	}
	p->data = e;
	p->next = NULL;
	tail->next = p;
	return p;
}

//尾插法（节点）
node* insertTailWithNode(node* tail, node* n)
{
	tail->next = n;
	n->next = NULL;
	return n;
}

//指定位置插入
int insertNode(node* head, int pos, elemtype e)
{
	node* p = head;
	if (pos < 1) return 0;
	for (int i = 0; i < pos-1; i++) {
		p = p->next;
		if (p == NULL) {
			return 0;
		}
	}
	node* q = (node*)malloc(sizeof(node));
	if (q == NULL) {
		printf("内存分配失败\n");
		free(q);
		return 0;
	}
	q->data = e;
	q->next = p->next;
	p->next = q;
	return 1;
}

//删除节点
int deletNode(node* head, int pos, elemtype* e)
{
	node* p = head;
	if (pos < 0) return 0;
	for (int i = 0; i < pos; i++) {
		p = p->next;
		if (p == NULL) return 0;
	}
	*e = p->next->data;
	node* q = p->next;
	p->next = q->next;
	free(q);
	return 1;
}

//获取链表长度
int listlength(node* head)
{
	node* p = head;
	int count = 0;
	while (p != NULL)
	{
		p = p->next;
		count++;
	}
	return count;
}

//释放链表
void freeList(node* head) {
	if (head == NULL) return;

	// 检测并断开环 
	node* slow = head, * fast = head;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) { // 有环 
			slow = head;
			while (slow->next != fast->next) {
				slow = slow->next;
				fast = fast->next;
			}
			fast->next = NULL; // 断开环 
			break;
		}
	}

	// 安全释放 
	node* curr = head;
	while (curr) {
		node* next = curr->next;
		free(curr);
		curr = next;
	}
}

//查找倒数第k个元素
node* findNodeFK(node* head, int k)
{
	node* fast = head->next;
	node* slow = head->next;
	if (k < 1) {
		return -1;
	}
	for (int i = 0; i < k; i++) {
		fast = fast->next;
		if (fast == NULL) return NULL;
	}
	while (fast != NULL) {
		fast = fast->next;
		slow = slow->next;
	}
	return slow;
}

//找到两个节点共同后缀的起始位置
node* findIntersectionNode(node* headA, node* headB)
{
	int len1 = listlength(headA);
	int len2 = listlength(headB);
	node* p = headA;node* q = headB;
	if (len1 > len2) {
		for (int i = 0; i < len1 - len2; i++) {
			p = p->next;
		}
		while (p != q) {
			p = p->next;
			q = q->next;
		}
		return p;
	}
	else {
		for (int i = 0; i < len2 - len1; i++) {
			q = q->next;
		}
		while (p != q) {
			p = p->next;
			q = q->next;
		}
		return p;
	}
}

//反转链表
node* reverseList(node* head)
{
	node* first = NULL;
	node* second = head->next;
	if (second == NULL || second->next == NULL) return head;
	node* third = second->next;
	while (second != NULL) {
		second->next = first;
		first = second;
		second = third;
		if (third != NULL) third = third->next;
	}
	head->next = first;
	return head;
}

//判断链表是否有环
int isCycle(node* head)
{
	node* fast = head;
	node* slow = head;
	while (fast->next != NULL && fast->next->next != NULL) {
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow) {
			return 1;
		}
	}
	return 0;
}

//找到链表环的入口
node* findBegin(node* head)
{
	node* fast = head;
	node* slow = head;
	while (fast != NULL && fast->next != NULL) {
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow)
		{
			node* p = fast;
			int count = 1;
			while (p->next != slow) {
				p = p->next;
				count++;
			}
			fast = head;
			slow = head;
			for (int i = 0; i < count; i++)
			{
				fast = fast->next;
			}
			while (fast != slow) {
				fast = fast->next;
				slow = slow->next;
			}
			return slow;
		}
	}
	return NULL;
}

int main() {
	// 初始化链表
	node* head = initList();
	if (head == NULL) {
		printf("初始化链表失败！\n");
		return -1;
	}

	// 测试头插法
	printf("测试头插法：\n");
	insertHead(head, 1);
	insertHead(head, 2);
	insertHead(head, 3);
	printf("头插法插入后链表：");
	list_node(head);

	// 测试尾插法
	printf("测试尾插法：\n");
	node* tail = get_tail(head);
	tail = insertTail(tail, 4);
	tail = insertTail(tail, 5);
	printf("尾插法插入后链表：");
	list_node(head);

	// 测试指定位置插入
	printf("测试指定位置插入：\n");
	insertNode(head, 2, 99);
	printf("在第2个位置插入99后链表：");
	list_node(head);

	// 测试删除节点
	printf("测试删除节点：\n");
	elemtype deleted;
	deletNode(head, 2, &deleted);
	printf("删除第2个节点后链表：");
	list_node(head);

	// 测试获取链表长度
	printf("测试获取链表长度：\n");
	printf("链表长度为：%d\n", listlength(head));

	// 测试查找倒数第k个元素
	printf("测试查找倒数第k个元素：\n");
	node* fk_node = findNodeFK(head, 2);
	if (fk_node != NULL) {
		printf("倒数第2个元素是：%d\n", fk_node->data);
	}
	else {
		printf("未找到倒数第2个元素\n");
	}

	// 测试反转链表
	printf("测试反转链表：\n");
	head = reverseList(head);
	printf("反转后链表：");
	list_node(head);

	// 测试判断链表是否有环
	printf("测试判断链表是否有环：\n");
	printf("当前链表是否有环：%d\n", isCycle(head));

	// 测试创建环
	printf("测试创建环并判断环的存在：\n");
	node* loop_node = get_tail(head);
	loop_node->next = head->next->next; // 创建环
	printf("创建环后链表是否有环：%d\n", isCycle(head));

	// 测试找到环的入口
	printf("测试找到环的入口：\n");
	node* loop_begin = findBegin(head);
	if (loop_begin != NULL) {
		printf("环的入口是：%d\n", loop_begin->data);
	}
	else {
		printf("未找到环的入口\n");
	}

	// 测试释放链表
	printf("测试释放链表：\n");
	freeList(head);
	printf("链表已释放\n");

	return 0;
}