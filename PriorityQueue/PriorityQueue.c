//
//  PriorityQueue.c
//  PriorityQueue
//
//  Created by 진태영 on 2022/08/15.
//

#include "PriorityQueue.h"
#include "UsefulHeap.h"

void PQueueInit(PQueue * ppq, PriorityComp pc)  // 우선순위 큐 초기화
{
    HeapInit(ppq, pc);
}

int PQIsEmpty(PQueue *ppq)  // 우선순위 큐가 비었는지 확인
{
    return HIsEmpty(ppq);
}

void PEnqueue(PQueue *ppq, PQData data)  // 우선순위 큐 데이터 삽입
{
    HInsert(ppq, data);
}

PQData PDequeue(PQueue *ppq)  // 우선순위 큐 데이터 삭제
{
    return HDelete(ppq);
}
