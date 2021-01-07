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

//打印堆
void printfHeap(Heap* h) {
	int num = h->n;
	for (int i = 1; i < num; i++) {
		printf("输出堆的%d号成员：%d\n", i, h->rcd[i]);
	}
}

//交换两个结点
void swapHeap(Heap* h, int i, int j) {
	Element t;
	t = h->rcd[i];
	h->rcd[i] = h->rcd[j];
	h->rcd[j] = t;
}

//筛选函数 前提 以pos结点为根的左右子树都为子堆
void shiftDown(Heap* h, int pos) {
	int c, rc;
	while (pos <= h->n / 2) { //若pos为叶子结点 循环结束
		c = pos * 2;   //c为pos的左孩子结点
		rc = pos * 2 + 1;   //rc为pos的右孩子结点
		if (rc <= h->n && h->rcd[rc] > h->rcd[c])
			c = rc;
		if (h->rcd[pos] > h->rcd[c])
			return;
		swapHeap(h, pos, c); //交换两节点
	    pos = c; //继续向下调整
	}
}

//建堆函数
void buildHeap(Heap* h) {
	for (int i = h->n / 2; i > 0; i--)
		shiftDown(h, i);
}

//判堆是否已满
bool heapFull(Heap* h) {
	if (h->n == h->size - 1) {
		return true;
	}

	return false;
}

//判堆是否为空
bool heapEmpty(Heap* h) {
	if (h->n == 0)
		return true;
	return false;
}

//向上调整数据
void shiftUp(Heap* h, int index) {
	while (1 != index && h->rcd[index] > h->rcd[index / 2]) {
		swapHeap(h, index, index / 2);
		index /= 2; //继续向上调整
	}
	
	return;
}

//插入数据
void insertHeap(Heap* h, int e) {
	if (heapFull(h)) {
		printf("堆已满，插入失败\n");
		return;
	}
	int curr = h->n++;
	h->rcd[curr] = e; //将数据插入到堆尾
	shiftUp(h, curr); //插入数据是向上调整数据
	
	return;
}

//删除数据
bool deleteHeap(Heap* h, Element e) {
	if (heapEmpty(h)) {
		printf("堆为空，删除失败\n");
		return false;
	}

	e = h->rcd[1];
	h->rcd[1] = h->rcd[h->n];
	shiftDown(h, 1);

	return true;
}

//销毁堆
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
	int arr[MAX_SIZE] = { 0, 42, 58, 68, 98, 86, 49 }; //0号基址闲置
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

			printf("请输入要插入的数据：");
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