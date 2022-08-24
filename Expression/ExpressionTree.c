#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "BinaryTree.h"
#include "ListBaseStack.h"

BTreeNode* MakeExpTree(char exp[])  // 수식트리 생성 함수
{
	Stack stack;
	BTreeNode* pnode;

	int explen = strlen(exp);
	int i;

	StackInit(&stack);

	for (i = 0; i < explen; i++)
	{
		pnode = MakeBTreeNode();

		if (isdigit(exp[i]))  // 숫자라면
		{
			SetData(pnode, exp[i] - '0');
		}
		else  // 연산자라면
		{
			MakeRightSubTree(pnode, SPop(&stack));  // 스택에서 꺼내어 왼쪽 오른쪽 서브트리에 연결
			MakeLeftSubTree(pnode, SPop(&stack));
			SetData(pnode, exp[i]);  // 연산자를 pnode에 저장
		}

		SPush(&stack, pnode);  // 연산자 서브트리를 다시 스택에 넣고
	}
	return SPop(&stack);  // 수식트리 완성 결과를 스택에 빼내어 반환
}

int EvaluateExpTree(BTreeNode* bt)  // 수식트리 계산결과 함수
{
	int op1, op2;

	if (GetLeftSubTree(bt) == NULL && GetRightSubTree(bt) == NULL)  // 재귀 함수 탈출 조건, 말단노드라면 
		return GetData(bt);  // 말단노드를 반환
	op1 = EvaluateExpTree(GetLeftSubTree(bt));  // 왼쪽 노드를 저장
	op2 = EvaluateExpTree(GetRightSubTree(bt)); // 오른쪽 노드를 저장

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

void ShowPrefixTypeExp(BTreeNode* bt)  // 전위 표기법의 수식 출력
{
	PreorderTraverse(bt, ShowNodeData);
}

void ShowInfixTypeExp(BTreeNode* bt)  // 중위 표기법의 수식 출력
{
	if (bt == NULL)
		return;
	if (bt->left != NULL || bt->right != NULL)  // 괄호를 포함한 중위 표기법의 수식 출력
		printf(" ( ");  // 연산자 노드에서 아래코드 수행가능
	ShowInfixTypeExp(bt->left);
	ShowNodeData(bt->data);
	ShowInfixTypeExp(bt->right);
	
	if (bt->left != NULL || bt->right != NULL)
		printf(" ) ");
}

void ShowPostfixTypeExp(BTreeNode* bt)  // 후위 표기법의 수식 출력
{
	PostorderTraverse(bt, ShowNodeData);
}