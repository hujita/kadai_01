//
//  my_text.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/03/03.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "my_text.h"

MyText::MyText():
config_main("パズルの設定(Enter：決定)"),
config_question_0("行数を指定してください(1~20)"),
config_question_1("列数を指定してください(1~12)"),
config_question_2("ブロックの種類数を指定してください(1~9)"),
config_question_3("ブロックを繋げるべき数を指定してください(行数列数どちらかよりは小さい数)"),
config_question_4("ブロックを操作できる秒数を指定してください(1~300)"),
config_question_finish("Enter:ゲーム開始 / 右Shift:TOPに戻る / ESC:終了"),
config_input_result("行数：%d  列数：%d  ブロック：%d  連鎖：%d　操作時間：%d"),
score("SCORE：%d"),
operations("残り操作回数：%d"),
crear("クリアしました"),
game_over("ゲームオーバー"),
condition("%d点とるとクリア"),
time("残り秒数：%d"),
item("【アイテム】"),
item_q("Q：全ブロック消滅"),
item_w("W：操作回数＋1"),
item_e("E：操作時間×2"),
rank("Rank：%c"),
mode("【モード】"),
mode_z("Z：プレイモード"),
mode_x("X：編集モード(停止)"),
mode_c("C：編集モード(起動)"),
mode_x_description("左クリックで指定した区画の機能停止"),
mode_c_description("左クリックで指定した区画を機能させます")
{}

char* MyText::GetConfigMain(){ return config_main; }
char* MyText::GetConfigQuestion0(){ return config_question_0; }
char* MyText::GetConfigQuestion1(){ return config_question_1; }
char* MyText::GetConfigQuestion2(){ return config_question_2; }
char* MyText::GetConfigQuestion3(){ return config_question_3; }
char* MyText::GetConfigQuestion4(){ return config_question_4; }
char* MyText::GetConfigQuestionFinish(){ return config_question_finish; }
char* MyText::GetConfigInputResult(){ return config_input_result; }
char* MyText::GetScore(){ return score; }
char* MyText::GetOperations(){ return operations; }
char* MyText::GetCrear(){ return crear;}
char* MyText::GetGameOver(){ return game_over; }
char* MyText::GetCondition(){ return condition; }
char* MyText::GetTime(){ return time; }
char* MyText::GetItem(){ return item; }
char* MyText::GetItemQ(){ return item_q; }
char* MyText::GetItemW(){ return item_w; }
char* MyText::GetItemE(){ return item_e; }
char* MyText::GetRank(){ return rank; }
char* MyText::GetMode(){ return mode; }
char* MyText::GetModeZ(){ return mode_z; }
char* MyText::GetModeX(){ return mode_x; }
char* MyText::GetModeC(){ return mode_c; }
char* MyText::GetModeXDescription(){ return mode_x_description; }
char* MyText::GetModeCDescription(){ return mode_c_description; }