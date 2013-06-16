//-----------------------------------------------------------------------------
// Copyright 2012 Masanori Morise. All Rights Reserved.
// Author: morise [at] fc.ritsumei.ac.jp (Masanori Morise)
//
// This file represents the functions about FFT (Fast Fourier Transform)
// implemented by Mr. Ooura, and wrapper functions implemented by M. Morise.
// We can use these wrapper functions as well as the FFTW functions.
// Please see the FFTW web-page to show the usage of the wrapper functions.
// Ooura FFT:
//   (Japanese) http://www.kurims.kyoto-u.ac.jp/~ooura/index-j.html
//   (English) http://www.kurims.kyoto-u.ac.jp/~ooura/index.html
// FFTW:
//   (English) http://www.fftw.org/
// 2012/08/24 by M. Morise
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <math.h>

#include "../fftsg/fftsg.h"
#include "./fft.h"

void cdft(int n, int isgn, double *a, int *ip, double *w);
void rdft(int n, int isgn, double *a, int *ip, double *w);

namespace {
void BackwardFFT(fft_plan p) {
  if (p.c_out == NULL) {  // c2r
    p.input[0] = p.c_in[0][0];
    p.input[1] = p.c_in[p.n / 2][0];
    for (int i = 1; i < p.n / 2; ++i) {
      p.input[i * 2]  = p.c_in[i][0];
      p.input[i * 2 + 1]  = p.c_in[i][1];
    }
    rdft(p.n, -1, p.input, p.ip, p.w);
    for (int i = 0; i < p.n; ++i) p.out[i] = p.input[i] * 2.0;
  } else {  // c2c
    for (int i = 0; i < p.n; ++i) {
      p.input[i * 2] = p.c_in[i][0];
      p.input[i * 2 + 1] = p.c_in[i][1];
    }
    cdft(p.n * 2, -1, p.input, p.ip, p.w);
    for (int i = 0; i < p.n; ++i) {
      p.c_out[i][0] = p.input[i * 2];
      p.c_out[i][1] = p.input[i * 2 + 1];
    }
  }
}

void ForwardFFT(fft_plan p) {
  if (p.c_in == NULL) {  // r2c
    for (int i = 0; i < p.n; ++i) p.input[i] = p.in[i];
    rdft(p.n, 1, p.input, p.ip, p.w);
    p.c_out[0][0] = p.input[0];
    p.c_out[0][1] = 0.0;
    for (int i = 1; i < p.n / 2; ++i) {
      p.c_out[i][0] = p.input[i * 2];
      p.c_out[i][1] = p.input[i * 2 + 1];
    }
    p.c_out[p.n / 2][0] = p.input[1];
    p.c_out[p.n / 2][1] = 0.0;
  } else {  // c2c
    for (int i = 0; i < p.n; ++i) {
      p.input[i * 2] = p.c_in[i][0];
      p.input[i * 2 + 1] = p.c_in[i][1];
    }
    cdft(p.n * 2, 1, p.input, p.ip, p.w);
    for (int i = 0; i < p.n; ++i) {
      p.c_out[i][0]   = p.input[i * 2];
      p.c_out[i][1]   = p.input[i * 2 + 1];
    }
  }
}

}  // namespace

fft_plan fft_plan_dft_1d(int n, fft_complex *in, fft_complex *out, int sign,
    unsigned int flags) {
  void makewt(int nw, int *ip, double *w);

  fft_plan output = {0};
  output.n = n;
  output.in = NULL;
  output.c_in = in;
  output.out = NULL;
  output.c_out = out;
  output.sign = sign;
  output.flags = flags;
  output.input = new double[n * 2];
  output.ip = new int[n];
  output.w = new double[n * 5 / 4];

  output.ip[0] = 0;
  makewt(output.n >> 1, output.ip, output.w);
  return output;
}

fft_plan fft_plan_dft_c2r_1d(int n, fft_complex *in, double *out,
    unsigned int flags) {
  void makewt(int nw, int *ip, double *w);
  void makect(int nc, int *ip, double *c);

  fft_plan output = {0};
  output.n = n;
  output.in = NULL;
  output.c_in = in;
  output.out = out;
  output.c_out = NULL;
  output.sign = FFT_BACKWARD;
  output.flags = flags;
  output.input = new double[n];
  output.ip = new int[n];
  output.w = new double[n * 5 / 4];

  output.ip[0] = 0;
  makewt(output.n >> 2, output.ip, output.w);
  makect(output.n >> 2, output.ip, output.w + (output.n >> 2));
  return output;
}

fft_plan fft_plan_dft_r2c_1d(int n, double *in, fft_complex *out,
    unsigned int flags) {
  void makewt(int nw, int *ip, double *w);
  void makect(int nc, int *ip, double *c);

  fft_plan output = {0};
  output.n = n;
  output.in = in;
  output.c_in = NULL;
  output.out = NULL;
  output.c_out = out;
  output.sign = FFT_FORWARD;
  output.flags = flags;
  output.input = new double[n];
  output.ip = new int[n];
  output.w = new double[n * 5 / 4];

  output.ip[0] = 0;
  makewt(output.n >> 2, output.ip, output.w);
  makect(output.n >> 2, output.ip, output.w + (output.n >> 2));
  return output;
}


void fft_execute(fft_plan p) {
  if (p.sign == FFT_FORWARD) {
    ForwardFFT(p);
  } else {  // ifft
    BackwardFFT(p);
  }
}

void fft_destroy_plan(fft_plan p) {
  p.n = 0;
  p.in = NULL;
  p.c_in = NULL;
  p.out = NULL;
  p.c_out = NULL;
  p.sign = 0;
  p.flags = 0;
  delete[] p.input;
  delete[] p.ip;
  delete[] p.w;
}

