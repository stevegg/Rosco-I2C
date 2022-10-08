/*
 * Copyright (c) 2020 You (you@youremail.com)
 */

#include <stdio.h>

void kmain() {

  printf("Starting up...");
  volatile char *address = (char *)0xF83F01;
  unsigned long count = 0l;
  char buffer[40];
  unsigned char value = 0;
  while ( 1 ) {
    sprintf(buffer, "Sending %lu with value %d", count ++, value );
    printf(buffer);
    *address = value ++;

    printf("complete\r\n");
  }
}

