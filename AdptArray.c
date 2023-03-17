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
	{
		return NULL;
	}
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delete_func;
	pArr->copyFunc = copy_func;
    pArr->printFunc = print_func;
	return pArr;
}


Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
	
	if (pArr == NULL)
		return FAIL;

	if (idx >= pArr->ArrSize)
	{	
		// Initial new elem Array
		PElement *newpElemArr;

		// Extend Array
		if ((newpElemArr = (PElement *)calloc((idx + 1), sizeof(PElement))) == NULL)
		{
			return FAIL;
		}
			

		// Copy old array to new one	
		for (int i = 0; i < pArr->ArrSize; i++)
		{
			if((pArr->pElemArr)[i] != NULL)
			{
				newpElemArr[i] = pArr->copyFunc((pArr->pElemArr)[i]);
				pArr->delFunc((pArr->pElemArr)[i]);
			}
				
		}
	
		// Free the old array
		free(pArr->pElemArr);

		// Set the new array to be current
		pArr->pElemArr = newpElemArr;

		// Insert the new elem
		(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);

		// Update Array Size
		pArr->ArrSize = (idx + 1);
		
	}else
	{
		// Delete Previous Elem if exist
		if(pArr->pElemArr[idx])
			pArr->delFunc((pArr->pElemArr)[idx]);

		// Insert the new elem
		(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);
	}

	return SUCCESS;
}


		

void DeleteAdptArray(PAdptArray pArr)
{
	if (pArr == NULL)
		return;
	for(int i = 0; i < pArr->ArrSize; ++i)
	{
		if(pArr->pElemArr[i])
		{
			pArr->delFunc((pArr->pElemArr)[i]);
		}
	}
	free(pArr->pElemArr);
	free(pArr);
}


PElement GetAdptArrayAt(PAdptArray pArr, int idx)
{  
    if(idx < pArr->ArrSize)
	{
		if(pArr->pElemArr[idx])
		{
			return pArr->copyFunc(pArr->pElemArr[idx]);
		}
		return NULL;
	}
    return NULL;
}


int GetAdptArraySize(PAdptArray pArr)
{
    if (pArr == NULL)
	{
		return -1;
	}
    return pArr->ArrSize;
}


void PrintDB(PAdptArray pArr)
{
    if (pArr == NULL)
	{
		return;
	}
	
    for (int i = 0; i < pArr->ArrSize; ++i)
    {
		if(pArr->pElemArr[i])
		{
			pArr->printFunc((pArr->pElemArr)[i]);
		} 
    }
}
