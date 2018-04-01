// Copyright 2018 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <zircon/listnode.h>

#include <lib/async/dispatcher.h>
#include <lib/async/task.h>
#include <lib/async/wait.h>

#include <zx/port.h>
#include <zx/time.h>

namespace async {

// A C++ implementation of async_t (to which this class can always be upcast),
// providing an ecapsulation of the dispatch methods at the core of |TestLoop|.
class TestLoopDispatcher : public async_t {
public:
    TestLoopDispatcher(zx::time* current_time);
    ~TestLoopDispatcher();

    // async_t operation implementations.
    zx::time Now() const { return *current_time_; };
    zx_status_t BeginWait(async_wait_t* wait);
    zx_status_t CancelWait(async_wait_t* wait);
    zx_status_t PostTask(async_task_t* task);
    zx_status_t CancelTask(async_task_t* task);

    // Dispatches the next queued wait. This is non-blocking.
    zx_status_t DispatchNextWait();

    // Dispatch all posted tasks with deadlines up to |time|.
    void DispatchTasks();

    // Dispatch all waits and task - with deadlines less than or equal to
    // |current_time| - with the |ASYNC_FLAG_HANDLE_SHUTDOWN| flag.
    void Shutdown();

private:
    zx::time* const current_time_;

    // Doubly-linked lists of posted waits and tasks.
    list_node_t task_list_;
    list_node_t wait_list_;

    // Port on which waits are signaled.
    zx::port port_;
};

} // namespace async
