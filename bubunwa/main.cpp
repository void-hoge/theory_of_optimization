#include <iostream>
#include <vector>

class bubunwa {
private:
	const std::vector<int> data;
public:
	bubunwa(std::vector<int> input):data(input) {}

	bool solve_subset(int b) {
		int n = data.size();
		std::vector<std::vector<int>> y;
		y.resize(data.size());
		for (auto &a: y) {
			a.resize(b+1);
			for (auto &num: a) {
				num = 0;
			}
		}
		y[0][0] = 1;
		y[0][data[0]] = 1;
		for (int k = 1; k < n; k++) {
			for (int p = 0; p <= b; p++) {
				if (y[k-1][p] == 1) {
					y[k][p] = 1;
				}else {
					if (p-data[k] >= 0 && y[k-1][p-data[k]] == 1) {
						y[k][p] = 1;
					}
				}
			}
		}
		for (int i = 0; i < y.size(); i++) {
			std::cout << i << ": ";
			for (auto cell: y[i]) {
				std::cout << cell << ' ';
			}
			std::cout << '\n';
		}
		if (y[n-1][b] == 1) {
			return true;
		}else {
			return false;
		}
	}
};

int main() {
	std::vector<int> nums;
	nums = {8,7,4,5,3};
	for (auto a: nums) {
		std::cout << a << ' ';
	}
	std::cout << '\n';
	bubunwa hoge(nums);
	int n;
	std::cin >> n;
	if (hoge.solve_subset(n) == true) {
		std::cout << "YES\n";
	}else {
		std::cout << "NO\n";
	}
	return 0;
}
