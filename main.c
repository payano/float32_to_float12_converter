#include <stdio.h>

/*
 *  12 Bit float:
 *  ------------------------------
 *  | Sign | Exponent | Mantissa |
 *  |  1b  |  5 bits  |  6 bits  |
 *  ------------------------------
 */

static unsigned int conv_float32_to_12bit(float *val)
{
	int sign, e_sign, exp, mantissa;
	unsigned int *int_val;
	int ret_val = 0;

	int_val = (unsigned int*)val;

	sign     = (*int_val >> 31)     & 0x1;
	e_sign   = (*int_val >> 30)     & 0x1;
	exp      = (*int_val >> 23)     & 0xf;
	mantissa = (*int_val >> 17)     & 0x3F;

	ret_val |= sign   << 11;
	ret_val |= e_sign << 10;
	ret_val |= exp    << 6;
	ret_val |= mantissa;

	return ret_val;
}

static float conv_float12_to_32bit(int *val)
{
	int sign, e_sign, exp, mantissa;
	int *int_val;
	float f_val = 0.f;

	int_val = (int*) &f_val;

	sign     = (*val >> 11)     & 0x1;
	e_sign   = (*val >> 10)     & 0x1;
	exp      = (*val >> 6)      & 0xf;
	mantissa = (*val)           & 0x3F;

	*int_val |= sign   << 31;
	*int_val |= e_sign << 30;
	if(!e_sign)
		*int_val |= 0x7 << 27;
	*int_val |= exp    << 23;
	*int_val |= mantissa << 17;

	return f_val;
}


int main(void)
{
	float t,y;
	int v;

	t = 0.025;
	v = conv_float32_to_12bit(&t);
	y = conv_float12_to_32bit(&v);
	printf("t: %f, y: %f\n", t,y);
	t = -0.025;
	v = conv_float32_to_12bit(&t);
	y = conv_float12_to_32bit(&v);
	printf("t: %f, y: %f\n", t,y);
	t = 1000;
	v =conv_float32_to_12bit(&t);
	y = conv_float12_to_32bit(&v);
	printf("t: %f, y: %f\n", t,y);
	t = -1000;
	v = conv_float32_to_12bit(&t);
	y = conv_float12_to_32bit(&v);
	printf("t: %f, y: %f\n", t,y);

	return 0;
}
