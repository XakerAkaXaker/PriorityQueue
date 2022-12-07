#include <iostream>
#include <vector>
#include <string>


const int INF = 2e9 + 11;
int get_min(std::vector<int>& v) {
	return v[0];
}

int find(std::vector<int>& v, int key) {
    int index = 0;
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] == key) {
            index = i;
            break;
        }
    }
    return index;
}

void sift_up(std::vector<int>& v, int pos) {
	while (pos > 0 && v[pos] < v[(pos - 1) / 2]) {
		std::swap(v[pos], v[(pos - 1) / 2]);
		pos = (pos - 1) / 2;
	}
}

void sift_down(std::vector<int>& v, int pos) {
	int i = pos;
	while (true) {
		if (2 * pos + 1 < v.size() && v[i] > v[2 * pos + 1]) {
			i = 2 * pos + 1;
		}
		if (2 * pos + 2 < v.size() && v[i] > v[2 * pos + 2]) {
			i = 2 * pos + 2;
		}
		if (i == pos) break;
		std::swap(v[pos], v[i]);
		pos = i;
	}
}

void build_heap(std::vector<int>& v) {
	for (int i = v.size() / 2; i >= 0; --i) {
		sift_down(v, i);
	}
}

void decrease(std::vector<int>& helper, std::vector<int>& v, int x, int y) {
	int index = find(v, helper[x]);
	v[index] = y;
	sift_up(v, index);
    helper[x] = y;
}

void remove_min(std::vector<int>& v) {
	std::swap(v[0], v.back());
	v.pop_back();
	sift_down(v, 0);
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

	std::vector<int> heap;
	std::vector<int> helper;
	std::string command;

	while (std::cin >> command) {
		if (command[0] == 'p') {
			int number; std::cin >> number;
			heap.push_back(number);
            sift_up(heap, heap.size() - 1);
			helper.push_back(number);
		}

		else if (command[0] == 'e') {
            if (heap.size() == 0) {
                std::cout << "*" << std::endl;
                helper.push_back(INF);
                continue;
            }
			std::cout << get_min(heap) << std::endl;
			remove_min(heap);
            helper.push_back(INF);
		}
		
		else if (command[0] == 'd') {
			int x, y;
			std::cin >> x >> y;
            decrease(helper, heap, x - 1, y);
            helper.push_back(INF);
		}
	}

	return 0;
}
