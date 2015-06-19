/*
//===========================================================================
// Copyright (c) : Pulserain Technology, LLC. 2015
//===========================================================================
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
*/

#ifndef CORDIC_H

#define CORDIC_MAX_ITERATIONS 30
#define CORDIC_SCALING_FACTOR      (1 << CORDIC_MAX_ITERATIONS)
#define CORDIC_SCALING_FACTOR_SQRT (1 << (CORDIC_MAX_ITERATIONS / 2))


extern int CORDIC_circular_vectoring_mode(int n, long long *px0, long long *py0);
extern long long CORDIC_amplitude (long long x, long long y);
extern int CORDIC_arctan (long long x, long long y);

extern long long CORDIC_circular_rotation_mode(int n, long long *px0, long long *py0,
                                        signed long long z0);
extern long long CORDIC_sin (long long z);
extern long long CORDIC_cos (long long z);
extern int CORDIC_linear_vectoring_mode (int n, long long x0, long long y0, int z0);
extern int CORDIC_division (long long x, long long y);
extern int CORDIC_linear_rotation_mode(int n, 
                                long long x0, long long y0, long long z0);
extern long long CORDIC_mult (int x, int y);
extern void CORDIC_hyperbolic_vectoring_mode (int n, 
                               long long *px0, long long *py0, long long *pz0);
extern long long CORDIC_sqrt (long long w);
extern long long CORDIC_ln (long long w);
extern void CORDIC_hyperbolic_rotation_mode (int n, long long *px0, long long *py0, long long *pz0);
extern long long CORDIC_exp (long long w);                               


#endif

