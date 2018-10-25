/*
 * Copyright (c) 2002-2018 "Neo4j,"
 * Neo4j Sweden AB [http://neo4j.com]
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
#ifndef SEABOLT_STATUS_H
#define SEABOLT_STATUS_H

#include "bolt-public.h"

typedef int BoltConnectionState;
// not connected
#define BOLT_CONNECTION_STATE_DISCONNECTED    0
// connected but not authenticated
#define BOLT_CONNECTION_STATE_CONNECTED       1
// connected and authenticated
#define BOLT_CONNECTION_STATE_READY           2
// recoverable failure
#define BOLT_CONNECTION_STATE_FAILED          3
// unrecoverable failure
#define BOLT_CONNECTION_STATE_DEFUNCT         4

/**
 * Status information about connection including details about errors
 */
typedef struct BoltStatus BoltStatus;

SEABOLT_EXPORT BoltConnectionState BoltStatus_get_state(BoltStatus* status);

SEABOLT_EXPORT int BoltStatus_get_error(BoltStatus* status);

SEABOLT_EXPORT const char* BoltStatus_get_error_context(BoltStatus* status);

#endif //SEABOLT_STATUS_H
