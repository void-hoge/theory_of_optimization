#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

int main() {
	std::vector<int> a = {-1,5,4,-4,-3,2,-9,5,-2};
	std::vector<int> y(a.size()+1);
	std::vector<int> z(a.size()+1);
	for (int i = 0; i < a.size(); i++) {
		z.at(i+1) = std::max(a.at(i), z.at(i)+a.at(i));
	}
	for (int i = 0; i < a.size(); i++) {
		y.at(i+1) = std::max(y.at(i), z.at(i+1));
	}
	std::cout << "a = ";
	for (auto&a:a) std::cout << std::setw(4)<< a; std::cout << std::endl;
	std::cout << "z = ";
	for (auto&a:z) std::cout << std::setw(4)<< a; std::cout << std::endl;
	std::cout << "y = ";
	for (auto&a:y) std::cout << std::setw(4) << a; std::cout << std::endl;

	auto end = std::max_element(y.begin(),y.end());
	std::cout << "max weigth = " << *end << '\n';
	int sum = 0;
	auto begin = end;
	for (; y.begin() <= begin && sum != *end; begin--) {
		sum += a.at(std::distance(y.begin(), begin)-1);
	}
	int resi = std::distance(y.begin(), begin);
	int resj = std::distance(y.begin(), end)-1;
	std::cout << "begin = " << resi << std::endl;
	std::cout << "end = " << resj << std::endl;
	return 0;
}
