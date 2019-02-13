#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PTR_SIZE sizeof(void*)

enum indexes { NEXT, CURR };

void PrintList(char** list)
{
	printf("----------------\n");
	unsigned int* node = (unsigned int*)(*list);

	while (node != NULL)
	{
		char* str = (char*)(node[CURR]);
		printf("%s\n", str);
		printf("----------------\n");
		node = (unsigned int*)node[NEXT];
	}
	printf("\n");
}


void StringListInit(char** list)
{
	*list = NULL;
}


void StringListAdd(char** list, const char* str)
{
	if (*list != NULL)
	{
		unsigned int* node = (unsigned int*)*list;

		while (node[NEXT] != NULL)
		{
			node = (unsigned int*)node[NEXT];
		}
		unsigned int* newNode = (unsigned int*)malloc(PTR_SIZE * 2);
		newNode[CURR] = (unsigned int)malloc(strlen(str) + 1);
		strcpy((char*)newNode[CURR], str);
		newNode[NEXT] = NULL;

		node[NEXT] = (unsigned int)newNode;
	}
	else
	{
		unsigned int* newNode = (unsigned int*)malloc(PTR_SIZE * 2);
		newNode[CURR] = (unsigned int)malloc(strlen(str) + 1);
		strcpy((char*)newNode[CURR], str);
		newNode[NEXT] = NULL;

		*list = (char*)newNode;
	}
}


void StringListRemove(char** list, const char* str)
{
	unsigned int* node = (unsigned int*)*list;
	unsigned int* prev_node = NULL;

	while (node != NULL)
	{
		if (!strcmp((char*)node[CURR], str))
		{
			free((void*)node[CURR]);

			if (prev_node)
				prev_node[NEXT] = node[NEXT];
			else
				*list = (char*)node[NEXT];

			void* node_to_free = (void*)node;
			node = (unsigned int*)node[NEXT];
			free(node_to_free);
		}
		else
		{
			prev_node = node;
			node = (unsigned int*)node[NEXT];
		}
	}
}


unsigned int StringListSize(char** list)
{
	unsigned int* node = (unsigned int*)(*list);
	unsigned int amount = 0;

	while (node != NULL)
	{
		amount++;
		node = (unsigned int*)node[NEXT];
	}
	return amount;
}


unsigned int StringListIndexOf(char** list, const char* str)
{
	unsigned int* node = (unsigned int*)*list;
	unsigned int amount = 0;

	while (node != NULL)
	{
		if (!strcmp((char*)node[CURR], str))
			break;
		else
			amount++;

		node = (unsigned int*)node[NEXT];
	}
	return (amount == StringListSize(list)) ? -1 : amount;
}


void StringListSort(char** list)
{
	unsigned int tmp = 0;
	for (unsigned int* node = (unsigned int*)*list; node[NEXT] != NULL; node = (unsigned int*)node[NEXT])
	{
		unsigned int* node_min_element = node;
		for (unsigned int* iter_node = (unsigned int*)node[NEXT]; iter_node != NULL; iter_node = (unsigned int*)iter_node[NEXT])
		{
			if (strcmp((char*)iter_node[CURR], (char*)node_min_element[CURR]) < 0)
				node_min_element = iter_node;
		}
		tmp = node[CURR];
		node[CURR] = node_min_element[CURR];
		node_min_element[CURR] = tmp;
	}
}


void StringListReplaceInStrings(char** list, const char* before, const char* after)
{
	for (unsigned int* node = (unsigned int*)*list; node != NULL; node = (unsigned int*)node[NEXT])
	{
		if (!strcmp((char*)node[CURR], before))
		{
			node[CURR] = (unsigned int)realloc((void*)node[CURR], strlen(after) + 1);
			strcpy((char*)node[CURR], after);
		}
	}
}

void StringListDestroy(char** list)
{
	for (unsigned int* node = (unsigned int*)*list; node != NULL; node = (unsigned int*)*list)
	{
		*list = (char*)node[NEXT];

		free((void*)node[CURR]);
		free((void*)node);
	}

}


int main()
{
	char* myList;
	StringListInit(&myList);

	StringListAdd(&myList, "Yulia");
	StringListAdd(&myList, "Ivanechko");
	StringListAdd(&myList, "studies");
	StringListAdd(&myList, "C++");
	PrintList(&myList);
	StringListSort(&myList);
	PrintList(&myList);
	StringListReplaceInStrings(&myList, "C++", "coding");
	PrintList(&myList);
	StringListSize(&myList);
	StringListIndexOf(&myList, "coding");


	StringListDestroy(&myList);
	if (myList)
	{
		PrintList(&myList);
	}

	system("pause");

	return 0;
}


