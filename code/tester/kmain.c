/*
 * Copyright (c) 2020 You (you@youremail.com)
 */

#include <stdio.h>

void kmain() {

  printf("Starting up...");
  volatile int *address = (int *)0xF83F01;
  while ( 1 ) {
    *address = 0x2A;
  }

  // while ( 1 ) {
  //   for ( unsigned char i = 0; i < 255; i ++ ) {
  //     *address = i;
  //   }
  // }
}

