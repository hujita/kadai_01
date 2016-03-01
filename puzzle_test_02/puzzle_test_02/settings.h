//
//  settings.h
//  puzzle_test_02
//
//  Created by hujita on 2016/02/24.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#ifndef __puzzle_test_02__settings__
#define __puzzle_test_02__settings__

#include <stdio.h>

// 共通
const int OFF = 0;
const int ON = 1;
const int Invalid = -1;
// 画面遷移
const int VIEW_TOP = 0;
const int VIEW_PLAY = 1;
// 設定
const int CONFIG_STATE_MAX = 4;
// ブロック
const int BLOCK_MAX = 81;
const int BLOCK_HIGH = 90;
const int BLOCK_WIDE = 90;
const int BLOCK_POSITION_00_X = 13;
const int BLOCK_POSITION_00_Y = 35;
const int BLOCK_POSITION_01_X = 255;
const int BLOCK_POSITION_01_Y = 35;
const int BLOCK_POSITION_02_X = 336;
const int BLOCK_POSITION_02_Y = 35;
const int BLOCK_POSITION_03_X = 13;
const int BLOCK_POSITION_03_Y = 127;
const int BLOCK_POSITION_04_X = 174;
const int BLOCK_POSITION_04_Y = 127;
const int BLOCK_POSITION_05_X = 174;
const int BLOCK_POSITION_05_Y = 127;
const int BLOCK_POSITION_06_X = 336;
const int BLOCK_POSITION_06_Y = 127;
const int BLOCK_POSITION_07_X = 13;
const int BLOCK_POSITION_07_Y = 200;
const int BLOCK_POSITION_08_X = 174;
const int BLOCK_POSITION_08_Y = 200;
// パズルボード
const int SECTION_HIGH = 95;
const int SECTION_WIDE = 95;


/*
const char* TEXT_TOP_MAIN = "パズルの設定(1~9で入力)";
const char* TEXT_TOP_SUB_0 = "行数を指定してください";
const char* TEXT_TOP_SUB_1 = "列数を指定してください";
const char* TEXT_TOP_SUB_2 = "ブロックの種類数を指定してください";
const char* TEXT_TOP_SUB_3 = "ブロックを繋げるべき数を指定してください";
const char* TEXT_TOP_SUB_4 = "Enter:ゲーム開始 / 右Shift:TOPに戻る / ESC:終了";
*/

#endif /* defined(__puzzle_test_02__settings__) */
