/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#include <stdio.h>

int main() {
    int a = 10;
    int b = 12;
    int sum = a + b;

    printf("The sum of %d and %d is: %d\n", a, b, sum);

    return sum;
}
