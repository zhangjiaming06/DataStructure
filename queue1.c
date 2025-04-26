#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef int elemtype;
typedef struct queue {
	elemtype* data;
	int front;
	int rear;
}queue;

//��ʼ��
queue* initQueue()
{
	queue* q = (queue*)malloc(sizeof(queue));
	if (q == NULL) {
		return NULL;
	}
	q->data = (elemtype*)malloc(sizeof(elemtype) * MAXSIZE);
	if (q->data == NULL) {
		free(q);
		return NULL;
	}
	q->front = 0;
	q->rear = 0;
	return q;
}

//�ж϶����Ƿ�Ϊ��
int isEmpty(queue* q) {
	if (q->front == q->rear) return 1;
	else return 0;
}

//���
int equeue(queue* q, elemtype e) {
	if ((q->rear + 1) % MAXSIZE == q->front) {
		return 0;
	}
	q->data[q->rear] = e;
	q->rear = (q->rear + 1) % MAXSIZE;
	return 1;
}

//����
int dequeuee(queue* q, elemtype *e) {
	if (q->front == q->rear) return 0;
	*e = q->data[q->front];
	q->front = (q->front + 1) % MAXSIZE;
	return 1;
}

//��ȡ��ͷԪ��
int gethead(queue* q, elemtype* e) {
	if (q->front == q->rear) return 0;
	*e = q->data[q->front];
	return 1;
}

int main() {
    printf("��ʼ���Զ��в���...\n\n");

    // ����1: ��ʼ������ 
    printf("����1: ��ʼ������\n");
    queue* q = initQueue();
    if (q == NULL) {
        printf("����: ���г�ʼ��ʧ��\n");
        return -1;
    }
    printf("���г�ʼ���ɹ�\n");
    printf("��ʼ״̬ - �����Ƿ�Ϊ��: %s\n", isEmpty(q) ? "��" : "��");
    printf("\n");

    // ����2: ��Ӳ��� 
    printf("����2: ��Ӳ���\n");
    for (int i = 1; i <= 5; i++) {
        if (equeue(q, i * 10)) {
            printf("��ӳɹ�: %d\n", i * 10);
        }
        else {
            printf("���ʧ��: %d\n", i * 10);
        }
    }
    printf("��ǰ����״̬ - �Ƿ�Ϊ��: %s\n", isEmpty(q) ? "��" : "��");
    printf("\n");

    // ����3: ��ȡ��ͷԪ�� 
    printf("����3: ��ȡ��ͷԪ��\n");
    elemtype head;
    if (gethead(q, &head)) {
        printf("��ͷԪ��: %d\n", head);
    }
    else {
        printf("��ȡ��ͷԪ��ʧ�� (���п���Ϊ��)\n");
    }
    printf("\n");

    // ����4: ���Ӳ��� 
    printf("����4: ���Ӳ���\n");
    elemtype dequeued;
    for (int i = 0; i < 3; i++) {
        if (dequeuee(q, &dequeued)) {
            printf("���ӳɹ�: %d\n", dequeued);
        }
        else {
            printf("����ʧ�� (���п���Ϊ��)\n");
        }
    }
    printf("��ǰ����״̬ - �Ƿ�Ϊ��: %s\n", isEmpty(q) ? "��" : "��");
    printf("\n");

    // ����5: �ٴλ�ȡ��ͷԪ�� 
    printf("����5: �ٴλ�ȡ��ͷԪ��\n");
    if (gethead(q, &head)) {
        printf("��ͷԪ��: %d\n", head);
    }
    else {
        printf("��ȡ��ͷԪ��ʧ�� (���п���Ϊ��)\n");
    }
    printf("\n");

    // ����6: ���������� 
    printf("����6: ����������\n");
    printf("������������...\n");
    int count = 0;
    for (int i = 0; i < MAXSIZE * 2; i++) { // ���Ⳣ�Գ������� 
        if (equeue(q, i)) {
            count++;
        }
        else {
            printf("�� %d ����Ӻ��������\n", count);
            break;
        }
    }
    printf("���ն���״̬ - �Ƿ�Ϊ��: %s\n", isEmpty(q) ? "��" : "��");
    printf("\n");

    // ����7: ��ն��� 
    printf("����7: ��ն���\n");
    printf("��ʼ��������Ԫ��...\n");
    while (!isEmpty(q)) {
        if (dequeuee(q, &dequeued)) {
            printf("����: %d\n", dequeued);
        }
    }
    printf("���ն���״̬ - �Ƿ�Ϊ��: %s\n", isEmpty(q) ? "��" : "��");
    printf("\n");

    // ����8: �ն��в������� 
    printf("����8: �ն��в�������\n");
    printf("���Դӿն��г���...\n");
    if (dequeuee(q, &dequeued)) {
        printf("���ӳɹ�: %d (��Ӧ�÷���)\n", dequeued);
    }
    else {
        printf("����ʧ�� (����Ԥ�ڣ�����Ϊ��)\n");
    }

    printf("���Ի�ȡ�ն��еĶ�ͷ...\n");
    if (gethead(q, &head)) {
        printf("��ȡ�ɹ�: %d (��Ӧ�÷���)\n", head);
    }
    else {
        printf("��ȡʧ�� (����Ԥ�ڣ�����Ϊ��)\n");
    }

    // �ͷŶ����ڴ� 
    free(q->data);
    free(q);

    printf("\n���в������!\n");
    return 0;
}