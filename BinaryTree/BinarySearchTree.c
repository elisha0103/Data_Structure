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
