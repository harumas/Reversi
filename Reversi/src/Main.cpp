#include <iostream>
#include <thread>
#include "../include/Board.h"
#include "../include/BoardWriter.h"
#include "../include/InputReader.h"
#include "../include/ReversiEngine.h"
#include "../include/GameSequencer.h"

using namespace Reversi;

int main()
{
	std::shared_ptr<Board> board = std::make_shared<Board>();
	std::shared_ptr<BoardWriter> board_writer = std::make_shared<BoardWriter>(8);
	std::shared_ptr<MessageWriter> message_writer = std::make_shared<MessageWriter>();
	GameSequencer sequencer(board, board_writer, message_writer);

	//起動メッセージの表示
	message_writer->WriteWelcomeMessage();

	while (sequencer.GetState() != State::Stop)
	{
		//オセロボードの表示
		sequencer.Refresh();

		//ターン選択
		sequencer.AskSelectTurn();

		//敵の強さ選択
		sequencer.AskSelectStrength();

		//ゲーム中のループ
		sequencer.InGameLoop();

		if (sequencer.GetState() == State::End)
		{
			//リトライ選択
			sequencer.AskRetry();
		}
	}

	return 0;
}
