// FirstGitHub.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream> // cout, endl
#include <vector>   // vector
#include <chrono>   // high_resolution_clock, duration_cast
#include <numeric>  // iota
#include <algorithm>
#include <opencv2/opencv.hpp> // opencv
#include <thread>

using namespace std;
using namespace chrono;
using namespace cv;

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
	const int NUMBER = pow(10, 3);
	vector<int> data(NUMBER);
	iota(begin(data), end(data), 0);
	
	Mat frame(480, 640, CV_8UC3);
	VideoCapture cap(0);
	VideoWriter vw;
	if (!cap.isOpened()) {
		cerr << "ビデオを開けませんでした。" << endl;
		exit(1);
	}
	namedWindow("camera", CV_WINDOW_AUTOSIZE);
	Mat copyFrame;
	Mat dst;
	//auto start = high_resolution_clock::now();
	vw.open("camera.mp4", VideoWriter::fourcc('M', 'P', '4', 'V'), 30, frame.size(), true);
	double waitTime = 26;
	while (true) {
		
		cap >> frame;
		frame.copyTo(copyFrame);
		imshow("camera", frame);
		//auto current = high_resolution_clock::now();
		//auto duration = duration_cast<milliseconds>(current - start).count();
		//if (duration >= 5000) break;
		auto begin = high_resolution_clock::now();
		if (cvWaitKey(1) >= 0) break;
		//this_thread::sleep_for(milliseconds(30));
		auto fin = high_resolution_clock::now();
		auto dur = duration_cast<milliseconds>(fin - begin).count();
		cout << dur << " ns" << endl;

	}
	
	reverse(begin(data), end(data));
	cout << "std::sort\t";
	
	measureProcessingTime([&]() { // sort()の処理時間計測する
		sort(begin(data), end(data)); // 昇順にソートする
	});
    return 0;
}