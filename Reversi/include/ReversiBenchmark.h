#pragma once

#include <chrono>
#include <vector>
#include <algorithm>
#include <iostream>

namespace Reversi
{
	/// <summary>
	/// 探索時間のベンチマークを行うクラス
	/// </summary>
	class ReversiBenchmark
	{
	public:
		/// <summary>
		/// 一手のベンチマークを開始します
		/// </summary>
		void Start();

		/// <summary>
		/// 一手のベンチマークを終了します
		/// </summary>
		void End();

		/// <summary>
		/// ベンチマーク結果を表示します
		/// </summary>
		void WriteResult();
		void Clear();
	private:
		std::chrono::system_clock::time_point start;
		std::chrono::system_clock::time_point end;
		std::vector<double> milliseconds;
		int move_count = 0;
	};
}
