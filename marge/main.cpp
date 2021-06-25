// 27019578
// Mugi Noda

#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <random>

int array_size = 1<<5;

class marge_sort {
private:
	std::array<int, 1<<16> data;
	int size;
	int ms_count;

	void recursion(int left, int right) {
		ms_count++;
		// std::cout << ms_count << "th call of MS. left = " << left << ", right = " << right << '\n';
		int mid;
		if ((left+1) < right) {
			mid = (left+right)/2;
			recursion(left, mid);
			// std::cout << left << ", " << right << " line 8 ended: ";
			show();
			recursion(mid, right);
			// std::cout << left << ", " << right << " line 9 ended: ";
			show();
			marge(left, mid, right);
		}
	}

	void marge(const int left, const int mid, const int right) {
		int comparison = 0;
		int n1 = mid - left;
		int n2 = right - mid;

		std::vector<int> L;
		for (int i = 0; i < n1; i++) {
			L.push_back(data[left+i]);
		}
		std::vector<int> R;
		for (int i = 0; i < n2; i++) {
			R.push_back(data[mid+i]);
		}

		L.push_back(~(1<<31));
		R.push_back(~(1<<31));
		int i = 0;
		int j = 0;
		for (int k = left; k < right; k++) {
			comparison++;
			if (L[i] <= R[j]) {
				data[k] = L[i++];
			}else {
				data[k] = R[j++];
			}
		}
		L.clear();
		R.clear();
		// std::cout << comparison << " comparison in marge(" << left << ", " << mid << ", " << right << ")\n";
	}
public:
	marge_sort() {
		size = 0;
		ms_count = 0;
		for (unsigned i = 0; i < data.size(); i++) {
			data[i] = 0;
		}
	}

	void show() const{
		for (int i = 0; i < size; i++) {
			std::cout << data[i] << ' ';
		}
		std::cout << '\n';
	}


	void sort() {
		recursion(0, size);
		// std::cout << "MS count: " << ms_count << '\n';
	}

	void insert(int num) {
		data[size] = num;
		size++;
	}

	void vector_input(std::vector<int> in) {
		for (unsigned i = 0; i < in.size(); i++) {
			insert(in[i]);
		}
	}
};

int main() {
	std::mt19937 mt;
	std::vector<int> a;
	a = {10, 3, 4, 5, 1, 2, 8, 9, 7, 6};
	// for (int i = 0; i < array_size; i++) {
	// 	a.push_back(mt()&((1<<10)-1));
	// }
	marge_sort mg;
	mg.vector_input(a);
	std::cout << "array size: " << a.size() << '\n';
	std::cout << "initial array: ";
	mg.show();
	mg.sort();
	std::cout << "sorted array: ";
	mg.show();
	return 0;
}
