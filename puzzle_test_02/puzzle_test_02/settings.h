// 定数
//
//  settings.h
//  puzzle_test_02
//
//  Created by hujita on 2016/02/24.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#ifndef __puzzle_test_02__settings__
#define __puzzle_test_02__settings__

#include <iostream>
using namespace std;


// 画面
const int WINDOW_WIDE = 1400;
const int WINDOW_HIGH = 850;
const int MOVE_AMOUNT = 3;
// プレイモード
const int MODE_PLAY = 0;
const int MODE_DELETE = 1;
const int MODE_REBORN = 2;
// 共通
const int OFF = 0;
const int ON = 1;
const int Invalid = -1;
// 画面遷移
const int VIEW_TOP = 0;
const int VIEW_PLAY = 1;
// 設定
const int CONFIG_STATE_MAX = 5;
const int CONFIG_LINE_MAX = 20;
const int CONFIG_ROW_MAX = 12;
const int CONFIG_TYPE_MAX = 9;
const int CONFIG_TIME_MAX = 60 * 5;


// ブロック
const int BLOCK_MAX = 12 * 20;
const int BLOCK_HIGH = 58;
const int BLOCK_WIDE = 58;
const int BLOCK_POSITION_00_X = 109;
const int BLOCK_POSITION_00_Y = 39;
const int BLOCK_POSITION_01_X = 365;
const int BLOCK_POSITION_01_Y = 39;
const int BLOCK_POSITION_02_X = 623;
const int BLOCK_POSITION_02_Y = 39;
const int BLOCK_POSITION_03_X = 237;
const int BLOCK_POSITION_03_Y = 179;
const int BLOCK_POSITION_04_X = 237;
const int BLOCK_POSITION_04_Y = 39;
const int BLOCK_POSITION_05_X = 493;
const int BLOCK_POSITION_05_Y = 39;
const int BLOCK_POSITION_06_X = 109;
const int BLOCK_POSITION_06_Y = 179;
const int BLOCK_POSITION_07_X = 365;
const int BLOCK_POSITION_07_Y = 179;
const int BLOCK_POSITION_08_X = 493;
const int BLOCK_POSITION_08_Y = 179;
// 区画
const int SECTION_MAX = 12 * 20;
const int SECTION_SOURCE_X = 8;
const int SECTION_SOURCE_Y = 8;
const int SECTION_HIGH = 70;
const int SECTION_WIDE = 70;
const int SECTION_SPACE_WIDE = 7;
const int SECTION_SPACE_HIGH = 7;
const int SECTION_LIMIT = 20;

//
const int OPERATION_MAX = 10;
const int SCORE_CREAR = 31000;
const int SCORE_BLOCK = 100;

const string WORD_TOP_MAIN = "パズルの設定(1~9で入力)";
const string WORD_TOP_SUB_0 = "行数を指定してください";
const string WORD_TOP_SUB_1 = "列数を指定してください";
const string WORD_TOP_SUB_2 = "ブロックの種類数を指定してください";
const string WORD_TOP_SUB_3 = "ブロックを繋げるべき数を指定してください";
const string WORD_TOP_SUB_FINISH = "Enter:ゲーム開始 / 右Shift:TOPに戻る / ESC:終了";

//const char* TEXT_TOP_SUB_4 = "Enter:ゲーム開始 / 右Shift:TOPに戻る / ESC:終了";


#endif /* defined(__puzzle_test_02__settings__) */
