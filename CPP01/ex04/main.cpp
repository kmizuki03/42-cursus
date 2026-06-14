#include "FileReplacer.hpp"
#include <iostream>

// =============================================================================
// main
// -----------------------------------------------------------------------------
// プログラムのエントリポイント。
// コマンドライン引数として「ファイル名・置換元 s1・置換先 s2」の 3 つを受け取り、
// FileReplacer に処理を委譲するだけのシンプルな構成。
//
// 使い方の例:
//   ./sed sample.txt foo bar
//     → sample.txt の中の "foo" をすべて "bar" に置換し、
//        結果を sample.txt.replace に書き出す。
// =============================================================================
int main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
		return (1);
	}

	FileReplacer replacer(argv[1], argv[2], argv[3]);

	if (!replacer.run())
		return (1);

	std::cout << "Replacement complete." << std::endl;
	return (0);
}
