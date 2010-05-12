#include "C_Euler.h"
#include "C_Primes.h"

int64 Euler_46() {


	int top = 10000;
	unsigned char* primes = SieveEratosthenes(top);
	int num, sq;
	for (num = 9; num < top; num += 2) {
		if (isPrimeE(num, primes))
			continue;
		sq = 1;
		while (2 * sq * sq < num) {
			if (isPrimeE(num - 2 * sq * sq, primes)) {
				break;
			}
			++sq;
		}
		if (2 * sq * sq >= num) {
//			printf("%d\n",num);
			return (int64) num;
		}
	}
	return 1;
//		This will be left here to show how bad you used to be
//		int number = 1000000;//only needs 5777
//		int count = 1;
//		int* list = primeListE(number);
//		while (list[count] != 0)
//			++count;
//		count--;
//		int check;
//		int num = 9;
//		while (list[count] > num) {//make sure we aren't testing a number that's too big.
//			if (isPrime(num) == 1) {
//				num += 2;
//				continue;
//			}
//			check = 0;
//			int truth = 1;
//			while (list[check] < num) {
//				int pot = num - list[check];
//				int square = 0;
//				while (square * square * 2 <= pot) {
//					if ((square * square * 2) == pot) {
//						truth = 0;
//						break;
//					}
//					square++;
//				}
//				if (truth == 0) {
//					break;
//				}
//				check++;
//			}
//			if (truth == 1) {
//				//return (int64) num;
//				printf("%d\n",num);
//			}
//			num += 2;
//		}
}
