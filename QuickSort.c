#include <stdio.h>
#include "stack.h"

void PrintArray(int* array, int size) {
	for (int i = 0; i < size; ++i)
		printf("%d ", array[i]);
	printf("\n");
}

void Swap(int* left, int* right) {
	int tmp = *left;
	*left = *right;
	*right = tmp;
}

int Partion(int* array, int left, int right) {
	int begin = left;
	int end = right - 1;
	int key = array[right - 1];
	while (begin < end) {
		while (begin < end&&array[begin] <= key)
			begin++;
		while (begin < end&&array[end] >= key)
			end--;
		if (begin != end)
			Swap(&array[begin], &array[end]);
	}
	if (begin != right - 1)
		Swap(&array[begin], &array[right - 1]);
	return begin;
}

int Partion1(int* array, int left, int right) {
	int begin = left;
	int end = right - 1;
	int key = array[right - 1];
	while (begin < end) {
		while (begin < end&&array[begin] <= key)
			begin++;
		if (begin < end) {
			array[end] = array[begin];
			end--;
		}
		while (begin < end&&array[end] >= key)
			end--;
		if (begin < end) {
			array[begin] = array[end];
			begin++;
		}
	}
	array[begin] = key;
	return begin;
}

int Partion2(int* array, int left, int right) {
	int cur = left;
	int prev = left - 1;
	int key = array[right - 1];
	while (cur < right) {
		while (array[cur] < key&&++prev != cur)
			Swap(&array[cur], &array[prev]);
		++cur;
	}
	if (++prev != right)
		Swap(&array[prev], &array[right - 1]);
	return prev;
}

void QuickSort(int* array, int left, int right) {
	if (right - left > 1) {
		//按照基准值将区间分割成左右两部分
		//左侧小于基准值， 右侧大于基准值
		int div = Partion2(array, left, right);
		QuickSort(array, left, div);
		QuickSort(array, div+1, right);
	}
}

void QuickSortNor(int* array, int left, int right) {
	Stack st;
	StackInit(&st);

	StackPush(&st, left);
	StackPush(&st, right);
	while (!StackEmpty(&st)) {
		int end = StackTop(&st);
		StackPop(&st);
		int begin = StackTop(&st);
		StackPop(&st);

		int div = Partion2(array, begin, end);

		if (begin < div-1) {
			StackPush(&st, begin);
			StackPush(&st, div);
		}
		if (div + 1 < end) {
			StackPush(&st, div + 1);
			StackPush(&st, end);
		}
	}
}

int main() {
	int array[] = { 3,4,2,9,1,7,6,0,8,5 };
	QuickSortNor(array, 0, sizeof(array) / sizeof(array[0]));
	PrintArray(array, sizeof(array) / sizeof(array[0]));
	return 0;
}