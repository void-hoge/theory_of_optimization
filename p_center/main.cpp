// 27019578
// Mugi Noda

#include <iostream>
#include <vector>
#include <cassert>

int null_node = -1;
int big_num = ~(1<<31);

class pos {
private:
public:
	int start;
	int end;
	double x;
	double dist;
	pos (int start, int end, double x, double dist):start(start),end(end), x(x), dist(dist) {}
};

bool operator<(const pos a, const pos b) {
	return a.dist < b.dist;
}

template<class T>
int check_vector(std::vector<T> v) {
	int tmp = 0;
	for (const auto&a: v) {
		tmp += (int)a;
	}
	return tmp;
}

class directed_edge {
private:
public:
	int points;
	double distance;
	directed_edge (){};
	directed_edge (int points, double distance): points(points), distance(distance){}
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
	double distance_recursion(std::vector<bool> visited, const int a, const int b, const int d) {
		visited.at(a) = true;
		assert(a >= 0);
		assert(b >= 0);
		assert(a < nd.size());
		assert(b < nd.size());
		if (a == b) {
			return 0;
		}
		std::vector<double> dist;
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
	double distance(const int a, const int b) {
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
	pos min_center(const int a, const int b) {
		std::cout << '\n';
		std::cout << "a = " << a << ", b = " << b << '\n';
		assert(a != b);
		// returns a center(distance to a) when it exists between a and b.
		double len_ab = big_num;
		for (int i = 0; i < nd.at(a).edg.size(); i++) {
			if (nd.at(a).edg.at(i).points == b) {
				len_ab = nd.at(a).edg.at(i).distance;
			}
		}
		if (len_ab == (double)big_num) {
			throw std::logic_error("no edge between a and b.");
		}
		// dist[i]+x[i]*pos
		std::vector<double> dist_a(size(),0); // via a
		std::vector<double> dist_b(size()); // via b
		for (int i = 0; i < size(); i++) {
			dist_a.at(i) = distance(a, i);
			dist_b.at(i) = len_ab+distance(b, i);
		}
		for (int i = 0; i < size(); i++) {
			std::cout << i << '\n';
			std::cout << "dist_a " << dist_a.at(i) << '\n';
			std::cout << "dist_b " << dist_b.at(i) << '\n';
		}
		double tmp;
		std::vector<double> v;
		while (tmp) {
			double max = -1;
			int idx = -1;
			for (int i = 0; i < size(); i++) {
				if (max < dist_a.at(i)) {
					idx = i;
					max = dist_a.at(i);
				}
			}
			v.push_back(max);
			tmp = max;
			dist_a.at(idx) = -1;
			v.push_back(dist_b.at(idx));
		}
		for (auto a:v) {
			std::cout << a << ' ';
		}
		std::cout << '\n';
		std::vector<double> d;
		std::vector<double> x;
		d.push_back(v.at(0));
		x.push_back(0);
		for (int i = 1; i < v.size(); i++) {
			x.push_back(std::abs((v.at(i)-v.at(i-1))/2));
			if (x.at(i)>=len_ab) {
				break;
			}
			if (i&1) {
				d.push_back(v.at(i)-x.at(i));
			}else {
				d.push_back(v.at(i)+x.at(i));
			}
			if (d.at(i) <= d.at(i-1)) {
				x.push_back(len_ab);
				d.push_back(x.at(i)+len_ab);
				break;
			}
		}
		for (auto a:x) {
			std::cout << a << ' ';
		}
		std::cout << '\n';
		for (auto a:d) {
			std::cout << a << ' ';
		}
		std::cout << '\n';
		return pos(a,b,
			x.at(std::min_element(d.begin(), d.end())-d.begin()),
			*std::min_element(d.begin(), d.end())
		);
	}
};

int main() {
	graph grph;
	// grph.nd.resize(3);
	// grph.add_undirected_edge(0, 1, 1);
	// grph.add_undirected_edge(0, 2, 3);
	// grph.add_undirected_edge(1, 2, 1);

	// grph.nd.resize(4);
	// grph.add_undirected_edge(0, 1, 2);
	// grph.add_undirected_edge(1, 2, 5);
	// grph.add_undirected_edge(0, 2, 4);
	// grph.add_undirected_edge(1, 3, 1);
	// grph.add_undirected_edge(2, 3, 3);

	grph.nd.resize(4);
	grph.add_undirected_edge(0, 1, 3);
	grph.add_undirected_edge(1, 2, 3);
	grph.add_undirected_edge(2, 0, 3);
	grph.add_undirected_edge(0, 3, 1);
	grph.add_undirected_edge(1, 3, 1);
	grph.add_undirected_edge(2, 3, 1);

	grph.dump_edge();


	std::vector<pos> v;
	for (int i = 0; i < grph.size(); i++) {
		for (int j = i+1; j < grph.size(); j++) {
			try {
				v.push_back(grph.min_center(i, j));
			} catch (std::exception e) {
				continue;
			}
		}
	}
	std::cout << '\n';
	for (int i = 0; i < v.size(); i++) {
		std::cout << "start node: " << v.at(i).start << ", "
		<< "end node: "<< v.at(i).end << ", "
		<< "x: " << v.at(i).x << ", "
		<< "min dist: " << v.at(i).dist << '\n';
	}

	auto result = *std::min_element(v.begin(), v.end());
	std::cout << "result" << '\n';
	std::cout << "start node: " << result.start << ", "
	<< "end node: "<< result.end << ", "
	<< "x: " << result.x << ", "
	<< "min dist: " << result.dist << '\n';
	return 0;
}
