#pragma once

#include <chrono>
#include <vector>
#include <algorithm>
#include <iostream>

class ReversiBenchmark
{
public:
	void Start();
	void End();
	void WriteResult();
	void Clear();

private:
	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;
	std::vector<double> milliseconds;
	int move_count = 0;
};

