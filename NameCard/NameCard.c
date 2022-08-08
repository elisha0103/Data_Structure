#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NameCard.h"
#pragma warning(disable: 4996)


NameCard* MakeNameCard(const char* name, const char* phone)
{
	NameCard* newCard = (NameCard*)malloc(sizeof(NameCard));
	strcpy(newCard->name, name);
	strcpy(newCard->phone, phone);

	return newCard;
}

void ShowNameCardInfo(NameCard* pcard)
{
	printf("[이름] : %s\n", pcard->name);
	printf("[번호] : %s\n", pcard->phone);
	return;
}

int NameCompare(NameCard* pcard, const char* name)
{
	return strcmp(pcard->name, name);
}

void ChangePhoneNum(NameCard* pcard, const char* phone)
{
	strcpy(pcard->phone, phone);
}