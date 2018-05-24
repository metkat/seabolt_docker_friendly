/*
 * Copyright (c) 2002-2018 "Neo Technology,"
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

#include <stdint.h>
#include <string.h>
#include <bolt/values.h>
#include <assert.h>
#include <inttypes.h>


void BoltValue_format_as_Integer(struct BoltValue * value, int64_t data)
{
    _format(value, BOLT_INTEGER, 0, 1, NULL, 0);
    value->data.as_int64[0] = data;
}

int64_t BoltInteger_get(const struct BoltValue * value)
{
    return value->data.as_int64[0];
}

int BoltInteger_write(struct BoltValue * value, FILE * file)
{
    assert(BoltValue_type(value) == BOLT_INTEGER);
    fprintf(file, "%" PRIi64 "L", BoltInteger_get(value));
    return 0;
}