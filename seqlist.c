#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100
typedef int elemtype;

//˳�����
typedef struct {
    elemtype* data;
    int length;
} seqlist;

//��ʼ��
seqlist* init_seqlist()
{
    seqlist* l = (seqlist*)malloc(sizeof(seqlist));
    if (l == NULL) {
        printf("�ڴ����ʧ��\n");
        return NULL;
    }
    l->data = (elemtype*)malloc(sizeof(elemtype) * MAXSIZE);
    if (l->data == NULL) {
        free(l); // �ͷ�֮ǰ������ڴ�
        printf("�ڴ����ʧ��\n");
        return NULL;
    }
    l->length = 0;
    return l;
}

//β�����Ԫ��
int appendElem(seqlist* l, elemtype e)
{
    if (l->length >= MAXSIZE) {
        printf("˳�������\n");
        return 0;
    }
    l->data[l->length++] = e;
    return 1;
}

//����
void listElem(seqlist* l)
{
    for (int i = 0; i < l->length; i++)
    {
        printf("%d ", l->data[i]);
    }
    printf("\n");
    return;
}

//��������(ʹ���Ϊ��i�����ݣ�
int insertElem(seqlist* l, int pos, elemtype e)
{
    if (l->length >= MAXSIZE || pos > l->length || pos < 0) {
        printf("�������\n");
        return 0;
    }
    for (int i = l->length; i > pos; i--) {
        l->data[i] = l->data[i - 1];
    }
    l->data[pos] = e;
    l->length++;
    return 1;
}

//ɾ������
int deleteElem(seqlist* l, int pos, elemtype* e)
{
    if (pos < 0 || pos >= l->length)
    {
        printf("ɾ��λ�ô���\n");
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

//��������λ��
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

//�ݻ����Ա�
void destroy_seqlist(seqlist* l)
{
    free(l->data);
    free(l);
}

//�����������Ը�����������ȷ��
int main()
{
    // ��ʼ��˳���
    seqlist* l = init_seqlist();
    if (l == NULL) {
        printf("��ʼ��ʧ��\n");
        return -1;
    }

    // ����β�����Ԫ��
    printf("����β�����Ԫ��:\n");
    appendElem(l, 10);
    appendElem(l, 20);
    appendElem(l, 30);
    listElem(l); // Ԥ�����: 10 20 30

    // ���Բ���Ԫ��
    printf("���Բ���Ԫ��:\n");
    insertElem(l, 1, 15); // ������1������15
    listElem(l); // Ԥ�����: 10 15 20 30

    // ����ɾ��Ԫ��
    printf("����ɾ��Ԫ��:\n");
    elemtype deleted;
    deleteElem(l, 1, &deleted); // ɾ������1����Ԫ��
    printf("ɾ����Ԫ����: %d\n", deleted); // Ԥ�����: ɾ����Ԫ����: 15
    listElem(l); // Ԥ�����: 10 20 30

    // ���Բ���Ԫ��
    printf("���Բ���Ԫ��:\n");
    int pos = -1; // ��ʼ��Ϊ��Чֵ
    if (findElem(l, &pos, 30)) {
        printf("Ԫ��30������%d��\n", pos); // Ԥ�����: Ԫ��30������2��
    }
    else {
        printf("Ԫ��30δ�ҵ�\n");
    }

    // �ݻ�˳���
    destroy_seqlist(l);

    return 0;
}