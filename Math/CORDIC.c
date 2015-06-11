#define CORDIC_MAX_ITERATIONS 30
#define CORDIC_SCALING_FACTOR (1 << 30)

int CORDIC_circular_vectoring_mode(int n, long long *px0, long long *py0)
{
	unsigned int theta[CORDIC_MAX_ITERATIONS];
	int i;
	int sigma;

	long long x,y;
	int z;
	long long x_tmp, y_tmp;
	double k = 1;
			
	x = *px0; y = *py0;
	z = 0;

	for (i = 0; i < n; ++i) {

		theta[i] = floor((atan2 (1, 1 << i) * CORDIC_SCALING_FACTOR + 0.5));
		k = k / sqrt (1 + 1.0 / (((long long)1) << (2 * i)));
	
		if  (y >= 0)  {
			sigma = -1;
		} else {
			sigma = 1;
		}

		if (i > 0) {
			x_tmp = x - sigma * (((y >> (i - 1)) + 1) >> 1);
			y_tmp = (((x >> (i - 1)) + 1) >> 1) * sigma + y;
		} else {
			x_tmp = x - sigma * y;
			y_tmp = x * sigma + y;
		}

		x = x_tmp;
		y = y_tmp;

		z = z - theta[i] * sigma;
	
		printf ("i = %d, k = %lf\n", i, k);
		
	} // End of for loop

	*px0 = x;
	
	return z;
}	   
