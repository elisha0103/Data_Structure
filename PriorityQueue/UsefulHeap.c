//
//  UsefulHeap.c
//  PriorityQueue
//
//  Created by 진태영 on 2022/08/15.
//

#include "UsefulHeap.h"

void HeapInit(Heap * ph, PriorityComp pc)  // 힙의 초기화
{
    ph->numOfData = 0;
    ph->comp = pc;
}

int HIsEmpty(Heap * ph)  // 힙이 비었는지 확인
{
    if(ph->numOfData == 0)
        return TRUE;
    else
        return FALSE;
}

int GetParentIDX(int idx)  // 부모 노드 인덱스 반환
{
    return idx/2;
}

int GetLChildIDX(int idx)  // 자식 노드 중 왼쪽 노드 인덱스 반환
{
    return idx*2;
}

int GetRChildIDX(int idx)  // 자식 노드 중 오른쪽 노드 인덱스 반환
{
    return GetLChildIDX(idx) + 1;
}

int GetHiPriChildIDX(Heap * ph, int idx)  // 부모 노드의 자식 노드 중 우선순위 비교
{
    if(GetLChildIDX(idx) > ph->numOfData)  // idx 노드가 단말노드인 경우
        return 0;
    else if(GetLChildIDX(idx) == ph->numOfData) // 자식 노드가 하나라면 TRUE
        return GetLChildIDX(idx);
    else  // idx 노드가 단말 노드도 아니고, 자식노드가 하나이지도 않은 경우
    {
        if(ph->comp(ph->heapArr[GetLChildIDX(idx)], ph->heapArr[GetRChildIDX(idx)]) < 0)
            // 우선순위 비교 후, 0보다 작으면 => 오른쪽 자식이 우선순위 더 높은 경우
            return GetRChildIDX(idx);
        else  // 우선순위 비교 후 0보다 큰 경우 => 왼쪽 자식이 우선순위 더 높은 경우
            return GetLChildIDX(idx);
    }
}

void HInsert(Heap * ph, HData data)
{
    int idx = ph->numOfData +1; // 새 노드가 저장될 인덱스 값을 idx에 저장
    
    while(idx != 1) // 새 노드가 저장될 위치가 루트 노드의 위치가 아니라면 반복
    {
        // 새 노드와 부모 노드의 우선순위 비교
        if(ph->comp(data, ph->heapArr[GetParentIDX(idx)]) > 0)
        {  // 새 노드의 우선순위가 높다면
            ph -> heapArr[idx] = ph->heapArr[GetParentIDX(idx)];  // 부모 노드를 한 레벨 내림, 실제로 내림
            idx = GetParentIDX(idx);  // 새 노드를 한 레벨 올림, 실제로 올리지는 않고 인덱스 값만 갱신
            
        }
        else  // 새 노드의 우선순위가 높지 않다면
        {
            break;
        }
    }
    ph->heapArr[idx] = data;  // 새 노드를 배열에 저장
    ph->numOfData += 1;
}

HData HDelete(Heap * ph)
{
    HData retData = ph->heapArr[1];  // 반환을 위해서 삭제할 데이터 저장
    HData lastElem = ph->heapArr[ph->numOfData];  // 힙의 마지막 노드 저장
    
    int parentIdx = 1;  // 루트 노드가 위치해야할 인덱스 값 저장
    int childIdx;
    
    while(childIdx = GetHiPriChildIDX(ph, parentIdx))  // 루트노드의 자식 노드 중 우선순위가 높은 노드를 시작으로 반복문 진행
    {
        if(ph->comp(lastElem, ph->heapArr[childIdx]) >= 0)  // 마지막 노드와 우선순위 비교
            break;
        ph->heapArr[parentIdx] = ph->heapArr[childIdx];  // 마지막 노드보다 우선순위가 높으니, 비교 대상 노드의 위치를 한 레벨 올림
        parentIdx = childIdx;  // 마지막 노드가 저장될 위치정보를 한 레벨 내림
        // 반복문 탈출하면 parentIdx 에는 마지막 노드의 위치 정보가 저장됨
    }
    
    ph->heapArr[parentIdx] = lastElem;  // 마지막 노드 최종 저장
    ph->numOfData -= 1;
    return retData;
}

