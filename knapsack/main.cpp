#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

int main() {
	std::vector<int> a = {2,6,3,10};
	std::vector<int> c = {4,3,2,8};
	int b = 11;
	std::cout << "w = " << b << '\n';
	std::cout << "a = ";
	for (auto&i:a) std::cout << i << " "; std::cout << '\n';
	std::cout << "c = ";
	for (auto&i:c) std::cout << i << " "; std::cout << '\n';
	std::vector<std::vector<int>> y;
	y.resize(a.size()+1);
	for (auto&i:y) {
		i.resize(b+1);
		for (auto&j:i) j=0;
	}
	std::vector<std::vector<bool>> x;
	x.resize(a.size()+1);
	for (auto&i:x) {
		i.resize(b+1);
	}
	for (int k = 1; k <= a.size(); k++) {
		// k: num of item
		for (int s = 1; s <= b; s++) {
			// s: size of knapsack
			if (s < c.at(k-1)) {
				y.at(k).at(s) = y.at(k-1).at(s);
				x.at(k).at(s) = false;
			}else {
				if (y.at(k-1).at(s) < y.at(k-1).at(s-c.at(k-1))+a.at(k-1)) {
					y.at(k).at(s) = y.at(k-1).at(s-c.at(k-1))+a.at(k-1);
					x.at(k).at(s) = true;
				}else {
					y.at(k).at(s) = y.at(k-1).at(s);
					x.at(k).at(s) = false;
				}
				// y.at(k).at(s) = std::max(y.at(k-1).at(s), y.at(k-1).at(s-c.at(k-1))+a.at(k-1));
			}
		}
	}
	std::cout << "y \n";
	for (auto&i:y) {
		for (auto&j:i) {
			std::cout << j << ' ';
		}
		std::cout << '\n';
	}
	std::cout << "use \n";
	for (const auto&i:x) {
		for (const auto&j:i) {
			std::cout << j << ' ';
		}
		std::cout << '\n';
	}
	std::vector<bool> use(a.size(), false);
	{
		int sum = y.at(a.size()).at(b);
		int i = a.size();
		int j = b;
		while (sum != 0) {
			if (x.at(i).at(j)) {
				use.at(i-1) = true;
				sum -= a.at(i-1);
				j -= c.at(i-1);
				i--;
			}else {
				i--;
			}
		}
	}
	std::cout << "max " << y.at(a.size()).at(b) << '\n';
	std::cout << "x = ";
	for (const auto&i:use) std::cout << i << " "; std::cout << '\n';
	return 0;
}
