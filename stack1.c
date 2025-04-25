#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef int elemtype;

typedef struct stack {
	elemtype* data;
	int top;
}stack;

//初始化
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

//检查栈是否为空
int isEmpty(stack* s) {
	if (s->top == -1) {
		return 1;
	}
	else return 0;
}

//进栈/压栈
int push(stack* s, elemtype e) {
	if (s->top >= MAXSIZE-1) {
		printf("栈满了\n");
		return 0;
	}
	s->data[++s->top] = e;
	return 1;
}

//出栈
int pop(stack* s, elemtype* e) {
	if (s->top < 0) {
		printf("栈空了\n");
		return 0;
	}
	*e = s->data[s->top--];
	return 1;
}

//获取栈顶元素
int getTop(stack* s, elemtype *e) {
	if (s->top < 0) {
		printf("栈空了\n");
		return 0;
	}
	*e = s->data[s->top];
	return 1;
}

int main() {
    printf("===== 栈功能测试 =====\n");
    int passed = 0, total = 0;

    // 测试1：初始化栈 
    printf("\n[测试1] 栈初始化\n");
    stack* s = initStack();
    if (s != NULL) {
        printf("＜（＾－＾）＞ 初始化成功\n");
        passed++;
    }
    else {
        printf("× 初始化失败\n");
    }
    total++;

    // 测试2：空栈检测 
    printf("\n[测试2] 空栈检测\n");
    if (isEmpty(s)) {
        printf("＜（＾－＾）＞ 空栈检测正确\n");
        passed++;
    }
    else {
        printf("× 空栈检测错误\n");
    }
    total++;

    // 测试3：压栈操作 
    printf("\n[测试3] 压栈测试\n");
    for (int i = 1; i <= 5; i++) {
        if (push(s, i * 10)) {
            printf("  压入 %d\n", i * 10);
        }
        else {
            printf("× 压栈失败\n");
        }
    }

    elemtype top_val;
    if (getTop(s, &top_val)) {
        if (top_val == 50) {
            printf("＜（＾－＾）＞ 栈顶元素正确(50)\n");
            passed++;
        }
        else {
            printf("× 栈顶元素错误，得到 %d\n", top_val);
        }
    }
    else {
        printf("× 获取栈顶失败\n");
    }
    total++;

    // 测试4：出栈操作 
    printf("\n[测试4] 出栈测试\n");
    elemtype pop_val;
    if (pop(s, &pop_val)) {
        if (pop_val == 50) {
            printf("＜（＾－＾）＞ 弹出元素正确(50)\n");
            passed++;
        }
        else {
            printf("× 弹出元素错误，得到 %d\n", pop_val);
        }
    }
    else {
        printf("× 出栈失败\n");
    }
    total++;

    // 测试5：栈满测试 
    printf("\n[测试5] 栈满测试\n");
    stack* full_stack = initStack();
    for (int i = 0; i < MAXSIZE; i++) {
        push(full_stack, i);
    }
    if (push(full_stack, MAXSIZE) == 0) {
        printf("＜（＾－＾）＞ 栈满检测正确\n");
        passed++;
    }
    else {
        printf("× 栈满检测失败\n");
    }
    total++;
    free(full_stack->data);
    free(full_stack);

    // 测试6：边界条件测试 
    printf("\n[测试6] 边界条件测试\n");
    stack* empty_stack = initStack();
    elemtype val;
    if (pop(empty_stack, &val) == 0) {
        printf("＜（＾－＾）＞ 空栈弹出检测正确\n");
        passed++;
    }
    else {
        printf("× 空栈弹出检测失败\n");
    }
    total++;
    free(empty_stack->data);
    free(empty_stack);

    // 测试7：内存释放 
    printf("\n[测试7] 内存释放测试\n");
    free(s->data);
    free(s);
    printf("＜（＾－＾）＞ 内存释放完成\n");
    passed++;
    total++;

    // 测试结果汇总 
    printf("\n===== 测试结果 =====\n");
    printf("通过测试: %d/%d\n", passed, total);
    printf("测试通过率: %.1f%%\n", (float)passed / total * 100);

    return 0;
}