//
//  main.c
//  PriorityQueue
//
//  Created by 진태영 on 2022/08/15.
//

#ifndef __USEFUL_HEAP_H__
#define __USEFUL_HEAP_H__

#define TRUE 1
#define FALSE 0

#define HEAP_LEN 100

typedef char HData;
typedef int (*PriorityComp)(HData d1, HData d2);  // 우선순위 기준을 정할 함수 포인터 변수 설정

typedef struct _heap  // 힙 자료구조
{
    PriorityComp comp;  // 힙 자료구조 우선순위를 결정할 함수 지정
    int numOfData;  // 노드 개수
    HData heapArr[HEAP_LEN];  // 힙 자료구조 최대 메모리 공간 할당
} Heap;

void HeapInit(Heap *ph, PriorityComp pc);  // 힙 자료구조 초기화
int HIsEmpty(Heap * ph);  // 힙 자료구조 비었는지 확인

void HInsert(Heap * ph, HData data);  // 힙 데이터 삽입
HData HDelete(Heap * ph);  // 힙 데이터 삭제

#endif
