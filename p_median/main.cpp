#include <iostream>
#include <vector>
#include <cassert>

int null_node = -1;
int big_num = ~(1<<31);

class directed_edge {
private:
public:
	int points;
	int distance;
	directed_edge (){};
	directed_edge (int points, int distance): points(points), distance(distance){}
};

class node {
private:
public:
	std::vector<directed_edge> edg;
	node (){};
	node (std::vector<directed_edge> edg):edg(edg){}
};

class graph {
private:
	int distance_recursion(std::vector<bool> visited, const int a, const int b, const int d) {
		visited.at(a) = true;
		assert(a >= 0);
		assert(b >= 0);
		assert(a < nd.size());
		assert(b < nd.size());
		if (a == b) {
			return 0;
		}
		std::vector<int> dist;
		for (const auto&i:nd.at(a).edg) {
			if (visited.at(i.points)) {
				continue;
			}
			if (i.points == b) {
				dist.push_back(i.distance+d);
			}else {
				auto tmp = distance_recursion(visited, i.points, b, i.distance);
				if (tmp != big_num) {
					dist.push_back(tmp+d);
				}
			}
		}
		dist.push_back(big_num);
		return *std::min_element(dist.begin(), dist.end());
	}
public:
	std::vector<node> nd;
	graph () {};
	int distance(const int a, const int b) {
		return distance_recursion(std::vector<bool>(size(),false), a, b, 0);
	}
	void add_undirected_edge (const int a, const int b, const int dist) {
		assert(a >= 0);
		assert(b >= 0);
		assert(a < nd.size());
		assert(b < nd.size());
		nd.at(a).edg.push_back(directed_edge(b, dist));
		nd.at(b).edg.push_back(directed_edge(a, dist));
	}
	void add_directed_edge (const int a, const int b, const int dist) {
		assert(a >= 0);
		assert(b >= 0);
		assert(a < nd.size());
		assert(b < nd.size());
		nd.at(a).edg.push_back(directed_edge(b, dist));
	}
	void dump_edge () {
		for (int i = 0; i < nd.size(); i++) {
			for (int j = 0; j < nd.at(i).edg.size(); j++) {
				std::cout << i << " to " << nd.at(i).edg.at(j).points
				 << ", dist: " << nd.at(i).edg.at(j).distance << std::endl;
			}
		}
	}
	size_t size() {
		return nd.size();
	}
};

int main() {
	graph grph;
	grph.nd.resize(5);
	grph.add_undirected_edge(0, 1, 1);
	grph.add_undirected_edge(1, 2, 2);
	grph.add_undirected_edge(2, 3, 3);
	grph.add_undirected_edge(2, 4, 4);
	// grph.add_undirected_edge(1, 4, 3);
	// grph.add_undirected_edge(3, 4, 1);
	grph.dump_edge();
	std::vector<int> sum_list(grph.size(), 0);
	for (int i = 0; i < grph.size(); i++) {
		for (int j = 0; j < grph.size(); j++) {
			sum_list.at(i) += grph.distance(i, j);
		}
	}
	for (auto&a: sum_list) std::cout << a << " "; std::cout << '\n';
	int min = ~(1<<31);
	int idx = -1;
	for (int i = 0; i < sum_list.size(); i++) {
		if (min > sum_list.at(i)) {
			min = sum_list.at(i);
			idx = i;
		}
	}
	std::cout << "min: " << min << '\n';
	std::cout << "idx: " << idx << '\n';
	return 0;
}
