#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "DynamicHeap.h"

void MEmpty_Heap(THeap* Heap)
{
	Heap->top = (TCell*)malloc(sizeof(TCell));
	Heap->bottom = Heap->top;
	Heap->top->next = NULL;
	Heap->size = 0;
}

int Empty_Heap(THeap Heap)
{
	return(Heap.size == 0);
}

void Push(TItem Item, THeap* Heap)
{
	TCell* aux;
	aux = (TCell*)malloc(sizeof(TCell));
	Heap->top->item = Item;
	aux->next = Heap->top;
	Heap->top = aux;
	Heap->size++;
}

void Pop(THeap* Heap, TItem* Item)
{
	TCell* aux;
	if (!Empty_Heap(*Heap))
	{
		aux = Heap->top;
		Heap->top = aux->next;
		*Item = aux->next->item;
		free(aux);
		Heap->size--;
	}
	else
	{
		printf("\n\t\t >>>>> MG: Empty Heap <<<<<\n");
	}
}

void Print_Item(TItem Item)
{
	printf("Code: %c\n", Item.c);
}

void Print_Heap(THeap* Heap)
{
	THeap Aux_Heap;
	MEmpty_Heap(&Aux_Heap);
	TItem Item;
	while (!Empty_Heap(*Heap))
	{
		Pop(Heap, &Item);
		Push(Item, &Aux_Heap);
	}
	while (!Empty_Heap(Aux_Heap))
	{
		Pop(&Aux_Heap, &Item);
		Print_Item(Item);
		Push(Item, Heap);
	}
	free(Aux_Heap.top);
}

void Print_Heap_FromTop(THeap* Heap)
{
	THeap Aux_Heap;
	MEmpty_Heap(&Aux_Heap);
	TItem Item;
	while (!Empty_Heap(*Heap))
	{
		Pop(Heap, &Item);
		Print_Item(Item);
		Push(Item, &Aux_Heap);
	}
	while (!Empty_Heap(Aux_Heap))
	{
		Pop(&Aux_Heap, &Item);
		Push(Item, Heap);
	}
	free(Aux_Heap.top);
}

void Free_Heap(THeap* Heap)
{
	TItem Item;
	while (!Empty_Heap(*Heap))
	{
		Pop(Heap, &Item);
	}
	free(Heap->top);
}

/* QUESTÃO 1 */
void Evaluate_Arithmetic_Expression(char* Expression, THeap* Heap)
{
	TItem Item;
	for (int i = 0; Expression[i] != '\0'; i++)
	{
		if (Expression[i] == '(' || Expression[i] == '[' || Expression[i] == '{')
		{
			Item.c = Expression[i];
			Push(Item, Heap);
		}
		else if (Expression[i] == ')')
		{
			if (Heap->top->next->item.c == '(')
			{
				Pop(Heap, &Item);
			}
			else
			{
				printf("This expression is incomplete. \n");
				return;
			}
		}
		else if (Expression[i] == ']')
		{
			if (Heap->top->next->item.c == '[')
			{
				Pop(Heap, &Item);
			}
			else
			{
				printf("This expression is incomplete. \n");
				return;
			}
		}
		else if (Expression[i] == '}')
		{
			if (Heap->top->next->item.c == '{')
			{
				Pop(Heap, &Item);
			}
			else
			{
				printf("This expression is incomplete. \n");
				return;
			}
		}

	}
	if(Empty_Heap(*Heap))
		printf("This expression is correct. \n");
	else
		printf("This expression is incorrect. \n");
	
}

/* QUESTÃO 2 */
void Translate_Expression(char* Expression, THeap* Heap)
{
	THeap Aux;
	MEmpty_Heap(&Aux);
	TItem Item;
	int i;
	char Top;
	for (i = 0; i < strlen(Expression); i++)
	{
		if (Expression[i] != ')' && Expression[i] != '-' &&
			Expression[i] != '+' && Expression[i] != '/' &&
			Expression[i] != '*' && Expression[i] != ' ')
		{
			Item.c = Expression[i];
			Push(Item, Heap);
		}
		else
		{
			Top = Heap->top->next->item.c;
			if (Expression[i] == '+' || Expression[i] == '-')
			{
				while (Top != '(')
				{
					Pop(Heap, &Item);
					Push(Item, &Aux);
					Top = Heap->top->next->item.c;
				}
				Item.c = Expression[i];
				Push(Item, Heap);
			}
			else if (Expression[i] == '*' || Expression[i] == '/')
			{
				while (Top != '(' && Top != '+' && Top != '-')
				{
					Pop(Heap, &Item);
					Push(Item, &Aux);
					Top = Heap->top->next->item.c;
				}
				Item.c = Expression[i];
				Push(Item, Heap);
			}
			else if (Expression[i] == ')')
			{
				while (Top != '(')
				{
					Pop(Heap, &Item);
					Push(Item, &Aux);
					Top = Heap->top->next->item.c;
				}
				Pop(Heap, &Item);
			} 
		}
	}
	printf("\n\t\t >>> Translated Expression <<<\n");
	Print_Heap(&Aux);
	printf("\n\n");
		while (!Empty_Heap(Aux))
		{
			Pop(&Aux, &Item);
			Push(Item, Heap);
		}
	Free_Heap(&Aux);
}

/* QUESTÃO 3 */
void Sum_Numbers(int* n1, int t1, int* n2, int t2)
{
	int i, result = 0;
	THeap Heap_N1, Heap_N2, Heap_Sum;
	MEmpty_Heap(&Heap_N1);
	MEmpty_Heap(&Heap_N2);
	MEmpty_Heap(&Heap_Sum);
	TItem Item1, Item2;
	for (i = 0; i < t1; i++)
	{
		Item1.code = n1[i];
		Push(Item1, &Heap_N1);
	}
	for (i = 0; i < t2; i++)
	{
		Item2.code = n2[i];
		Push(Item2, &Heap_N2);
	}
	while (!Empty_Heap(Heap_N1) && !Empty_Heap(Heap_N2))
	{
		Pop(&Heap_N1, &Item1);
		Pop(&Heap_N2, &Item2);
		result = result + Item1.code + Item2.code;
		if (result < 9)
		{
			Item1.code = result;
			Push(Item1, &Heap_Sum);
			result = 0;
		}
		else
		{
			Item1.code = result % 10;
			Push(Item1, &Heap_Sum);
			result = 1;
		}
	}
	printf("Tamanho pilha 1: %d\n", Heap_N1.size);
	printf("Tamanho pilha 2: %d\n", Heap_N2.size);
	while (!Empty_Heap(Heap_N1))
	{
		Pop(&Heap_N1, &Item1);
		result = result + Item1.code;
		Item1.code = result;
		Push(Item1, &Heap_Sum);
		result = 0;
	}

	while (!Empty_Heap(Heap_N2))
	{
		Pop(&Heap_N2, &Item2);
		result = result + Item2.code;
		Item2.code = result;
		Push(Item2, &Heap_Sum);
		result = 0;
	}
	result = 0;
	int s_max = Heap_Sum.size - 1;
	while (!Empty_Heap(Heap_Sum))
	{
		Pop(&Heap_Sum, &Item1);
		result = result + (Item1.code * pow(10, s_max));
		printf("%d\n", result);
		s_max--;
	}
	printf("Result: %d", result);
	Free_Heap(&Heap_N1);
	Free_Heap(&Heap_N2);
	Free_Heap(&Heap_Sum);
}