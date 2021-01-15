#include <functional>
#include <iostream>
#include <vector>
#include <queue>

int main() {
	int n;
	long long int number, sum, partial_sum;

	while (true) {
		std::priority_queue<long long int,
			std::vector<long long int>, std::greater<long long int>> min_heap;
		sum = 0;

		std::cin >> n;

		if (n == 0) break;

		for (int i = 0; i < n; ++i) {
			std::cin >> number;
			min_heap.push(number);
		}

		for (int i = 0; i < n - 1; ++i) {
			long long int f = min_heap.top();
			min_heap.pop();
			long long int s = min_heap.top();
			min_heap.pop();

			partial_sum = f + s;
			sum += partial_sum;
			min_heap.push(partial_sum);
		}

		std::cout << sum << '\n';
	}

	return 0;
}
