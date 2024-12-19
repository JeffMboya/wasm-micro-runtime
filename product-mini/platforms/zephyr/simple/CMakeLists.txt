# Copyright (C) 2019 Intel Corporation.  All rights reserved.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

cmake_minimum_required(VERSION 3.8.2)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(wamr)

enable_language (ASM)

set (WAMR_BUILD_PLATFORM "zephyr")

# Default Build Target
if (NOT DEFINED WAMR_BUILD_TARGET)
  set (WAMR_BUILD_TARGET "X86_32")
endif ()

# Configure for ESP32-S3
if (BOARD STREQUAL "esp32s3_devkitc" OR BOARD STREQUAL "esp32s3_devkitc_1")
  set (WAMR_BUILD_TARGET "XTENSA")
  set (WAMR_BUILD_AOT 0)
  set (WAMR_BUILD_INTERP 1)
  set (WAMR_BUILD_GLOBAL_HEAP_SIZE 65536)
endif ()

if (NOT DEFINED WAMR_BUILD_INTERP)
  set (WAMR_BUILD_INTERP 1) 
endif ()

if (NOT DEFINED WAMR_BUILD_AOT)
  set (WAMR_BUILD_AOT 1)
endif ()

if (NOT DEFINED WAMR_BUILD_LIBC_BUILTIN)
  set (WAMR_BUILD_LIBC_BUILTIN 1)
endif ()

if (NOT DEFINED WAMR_BUILD_LIBC_WASI)
  set (WAMR_BUILD_LIBC_WASI 0)
endif ()

if (NOT DEFINED WAMR_BUILD_GLOBAL_HEAP_POOL)
  set (WAMR_BUILD_GLOBAL_HEAP_POOL 1)
endif ()

if (NOT DEFINED WAMR_BUILD_GLOBAL_HEAP_SIZE)
  set (WAMR_BUILD_GLOBAL_HEAP_SIZE 131072)
endif ()

set (WAMR_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../..)

include (${WAMR_ROOT_DIR}/build-scripts/runtime_lib.cmake)

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/boards/${BOARD})
  zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/boards/${BOARD})
endif ()

# Conditionally add architecture-specific files
if (WAMR_BUILD_TARGET STREQUAL "X86_32")
  target_sources(app PRIVATE
                 ${WAMR_ROOT_DIR}/core/iwasm/common/arch/invokeNative_ia32.s)
endif ()

# Add the main source files
target_sources(app PRIVATE
               ${WAMR_RUNTIME_LIB_SOURCE}
               src/main.c)
