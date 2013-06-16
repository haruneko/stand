//-----------------------------------------------------------------------------
// Copyright 2012 Masanori Morise. All Rights Reserved.
// Author: morise [at] fc.ritsumei.ac.jp (Masanori Morise)
//-----------------------------------------------------------------------------
#ifndef WORLD_PLATINUM_H_
#define WORLD_PLATINUM_H_

//-----------------------------------------------------------------------------
// Platinum() calculates the spectrum of the excitation signal.
// Exciation signal is calculated by convoluting the windowed signal and
// Inverse function of the spectral envelope. The minimum phase is used as the
// phase of the spectral envelope.
// Input:
//   x                    : Input signal
//   x_length             : Length of x
//   fs                   : Sampling frequency
//   time_axis            : Temporal positions used for calculating the
//                          excitation signal
//   f0                   : f0 contour
//   spectrogram          : Spectrogram (WORLD assumes spectrogram by Star())
// Output:
//   residual_spectrogram : Extracted spectrum of the excitation signal
//-----------------------------------------------------------------------------
void Platinum(const double *x, int x_length, int fs, const double *time_axis,
  const double *f0, int f0_length, const double * const*spectrogram,
  int fft_size, double **residual_spectrogram);
#endif  // WORLD_PLATINUM_H_
