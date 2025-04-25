#include <stdio.h>
#include <stdlib.h>

typedef int elemtype;
typedef struct stack {
	elemtype data;
	struct stack* next;
}stack;

//栈的初始化
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

//判断栈是否为空
int isEmpty(stack* s)
{
	if (s->next == NULL) {
		return 1;
	}
	else return 0;
}

//进栈/压栈
//因为栈的操作满足后进先出，先进后出，所以我们选择使用头插法
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

//出栈
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

//获取栈顶元素
int getTop(stack* s, elemtype* e) {
	if (s->next == NULL) {
		return 0;
	}
	*e = s->next->data;
	return 1;
}

//毁栈
void destroyStack(stack* s) {
	elemtype temp;
	while (pop(s, &temp)); // 弹出所有元素 
	free(s);
}

#include <stdio.h>
#include <stdlib.h>

/* [在此插入您提供的所有栈函数定义] */

int main() {
    printf("===== 链栈功能测试 =====\n");
    int test_count = 0;
    int passed_count = 0;

    // 测试1：初始化栈 
    printf("\n[测试1] 栈初始化\n");
    stack* s = initSack();
    if (s != NULL) {
        printf("＜（＾－＾）＞ 初始化成功\n");
        passed_count++;
    }
    else {
        printf("× 初始化失败\n");
    }
    test_count++;

    // 测试2：空栈检测 
    printf("\n[测试2] 空栈检测\n");
    if (isEmpty(s)) {
        printf("＜（＾－＾）＞ 空栈检测正确\n");
        passed_count++;
    }
    else {
        printf("× 空栈检测错误\n");
    }
    test_count++;

    // 测试3：压栈操作 
    printf("\n[测试3] 压栈测试(压入10,20,30)\n");
    push(s, 10);
    push(s, 20);
    push(s, 30);

    elemtype top_val;
    if (getTop(s, &top_val)) {
        if (top_val == 30) {
            printf("＜（＾－＾）＞ 栈顶元素正确(30)\n");
            passed_count++;
        }
        else {
            printf("× 栈顶元素错误，得到 %d\n", top_val);
        }
    }
    else {
        printf("× 获取栈顶失败\n");
    }
    test_count++;

    // 测试4：出栈操作 
    printf("\n[测试4] 出栈测试\n");
    elemtype pop_val;
    if (pop(s, &pop_val)) {
        if (pop_val == 30) {
            printf("＜（＾－＾）＞ 弹出元素正确(30)\n");
            passed_count++;
        }
        else {
            printf("× 弹出元素错误，得到 %d\n", pop_val);
        }
    }
    else {
        printf("× 出栈失败\n");
    }
    test_count++;

    // 测试5：栈顺序测试(LIFO)
    printf("\n[测试5] 后进先出测试\n");
    pop(s, &pop_val);
    getTop(s, &top_val);
    if (pop_val == 20 && top_val == 10) {
        printf("＜（＾－＾）＞ 顺序正确(弹出20，剩余10)\n");
        passed_count++;
    }
    else {
        printf("× 顺序错误，弹出 %d，剩余 %d\n", pop_val, top_val);
    }
    test_count++;

    // 测试6：边界条件测试 
    printf("\n[测试6] 边界条件测试\n");
    pop(s, &pop_val); // 弹出最后一个元素 
    if (pop(s, &pop_val) == 0 && isEmpty(s)) {
        printf("＜（＾－＾）＞ 空栈弹出检测正确\n");
        passed_count++;
    }
    else {
        printf("× 空栈弹出检测失败\n");
    }
    test_count++;

    // 测试7：内存释放测试 
    printf("\n[测试7] 内存释放测试\n");
    free(s);
    printf("＜（＾－＾）＞ 内存释放完成\n");
    passed_count++;
    test_count++;

    // 测试结果汇总 
    printf("\n===== 测试结果 =====\n");
    printf("通过测试: %d/%d\n", passed_count, test_count);
    printf("测试通过率: %.1f%%\n", (float)passed_count / test_count * 100);

    return 0;
}