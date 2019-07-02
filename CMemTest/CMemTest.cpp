// CMemTest.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

/**
* @file CMemTest.cpp
* @brief メモリリークテスト用
* @author 小野山康憲
* @date　2019/05/22
* @details メモリリークをテストするために意図的に発生させいます。
*/

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "pch.h"
#include <iostream>

#include <malloc.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

struct PointData {
	int x;
	int y;
	int z;
};
struct CharacterData {
	char name[100];
	int hp;
	int mp;
};


/**
* @brief 3を足す関数
* @param[in] a(元の値) 計算する元の数値
* @param[out] b(代入先) 計算結果を代入する先
* @return bool 常にtrueを返却します。
* @details第一引数に3を足して、第2引数に結果を代入
*/
bool function(int a, int &b) {
	b = a + 3;
	return true;
}

/**
* @brief メイン関数
* @return int 常に0を返す
*/
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_crtBreakAlloc = 160; //breakpoint
	PointData* pPointData = DBG_NEW PointData;

	for (int i = 0; i < 50; i++) {
		delete pPointData;
		pPointData = DBG_NEW PointData;
	}
	_RPT0(_CRT_WARN, "Set Break Point"); //breakpoint

	CharacterData* pCharacterData = DBG_NEW CharacterData;
	for (int i = 0; i < 50; i++) {
		delete pCharacterData;
		pCharacterData = DBG_NEW CharacterData;
	}

	char *p = (char*)_alloca(100);
	char *p2 = (char*)_alloca(100);
	*p2 = 'a';
	p = p2;
	delete pPointData; //breakpoint
	delete pCharacterData; //breakpoint

	_CrtDumpMemoryLeaks(); //breakpoint

	return 0;
}


// コメント１