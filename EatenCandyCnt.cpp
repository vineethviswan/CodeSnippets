/*
Find the maximum number of candies you can eat.
you will be given N candies. For every x candies that you eat, you will get an extra candy. 
N = 3, x = 2
Eating 2 : Balance after first step : 3-2 + 1 = 2
Eating 2 : Balance after second step : 2-2 + 1 = 1
Eating 1 - Total 5
*/

#include <iostream>
#include <vector>
#include <algorithm>

//Recursive version
int eatenCandyCountRec(int balance, int newEvery) {
	if (balance < newEvery)
		return balance;

	return newEvery + eatenCandyCountRec(balance - newEvery + 1, newEvery);
}

//Using loops
int eatenCandyCount(int pCandyCnt, int pBonusCandyCnt) {
	
	int eatenCnt = 0, ateTotal = 0;
	int balance = pCandyCnt;

	while (balance) {
		eatenCnt = std::min(balance, pBonusCandyCnt);
		balance -= eatenCnt;
		ateTotal += eatenCnt;
		if (eatenCnt == pBonusCandyCnt)
			balance++;
	}

	return ateTotal;	
}


int main() {

	std::cout << eatenCandyCount(3, 2) << std::endl;
	std::cout << eatenCandyCountRec(3, 2) << std::endl;
}