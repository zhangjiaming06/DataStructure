#include <stdio.h>
#include <stdlib.h>

typedef int elemtype;

typedef struct node {
	elemtype data;
	struct node* next;
}node;

//��ʼ������
node* initList()
{
	node* head = (node*)malloc(sizeof(node));
	if (head == NULL)
	{
		printf("����ʧ��\n");
		free(head);
		return NULL;
	}
	head->next = NULL;
	head->data = 0;
	return head;
}

//��ʼ���ڵ�
node* init_node(elemtype e)
{
	node* n = (node*)malloc(sizeof(node));
	if (n == NULL)
	{
		printf("����ʧ��\n");
		free(n);
		return NULL;
	}
	n->data = e;
	n->next = NULL;
	return n;
}

//ͷ�巨
int insertHead(node* head, elemtype e)
{
	node* n = (node*)malloc(sizeof(node));
	if (n == NULL) {
		printf("����ʧ��\n");
		free(n);
		return 0;
	}
	n->data = e;
	n->next = head->next;
	head->next = n;
	return 1;
}

//����
void list_node(node* head)
{
	if (head->next == NULL)
	{
		printf("û��Ԫ�أ��޷�����\n");
		return;
	}
	node* tempt = head->next;
	while (tempt != NULL) {
		printf("%d ", tempt->data);
		tempt = tempt->next;
	}
	printf("\n");
}

//��ȡβ�����
node* get_tail(node* head)
{
	node* p = head;
	while (p->next != NULL) {
		p = p->next;
	}
	return p;
}

//β�巨
node* insertTail(node* tail, elemtype e)
{
	node* p = (node*)malloc(sizeof(node));
	if (p == NULL) {
		printf("�ڴ����ʧ��\n");
		free(p);
		return NULL;
	}
	p->data = e;
	p->next = NULL;
	tail->next = p;
	return p;
}

//β�巨���ڵ㣩
node* insertTailWithNode(node* tail, node* n)
{
	tail->next = n;
	n->next = NULL;
	return n;
}

//ָ��λ�ò���
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
		printf("�ڴ����ʧ��\n");
		free(q);
		return 0;
	}
	q->data = e;
	q->next = p->next;
	p->next = q;
	return 1;
}

//ɾ���ڵ�
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

//��ȡ������
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

//�ͷ�����
void freeList(node* head) {
	if (head == NULL) return;

	// ��Ⲣ�Ͽ��� 
	node* slow = head, * fast = head;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) { // �л� 
			slow = head;
			while (slow->next != fast->next) {
				slow = slow->next;
				fast = fast->next;
			}
			fast->next = NULL; // �Ͽ��� 
			break;
		}
	}

	// ��ȫ�ͷ� 
	node* curr = head;
	while (curr) {
		node* next = curr->next;
		free(curr);
		curr = next;
	}
}

//���ҵ�����k��Ԫ��
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

//�ҵ������ڵ㹲ͬ��׺����ʼλ��
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

//��ת����
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

//�ж������Ƿ��л�
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

//�ҵ����������
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
	// ��ʼ������
	node* head = initList();
	if (head == NULL) {
		printf("��ʼ������ʧ�ܣ�\n");
		return -1;
	}

	// ����ͷ�巨
	printf("����ͷ�巨��\n");
	insertHead(head, 1);
	insertHead(head, 2);
	insertHead(head, 3);
	printf("ͷ�巨���������");
	list_node(head);

	// ����β�巨
	printf("����β�巨��\n");
	node* tail = get_tail(head);
	tail = insertTail(tail, 4);
	tail = insertTail(tail, 5);
	printf("β�巨���������");
	list_node(head);

	// ����ָ��λ�ò���
	printf("����ָ��λ�ò��룺\n");
	insertNode(head, 2, 99);
	printf("�ڵ�2��λ�ò���99������");
	list_node(head);

	// ����ɾ���ڵ�
	printf("����ɾ���ڵ㣺\n");
	elemtype deleted;
	deletNode(head, 2, &deleted);
	printf("ɾ����2���ڵ������");
	list_node(head);

	// ���Ի�ȡ������
	printf("���Ի�ȡ�����ȣ�\n");
	printf("������Ϊ��%d\n", listlength(head));

	// ���Բ��ҵ�����k��Ԫ��
	printf("���Բ��ҵ�����k��Ԫ�أ�\n");
	node* fk_node = findNodeFK(head, 2);
	if (fk_node != NULL) {
		printf("������2��Ԫ���ǣ�%d\n", fk_node->data);
	}
	else {
		printf("δ�ҵ�������2��Ԫ��\n");
	}

	// ���Է�ת����
	printf("���Է�ת����\n");
	head = reverseList(head);
	printf("��ת������");
	list_node(head);

	// �����ж������Ƿ��л�
	printf("�����ж������Ƿ��л���\n");
	printf("��ǰ�����Ƿ��л���%d\n", isCycle(head));

	// ���Դ�����
	printf("���Դ��������жϻ��Ĵ��ڣ�\n");
	node* loop_node = get_tail(head);
	loop_node->next = head->next->next; // ������
	printf("�������������Ƿ��л���%d\n", isCycle(head));

	// �����ҵ��������
	printf("�����ҵ�������ڣ�\n");
	node* loop_begin = findBegin(head);
	if (loop_begin != NULL) {
		printf("��������ǣ�%d\n", loop_begin->data);
	}
	else {
		printf("δ�ҵ��������\n");
	}

	// �����ͷ�����
	printf("�����ͷ�����\n");
	freeList(head);
	printf("�������ͷ�\n");

	return 0;
}