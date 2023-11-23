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
	class GameSequencer
	{
	public:
		GameSequencer(std::shared_ptr<Board>& board, std::shared_ptr<BoardWriter>& board_writer, std::shared_ptr<MessageWriter>& message_writer);
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

		void ChangeTurn();
		void EnemyTurn();
		void PlayerTurn();
		BoardInfo GetBoardInfo() const;
		u64 GetRandomInput();
	};
}




