#ifndef FILEREPLACER_HPP
#define FILEREPLACER_HPP
// ヘッダガード：このヘッダが複数回 #include されても
// 中身が二重に展開されないようにするための定型句。
// FILEREPLACER_HPP がまだ定義されていなければ define して中身を読み込み、
// 2 回目以降はスキップする。

#include <string>
// std::string を使うために必要。

// =============================================================================
// FileReplacer クラス
// -----------------------------------------------------------------------------
// ファイルの中身を読み込み、文字列 s1 をすべて s2 に置換した結果を
// "<元のファイル名>.replace" という新しいファイルに書き出すクラス。
//
// ex04 の課題（"sed -e 's/s1/s2/g' を簡易再現する」課題）を担う本体。
// main からは「ファイル名・s1・s2」を渡してインスタンスを作り、
// run() を呼ぶだけで一連の処理が完結する。
// =============================================================================
class FileReplacer
{
private:
	std::string _filename;
	std::string _s1;
	std::string _s2;
	std::string replaceAll(const std::string& content) const;

public:
	FileReplacer(const std::string& filename,const std::string& s1,const std::string& s2);
	bool run() const;
};

#endif
