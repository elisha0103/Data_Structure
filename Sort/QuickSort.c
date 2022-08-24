#include <stdio.h>

void swap(int arr[], int idx1, int idx2)
{
	int temp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = temp;
}

int Patition(int arr[], int left, int right)
{
	int pivot = arr[left];  // 피벗의 위치는 가장 왼쪽
	int low = left + 1;
	int high = right;

	while (low <= high)   // 교차되지 않을 때까지 반복
	{
		// 피벗보다 큰 값을 찾는 과정
		while (pivot >= arr[low] && low<= right)   // 배열 변수가 pivot 보다 큰면 탈출
			// 피벗 값과 배열의 값이 같은 경우도 정렬 대상으로 반영하고, 큰 값을 찾는 과정에서 해당 배열 영역내에서만 찾을 수 있도록 low<=right 값을 추가(index 오류 방지)
			low++;      //  low를 오른쪽으로 이동

		// 피벗보다 작은 값을 찾는 과정
		while (pivot <= arr[high] && high >= (left +1))  // 배열 변수가 pivot 보다 작으면 탈출
			// 피벗 값과 배열의 값이 같은경우도 정렬 대상으로 반영하고 작은 값을 찾는 과정에서 해당 배열 영역내에서만 찾을 수 있도록 high>=(left+1)로 조건 추가. left+1은 피벗을 침해받지않기 위함
			high--;

		// 교차되지 않은 상태라면 swap 진행
		if (low <= high)
			swap(arr, low, high);

	}
	
	swap(arr, left, high);  // 피벗과 high가 가리키는 대상 교환
	return high;  // 옮겨진 피벗의 위치정보 반환, 제 자리를 찾은 피벗의 위치를 반환한다.
}

void quicksort(int arr[], int left, int right)
{
	if (left <= right)
	{
		int pivot = Patition(arr, left, right);   // 둘로 나눠서
		quicksort(arr, left, pivot - 1);          // 왼쪽 영역을 정렬
		quicksort(arr, pivot + 1, right);         // 오른쪽 영역을 정렬
	}
}


int main(void)
{
	int arr[7] = { 3, 2, 4, 1, 7, 6, 5 };
	// int arr[3] = {3, 3, 3};

	int len = sizeof(arr) / sizeof(int);
	int i;

	quicksort(arr, 0, sizeof(arr) / sizeof(int) - 1);

	for (i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);

	}

	printf("\n");
	return 0;
}
