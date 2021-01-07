#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TRUE 0
#define FALSE 1
#define MAX_SIZE 20

typedef int Element;

typedef struct Heap
{
	Element* rcd;
	int n;
	int size;
}Heap;

Heap* createHeap() {
	Heap* h;
	h = (Heap*)malloc(sizeof(Heap));
	h->rcd = (Element*)malloc(sizeof(Element));
	if (h->rcd == NULL || h == NULL) return NULL;
	h->n = 0;
	return h;
}

//��ӡ��
void printfHeap(Heap* h) {
	int num = h->n;
	for (int i = 1; i < num; i++) {
		printf("����ѵ�%d�ų�Ա��%d\n", i, h->rcd[i]);
	}
}

//�����������
void swapHeap(Heap* h, int i, int j) {
	Element t;
	t = h->rcd[i];
	h->rcd[i] = h->rcd[j];
	h->rcd[j] = t;
}

//ɸѡ���� ǰ�� ��pos���Ϊ��������������Ϊ�Ӷ�
void shiftDown(Heap* h, int pos) {
	int c, rc;
	while (pos <= h->n / 2) { //��posΪҶ�ӽ�� ѭ������
		c = pos * 2;   //cΪpos�����ӽ��
		rc = pos * 2 + 1;   //rcΪpos���Һ��ӽ��
		if (rc <= h->n && h->rcd[rc] > h->rcd[c])
			c = rc;
		if (h->rcd[pos] > h->rcd[c])
			return;
		swapHeap(h, pos, c); //�������ڵ�
	    pos = c; //�������µ���
	}
}

//���Ѻ���
void buildHeap(Heap* h) {
	for (int i = h->n / 2; i > 0; i--)
		shiftDown(h, i);
}

//�ж��Ƿ�����
bool heapFull(Heap* h) {
	if (h->n == h->size - 1) {
		return true;
	}

	return false;
}

//�ж��Ƿ�Ϊ��
bool heapEmpty(Heap* h) {
	if (h->n == 0)
		return true;
	return false;
}

//���ϵ�������
void shiftUp(Heap* h, int index) {
	while (1 != index && h->rcd[index] > h->rcd[index / 2]) {
		swapHeap(h, index, index / 2);
		index /= 2; //�������ϵ���
	}
	
	return;
}

//��������
void insertHeap(Heap* h, int e) {
	if (heapFull(h)) {
		printf("������������ʧ��\n");
		return;
	}
	int curr = h->n++;
	h->rcd[curr] = e; //�����ݲ��뵽��β
	shiftUp(h, curr); //�������������ϵ�������
	
	return;
}

//ɾ������
bool deleteHeap(Heap* h, Element e) {
	if (heapEmpty(h)) {
		printf("��Ϊ�գ�ɾ��ʧ��\n");
		return false;
	}

	e = h->rcd[1];
	h->rcd[1] = h->rcd[h->n];
	shiftDown(h, 1);

	return true;
}

//���ٶ�
bool heapDestroy(Heap* h)
{
	int i = 1;

	if (heapEmpty(h))
	{
		free(h);
		return true;
	}

	while (i <= h->n)
	{
		free(h->rcd + i);
	}

	free(h);
	return true;
}

void main() {
	int arr[MAX_SIZE] = { 0, 42, 58, 68, 98, 86, 49 }; //0�Ż�ַ����
	Heap* H;
	H = createHeap();
	H->size = MAX_SIZE;
	H->rcd = arr;
	H->n = 7;
	printfHeap(H);
	printf("---------------------\n");
	buildHeap(H);
	printfHeap(H);

	int choice;
	int data;
	
	while(1)
	{ 
		printf("---------------------\n");
	    printf("\nOption\n");
	    printf("1. Insert\n");
		printf("2. Delete\n");
		printf("3. Destroy\n");
		printf("--------------------\n");
		printf("What do you want? : ");
		scanf_s("%d", &choice);

		switch (choice)
		{
		case 1:

			printf("������Ҫ��������ݣ�");
			scanf_s("%d", &data);
			insertHeap(H, data);
			printfHeap(H);
			break;

		case 2:

			if (deleteHeap(H, data) == FALSE)
			{
				printf("Delete failed\n");
			}
			printfHeap(H);
			break;

		case 3:

			if (heapDestroy(H))
			{
				printf("Destroy success\n");
			}
			else
				printf("Destory failed\n");
			break;
		}
	}
}