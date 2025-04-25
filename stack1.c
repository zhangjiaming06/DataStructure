#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef int elemtype;

typedef struct stack {
	elemtype* data;
	int top;
}stack;

//��ʼ��
stack* initStack()
{
	stack* s = (stack*)malloc(sizeof(stack));
	if (s == NULL) {
		free(s);
		return NULL;
	}
	s->data = (elemtype*)malloc(sizeof(elemtype) * MAXSIZE);
	if (s->data == NULL) {
		free(s->data);
		free(s);
		return NULL;
	}
	s->top = -1;
	return s;
}

//���ջ�Ƿ�Ϊ��
int isEmpty(stack* s) {
	if (s->top == -1) {
		return 1;
	}
	else return 0;
}

//��ջ/ѹջ
int push(stack* s, elemtype e) {
	if (s->top >= MAXSIZE-1) {
		printf("ջ����\n");
		return 0;
	}
	s->data[++s->top] = e;
	return 1;
}

//��ջ
int pop(stack* s, elemtype* e) {
	if (s->top < 0) {
		printf("ջ����\n");
		return 0;
	}
	*e = s->data[s->top--];
	return 1;
}

//��ȡջ��Ԫ��
int getTop(stack* s, elemtype *e) {
	if (s->top < 0) {
		printf("ջ����\n");
		return 0;
	}
	*e = s->data[s->top];
	return 1;
}

int main() {
    printf("===== ջ���ܲ��� =====\n");
    int passed = 0, total = 0;

    // ����1����ʼ��ջ 
    printf("\n[����1] ջ��ʼ��\n");
    stack* s = initStack();
    if (s != NULL) {
        printf("�����ޣ��ޣ��� ��ʼ���ɹ�\n");
        passed++;
    }
    else {
        printf("�� ��ʼ��ʧ��\n");
    }
    total++;

    // ����2����ջ��� 
    printf("\n[����2] ��ջ���\n");
    if (isEmpty(s)) {
        printf("�����ޣ��ޣ��� ��ջ�����ȷ\n");
        passed++;
    }
    else {
        printf("�� ��ջ������\n");
    }
    total++;

    // ����3��ѹջ���� 
    printf("\n[����3] ѹջ����\n");
    for (int i = 1; i <= 5; i++) {
        if (push(s, i * 10)) {
            printf("  ѹ�� %d\n", i * 10);
        }
        else {
            printf("�� ѹջʧ��\n");
        }
    }

    elemtype top_val;
    if (getTop(s, &top_val)) {
        if (top_val == 50) {
            printf("�����ޣ��ޣ��� ջ��Ԫ����ȷ(50)\n");
            passed++;
        }
        else {
            printf("�� ջ��Ԫ�ش��󣬵õ� %d\n", top_val);
        }
    }
    else {
        printf("�� ��ȡջ��ʧ��\n");
    }
    total++;

    // ����4����ջ���� 
    printf("\n[����4] ��ջ����\n");
    elemtype pop_val;
    if (pop(s, &pop_val)) {
        if (pop_val == 50) {
            printf("�����ޣ��ޣ��� ����Ԫ����ȷ(50)\n");
            passed++;
        }
        else {
            printf("�� ����Ԫ�ش��󣬵õ� %d\n", pop_val);
        }
    }
    else {
        printf("�� ��ջʧ��\n");
    }
    total++;

    // ����5��ջ������ 
    printf("\n[����5] ջ������\n");
    stack* full_stack = initStack();
    for (int i = 0; i < MAXSIZE; i++) {
        push(full_stack, i);
    }
    if (push(full_stack, MAXSIZE) == 0) {
        printf("�����ޣ��ޣ��� ջ�������ȷ\n");
        passed++;
    }
    else {
        printf("�� ջ�����ʧ��\n");
    }
    total++;
    free(full_stack->data);
    free(full_stack);

    // ����6���߽��������� 
    printf("\n[����6] �߽���������\n");
    stack* empty_stack = initStack();
    elemtype val;
    if (pop(empty_stack, &val) == 0) {
        printf("�����ޣ��ޣ��� ��ջ���������ȷ\n");
        passed++;
    }
    else {
        printf("�� ��ջ�������ʧ��\n");
    }
    total++;
    free(empty_stack->data);
    free(empty_stack);

    // ����7���ڴ��ͷ� 
    printf("\n[����7] �ڴ��ͷŲ���\n");
    free(s->data);
    free(s);
    printf("�����ޣ��ޣ��� �ڴ��ͷ����\n");
    passed++;
    total++;

    // ���Խ������ 
    printf("\n===== ���Խ�� =====\n");
    printf("ͨ������: %d/%d\n", passed, total);
    printf("����ͨ����: %.1f%%\n", (float)passed / total * 100);

    return 0;
}