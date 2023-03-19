#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"
#include <string.h>


typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;

}AdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC  printFunc){
    PAdptArray new_arr = (PAdptArray)malloc(sizeof(AdptArray));
	if (new_arr == NULL)
		return NULL;
	new_arr->ArrSize = 0;
	new_arr->pElemArr = NULL;
	new_arr->delFunc = delFunc;
	new_arr->copyFunc = copyFunc;
    new_arr->printFunc = printFunc;
	return new_arr;
}

void DeleteAdptArray(PAdptArray del_Arr){
    
	if (del_Arr == NULL)
		return;
    int size = del_Arr->ArrSize;
	for(int i = 0; i < size; ++i){
        if((del_Arr->pElemArr[i]) != NULL){

		del_Arr->delFunc((del_Arr->pElemArr)[i]);
        }
	}
	free(del_Arr->pElemArr);
	free(del_Arr);
    
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem){

    PElement* newpElemArr;
	if (pArr == NULL)
		return FAIL;

	if (idx >= pArr->ArrSize){
		
// Extend Array
		if ((newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
			return FAIL;
        //copy the old arr to new arr with size idx+1 
        for(int i = 0; i < pArr-> ArrSize ; i++){
            if((pArr->pElemArr[i]) != NULL){
                newpElemArr[i] = (pArr->pElemArr[i]);
            }
        }
    
		//memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
        // free the old arr
		free(pArr->pElemArr);
        // apdate the pointer
		pArr->pElemArr = newpElemArr;
	}

	// Delete Previous Elem
    if(((pArr->pElemArr)[idx]) != NULL){

	pArr->delFunc((pArr->pElemArr)[idx]);
    }
	(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);

	// Update Array Size
	pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
    
	return SUCCESS;

}

PElement GetAdptArrayAt(PAdptArray pArr, int index){
  
    if(pArr == NULL){
        return NULL;
    }
    int size = pArr->ArrSize;
    
    if(index > size){
        if(index < 0){
        return FAIL;
        }
    }

    if(pArr->pElemArr[index] != NULL){

        return pArr-> copyFunc((pArr->pElemArr)[index]);
    }
    return NULL;
    

}

int GetAdptArraySize(PAdptArray pArr){
    if(pArr == NULL){
        return -1;
    }else{
        return pArr->ArrSize;
    }

}

void PrintDB(PAdptArray pArr){
    if(pArr == NULL){
        return;
    }
    int size = pArr->ArrSize;
    for(int i=0; i<size; i++){
        if(pArr->pElemArr[i] != NULL)
        pArr->printFunc(pArr->pElemArr[i]);
    } 
}


