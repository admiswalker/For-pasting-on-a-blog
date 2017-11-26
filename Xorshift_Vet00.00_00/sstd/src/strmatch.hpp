#pragma once	//インクルードガード


namespace sstd{
	bool strmatch(
		const char* str,     // 比較する文字列
		const char* wildCard // ワイルドカード
	);

	bool isNum               (char rhs);
	bool isAlphabet          (char rhs);
	bool isAlphabet_onlyUpper(char rhs);
	bool isAlphabet_onlyLower(char rhs);
}
