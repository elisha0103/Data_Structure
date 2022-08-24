#include <stdio.h>
#include "BinaryTree.h"
#include "BinarySearchTree.h"

void BSTMakeAndInit(BTreeNode** pRoot)  
{
	*pRoot = NULL;
}

BSTData BSTGetNodeData(BTreeNode* bst)  
{
	return GetData(bst);
}

void BSTInsert(BTreeNode** pRoot, BSTData data)
{
	BTreeNode* pNode = NULL;  // parent node
	BTreeNode* cNode = *pRoot;  // current node
	BTreeNode* nNode = NULL;  // new node

	// 새로운 노드가(새 데이터가 담긴 노드가) 추가될 위치를 찾는다. (pNode)
	while (cNode != NULL)  
	{
		if (data == GetData(cNode))
			return;  // 데이터의(키의) 중복을 허용하지 않음

		pNode = cNode;

		if (GetData(cNode) > data)
			cNode = GetLeftSubTree(cNode);  // 현재 노드를 왼쪽 자식 노드로 이동
		else
			cNode = GetRightSubTree(cNode);
	}

	// 노드의 생성부
	// pNode의 자식 노드로 추가할 새 노드의 생성
	nNode = MakeBTreeNode(); // 새 노드의 생성
	SetData(nNode, data);  // 새 노드에 데이터 저장

	// pNode 의 자식 노드로 새 노드를 추가
	if (pNode != NULL)  // 새 노드가 루트 노드가 아니라면( 새 노드가 최상단 루트 노드가 아니라면)
	{
		if (data < GetData(pNode))
			MakeLeftSubTree(pNode, nNode);
		else
			MakeRightSubTree(pNode, nNode);
	}
	else  // 새 노드가 최상단 루트 노드라면
		*pRoot = nNode;
}

BTreeNode* BSTSearch(BTreeNode* bst, BSTData target)
{
	BTreeNode* cNode = bst;
	BSTData cd;

	while (cNode != NULL)
	{
		cd = GetData(cNode);

		if (target == cd)
			return cNode;
		else if (target < cd)
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}

	return NULL;
}

BTreeNode* BSTRemove(BTreeNode** pRoot, BSTData target)
{
	// 삭제 대상이 루트 노드인 경우를 별도로 고려해야한다.
	BTreeNode* pVRoot = MakeBTreeNode();  // 가상 루트 노드
	BTreeNode* pNode = pVRoot;  // parent node
	BTreeNode* cNode = *pRoot;  // current node
	BTreeNode* dNode;  // delete node

	// 루트 노드를 pVRoot가 가리키는 노드의 오른쪽 자식 노드가 되게 한다.
	ChangeRightSubTree(pVRoot, *pRoot);  // 삭제 대상이 루트 노드인 경우를 고려하여 루트노드의 부모 노드를 가상의 루트 노드로 설정

	// 삭제 대상인 노드를 탐색
	// 현재 노드가 단말노드가 아니고, 삭제 대상이 아닐경우 반복
	while (cNode != NULL && GetData(cNode) != target)
	{
		// 노드를 아래로 내려가면서 대상을 찾는 과정
		pNode = cNode;

		if (target < GetData(cNode))  // target이 값이 작으면 왼쪽 아래로 이동
			cNode = GetLeftSubTree(cNode);
		else  // target 값이 더 크면 오른쪽 아래로 이동
			cNode = GetRightSubTree(cNode);
	}

	if (cNode == NULL)  // while 문 탈출 이유가 cNode == NULL 이라면 삭제 대상이 존재하지 않음
		return NULL;

	dNode = cNode;  // while 문 탈출 이유가 target == cNode 인 경우

	// 첫 번째 경우 : 삭제 대상이 단말 노드인 경우
	if (GetLeftSubTree(dNode) == NULL && GetRightSubTree(dNode) == NULL)
	{
		if (GetLeftSubTree(pNode) == dNode)  // 삭제 대상이 왼쪽 단말이라면
			RemoveLeftSubTree(pNode);
		else  // 삭제 대상이 오른쪽 단말이라면
			RemoveRightSubTree(pNode);
	}

	// 두 번째 경우 : 삭제 대상이 하나의 자식 노드를 갖는 경우
	else if (GetLeftSubTree(dNode) == NULL || GetRightSubTree(dNode) == NULL)
	{
		BTreeNode* dcNode;

		if (GetLeftSubTree(dNode) != NULL)
			dcNode = GetLeftSubTree(dNode);  // 왼쪽 자식이 있는 경우
		else  
			dcNode = GetRightSubTree(dNode);  // 오른쪽 자식이 있는 경우

		if (GetLeftSubTree(pNode) == dNode)  // 삭제 대상 노드의 자리를 그 자식 노드가 대신함
			ChangeLeftSubTree(pNode, dcNode);
		else
			ChangeRightSubTree(pNode, dcNode);
	}

	// 세 번째 경우 : 두 개의 자식 노드를 모두 갖는 경우
	else
	{
		BTreeNode* mNode = GetRightSubTree(dNode);  // mNode 는 대체노드를 가리킴
		BTreeNode* mpNode = dNode;  // mpNode 는 대체노드의 부모노드를 가리킴
		int delData;

		// 삭제 대상의 대체 노드를 찾는다.
		while (GetLeftSubTree(mNode) != NULL)
		{
			// dNode의 오른쪽 서브트리의 맨 왼쪽 노드를 찾는 과정
			mpNode = mNode;
			mNode = GetLeftSubTree(mNode);
		}

		// 대체 노드에 저장된 값을 삭제할 노드에 대입한다.
		delData = GetData(dNode);  // 대입 전 데이터 백업
		SetData(dNode, GetData(mNode));  // 대입

		// 대체 노드의 부모 노드와 자식 노드를 연결한다.
		if (GetLeftSubTree(mpNode) == mNode)
			ChangeLeftSubTree(mpNode, GetRightSubTree(mNode));
		else
			ChangeRightSubTree(mpNode, GetRightSubTree(mNode));

		dNode = mNode;  // mNode의 부모와 mNode의 자식노드가 연결된 후 mNode는 연결성이 사라진 노드
		// cNode를 가리키던 dNode를 연결성 없는 mNode를 가리키게 한다.
		SetData(dNode, delData);  // 연결성 없는 mNode 즉, dNode에 백업 데이터 복원
	}

	// 삭제된 노드가 루트 노드인 경우에 대한 추가적인 처리
	// 삭제된 노드가 루트 노드인 경우 pRoot는 더이상 루트노드를 가리키지 않음
	// 따라서 pRoot 변수를 새롭게 갱신해야 함. 이를 위해 pVRoot 변수가 사용되었음
	if (GetRightSubTree(pVRoot) != *pRoot)
		*pRoot = GetRightSubTree(pVRoot);

	free(pVRoot);  // pVRoot는 가상 루트 변수이므로 역할을 다하고 메모리 해제
	return dNode;  // 삭제 대상의 반환
}

void ShowIntData(int data)
{
	printf("%d ", data);
}

void BSTShowAll(BTreeNode* bst)
{
	InorderTraverse(bst, ShowIntData);  // 중위 순회
}