#include <stdio.h>
#include <stdlib.h>

typedef struct matrix {
	int** arr;
	int rows;
	int* columns;
}matrix;

typedef struct vect {
	int* vect;
	int size;
}vect;

int scanfs(int* a, int b) {
	int c;
	do {
		c = scanf("%d", a);
		if (c < 0)
			return 0;
		if (c == 0 || (b == 1 && *a <= 0)) {
			printf("Error, try again: ");
			scanf("%*c");
		}
	} while (c == 0 || (b == 1 && *a <= 0));
	return 1;
}

int init_arr(matrix* a) {
	int* ptr1, * ptr3;
	int** ptr2;
	printf("Enter the number of rows: ");
	if (scanfs(&a->rows, 1) == 0) {
		return 0;
	}
	a->arr = (int**)malloc(a->rows * sizeof(int*));
	a->columns = (int*)malloc(a->rows * sizeof(int));
	ptr1 = &a->columns[0];
	ptr2 = &a->arr[0];
	for (int i = 0; i < a->rows; i++) {
		printf("Enter the number of elements the %d row: ", i + 1);
		if (scanfs(ptr1, 1) == 0) {
			return 0;
		}
		*ptr2 = (int*)malloc((*ptr1) * sizeof(int));
		printf("Enter the row elements: ");
		ptr3 = *ptr2;
		for (int j = 0; j < *ptr1; j++) {
			if (scanfs(ptr3, 0) == 0) {
				return 0;
			}
			ptr3++;
		}
		ptr1++;
		ptr2++;
	}
	return 1;
}

void print_arr(matrix* a) {
	printf("Introduced matrix:\n");
	for (int i = 0; i < a->rows; i++) {
		for (int j = 0; j < *(a->columns + i); j++) {
			printf("%d ", *(*(a->arr + i) + j));
		}
		printf("\n");
	}
}

void free_arr(matrix* a) {
	for (int i = 0; i < a->rows; i++) {
		free(a->arr[i]);
	}
	free(a->arr);
	free(a->columns);
}

int sum_digits(int a) {
	int b = 0;
	if (a < 0) {
		a *= -1;
	}
	while (a != 0) {
		b += a % 10;
		a /= 10;
	}
	return b;
}

void init_vect(matrix* a, vect* v) {
	v->size = a->rows;
	v->vect = (int*)malloc(v->size * sizeof(int));
	for (int i = 0; i < a->rows; i++) {
		int b = a->arr[i][0];
		int c = sum_digits(a->arr[i][0]);
		for (int j = 1; j < a->columns[i]; j++) {
			if (sum_digits(a->arr[i][j]) == c) {
				b += a->arr[i][j];
			}
		}
		v->vect[i] = b;
	}
}

void print_vect(vect* v) {
	printf("Vector:\n");
	for (int i = 0; i < v->size; i++) {
		printf("%d ", v->vect[i]);
	}
	printf("\n");
}

int main() {
	matrix a;
	vect v;
	if (init_arr(&a) == 0) {
		free(v.vect);
		free_arr(&a);
		return 0;
	}
	print_arr(&a);
	init_vect(&a, &v);
	print_vect(&v);
	free(v.vect);
	free_arr(&a);
	return 0;
}