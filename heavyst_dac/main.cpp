// 27019578
// Mugi Noda

#include <iostream>
#include <vector>
#include <utility>

class section {
public:
	int x;
	int y;
	int sum;
	section ():x(0),y(0),sum(0){}
	section (int x, int y, int sum):x(x), y(y), sum(sum){}
	section (std::vector<int> v, int x, int y):x(x),y(y) {
		sum = 0;
		for (int i = x; i<y; i++) {
			sum += v.at(i);
		}
	}
};

int operator<(const section a, const section b) {
	return a.sum < b.sum;
}

section heavyst_dac(const std::vector<int> v, int begin, int end) {
	std::cout << "func call: " << begin << " " << end << '\n';
	std::cout << "section: ";
	for (int i = begin; i < end; i++) std::cout << v.at(i) << ' '; std::cout << '\n';
	if (end-begin == 1) {
		return section(begin, end, v.at(begin));
	}else {
		auto left = heavyst_dac(v, begin, (begin+end)/2);
		auto right = heavyst_dac(v, (begin+end)/2, end);
		section midl(v, (begin+end)/2-1, (begin+end)/2);
		section midr(v, (begin+end)/2, (begin+end)/2+1);
		{
			auto tmp = midl.sum;
			auto tmppos = midl.x-1;
			while (midl.sum >= tmp && tmppos >= 0) {
				tmp = midl.sum;
				midl = section(tmppos, midl.y, midl.sum+v.at(tmppos));
				tmppos--;
			}
			midl = section(v, ++++tmppos, midl.y);
			tmp = midr.sum;
			tmppos = midr.y+1;
			while (midr.sum >= tmp && tmppos < v.size()) {
				tmp = midr.sum;
				midr = section(midr.x, tmppos, midr.sum+v.at(tmppos));
				tmppos++;
			}
			midr = section(v, midr.x, ----tmppos);
		}
		section mid = std::max({midl, midr, section(v, midl.x, midr.y)});
		std::cout << "left, right, mid: " << left.sum << ", " << right.sum << ", " << mid.sum << '\n';
		return std::max({left, right, mid});
	}
}

int main() {
	std::vector<int> v =
	{-1,5,4,4,-3,2,-9,5};
	// {-1,2,3,-4,2,5,1,-3};
	std::cout << "initial array: ";
	for (auto&a:v) std::cout << a << ' '; std::cout << '\n';
	auto hoge = heavyst_dac(v, 0, v.size());
	std::cout << "result" << '\n';
	std::cout << "section: " << hoge.x << " " << hoge.y << '\n';
	std::cout << "sum: "<< hoge.sum << '\n';
	return 0;
}
