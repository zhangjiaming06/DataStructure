#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100
typedef int elemtype;

//顺序表定义
typedef struct {
    elemtype* data;
    int length;
} seqlist;

//初始化
seqlist* init_seqlist()
{
    seqlist* l = (seqlist*)malloc(sizeof(seqlist));
    if (l == NULL) {
        printf("内存分配失败\n");
        return NULL;
    }
    l->data = (elemtype*)malloc(sizeof(elemtype) * MAXSIZE);
    if (l->data == NULL) {
        free(l); // 释放之前分配的内存
        printf("内存分配失败\n");
        return NULL;
    }
    l->length = 0;
    return l;
}

//尾部添加元素
int appendElem(seqlist* l, elemtype e)
{
    if (l->length >= MAXSIZE) {
        printf("顺序表已满\n");
        return 0;
    }
    l->data[l->length++] = e;
    return 1;
}

//遍历
void listElem(seqlist* l)
{
    for (int i = 0; i < l->length; i++)
    {
        printf("%d ", l->data[i]);
    }
    printf("\n");
    return;
}

//插入数据(使其成为第i个数据）
int insertElem(seqlist* l, int pos, elemtype e)
{
    if (l->length >= MAXSIZE || pos > l->length || pos < 0) {
        printf("插入错误\n");
        return 0;
    }
    for (int i = l->length; i > pos; i--) {
        l->data[i] = l->data[i - 1];
    }
    l->data[pos] = e;
    l->length++;
    return 1;
}

//删除数据
int deleteElem(seqlist* l, int pos, elemtype* e)
{
    if (pos < 0 || pos >= l->length)
    {
        printf("删除位置错误\n");
        return 0;
    }
    *e = l->data[pos];
    for (int i = pos; i < l->length - 1; i++)
    {
        l->data[i] = l->data[i + 1];
    }
    l->length--;
    return 1;
}

//查找数据位置
int findElem(seqlist* l, int* pos, elemtype e)
{
    for (int i = 0; i < l->length; i++)
    {
        if (l->data[i] == e) {
            *pos = i;
            return 1;
        }
    }
    return 0;
}

//摧毁线性表
void destroy_seqlist(seqlist* l)
{
    free(l->data);
    free(l);
}

//主函数，测试各个函数的正确性
int main()
{
    // 初始化顺序表
    seqlist* l = init_seqlist();
    if (l == NULL) {
        printf("初始化失败\n");
        return -1;
    }

    // 测试尾部添加元素
    printf("测试尾部添加元素:\n");
    appendElem(l, 10);
    appendElem(l, 20);
    appendElem(l, 30);
    listElem(l); // 预期输出: 10 20 30

    // 测试插入元素
    printf("测试插入元素:\n");
    insertElem(l, 1, 15); // 在索引1处插入15
    listElem(l); // 预期输出: 10 15 20 30

    // 测试删除元素
    printf("测试删除元素:\n");
    elemtype deleted;
    deleteElem(l, 1, &deleted); // 删除索引1处的元素
    printf("删除的元素是: %d\n", deleted); // 预期输出: 删除的元素是: 15
    listElem(l); // 预期输出: 10 20 30

    // 测试查找元素
    printf("测试查找元素:\n");
    int pos = -1; // 初始化为无效值
    if (findElem(l, &pos, 30)) {
        printf("元素30在索引%d处\n", pos); // 预期输出: 元素30在索引2处
    }
    else {
        printf("元素30未找到\n");
    }

    // 摧毁顺序表
    destroy_seqlist(l);

    return 0;
}