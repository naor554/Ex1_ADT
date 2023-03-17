#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
    int ArrSize;
    PElement* pElemArr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC delete_func ,PRINT_FUNC print_func)
{
    PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delete_func;
	pArr->copyFunc = copy_func;
    pArr->printFunc = print_func;
	return pArr;
}


Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
	PElement* newpElemArr = NULL;
	if (pArr == NULL)
		return FAIL;

	if (idx >= pArr->ArrSize)
	{
		
// Extend Array
		if ((newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
			return FAIL;
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
		free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;
	}

	// Delete Previous Elem
	pArr->delFunc((pArr->pElemArr)[idx]);
	(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);

	// Update Array Size
	pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
	return SUCCESS;
}


void DeleteAdptArray(PAdptArray pArr)
{
	if (pArr == NULL)
		return;
	for(int i = 0; i < pArr->ArrSize; ++i)
	{
		pArr->delFunc((pArr->pElemArr)[i]);
	}
	free(pArr->pElemArr);
	free(pArr);
}


PElement GetAdptArrayAt(PAdptArray pArr, int idx)
{  
    if(idx < pArr->ArrSize)
        return pArr->copyFunc((pArr->pElemArr)[idx]);
    
    return NULL;
}


int GetAdptArraySize(PAdptArray pArr)
{
    if (pArr == NULL)
        return -1;

    return pArr->ArrSize;
}


void PrintDB(PAdptArray pArr)
{
    if (pArr == NULL)
	    return;
    for (int i = 0; i < pArr->ArrSize; ++i)
    {
	    pArr->printFunc((pArr->pElemArr)[i]);
    }
}
