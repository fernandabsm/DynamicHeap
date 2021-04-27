#include <stdio.h>
#include <stdlib.h>

#ifndef DYNAMIC_HEAP_H
#define DYNAMIC_HEAP_H

typedef struct
{
	int code;
	char c;
}TItem;

typedef	struct Cell
{
	TItem item;
	struct Cell* next;
}TCell;

typedef struct
{
	TCell* bottom;
	TCell* top;
	int size;
}THeap;

void MEmpty_Heap(THeap* Heap);

int Empty_Heap(THeap Heap);

void Push(TItem Item, THeap* Heap);

void Pop(THeap* Heap, TItem* Item);

void Print_Item(TItem Item);

void Print_Heap(THeap* Heap);

void Print_Heap_FromTop(THeap* Heap);

void Free_Heap(THeap* Heap);

void Evaluate_Arithmetic_Expression(char* Expression, THeap* Heap);

void Translate_Expression(char* Expression, THeap* Heap);

void Sum_Numbers(int* n1, int t1, int* n2, int t2);

#endif // !DYNAMIC_HEAP_H

