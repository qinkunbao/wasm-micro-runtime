/*
 * Copyright (C) 2021 Ant Group.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#ifndef _GDB_SERVER_H
#define _GDB_SERVER_H

#include <stdbool.h>

#define PACKET_BUF_SIZE 0x8000

enum GDBStoppointType {
    eStoppointInvalid = -1,
    eBreakpointSoftware = 0,
    eBreakpointHardware,
    eWatchpointWrite,
    eWatchpointRead,
    eWatchpointReadWrite
};
typedef struct WasmDebugPacket {
    unsigned char buf[PACKET_BUF_SIZE];
    unsigned int size;
} WasmDebugPacket;

struct WASMDebugControlThread;
typedef struct WASMGDBServer {
    int listen_fd;
    int socket_fd;
    WasmDebugPacket pkt;
    bool noack;
    struct WASMDebugControlThread *thread;
} WASMGDBServer;

WASMGDBServer *
wasm_launch_gdbserver(char *addr, int port);

void
wasm_close_gdbserver(WASMGDBServer *server);

bool
wasm_gdbserver_handle_packet(WASMGDBServer *server);
#endif
