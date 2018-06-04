// FirstGitHub.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream> // cout, endl
#include <vector>   // vector
#include <chrono>   // high_resolution_clock, duration_cast
#include <numeric>  // iota
#include <algorithm>

using namespace std;
using namespace chrono;

// 関数を放り込んで処理時間を計測する
template<typename Function>
void measureProcessingTime(Function func) {
	auto start = high_resolution_clock::now();
	func();
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start).count();
	cout << duration << " micro sec" << endl;
}

// メイン関数
int main(void)
{
	const int NUMBER = 4000000;
	vector<int> data(NUMBER);
	iota(begin(data), end(data), 0);
	
	reverse(begin(data), end(data));
	cout << "std::sort\t";
	measureProcessingTime([&]() { // sort()の処理時間計測する
		sort(begin(data), end(data)); // 昇順にソートする
	});

	cout << "Hello, GitHub" << endl;

    return 0;
}

