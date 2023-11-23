#pragma once

#include <random>
#include <chrono>
#include <thread>

#include "Board.h"
#include "ReversiEngine.h"
#include "BoardWriter.h"
#include "InputReader.h"
#include "MessageWriter.h"
#include "ReversiBenchmark.h"

namespace Reversi
{
	/// <summary>
	/// 現在の盤面の戦況を表すクラス
	/// </summary>
	struct BoardInfo
	{
		int black_count;
		int white_count;
		bool is_end;
	};

	/// <summary>
	/// ゲームの進行を管理するクラス
	/// </summary>
	class GameSequencer
	{
	public:
		GameSequencer(std::shared_ptr<Board>& board, std::shared_ptr<BoardWriter>& board_writer, std::shared_ptr<MessageWriter>& message_writer);

		//ボードの更新
		void Refresh();

		void InGameLoop();
		State GetState();

		void AskSelectTurn();
		void AskRetry();
		void AskSelectStrength();
	private:
		std::shared_ptr<Board> board;
		std::shared_ptr<BoardWriter> board_writer;
		std::shared_ptr<MessageWriter> message_writer;
		ReversiBenchmark reversiBenchmark;
		ReversiEngine engine;
		InputReader reader;
		State current_state;
		Side player_turn;
		Side current_turn;
		u64 prev_input;

		std::mt19937 rand_module;

		void EnemyTurn();
		void PlayerTurn();

		void ChangeTurn();
		BoardInfo GetBoardInfo() const;
		u64 GetRandomInput();
	};
}




