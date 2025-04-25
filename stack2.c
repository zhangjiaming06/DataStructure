#include <stdio.h>
#include <stdlib.h>

typedef int elemtype;
typedef struct stack {
	elemtype data;
	struct stack* next;
}stack;

//ջ�ĳ�ʼ��
stack* initSack()
{
	stack* s = (stack*)malloc(sizeof(stack));
	if (s == NULL) {
		free(s);
		return NULL;
	}
	s->data = -1;
	s->next = NULL;
}

//�ж�ջ�Ƿ�Ϊ��
int isEmpty(stack* s)
{
	if (s->next == NULL) {
		return 1;
	}
	else return 0;
}

//��ջ/ѹջ
//��Ϊջ�Ĳ����������ȳ����Ƚ��������������ѡ��ʹ��ͷ�巨
int push(stack* s, elemtype e)
{
	stack* p = malloc(sizeof(stack));
	if (p == NULL) {
		free(p);
		return 0;
	}
	p->data = e;
	p->next = s->next;
	s->next = p;
	return 1;
}

//��ջ
int pop(stack* s, elemtype *e)
{
	if (s->next == NULL) {
		return 0;
	}
	*e = s->next->data;
	stack* p = s->next;
	s->next = p->next;
	free(p);
	return 1;
}

//��ȡջ��Ԫ��
int getTop(stack* s, elemtype* e) {
	if (s->next == NULL) {
		return 0;
	}
	*e = s->next->data;
	return 1;
}

//��ջ
void destroyStack(stack* s) {
	elemtype temp;
	while (pop(s, &temp)); // ��������Ԫ�� 
	free(s);
}

#include <stdio.h>
#include <stdlib.h>

/* [�ڴ˲������ṩ������ջ��������] */

int main() {
    printf("===== ��ջ���ܲ��� =====\n");
    int test_count = 0;
    int passed_count = 0;

    // ����1����ʼ��ջ 
    printf("\n[����1] ջ��ʼ��\n");
    stack* s = initSack();
    if (s != NULL) {
        printf("�����ޣ��ޣ��� ��ʼ���ɹ�\n");
        passed_count++;
    }
    else {
        printf("�� ��ʼ��ʧ��\n");
    }
    test_count++;

    // ����2����ջ��� 
    printf("\n[����2] ��ջ���\n");
    if (isEmpty(s)) {
        printf("�����ޣ��ޣ��� ��ջ�����ȷ\n");
        passed_count++;
    }
    else {
        printf("�� ��ջ������\n");
    }
    test_count++;

    // ����3��ѹջ���� 
    printf("\n[����3] ѹջ����(ѹ��10,20,30)\n");
    push(s, 10);
    push(s, 20);
    push(s, 30);

    elemtype top_val;
    if (getTop(s, &top_val)) {
        if (top_val == 30) {
            printf("�����ޣ��ޣ��� ջ��Ԫ����ȷ(30)\n");
            passed_count++;
        }
        else {
            printf("�� ջ��Ԫ�ش��󣬵õ� %d\n", top_val);
        }
    }
    else {
        printf("�� ��ȡջ��ʧ��\n");
    }
    test_count++;

    // ����4����ջ���� 
    printf("\n[����4] ��ջ����\n");
    elemtype pop_val;
    if (pop(s, &pop_val)) {
        if (pop_val == 30) {
            printf("�����ޣ��ޣ��� ����Ԫ����ȷ(30)\n");
            passed_count++;
        }
        else {
            printf("�� ����Ԫ�ش��󣬵õ� %d\n", pop_val);
        }
    }
    else {
        printf("�� ��ջʧ��\n");
    }
    test_count++;

    // ����5��ջ˳�����(LIFO)
    printf("\n[����5] ����ȳ�����\n");
    pop(s, &pop_val);
    getTop(s, &top_val);
    if (pop_val == 20 && top_val == 10) {
        printf("�����ޣ��ޣ��� ˳����ȷ(����20��ʣ��10)\n");
        passed_count++;
    }
    else {
        printf("�� ˳����󣬵��� %d��ʣ�� %d\n", pop_val, top_val);
    }
    test_count++;

    // ����6���߽��������� 
    printf("\n[����6] �߽���������\n");
    pop(s, &pop_val); // �������һ��Ԫ�� 
    if (pop(s, &pop_val) == 0 && isEmpty(s)) {
        printf("�����ޣ��ޣ��� ��ջ���������ȷ\n");
        passed_count++;
    }
    else {
        printf("�� ��ջ�������ʧ��\n");
    }
    test_count++;

    // ����7���ڴ��ͷŲ��� 
    printf("\n[����7] �ڴ��ͷŲ���\n");
    free(s);
    printf("�����ޣ��ޣ��� �ڴ��ͷ����\n");
    passed_count++;
    test_count++;

    // ���Խ������ 
    printf("\n===== ���Խ�� =====\n");
    printf("ͨ������: %d/%d\n", passed_count, test_count);
    printf("����ͨ����: %.1f%%\n", (float)passed_count / test_count * 100);

    return 0;
}