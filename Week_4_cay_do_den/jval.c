#include <stdio.h>
#include <string.h>
#include "jval.h"

Jval JNULL;

// ham khoi tao gia tri kieu int sang kieu jval
Jval new_jval_i(int i) {
  Jval j;
  j.i = i;
  return j;
}

// ham khoi tao gia tri kieu long sang kieu jval
Jval new_jval_l(long l) {
  Jval j;
  j.l = l;
  return j;
}

// ham khoi tao gia tri kieu float sang kieu jval
Jval new_jval_f(float f) {
  Jval j;
  j.f = f;
  return j;
}

// ham khoi tao gia tri double sang kieu jval
Jval new_jval_d(double d) {
  Jval j;
  j.d = d;
  return j;
}

// ham khoi tao gia tri kieu void(tong quat) sang kieu jval
Jval new_jval_v(void *v) {
  Jval j;
  j.v = v;
  return j;
}

// ham khoi gia tri kieu chuoi sang kieu jval
Jval new_jval_s(char *s) {
  Jval j;
  j.s = s;
  return j;
}

// ham khoi tao gia tri kieu ki tu char sang kieu jval
Jval new_jval_c(char c) {
  Jval j;
  j.c = c;
  return j;
}

// ham khoi tao gia tri kieu unsigned char sang kieu jval
Jval new_jval_uc(unsigned char uc) {
  Jval j;
  j.uc = uc;
  return j;
}

// ham khoi tao gia tri kieu short sang kieu jval
Jval new_jval_sh(short sh) {
  Jval j;
  j.sh = sh;
  return j;
}

// ham khoi tao gia tri kieu unsigned short sang kieu jval
Jval new_jval_ush(unsigned short ush) {
  Jval j;
  j.ush = ush;
  return j;
}

// ham khoi tao gia tri kieu unsigned int sang kieu jval
Jval new_jval_ui(unsigned int i) {
  Jval j;
  j.i = i;
  return j;
}


Jval new_jval_iarray(int i0, int i1) {
  Jval j;
  j.iarray[0] = i0;
  j.iarray[1] = i1;
  return j;
}
  
Jval new_jval_farray(float f0, float f1) {
  Jval j;
  j.farray[0] = f0;
  j.farray[1] = f1;
  return j;
}
  
Jval new_jval_carray_nt(char *carray) {
  Jval j;
  int i;

  for (i = 0; i < 8 && carray[i] != '\0'; i++) {
    j.carray[i] = carray[i];
  }
  if (i < 8) j.carray[i] = carray[i];
  return j;
}
  
Jval new_jval_carray_nnt(char *carray) {
  Jval j;

  memcpy(j.carray, carray, 8);
  return j;
}

int jval_i(Jval j) {
  return j.i;
}

long jval_l(Jval j) {
  return j.l;
}

float jval_f(Jval j) {
  return j.f;
}

double jval_d(Jval j) {
  return j.d;
}

void *jval_v(Jval j) {
  return j.v;
}

char *jval_s(Jval j) {
  return j.s;
}

char jval_c(Jval j) {
  return j.c;
}

unsigned char jval_uc(Jval j) {
  return j.uc;
}

short jval_sh(Jval j) {
  return j.sh;
}

unsigned short jval_ush(Jval j) {
  return j.ush;
}

unsigned int jval_ui(Jval j) {
  return j.ui;
}

int *jval_iarray(Jval j) {
  return j.iarray;
}

float *jval_farray(Jval j) {
  return j.farray;
}

char *jval_carray(Jval j) {
  return j.carray;
}
