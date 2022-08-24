#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "BinaryTree.h"
#include "ListBaseStack.h"

BTreeNode* MakeExpTree(char exp[])  // ����Ʈ�� ���� �Լ�
{
	Stack stack;
	BTreeNode* pnode;

	int explen = strlen(exp);
	int i;

	StackInit(&stack);

	for (i = 0; i < explen; i++)
	{
		pnode = MakeBTreeNode();

		if (isdigit(exp[i]))  // ���ڶ��
		{
			SetData(pnode, exp[i] - '0');
		}
		else  // �����ڶ��
		{
			MakeRightSubTree(pnode, SPop(&stack));  // ���ÿ��� ������ ���� ������ ����Ʈ���� ����
			MakeLeftSubTree(pnode, SPop(&stack));
			SetData(pnode, exp[i]);  // �����ڸ� pnode�� ����
		}

		SPush(&stack, pnode);  // ������ ����Ʈ���� �ٽ� ���ÿ� �ְ�
	}
	return SPop(&stack);  // ����Ʈ�� �ϼ� ����� ���ÿ� ������ ��ȯ
}

int EvaluateExpTree(BTreeNode* bt)  // ����Ʈ�� ����� �Լ�
{
	int op1, op2;

	if (GetLeftSubTree(bt) == NULL && GetRightSubTree(bt) == NULL)  // ��� �Լ� Ż�� ����, ���ܳ���� 
		return GetData(bt);  // ���ܳ�带 ��ȯ
	op1 = EvaluateExpTree(GetLeftSubTree(bt));  // ���� ��带 ����
	op2 = EvaluateExpTree(GetRightSubTree(bt)); // ������ ��带 ����

	switch (GetData(bt))
	{
	case '+':
		return op1 + op2;
	case '-':
		return op1 - op2;
	case '*':
		return op1 * op2;
	case '/':
		return op1 / op2;
	}

	return 0;
}

void ShowNodeData(int data)
{
	if (0 <= data && data <= 9)
		printf("%d ", data);
	else
		printf("%c ", data);
}

void ShowPrefixTypeExp(BTreeNode* bt)  // ���� ǥ����� ���� ���
{
	PreorderTraverse(bt, ShowNodeData);
}

void ShowInfixTypeExp(BTreeNode* bt)  // ���� ǥ����� ���� ���
{
	if (bt == NULL)
		return;
	if (bt->left != NULL || bt->right != NULL)  // ��ȣ�� ������ ���� ǥ����� ���� ���
		printf(" ( ");  // ������ ��忡�� �Ʒ��ڵ� ���డ��
	ShowInfixTypeExp(bt->left);
	ShowNodeData(bt->data);
	ShowInfixTypeExp(bt->right);
	
	if (bt->left != NULL || bt->right != NULL)
		printf(" ) ");
}

void ShowPostfixTypeExp(BTreeNode* bt)  // ���� ǥ����� ���� ���
{
	PostorderTraverse(bt, ShowNodeData);
}