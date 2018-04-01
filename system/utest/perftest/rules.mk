# Copyright 2018 The Fuchsia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

MODULE_TYPE := usertest

MODULE_SRCS += \
    $(LOCAL_DIR)/clock-test.cpp \
    $(LOCAL_DIR)/null-test.cpp \
    $(LOCAL_DIR)/results-test.cpp \
    $(LOCAL_DIR)/runner-test.cpp \
    $(LOCAL_DIR)/sleep-test.cpp \
    $(LOCAL_DIR)/syscalls-test.cpp \

MODULE_NAME := perf-test

MODULE_STATIC_LIBS := \
    system/ulib/fbl \
    system/ulib/perftest \
    system/ulib/zxcpp \

MODULE_LIBS := \
    system/ulib/c \
    system/ulib/fdio \
    system/ulib/unittest \
    system/ulib/zircon \

include make/module.mk
