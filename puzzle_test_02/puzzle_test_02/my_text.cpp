//
//  my_text.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/03/03.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "my_text.h"

MyText::MyText(){
    config_main = "パズルの設定(Enter：決定)";
    config_question_0 = "行数を指定してください(1~20)";
    config_question_1 = "列数を指定してください(1~12)";
    config_question_2 = "ブロックの種類数を指定してください(1~9)";
    config_question_3 = "ブロックを繋げるべき数を指定してください(行数列数どちらかよりは小さい数)";
    config_question_finish = "Enter:ゲーム開始 / 右Shift:TOPに戻る / ESC:終了";
    config_input_result = "行数：%d  列数：%d  ブロック：%d  連鎖：%d";
    score = "SCORE：%d";
    operations = "残り操作回数：%d";
    crear = "クリアしました";
    game_over = "ゲームオーバー";
    condition = "%d点とるとクリア";
}

char* MyText::GetConfigMain(){ return config_main; }
char* MyText::GetConfigQuestion0(){ return config_question_0; }
char* MyText::GetConfigQuestion1(){ return config_question_1; }
char* MyText::GetConfigQuestion2(){ return config_question_2; }
char* MyText::GetConfigQuestion3(){ return config_question_3; }
char* MyText::GetConfigQuestionFinish(){ return config_question_finish; }
char* MyText::GetConfigInputResult(){ return config_input_result; }
char* MyText::GetScore(){ return score; }
char* MyText::GetOperations(){ return operations; }
char* MyText::GetCrear(){ return crear;}
char* MyText::GetGameOver(){ return game_over; }
char* MyText::GetCondition(){ return condition; }
