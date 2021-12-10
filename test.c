#include <string.h>
#include <assert.h>
#include <stdio.h>

#define XUTF8_IMPL
#include "xutf8.h"

int main()
{
	static const char sample[] = "∀x∈ℝf";

	printf("sizeof(%s) = %ld\n", sample, sizeof(sample));

	int count = xutf8_strlen(sample, sizeof(sample)-1); 
	assert(count == 5);

	int i = 0, k = 0;
	do
		{
			int offset = i;

			i = xutf8_next(sample, sizeof(sample)-1, i, NULL);

			if(i < 0)
				break;

			int length = i - offset;

			switch(k)
				{
					case 0: 
					{
						static const char expected[] = "∀";
						assert(sizeof(expected)-1 == length);
						assert(!strncmp(sample + offset, expected, length));
						break;
					}

					case 1: 
					{
						static const char expected[] = "x";
						assert(sizeof(expected)-1 == length);
						assert(!strncmp(sample + offset, expected, length));
						break;
					}

					case 2: 
					{
						static const char expected[] = "∈";
						assert(sizeof(expected)-1 == length);
						assert(!strncmp(sample + offset, expected, length));
						break;
					}

					case 3: 
					{
						static const char expected[] = "ℝ";
						assert(sizeof(expected)-1 == length);
						assert(!strncmp(sample + offset, expected, length));
						break;
					}

					case 4: 
					{
						static const char expected[] = "f";
						assert(sizeof(expected)-1 == length);
						assert(!strncmp(sample + offset, expected, length));
						break;
					}

					default:
					assert(0);
				}

			printf("%d: %.*s\n", k, length, sample + offset);

			k += 1;
		}
	while(i < (int) sizeof(sample)-1);

	i = sizeof(sample)-1;
	k = 0;

	do
		{
			int temp = i;

			i = xutf8_prev(sample, sizeof(sample)-1, i, NULL);

			if(i < 0)
				break;
			
			int offset = i;
			int length = temp - offset;

			switch(k)
				{
					case 4: 
					{
						static const char expected[] = "∀";
						assert(sizeof(expected)-1 == length);
						assert(!strncmp(sample + offset, expected, length));
						break;
					}

					case 3: 
					{
						static const char expected[] = "x";
						assert(sizeof(expected)-1 == length);
						assert(!strncmp(sample + offset, expected, length));
						break;
					}

					case 2: 
					{
						static const char expected[] = "∈";
						assert(sizeof(expected)-1 == length);
						assert(!strncmp(sample + offset, expected, length));
						break;
					}

					case 1: 
					{
						static const char expected[] = "ℝ";
						assert(sizeof(expected)-1 == length);
						assert(!strncmp(sample + offset, expected, length));
						break;
					}

					case 0: 
					{
						static const char expected[] = "f";
						assert(sizeof(expected)-1 == length);
						assert(!strncmp(sample + offset, expected, length));
						break;
					}

					default:
					assert(0);
				}

			printf("%d: %.*s\n", k, length, sample + offset);

			k += 1;
		}
	while(i > 0);


	return 0;
}