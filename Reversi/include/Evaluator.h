#pragma once

#include <limits>
#include <memory>
#include <intrin.h>
#include "Basic.h"
#include "Board.h"

namespace Reversi
{
	/// <summary>
	/// 盤面評価を行うクラス
	/// </summary>
	class Evaluator
	{
	public:
		explicit Evaluator(std::shared_ptr<Board>& board);

		//評価関数
		int Evaluate(Side side) const;

	private:
		std::shared_ptr<Board> board;

		//それぞれのマスに対する評価ウェイト
		static constexpr int weights[64] = {
				45, -11, 4, -1, -1, 4, -11, 45,
				-11, -16, -1, -3, -3, 2, -16, -11,
				4, -1, 2, -1, -1, 2, -1, 4,
				-1, -3, -1, 0, 0, -1, -3, -1,
				-1, -3, -1, 0, 0, -1, -3, -1,
				4, -1, 2, -1, -1, 2, -1, 4,
				-11, -16, -1, -3, -3, 2, -16, -11,
				45, -11, 4, -1, -1, 4, -11, 45,
		};

		//角のマス情報
		static constexpr u64 corners[4] = {
			0x0000000000000001, 0x0000000000000080, 0x0100000000000000, 0x8000000000000000
		};


		//ゲーム終了時に対する評価関数
		int EvaluateGameEnd(std::pair<int, int> counts, int legal_count_black, int legal_count_white) const;

		//マスのウェイトに対する評価関数
		int EvaluateWeight(std::pair<u64, u64> field) const;

		//確定石に対する評価関数
		int EvaluateConfirm(std::pair<u64, u64> field) const;
	};
}


