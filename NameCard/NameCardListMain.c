    #include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"
#include "NameCard.h"
#pragma warning(disable: 4996)

int main()
{
	List list;
	NameCard* pcard;

	ListInit(&list);

	pcard = MakeNameCard("진태영", "010 1234 7894");
	LInsert(&list, pcard);

	pcard = MakeNameCard("진성용", "010 5468 5464");
	LInsert(&list, pcard);

	pcard = MakeNameCard("이정인", "010 2131 5487");
	LInsert(&list, pcard);

	pcard = MakeNameCard("김지영", "010 2454 8756");
	LInsert(&list, pcard);

	if (LFirst(&list, &pcard))
	{
		if (!NameCompare(pcard, "김지영"))
		{
			ShowNameCardInfo(pcard);

		}
		else
		{
			while (LNext(&list, &pcard))
			{
				if (!NameCompare(pcard, "김지영"))
				{
					ShowNameCardInfo(pcard);
					break;
				}
			}
		}
	}

	if (LFirst(&list, &pcard))
	{
		if (!NameCompare(pcard, "이정인"))
		{
			ChangePhoneNum(pcard, "010 1111 1111");

		}
		else
		{
			while (LNext(&list, &pcard))
			{
				if (!NameCompare(pcard, "이정인"))
				{
					ChangePhoneNum(pcard, "010 1111 1111");
					break;
				}
			}
		}
	}

	if (LFirst(&list, &pcard))
	{
		if (!NameCompare(pcard, "진성용"))
		{
			pcard = LRemove(&list);
			free(pcard);

		}
		else
		{
			while (LNext(&list, &pcard))
			{
				if (!NameCompare(pcard, "진성용"))
				{
					pcard = LRemove(&list);
					free(pcard);
					break;
				}
			}
		}
	}

	if (LFirst(&list, &pcard))
	{
		ShowNameCardInfo(pcard);

		while (LNext(&list, &pcard))
		{
			ShowNameCardInfo(pcard);
		}
	}

	return 0;
}
