#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int TMP[50];

// INSERTION SORT
void insertionSort(int* A, int n){
	for(int i = 1; i < n; i++){
		// Tìm vị trí cho mỗi A[i]
		int j = i;
		while(j > 0 && A[j-1] > A[i]){
			j--;
		}
		// Đưa A[i] về đúng trị trí
		int tmp = A[i];
		for(int k = i; k > j; k--){
			A[k] = A[k-1];
		}
		A[j] = tmp;
	}
}

// MERGE SORT
void mergeSort(int* A, int L, int R){
	if(L == R){		// Khi không còn phần tử nào
		return;
	}
	int mid = (L+R)/2;

	// Chia đôi hai phần
	mergeSort(A, L, mid);
	mergeSort(A, mid+1, R);

	// Trộn hai phần đã chia
	int i = L, j = mid+1;
	int tmp = 0;
	while(i <= mid || j <= R){
		if(i > mid){
			TMP[tmp++] = A[j++];
		}
		else if(j > R){
			TMP[tmp++] = A[i++];
		}
		else if(A[i] < A[j]){
			TMP[tmp++] = A[i++];
		}
		else{
			TMP[tmp++] = A[j++];
		}
	}
	
	for(int i = 0; i < tmp; i++){
		A[L+i] = TMP[i];
	}
}

// BUBBLE SORT
void bubbleSort(int* A, int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n-1; j++){
			if(A[j] > A[j+1]){
				int tmp = A[j];
				A[j] = A[j+1];
				A[j+1] = tmp;
			}
		}
	}
}

// SELECTION SORT 
void selectionSort(int* A, int n){
	for(int i = 0; i < n; i++){
		int indexmin = i;
		for(int j = i+1; j < n; j++){
			if(A[indexmin] > A[j]){
				indexmin = j;
			}
		}
		if(indexmin != i){
			int tmp = A[indexmin];
			A[indexmin] = A[i];
			A[i] = tmp;
		}	
	}
}

// QUICK SORT
void quickSort(int* A, int L, int R){
	int i = L, j = R;
	int pivot = A[ L + rand() % (R-L+1) ];

	// Sắp xếp các phần tử
	while(i <= j){
		while(A[i] < pivot){
			++i;
		}
		while(A[j] > pivot){
			--j;
		}
		if(i <= j){
			int tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
			++i;
			--j;
		}
	}

	// Gọi đệ quy cho từng nửa 2 bên phần tử pivot
	if(L < j){
		quickSort(A, L, j);
	}
	if(i < R){
		quickSort(A, i, R);
	}
}

// HEAP SORT
void swap(int& a, int& b){
	int tmp = a;
	a = b;
	b = tmp;
}

void heapify(int* A, int i, int N){
	int L = 2*i;
	int R = 2*i + 1;
	int max = i;

	if(L <= N && A[L] > A[i]){
		max = L;
	}
	if(R <= N && A[R] > A[max]){
		max = R;
	}
	if(max != i){
		swap(A[i], A[max]);
		heapify(A, max, N);
	}
}

void heapSort(int* A, int N){
	// Built Heap
	for(int i = N/2-1; i >= 0; i--){
		heapify(A, i, N);
	}
	// Heap Sort
	for(int i = N-1; i > 0; i--){
		swap(A[0], A[i]);
		heapify(A, 0, i-1);
	}


}


int main(){
	int A[] = {5, 7, 3, 8, 2, 1, 100, 4, 6};
	int n = 9;
	int L = 0, R = 8;

	//insertionSort(A, n);

	//mergeSort(A, L, R);

	//bubbleSort(A, n);

	//selectionSort(A, n);

	//quickSort(A, L, R);

	heapSort(A, n);

	printf("\nResult:");
	for(int i = 0; i < n; i++){
		printf(" %d", A[i]);
	}
	getch();
	return 0;
}
