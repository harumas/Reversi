#include "../include/ReversiBenchmark.h"

namespace Reversi
{
	void ReversiBenchmark::Start()
	{
		start = std::chrono::system_clock::now();
	}

	void ReversiBenchmark::End()
	{
		end = std::chrono::system_clock::now();

		double elapsed = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0);
		milliseconds.emplace_back(elapsed);
		move_count++;
	}

	void ReversiBenchmark::Clear()
	{
		milliseconds.clear();
		move_count = 0;
	}

	void ReversiBenchmark::WriteResult()
	{
		double sum = 0.0;
		std::wstring str;

		str += L"[Benchmark]\n";
		for (int i = 0; i < milliseconds.size(); ++i)
		{
			str += std::format(L"{}: {}s\n", std::to_wstring(i), std::to_wstring(milliseconds[i]));
			sum += milliseconds[i];
		}

		str += std::format(L"Ave: {}s\n", sum / static_cast<double>(milliseconds.size()));

		auto minmax = std::minmax_element(milliseconds.begin(), milliseconds.end());
		str += std::format(L"Min: {}s\n", *minmax.first);
		str += std::format(L"Max: {}s\n", *minmax.second);

		std::wcout << str << std::endl;
	}
}
