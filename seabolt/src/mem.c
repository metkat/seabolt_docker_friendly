/*
 * Copyright (c) 2002-2017 "Neo Technology,"
 * Network Engine for Objects in Lund AB [http://neotechnology.com]
 *
 * This file is part of Neo4j.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stddef.h>
#include <malloc.h>
#include <logging.h>

#include "mem.h"


static size_t __memory = 0;
static long long __activity = 0;


void* BoltMem_allocate(size_t new_size)
{
    void* p = malloc(new_size);
    __memory += new_size;
    log("[MEM] Allocated %ld bytes (balance: %lu)", new_size, __memory);
    __activity += 1;
    return p;
}

void* BoltMem_reallocate(void* ptr, size_t old_size, size_t new_size)
{
    void* p = realloc(ptr, new_size);
    __memory = __memory - old_size + new_size;
    log("[MEM] Reallocated %ld bytes as %ld bytes (balance: %lu)", old_size, new_size, __memory);
    __activity += 1;
    return p;
}

void* BoltMem_deallocate(void* ptr, size_t old_size)
{
    free(ptr);
    __memory -= old_size;
    log("[MEM] Freed %ld bytes (balance: %lu)", old_size, __memory);
    __activity += 1;
    return NULL;
}

void* BoltMem_adjust(void* ptr, size_t old_size, size_t new_size)
{
    if (new_size == old_size)
    {
        // In this case, the physical data storage requirement
        // hasn't changed, whether zero or some positive value.
        // This means that we can reuse the storage exactly
        // as-is and no allocation needs to occur. Therefore,
        // if we reuse a value for the same fixed-size type -
        // an int32 for example - then we can continue to reuse
        // the same storage for each value, avoiding memory
        // reallocation.
        return ptr;
    }
    if (old_size == 0)
    {
        // In this case we need to allocate new storage space
        // where previously none was allocated. This means
        // that a full allocation is required.
        return BoltMem_allocate(new_size);
    }
    if (new_size == 0)
    {
        // In this case, we are moving from previously having
        // data to no longer requiring any storage space. This
        // means that we can free up the previously-allocated
        // space.
        return BoltMem_deallocate(ptr, old_size);
    }
    // Finally, this case deals with previous allocation
    // and a new allocation requirement, but of different
    // sizes. Here, we `realloc`, which should be more
    // efficient than a naïve deallocation followed by a
    // brand new allocation.
    return BoltMem_reallocate(ptr, old_size, new_size);
}


long long BoltMem_activity()
{
    return __activity;
}