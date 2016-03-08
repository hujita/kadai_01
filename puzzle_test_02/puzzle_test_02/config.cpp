//
//  config.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/02/24.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "config.h"

Config::Config():
    state(0),
    line(0),
    row(0),
    type(0),
    chain(0)
{}

void Config::UpdateState(){
    // 数値入力する前にエンターキーでこの関数が呼ばれても、stateを更新しない
    int result = OFF;
    switch (state){
        case 0:
            if (line != 0)
                result = ON;
            break;
        case 1:
            if (row != 0)
                result = ON;
            break;
        case 2:
            if (type != 0)
                result = ON;
            break;
        case 3:
            if (chain != 0)
                result = ON;
            break;
    }
    if (result == ON && state < CONFIG_STATE_MAX)
      ++state;
}

// 多態性のつもり
void Config::Set(int value){
    switch (state){
        case 0:
            line = line * 10 + value;
            if (line > CONFIG_LINE_MAX){
                line = CONFIG_LINE_MAX;
            }
            break;
        case 1:
            row = row * 10 + value;
            if (row > CONFIG_ROW_MAX){
                row = CONFIG_ROW_MAX;
            }
            break;
        case 2:
            type = type * 10 + value;
            if (type > CONFIG_TYPE_MAX){
                type = CONFIG_TYPE_MAX;
            }
            break;
        case 3:
            chain = chain * 10 + value;
            if (chain > row && chain > line){
                chain = line;
            }
            break;
    }
}

void Config::Reset(){
    state = OFF;
    line = OFF;
    row = OFF;
    type = OFF;
    chain = OFF;
}

char* Config::GetQuestion(){
    MyText my_text;
    // 質問文
    char* word_sub = NULL;
    switch (state){
        case 0:
            word_sub = my_text.GetConfigQuestion0();
            break;
        case 1:
            word_sub = my_text.GetConfigQuestion1();
            break;
        case 2:
            word_sub = my_text.GetConfigQuestion2();
            break;
        case 3:
            word_sub = my_text.GetConfigQuestion3();
            break;
        case 4:
            word_sub = my_text.GetConfigQuestionFinish();
            break;
    }
    
    // questionもword_subの戻り値をstd::coutで出力すると同じ文言が出力されるけど、なぜかTTF_RenderUTF8_Blendedで描画するとquestionは文字化けしてしまう
    //文字コードの問題？
    //char question[100];
    //string word_su;
    //word_su = WORD_TOP_SUB_0;
    //std::sprintf(question, word_su.c_str());
    //std::cout << "iiiii=" << question << std::endl;
    //return question;
    // 文字コードが違う？
    //if (word_sub == question){
    //    return "一緒";
    //}
    //return "違う";
    
    return word_sub;
}

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