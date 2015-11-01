// Wavetable generator for JS: Tale/wavetable_synth
// Copyright (C) 2014, 2015 Theo Niessink
// License: GPL - http://www.gnu.org/licenses/gpl.html

#include "wavetable_generator.h"

double circ(double t, int k, double)
{
	return k & 1 ? -4 * j1(M_PI * (2*k - 1)) / k * sin(2*M_PI * k * t) : 0;
}

double arc(double t, int k, double)
{
	return k ? 2 * j1(M_PI * k) / k * cos(2*M_PI * k * (t + 0.25)) : 0.5*M_PI - 1;
}

double combo(double t, int k, double n)
{
	if (!k) return 0;

	const int int_n = (int)n;
	int i = 0;
	for (int j = 0; j < int_n; ++j)
	{
		i = 1 << j;
		if ((k & (2*i - 1)) == i) break;
		i = 0;
	}

	return i ? 4/(M_PI * int_n) * i / k * sin(2*M_PI * k * (t + 0.5)) : 0;
}

double full(double t, int k, double)
{
	return k ? 8/M_PI / (1 - 4*k*k) * cos(2*M_PI * k * (t + 0.75)) : 4/M_PI - 1;
}

double half(double t, int k, double pw = 0.5)
{
	return k ? (pw*k == 0.5 ? (k & 1 ? -1 : 1) / k : 2/M_PI * pw * cos(M_PI * (1 - pw) * k) / (0.25 - pw*pw * k*k)) * cos(2*M_PI * k * (t + 0.75)) : 4/M_PI * pw - 1;
}

double ham(double t, int k, double n = 3)
{
	if (!k) return 0;

	const int int_n = (int)n;
	switch (int_n)
	{
		case 1: case 2: default: case 3: case 4: if (k > int_n) return 0; break;
		case 5: case 6: case 7: case 8: if (k > 4 && (k & 1 || k > 4 + 2 * (int(n) - 4))) return 0; break;
		case 9: if (k > 4 && (k & 1 || k > 12) && k != 16) return 0; break;
	}

	double a;
	switch (int_n)
	{
		case 1: a = 1; break;
		case 2: a = 0.568134086134179594473891938833; break;
		default: case 3: a = /* 0.400084401888847696060480529923 */ 0.4; break;
		case 4: a = 0.309382307569317671624986587631; break;
		case 5: a = 0.268382163704272314053156378577; break;
		case 6: a = 0.236287471015808936414259733283; break;
		case 7: a = 0.208586523765622755544058009036; break;
		case 8: a = 0.18534593451986317025337314135; break;
		case 9: a = 0.172410339992880773385408588183; break;
	}

	return a * sin(2*M_PI * k * (t + 0.5));
}

double lpsqr(double t, int k, double fc)
{
	return k & 1 ? 4/M_PI * (fc / (fc*fc + k*k) * cos(2*M_PI * k * t) - fc*fc / ((fc*fc + k*k) * k) * sin(2*M_PI * k * t)) : 0;
}

double rect(double t, int k, double pw)
{
	return k ? 4/M_PI * sin(M_PI * pw * k) / k * cos(2*M_PI * k * (t + 0.5*(1 - pw))) : 2*pw - 1;
}

double saw(double t, int k, double)
{
	return k ? -2/M_PI / k * sin(2*M_PI * k * t) : 0;
}

double sine(double t, int k, double)
{
	return k == 1 ? -sin(2*M_PI * k * t) : 0;
}

double sqr(double t, int k, double)
{
	return k & 1 ? -4/M_PI / k * sin(2*M_PI * k * t) : 0;
}

double sqr2(double t, int k, double pw)
{
	return k & 1 ? -4/M_PI * cos(0.5*M_PI * k * (1 - pw)) / k * sin(2*M_PI * k * t) : 0;
}

double stairs(double t, int k, double)
{
	return k & 3 ? 8/(3*M_PI) / k * sin(2*M_PI * k * (t + 0.5)) : 0;
}

double trap(double t, int k, double pw = 0.5)
{
	return k & 1 ? (pw >= 1 ? -4/M_PI / k : -8/(M_PI*M_PI) * sin(0.5*M_PI * (1 - pw) * k) / ((1 - pw) * k*k)) * sin(2*M_PI * k * t) : 0;
}

double tri(double t, int k, double)
{
	return k & 1 ? 8/(M_PI*M_PI) / (k*k) * cos(2*M_PI * k * (t + 0.25)) : 0;
}

double tri2(double t, int k, double pw)
{
	return k ? (pw <= 0 ? 2/M_PI / k : pw >= 1 ? -2/M_PI / k : -2/(M_PI*M_PI) * sin(M_PI * (1 - pw) * k) / (pw * (1 - pw) * k*k)) * sin(2*M_PI * k * (t + (pw <= 0 ? 0.5 : 0))) : 0;
}

double trip(double t, int k, double pw = 0.5)
{
	if (!k) return pw - 1;
	if (pw <= 0) return 0;

	const double x = sin(0.5*M_PI * pw * k);
	return 8/(M_PI*M_PI) * x*x / (pw * k*k) * cos(2*M_PI * k * (t + 0.25));
}

int main()
{
	bool ok = true;

	ok &= gen_wavetbl("Circle.wav", circ);
	ok &= gen_wavetbl("Cycloid.wav", arc);
	ok &= gen_wavetbl("Combo Organ.wav", combo, 3);
	ok &= gen_wavetbl("Filtered Square.wav", lpsqr, M_SQRT2);
	ok &= gen_wavetbl("Full Organ.wav", ham, 9);
	ok &= gen_wavetbl("Full-Wave Rectified Sine.wav", full, 1, 0.75);
	ok &= gen_wavetbl("Half-Wave Rectified Sine.wav", half, 0.5);
	ok &= gen_wavetbl("Hammond.wav", ham, 3);
	ok &= gen_wavetbl("Modified Square.wav", sqr2, 0.4, 0.85);
	ok &= gen_wavetbl("Modified Triangle.wav", tri2, 0.3);
	ok &= gen_wavetbl("Narrow Pulse.wav", rect, 0.1);
	ok &= gen_wavetbl("Pulse.wav", rect, 0.3);
	ok &= gen_wavetbl("Sawtooth.wav", saw, 1, 0.5);
	ok &= gen_wavetbl("Sine.wav", sine, 0, 0, false);
	ok &= gen_wavetbl("Square.wav", sqr);
	ok &= gen_wavetbl("Staircase.wav", stairs);
	ok &= gen_wavetbl("Trapezoid.wav", trap, (double)2/3);
	ok &= gen_wavetbl("Triangle.wav", tri);
	ok &= gen_wavetbl("Triangular Pulse.wav", trip, 0.5);

	return ok ? 0 : 1;
}
