#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

typedef int BTData;

// ����Ʈ���� ��带 ǥ���� ����ü
typedef struct _bTreeNode
{
	BTData data;
	struct _bTreeNode* left;
	struct _bTreeNode* right;
} BTreeNode;

BTreeNode* MakeBTreeNode(void);  // ����� ����
BTData GetData(BTreeNode* bt);  // ��忡 ����� �����͸� ��ȯ
void SetData(BTreeNode* bt, BTData data);  // ��忡 �����͸� ����

BTreeNode* GetLeftSubTree(BTreeNode* bt);  // ���� ���� Ʈ�� �ּ� �� ��ȯ
BTreeNode* GetRightSubTree(BTreeNode* bt);  // ������ ���� Ʈ�� �ּ� �� ��ȯ

void MakeLeftSubTree(BTreeNode* main, BTreeNode* sub);  // ���� Ʈ���� Ʈ���� ������ ���
void MakeRightSubTree(BTreeNode* main, BTreeNode* sub);  // ������ Ʈ���� Ʈ���� ������ ���

typedef void (*VisitFuncPtr)(BTData data);

void PreorderTraverse(BTreeNode* bt, VisitFuncPtr action);
void InorderTraverse(BTreeNode* bt, VisitFuncPtr action);
void PostorderTraverse(BTreeNode* bt, VisitFuncPtr action);

BTreeNode* RemoveLeftSubTree(BTreeNode* bt);  // ���� �ڽ� ��带 Ʈ������ ����, ���ŵ� ����� �ּ� ���� ��ȯ�ȴ�.
BTreeNode* RemoveRightSubTree(BTreeNode* bt);  // ������ �ڽ� ��带 Ʈ������ ����, ���ŵ� ����� �ּ� ���� ��ȯ�ȴ�.
void ChangeLeftSubTree(BTreeNode* main, BTreeNode* sub);  // �޸� �Ҹ��� �������� �ʰ� main�� ���� �ڽ� ��带 �����Ѵ�.(MakeLeftSubTree�� �޸� �Ҹ��� �ϰ� �ڽ� ��ü)
void ChangeRightSubTree(BTreeNode* main, BTreeNode* sub);  // �޸� �Ҹ��� �������� �ʰ� main�� ������ �ڽ� ��带 �����Ѵ�. (MakeRightSubTree�� �޸� �Ҹ��� �ϰ� �ڽ� ��ü)
#endif