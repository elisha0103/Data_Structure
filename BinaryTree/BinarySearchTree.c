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

	// ���ο� ��尡(�� �����Ͱ� ��� ��尡) �߰��� ��ġ�� ã�´�. (pNode)
	while (cNode != NULL)  
	{
		if (data == GetData(cNode))
			return;  // ��������(Ű��) �ߺ��� ������� ����

		pNode = cNode;

		if (GetData(cNode) > data)
			cNode = GetLeftSubTree(cNode);  // ���� ��带 ���� �ڽ� ���� �̵�
		else
			cNode = GetRightSubTree(cNode);
	}

	// ����� ������
	// pNode�� �ڽ� ���� �߰��� �� ����� ����
	nNode = MakeBTreeNode(); // �� ����� ����
	SetData(nNode, data);  // �� ��忡 ������ ����

	// pNode �� �ڽ� ���� �� ��带 �߰�
	if (pNode != NULL)  // �� ��尡 ��Ʈ ��尡 �ƴ϶��( �� ��尡 �ֻ�� ��Ʈ ��尡 �ƴ϶��)
	{
		if (data < GetData(pNode))
			MakeLeftSubTree(pNode, nNode);
		else
			MakeRightSubTree(pNode, nNode);
	}
	else  // �� ��尡 �ֻ�� ��Ʈ �����
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
	// ���� ����� ��Ʈ ����� ��츦 ������ ����ؾ��Ѵ�.
	BTreeNode* pVRoot = MakeBTreeNode();  // ���� ��Ʈ ���
	BTreeNode* pNode = pVRoot;  // parent node
	BTreeNode* cNode = *pRoot;  // current node
	BTreeNode* dNode;  // delete node

	// ��Ʈ ��带 pVRoot�� ����Ű�� ����� ������ �ڽ� ��尡 �ǰ� �Ѵ�.
	ChangeRightSubTree(pVRoot, *pRoot);  // ���� ����� ��Ʈ ����� ��츦 ����Ͽ� ��Ʈ����� �θ� ��带 ������ ��Ʈ ���� ����

	// ���� ����� ��带 Ž��
	// ���� ��尡 �ܸ���尡 �ƴϰ�, ���� ����� �ƴҰ�� �ݺ�
	while (cNode != NULL && GetData(cNode) != target)
	{
		// ��带 �Ʒ��� �������鼭 ����� ã�� ����
		pNode = cNode;

		if (target < GetData(cNode))  // target�� ���� ������ ���� �Ʒ��� �̵�
			cNode = GetLeftSubTree(cNode);
		else  // target ���� �� ũ�� ������ �Ʒ��� �̵�
			cNode = GetRightSubTree(cNode);
	}

	if (cNode == NULL)  // while �� Ż�� ������ cNode == NULL �̶�� ���� ����� �������� ����
		return NULL;

	dNode = cNode;  // while �� Ż�� ������ target == cNode �� ���

	// ù ��° ��� : ���� ����� �ܸ� ����� ���
	if (GetLeftSubTree(dNode) == NULL && GetRightSubTree(dNode) == NULL)
	{
		if (GetLeftSubTree(pNode) == dNode)  // ���� ����� ���� �ܸ��̶��
			RemoveLeftSubTree(pNode);
		else  // ���� ����� ������ �ܸ��̶��
			RemoveRightSubTree(pNode);
	}

	// �� ��° ��� : ���� ����� �ϳ��� �ڽ� ��带 ���� ���
	else if (GetLeftSubTree(dNode) == NULL || GetRightSubTree(dNode) == NULL)
	{
		BTreeNode* dcNode;

		if (GetLeftSubTree(dNode) != NULL)
			dcNode = GetLeftSubTree(dNode);  // ���� �ڽ��� �ִ� ���
		else  
			dcNode = GetRightSubTree(dNode);  // ������ �ڽ��� �ִ� ���

		if (GetLeftSubTree(pNode) == dNode)  // ���� ��� ����� �ڸ��� �� �ڽ� ��尡 �����
			ChangeLeftSubTree(pNode, dcNode);
		else
			ChangeRightSubTree(pNode, dcNode);
	}

	// �� ��° ��� : �� ���� �ڽ� ��带 ��� ���� ���
	else
	{
		BTreeNode* mNode = GetRightSubTree(dNode);  // mNode �� ��ü��带 ����Ŵ
		BTreeNode* mpNode = dNode;  // mpNode �� ��ü����� �θ��带 ����Ŵ
		int delData;

		// ���� ����� ��ü ��带 ã�´�.
		while (GetLeftSubTree(mNode) != NULL)
		{
			// dNode�� ������ ����Ʈ���� �� ���� ��带 ã�� ����
			mpNode = mNode;
			mNode = GetLeftSubTree(mNode);
		}

		// ��ü ��忡 ����� ���� ������ ��忡 �����Ѵ�.
		delData = GetData(dNode);  // ���� �� ������ ���
		SetData(dNode, GetData(mNode));  // ����

		// ��ü ����� �θ� ���� �ڽ� ��带 �����Ѵ�.
		if (GetLeftSubTree(mpNode) == mNode)
			ChangeLeftSubTree(mpNode, GetRightSubTree(mNode));
		else
			ChangeRightSubTree(mpNode, GetRightSubTree(mNode));

		dNode = mNode;  // mNode�� �θ�� mNode�� �ڽĳ�尡 ����� �� mNode�� ���Ἲ�� ����� ���
		// cNode�� ����Ű�� dNode�� ���Ἲ ���� mNode�� ����Ű�� �Ѵ�.
		SetData(dNode, delData);  // ���Ἲ ���� mNode ��, dNode�� ��� ������ ����
	}

	// ������ ��尡 ��Ʈ ����� ��쿡 ���� �߰����� ó��
	// ������ ��尡 ��Ʈ ����� ��� pRoot�� ���̻� ��Ʈ��带 ����Ű�� ����
	// ���� pRoot ������ ���Ӱ� �����ؾ� ��. �̸� ���� pVRoot ������ ���Ǿ���
	if (GetRightSubTree(pVRoot) != *pRoot)
		*pRoot = GetRightSubTree(pVRoot);

	free(pVRoot);  // pVRoot�� ���� ��Ʈ �����̹Ƿ� ������ ���ϰ� �޸� ����
	return dNode;  // ���� ����� ��ȯ
}

void ShowIntData(int data)
{
	printf("%d ", data);
}

void BSTShowAll(BTreeNode* bst)
{
	InorderTraverse(bst, ShowIntData);  // ���� ��ȸ
}