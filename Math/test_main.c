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

#include <stdio.h>
#include "CORDIC.h"
#include "math.h"

int main()
{

    long long ret, w;
    long long x, y;
    long long cosz, sinz;
    
    x = 2490; y = 3276;
    ret = CORDIC_amplitude  (x, y);
    printf ("\nAmplitude Test, lib_func = %ld, ret = %ld\n", (long)sqrt (x * x + y * y) , (long)ret);
    
    x = 2490; y = 3276;
    ret = CORDIC_arctan (x, y);
    printf ("\nArctan Test, lib_func = %f, ret = %f\n", atan2 (y, x) , (double)ret / CORDIC_SCALING_FACTOR);
        
    x = 32767; y = 32767;
    ret = CORDIC_mult (x, y);
    printf ("\nMult Test, lib_func = %ld, ret = %ld\n",  (long)(x * y) , (long)ret);
 
    x = 3276; y = 2490;
    ret = CORDIC_division (x, y);
    printf ("\nDivision Test, lib_func = %f, ret = %f\n",  (double)y/x , (double)ret / CORDIC_SCALING_FACTOR);

    w = 562332068;
    ret = CORDIC_exp (w);
    printf ("\nExp Test, lib_func = %f, ret = %f\n", exp ((double)w/CORDIC_SCALING_FACTOR) , (double)ret / CORDIC_SCALING_FACTOR);

    w = 140583017;    
    ret = CORDIC_sqrt(w);
    printf ("\nSqrt Test, lib_func = %ld, ret = %ld\n", (long) round(sqrt (w)) , (long)ret);
    
    w = CORDIC_SCALING_FACTOR / 2;
    ret = CORDIC_ln (w);
    printf ("\nNatural Logarithm Test, lib_func = %f, ret = %f\n",  log ((double)w / CORDIC_SCALING_FACTOR) , (double)ret / CORDIC_SCALING_FACTOR);
    
    
    x = 2; y = 1;
    w = floor((atan2 (y, x) * CORDIC_SCALING_FACTOR + 0.5));
    cosz = CORDIC_cos (w);
    sinz = CORDIC_sin (w);
    printf ("\nCos/Sin Test, \n lib_func Cos = %f, lib_func Sin = %f, \n Ret Cos = %f, Ret Sin = %f\n", 
              cos(atan2(y, x)), sin(atan2(y,x)), (double)cosz / CORDIC_SCALING_FACTOR, (double)sinz / CORDIC_SCALING_FACTOR);

    
   /* 
    

    z0 = floor((atan2 (1, 2) * CORDIC_SCALING_FACTOR + 0.5));

    CORDIC_circular_vectoring_mode(30, &x0, &y0);

    z0 = 

    i =  

    x0 = CORDIC_SCALING_FACTOR; y0 = 0;

    z0 = 

    CORDIC_circular_rotation_mode(30, &x0, &y0,z0 );

    z0 = floor((atan2 (1, 2) * CORDIC_SCALING_FACTOR + 0.5));

    
    //c = CORDIC_linear_vectoring_mode(30, 3276, 2490, 0);
    
//  CORDIC_linear_vectoring_mode(30, 2400, 2400);
 c =    CORDIC_linear_vectoring_mode(30,  32767, 24900, 0);
    printf ("c = %lf\n", (double)c / CORDIC_SCALING_FACTOR);
    */
    return 0;

} // End of main()