/*
 * exponentiation.h
 *
 * Created: 15.12.2020 23:41:04
 *  Author: Аркадий
 */ 


#ifndef EXPONENTIATION_H_
#define EXPONENTIATION_H_

uint8_t base = 251;

// 1. A←1
// 2. For i from t down to 0 do:
//     2.1. A←A*A mod m
//     2.2. If k[i]==1 than A←A*base mod m
// 3. Return A

void test_exp(const TYPE k, uint8_t k_len)
{
	uint8_t A = 1;
	for (uint8_t i = 0; i < k_len; i++)
	{
		A = A * A % 0x100; // (mod 2^8)
		if ((k >> i) & 1)
		{
			A = A * base % 0x100; // (mod 2^8)
		}
	}
}

#endif /* EXPONENTIATION_H_ */