/*
Nth Rarest Element in an array. 
{ 2, 2, 5, 5, 5, 3, 4, 4, 4, 4, 8, 8, 8 }
1st Rarest element - 3 (occurs only once)
2nd Rarest element - 2 (occurs twice)
3rd Rarest element - 5 (occurs 3 times. If multiple elements with same count, take the first one
*/

#include <iostream>
#include <vector>
#include <algorithm>

int nthRarestElement(std::vector<int> &vec, const int &n) {

	int count = 0;

	if (n <= 0)
		return -1;

	std::sort(vec.begin(), vec.end());
	std::vector<std::pair<int, int>> table;
	for (auto itr = vec.begin(); itr != vec.end(); itr++) {
		if (itr == vec.begin() || *itr != *(itr - 1)) {
			count = std::count(vec.begin(), vec.end(), *itr);
			if (std::find_if_not(table.begin(), table.end(), [&count](std::pair<int, int> &a) {
						return a.first != count; }) == table.end())
				table.push_back(std::pair<int, int>(count, *itr));
		}
	}

	std::sort(table.begin(), table.end(), [](std::pair<int, int> &a, std::pair<int, int> &b) {
		return a.first < b.first;
	});

	return table[n - 1].second;
}

int main() {

std::vector<int> range = { 2, 2, 5, 5, 5, 3, 4, 4, 4, 4, 8, 8, 8 };
std::cout << nthRarestElement(range, 3);

}