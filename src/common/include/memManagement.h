/*==================================================================================*\
|                                                                                    |
|                    EXIP - Efficient XML Interchange Processor                      |
|                                                                                    |
|------------------------------------------------------------------------------------|
| Copyright (c) 2010, EISLAB - Luleå University of Technology                        |
| All rights reserved.                                                               |
|                                                                                    |
| Redistribution and use in source and binary forms, with or without                 |
| modification, are permitted provided that the following conditions are met:        |
|     * Redistributions of source code must retain the above copyright               |
|       notice, this list of conditions and the following disclaimer.                |
|     * Redistributions in binary form must reproduce the above copyright            |
|       notice, this list of conditions and the following disclaimer in the          |
|       documentation and/or other materials provided with the distribution.         |
|     * Neither the name of the EISLAB - Luleå University of Technology nor the      |
|       names of its contributors may be used to endorse or promote products         |
|       derived from this software without specific prior written permission.        |
|                                                                                    |
| THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND    |
| ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED      |
| WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE             |
| DISCLAIMED. IN NO EVENT SHALL EISLAB - LULEÅ UNIVERSITY OF TECHNOLOGY BE LIABLE    |
| FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES |
| (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;       |
| LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND        |
| ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT         |
| (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS      |
| SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                       |
|                                                                                    |
|                                                                                    |
|                                                                                    |
\===================================================================================*/

/**
 * @file memManagement.h
 * @brief Handles memory operations - allocation, deallocation etc.
 *
 * @date Oct 25, 2010
 * @author Rumen Kyusakov
 * @version 0.1
 * @par[Revision] $Id$
 */

#ifndef MEMMANAGEMENT_H_
#define MEMMANAGEMENT_H_

#include "errorHandle.h"
#include "procTypes.h"

/**
 * Except Data Values (Binary data, DateTime etc.), which are
 * freed after the respective ContentHandler is called, all other
 * allocations are freed at the end of the parsing/serializing.
 */

/**
 * @brief Allocate a memory block with size <size> and store a copy of
 * the pointer in a linked list for freeing it at the end.
 *
 * @param[in, out] strm EXI stream for which the allocation is made
 * @param[in] size the size of the memory block to be allocated
 * @return pointer to the allocated block if successful. NULL otherwise
 */
void* memManagedAllocate(EXIStream* strm, size_t size);

/**
 * @brief Allocate a memory block with size <size> and store a copy of
 * the pointer in a linked list for freeing it at the end.
 * It also return the pointer to the linked list node used later
 * during reallocation. Use this function in case the allocated block
 * might need to be reallocated later.
 *
 * @param[in, out] strm EXI stream for which the allocation is made
 * @param[in] size the size of the memory block to be allocated
 * @param[out] memNode pointer to the memAlloc node created
 * @return pointer to the allocated block if successful. NULL otherwise
 */
void* memManagedAllocatePtr(EXIStream* strm, size_t size, void** p_memNode);

/**
 * @brief Reallocate a memory block with size <size>
 *
 * @param[in, out] ptr pointer to be reallocated
 * @param[in] size the size of the memory block to be reallocated
 * @param[in] p_memNode pointer to the memAlloc node created when the ptr was allocated
 * @return pointer to the allocated block if successful. NULL otherwise
 */
errorCode memManagedReAllocate(void** ptr, size_t size, void* p_memNode);

/**
 * @brief Frees all the managed memory for a particular EXI stream.
 * It should be called after an error in the processing occur or at the
 * end of the parsing/serializing if the processing is successful.
 *
 * @param[in, out] strm EXI stream for which the allocations were made
 * @return Error handling code
 */
errorCode freeAllMem(EXIStream* strm);

#endif /* MEMMANAGEMENT_H_ */