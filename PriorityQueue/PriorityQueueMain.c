//
//  PriorityQueueMain.c
//  PriorityQueue
//
//  Created by 진태영 on 2022/08/15.
//

#include <stdio.h>
#include "PriorityQueue.h"

int DataPriorityComp(char ch1, char ch2) // 우선순위를 정할 기준 함수
{
    return ch2 - ch1;  // 첫번째 인자의 우선순위가 높다면 0보다 큰 값, 두번째 인자가 높다면 0보다 작은 값, 같다면 0
}

int main()
{
    PQueue pq;
    PQueueInit(&pq, DataPriorityComp); // 우선순위 비교 함수 등록
    
    PEnqueue(&pq, 'A');
    PEnqueue(&pq, 'B');
    PEnqueue(&pq, 'C');
    printf("%c \n", PDequeue(&pq));
    
    PEnqueue(&pq, 'A');
    PEnqueue(&pq, 'B');
    PEnqueue(&pq, 'C');
    printf("%c \n", PDequeue(&pq));
    
    while(!PQIsEmpty(&pq))
        printf("%c \n", PDequeue(&pq));
    
    return 0;
}
