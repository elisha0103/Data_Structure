#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

typedef int BTData;

// 이진트리의 노드를 표현한 구조체
typedef struct _bTreeNode
{
	BTData data;
	struct _bTreeNode* left;
	struct _bTreeNode* right;
} BTreeNode;

BTreeNode* MakeBTreeNode(void);  // 노드의 생상
BTData GetData(BTreeNode* bt);  // 노드에 저장된 데이터를 반환
void SetData(BTreeNode* bt, BTData data);  // 노드에 데이터를 저장

BTreeNode* GetLeftSubTree(BTreeNode* bt);  // 왼쪽 서브 트리 주소 값 반환
BTreeNode* GetRightSubTree(BTreeNode* bt);  // 오른쪽 서브 트리 주소 값 반환

void MakeLeftSubTree(BTreeNode* main, BTreeNode* sub);  // 왼쪽 트리와 트리의 연결을 담당
void MakeRightSubTree(BTreeNode* main, BTreeNode* sub);  // 오른쪽 트리와 트리의 연결을 담당

typedef void (*VisitFuncPtr)(BTData data);

void PreorderTraverse(BTreeNode* bt, VisitFuncPtr action);
void InorderTraverse(BTreeNode* bt, VisitFuncPtr action);
void PostorderTraverse(BTreeNode* bt, VisitFuncPtr action);

BTreeNode* RemoveLeftSubTree(BTreeNode* bt);  // 왼쪽 자식 노드를 트리에서 제거, 제거된 노드의 주소 값이 반환된다.
BTreeNode* RemoveRightSubTree(BTreeNode* bt);  // 오른쪽 자식 노드를 트리에서 제거, 제거된 노듸의 주소 값이 반환된다.
void ChangeLeftSubTree(BTreeNode* main, BTreeNode* sub);  // 메모리 소멸을 수반하지 않고 main의 왼쪽 자식 노드를 변경한다.(MakeLeftSubTree는 메모리 소멸을 하고 자식 교체)
void ChangeRightSubTree(BTreeNode* main, BTreeNode* sub);  // 메모리 소멸을 수반하지 않고 main의 오른쪽 자식 노드를 변경한다. (MakeRightSubTree는 메모리 소멸을 하고 자식 교체)
#endif