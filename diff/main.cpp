// 27019578
// Mugi Noda

#include <iostream>
#include <vector>

int main() {
	std::vector<int> s = {4,6,7,1,5,5,1,4,7};
	std::vector<int> t = {3,6,2,7,1,5,5,1,8,7};
	// std::vector<int> s = {1,2,3,4};
	// std::vector<int> t = {1,2,3,4,5};
	std::vector<std::vector<int>> y;
	y.resize(s.size()+1);
	for (auto&a:y) {
		a.resize(t.size()+1);
		for (auto&b:a) {
			b = 0;
		}
	}
	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < t.size(); j++) {
			if (s.at(i) == t.at(j)) {
				y.at(i+1).at(j+1) = std::min({y.at(i).at(j), y.at(i).at(j+1)+1, y.at(i+1).at(j)+1});
			} else {
				y.at(i+1).at(j+1) = std::min({y.at(i).at(j)+1, y.at(i).at(j+1)+1, y.at(i+1).at(j)+1});
			}
		}
	}
	std::cout << "s = ";
	for (auto&a:s) {
		std::cout << a << " ";
	}
	std::cout << std::endl;
	std::cout << "t = ";
	for (auto&a:t) {
		std::cout << a << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
	for (auto&a: y) {
		for (auto&b:a) {
			std::cout << b << " ";
		}
		std::cout << std::endl;
	}
	std::cout << y[s.size()][t.size()] << std::endl;
	return 0;
}
