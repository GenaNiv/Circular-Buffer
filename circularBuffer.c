/*
 * main.c
 *
 *  Created on: May 11, 2017
 *      Author: gena
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false=0, true} bool;
typedef enum  {EMPTY = 0, OCCUPIED, FULL} bufferStatus;

//define circular buffer structure
typedef struct buffer
{

	int head;
	int tail;
	int bufferSize;
	int occupied;
	bufferStatus status;
	int sizeRemaining;
	char* str;
}buffer;

//define and initialize to NULL sircular buffer pointer
buffer* serialDataBuffer = NULL;


//-------Function declarations--------
buffer* initBuffer(buffer* pBuffer, int size);
buffer* createNewBuffer(buffer* pBuffer);
bool isBufferFull(buffer* pBuf);
bool isBufferEmpty(buffer* pBuf);
bool bufferWrite(buffer* pBuffer, int sizeBytes, char* dataToBeWrite);
bool bufferRead(buffer* pBuffer, int sizeBytes, char* dataToBeRead);


//----MAIN----
int main()
{
	int run = 1;
	bool ret;
	char data;
	char* pch;
	char ch = 't';
	char func;
	pch = &ch;

  //init buffer
	serialDataBuffer = initBuffer(serialDataBuffer, 4);

	while(run)
	{
		printf("\nChoose one of the following options:...\n1. Write data 'w'\n2. Read data 'r'\n3. Print data 'p'\n4. Delete data 'd'\n");
		printf("Insert function:...");
		scanf(" %c", &func);

		switch(func)
		{
			case 'w':
				printf("\nType data to be stored...");
				scanf("\n %c", &data);
				bufferWrite(serialDataBuffer, 1, &data);
				break;
			case 'r':
				bufferRead(serialDataBuffer, 1, &data);
                break;

		}

	}

	return 0;
}

//----------Funtion definitions------------

buffer* initBuffer(buffer* pBuffer, int size)
{
	buffer* buf = NULL;

	//create buffer
	buf = createNewBuffer(pBuffer);

   //initialize all members of struct buffer
	buf->head = 0;
	buf->tail = 0;
	buf->bufferSize = size;
	buf->occupied = 0;
	buf->sizeRemaining = size;
	buf->status = EMPTY;
	buf->str = (char*)malloc(sizeof(char)*size);
	if(!buf->str)
	{
		printf("\nError memory allocation...");
	}

	return buf;

}//end func.

buffer* createNewBuffer(buffer* pBuffer)
{
	//create new buffer
	pBuffer = (buffer*)malloc(sizeof(buffer));
	if(!pBuffer)
	{
		printf("\nError memory allocation...");
	}

	return pBuffer;
}//end function

//Function check if buffer is full
bool isBufferFull(buffer* pBuf)
{
	bool status = false;

	if(pBuf->sizeRemaining == 0 && pBuf->status == FULL)
	{
		status = true;
	}
	return status;
}//end func.

//Function check if buffer is empty
bool isBufferEmpty(buffer* pBuf)
{
	bool status = false;

	if(pBuf->sizeRemaining == pBuf->bufferSize  && pBuf->status == EMPTY)
	{
		status = true;
	}
	return status;
}//end func.

//
bool bufferWrite(buffer* pBuffer, int sizeBytes, char* dataToBeWrite)
{
	bool status = false;

	//check if buffer is full
	if(!isBufferFull(pBuffer))
	{
		//check if there buffer has enough space to accept new chars
		if(pBuffer->sizeRemaining >= sizeBytes)
		{
			//write to buffer
			pBuffer->str[pBuffer->head] = *dataToBeWrite;

			pBuffer->status = OCCUPIED;

			//increment head by one
			pBuffer->head = pBuffer->head + 1;

			//update size occupied in buffer
			pBuffer->head = (pBuffer->head)%(pBuffer->bufferSize);

			pBuffer->sizeRemaining--;

			if(pBuffer->sizeRemaining == 0)
			{
				pBuffer->status = FULL;
			}

			pBuffer->occupied++;

			status = true;
		}
		else
		{
			printf("\nNot enough space to write...\n");
			status = false;
		}

	 }
	 else
	 {
		printf("\nNot enough space to write...");
		status = false;
	 }


	return status;
}//end func.

bool bufferRead(buffer* pBuffer, int sizeBytes, char* dataToBeRead)
{
 bool ret = false;

	if(!isBufferEmpty(pBuffer))
	{
		*dataToBeRead = pBuffer->str[pBuffer->tail];

		printf("\ndata %c \n", *dataToBeRead);

		//increment tail by one
		pBuffer->tail = pBuffer->tail + 1;

        //update remaining size
		pBuffer->tail = (pBuffer->tail)%(pBuffer->bufferSize);

		pBuffer->occupied--;

		if(pBuffer->occupied == 0)
		{
			pBuffer->status = EMPTY;
		}

		pBuffer->sizeRemaining++;

	}
	else
	{
		printf("\nBuffer is empty...\n");

	}

	return ret;
}//end func.
