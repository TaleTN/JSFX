// Wavetable generator for JS: Tale/wavetable_synth
// Copyright (C) 2014, 2015 Theo Niessink
// License: GPL - http://www.gnu.org/licenses/gpl.html

/* REQUIRES WDL

   Get WDL from http://www.cockos.com/wdl

   Extract it so you have:

      wavetable_generator.cpp
      wavetable_generator.h

   and

      WDL/heapbuf.h
      WDL/pcmfmtcvt.h
      WDL/wavwrite.h
      WDL/wdlstring.h
      WDL/wdltypes.h

   from the same relative path.

*/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "WDL/wavwrite.h"

static double sigma(int k, int n)
{
	double x = M_PI * k / (n + 1);
	return sin(x) / x;
}

static bool gen_wavetbl(const char* filename, int bps, double (*fourier_series)(double, int, int, double), double param)
{
	static const int num_wavetbls = 8, wavetbl_len = 4 << (num_wavetbls - 1), wavetbl_size = num_wavetbls * wavetbl_len;
	double wavetbl[wavetbl_size];

	double* tbl = wavetbl;
	for (int i = 0; i < num_wavetbls; ++i)
	{
		int n = 1 << i;

		for (int j = 0; j < wavetbl_len; ++j)
		{
			double t = (double)j / wavetbl_len;

			double sum = 0;
			for (int k = 1; k <= n; ++k)
			{
				sum += fourier_series(t, k, n, param);
			}

			*tbl++ = M_SQRT1_2 * sum;
		}
	}

	WaveWriter fh;
	if (!fh.Open(filename, bps, 1, wavetbl_len, 0)) return false;
	fh.WriteDoubles(wavetbl, wavetbl_size);

	return fh.BytesWritten() == wavetbl_size * bps/8;
}

static bool gen_wavetbl(const char* filename, double (*fourier_series)(double, int, int, double), double param = 0)
{
	return gen_wavetbl(filename, 16, fourier_series, param);
}
