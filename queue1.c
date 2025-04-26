#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef int elemtype;
typedef struct queue {
	elemtype* data;
	int front;
	int rear;
}queue;

//初始化
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

//判断队列是否为空
int isEmpty(queue* q) {
	if (q->front == q->rear) return 1;
	else return 0;
}

//入队
int equeue(queue* q, elemtype e) {
	if ((q->rear + 1) % MAXSIZE == q->front) {
		return 0;
	}
	q->data[q->rear] = e;
	q->rear = (q->rear + 1) % MAXSIZE;
	return 1;
}

//出队
int dequeuee(queue* q, elemtype *e) {
	if (q->front == q->rear) return 0;
	*e = q->data[q->front];
	q->front = (q->front + 1) % MAXSIZE;
	return 1;
}

//获取队头元素
int gethead(queue* q, elemtype* e) {
	if (q->front == q->rear) return 0;
	*e = q->data[q->front];
	return 1;
}

int main() {
    printf("开始测试队列操作...\n\n");

    // 测试1: 初始化队列 
    printf("测试1: 初始化队列\n");
    queue* q = initQueue();
    if (q == NULL) {
        printf("错误: 队列初始化失败\n");
        return -1;
    }
    printf("队列初始化成功\n");
    printf("初始状态 - 队列是否为空: %s\n", isEmpty(q) ? "是" : "否");
    printf("\n");

    // 测试2: 入队操作 
    printf("测试2: 入队操作\n");
    for (int i = 1; i <= 5; i++) {
        if (equeue(q, i * 10)) {
            printf("入队成功: %d\n", i * 10);
        }
        else {
            printf("入队失败: %d\n", i * 10);
        }
    }
    printf("当前队列状态 - 是否为空: %s\n", isEmpty(q) ? "是" : "否");
    printf("\n");

    // 测试3: 获取队头元素 
    printf("测试3: 获取队头元素\n");
    elemtype head;
    if (gethead(q, &head)) {
        printf("队头元素: %d\n", head);
    }
    else {
        printf("获取队头元素失败 (队列可能为空)\n");
    }
    printf("\n");

    // 测试4: 出队操作 
    printf("测试4: 出队操作\n");
    elemtype dequeued;
    for (int i = 0; i < 3; i++) {
        if (dequeuee(q, &dequeued)) {
            printf("出队成功: %d\n", dequeued);
        }
        else {
            printf("出队失败 (队列可能为空)\n");
        }
    }
    printf("当前队列状态 - 是否为空: %s\n", isEmpty(q) ? "是" : "否");
    printf("\n");

    // 测试5: 再次获取队头元素 
    printf("测试5: 再次获取队头元素\n");
    if (gethead(q, &head)) {
        printf("队头元素: %d\n", head);
    }
    else {
        printf("获取队头元素失败 (队列可能为空)\n");
    }
    printf("\n");

    // 测试6: 队列满测试 
    printf("测试6: 队列满测试\n");
    printf("尝试填满队列...\n");
    int count = 0;
    for (int i = 0; i < MAXSIZE * 2; i++) { // 故意尝试超过容量 
        if (equeue(q, i)) {
            count++;
        }
        else {
            printf("在 %d 次入队后队列已满\n", count);
            break;
        }
    }
    printf("最终队列状态 - 是否为空: %s\n", isEmpty(q) ? "是" : "否");
    printf("\n");

    // 测试7: 清空队列 
    printf("测试7: 清空队列\n");
    printf("开始出队所有元素...\n");
    while (!isEmpty(q)) {
        if (dequeuee(q, &dequeued)) {
            printf("出队: %d\n", dequeued);
        }
    }
    printf("最终队列状态 - 是否为空: %s\n", isEmpty(q) ? "是" : "否");
    printf("\n");

    // 测试8: 空队列操作测试 
    printf("测试8: 空队列操作测试\n");
    printf("尝试从空队列出队...\n");
    if (dequeuee(q, &dequeued)) {
        printf("出队成功: %d (不应该发生)\n", dequeued);
    }
    else {
        printf("出队失败 (符合预期，队列为空)\n");
    }

    printf("尝试获取空队列的队头...\n");
    if (gethead(q, &head)) {
        printf("获取成功: %d (不应该发生)\n", head);
    }
    else {
        printf("获取失败 (符合预期，队列为空)\n");
    }

    // 释放队列内存 
    free(q->data);
    free(q);

    printf("\n所有测试完成!\n");
    return 0;
}