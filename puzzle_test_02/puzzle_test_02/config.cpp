//
//  config.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/02/24.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "config.h"

Config::Config() {
    state = 0;
    line = 0;
    row = 0;
    type = 0;
    chain = 0;
}

void Config::Set(int value){
    switch (state){
        case 0:
            line = value;
            break;
        case 1:
            row = value;
            break;
        case 2:
            type = value;
            break;
        case 3:
            chain = value;
            break;
    }
    if (state < CONFIG_STATE_MAX)
        ++state;
}

void Config::Reset(){
    state = OFF;
    line = OFF;
    row = OFF;
    type = OFF;
    chain = OFF;
}

char* Config::GetQuestion(){
    // 質問文
    char* word_sub = NULL;
    switch (state){
        case 0:
            word_sub = "行数を指定してください";
            break;
        case 1:
            word_sub = "列数を指定してください";
            break;
        case 2:
            word_sub = "ブロックの種類数を指定してください";
            break;
        case 3:
            word_sub = "ブロックを繋げるべき数を指定してください";
            break;
        case 4:
            word_sub = "Enter:ゲーム開始 / 右Shift:TOPに戻る / ESC:終了";
            break;
    }
    return word_sub;
}

/* 戻り値がうまく取得できず
char* Config::GetResult(){
    char* word_result = NULL;
    char buf[50];
    sprintf(buf, "行数：%d  列数：%d  ブロック：%d  連鎖：%d", line, row, type, chain);
    word_result = buf;
    return word_result;
}
*/

// 全ての設定が完了済みか
int Config::FlagFinish(){
    int result = OFF;
    if (state == CONFIG_STATE_MAX)
        result = ON;
    return result;
}

// Getter
int Config::GetLine(){ return line; }
int Config::GetRow(){ return row; }
int Config::GetType(){ return type; }
int Config::GetChain(){ return chain; }