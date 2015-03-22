// Wavetable generator for JS: Tale/wavetable_synth
// (c) Theo Niessink 2014, 2015
// License: GPL - http://www.gnu.org/licenses/gpl.html

#include "wavetable_generator.h"

double circ(double t, int k, int n, double)
{
	return k & 1 ? 4 * j1(M_PI * (2*k - 1)) * sin(2*M_PI * k * t) / k * sigma(k, n) : 0;
}

double combo(double t, int k, int n, double num)
{
	int m = 0, inum = (int)num;
	for (int i = 0; i < inum && !m; ++i)
	{
		int j = 1 << i;
		if ((k & (2*j - 1)) == j) m = j;
	}
	return m ? 4/(inum*M_PI) * sin(2*M_PI * k * t) / k * m * sigma(k, n) : 0;
}

double full(double t, int k, int n, double)
{
	double dc = 4/M_PI - 1;
	return dc/n - 8/M_PI * cos(2*M_PI * k * t) / (4 * k*k - 1) * sigma(k, n);
}

double half(double t, int k, int n, double)
{
	double dc = 2/M_PI - 1;
	return dc/n + (k == 1 ? sin(2*M_PI * t) : k & 1 ? 0 : -4/M_PI * cos(2*M_PI * k * t) / (k*k - 1)) * sigma(k, n);
}

double ham(double t, int k, int n, double num)
{
	int inum = (int)num;
	switch (inum)
	{
		case 1: case 2: case 3: case 4: if (k > inum) return 0; break;
		case 5: case 6: case 7: case 8: if (k > 4 && (k & 1 || k > 4 + 2 * (inum - 4))) return 0; break;
		default: case 9: if (k > 4 && (k & 1 || k > 12) && k != 16) return 0; break;
	}
	double a = 0;
	switch (inum)
	{
		case 1: a = 1; break;
		case 2: a = 0.568134086134179594473891938833; break;
		case 3: a = /* 0.400084401888847696060480529923 */ 0.4; break;
		case 4: a = 0.309382307569317671624986587631; break;
		case 5: a = 0.268382163704272314053156378577; break;
		case 6: a = 0.236287471015808936414259733283; break;
		case 7: a = 0.208586523765622755544058009036; break;
		case 8: a = 0.18534593451986317025337314135; break;
		default: case 9: a = 0.172410339992880773385408588183; break;
	}
	return a * sin(2*M_PI * k * t) * sigma(k, n);
}

double lpsqr(double t, int k, int n, double fc)
{
	double x = 1/fc * k;
	double gain = 1/sqrt(1 + x*x);
	double phase_shift = -atan(x);
	return k & 1 ? 4/M_PI * gain * sin(2*M_PI * k * t + phase_shift) / k * sigma(k, n) : 0;
}

double rect(double t, int k, int n, double pw)
{
	double dc = 2*pw - 1;
	return dc/n + 4/M_PI * sin(M_PI * k * pw) * cos(2*M_PI * k * (t - 0.5*pw)) / k * sigma(k, n);
}

double saw(double t, int k, int n, double)
{
	return -2/M_PI * sin(2*M_PI * k * t) / k * sigma(k, n);
}

double sine(double t, int k, int n, double)
{
	return k == 1 ? sin(2*M_PI * k * t) : 0;
}

double sqr(double t, int k, int n, double)
{
	return k & 1 ? 4/M_PI * sin(2*M_PI * k * t) / k * sigma(k, n) : 0;
}

double sqr2(double t, int k, int n, double pw)
{
	return k & 1 ? 4/M_PI * cos(M_PI * k * (0.5 - pw)) * sin(2*M_PI * k * (t + 0.5*pw + 0.75)) / k * sigma(k, n) : 0;
}

double stairs(double t, int k, int n, double pw)
{
	double dc = (4*pw - 1) / 3;
	double s = k & 1 ? sin(2*M_PI * k * t) / k * sigma(k, n) : 0;
	if (2*k <= n) s += 0.5 * sin(M_PI * k * 2*pw) * cos(2*M_PI * k * (2*t - pw)) / k * sigma(2*k, n);
	return dc/n + (double)2/3 * 4/M_PI * s;
}

double trap(double t, int k, int n, double pw)
{
	double s = k & 1 ? 0.25/(0.5 - pw) * 8/(M_PI*M_PI) * (sin(2*M_PI * k * (t - 0.5*pw)) + sin(2*M_PI * k * (t + 0.5*pw))) / (k*k) * sigma(k, n) : 0;
	return k & 2 ? -s : s;
}

double tri(double t, int k, int n, double)
{
	double s = k & 1 ? 8/(M_PI*M_PI) * sin(2*M_PI * k * t) / (k*k) * sigma(k, n) : 0;
	return k & 2 ? -s : s;
}

double tri2(double t, int k, int n, double pw)
{
	double m = 1/pw;
	return -2*m*m / (M_PI*M_PI) * sin(M_PI * (1 - pw) * k) * sin(2*M_PI * k * (t + 0.5)) / ((m - 1) * k*k) * sigma(k, n);
}

double trip(double t, int k, int n, double pw)
{
	double dc = pw - 1;
	double m = 1/(1 - 0.5*pw);
	double x = sin(0.5*M_PI * k * pw);
	return dc/n + (1 - 0.5*pw) * 4*m*m / (M_PI*M_PI) * x*x * cos(2*M_PI * k * (t - 0.5*pw)) / ((m - 1) * k*k) * sigma(k, n);
}

int main()
{
	bool ok = true;

	ok &= gen_wavetbl("Circle.wav", circ);
	ok &= gen_wavetbl("Combo Organ.wav", combo, 3);
	ok &= gen_wavetbl("Filtered Square.wav", lpsqr, M_SQRT2);
	ok &= gen_wavetbl("Full Organ.wav", ham, 9);
	ok &= gen_wavetbl("Full-Wave Rectified Sine.wav", full);
	ok &= gen_wavetbl("Half-Wave Rectified Sine.wav", half);
	ok &= gen_wavetbl("Hammond.wav", ham, 3);
	ok &= gen_wavetbl("Modified Square.wav", sqr2, 0.25);
	ok &= gen_wavetbl("Modified Triangle.wav", tri2, 0.3);
	ok &= gen_wavetbl("Narrow Pulse.wav", rect, 0.1);
	ok &= gen_wavetbl("Pulse.wav", rect, 0.3);
	ok &= gen_wavetbl("Sawtooth.wav", saw);
	ok &= gen_wavetbl("Sine.wav", sine);
	ok &= gen_wavetbl("Square.wav", sqr);
	ok &= gen_wavetbl("Staircase.wav", stairs, 0.25);
	ok &= gen_wavetbl("Trapezoid.wav", trap, (double)1/3);
	ok &= gen_wavetbl("Triangle.wav", tri);
	ok &= gen_wavetbl("Triangular Pulse.wav", trip, 0.5);

	return ok ? 0 : 1;
}
