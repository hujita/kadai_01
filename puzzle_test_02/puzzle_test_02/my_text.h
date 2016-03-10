//
//  my_text.h
//  puzzle_test_02
//
//  Created by hujita on 2016/03/03.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#ifndef __puzzle_test_02__my_text__
#define __puzzle_test_02__my_text__

#include <stdio.h>

class MyText {
    char* config_main;
    char* config_question_0;
    char* config_question_1;
    char* config_question_2;
    char* config_question_3;
    char* config_question_4;
    char* config_question_finish;
    char* config_input_result;
    char* score;
    char* operations;
    char* crear;
    char* game_over;
    char* condition;
    char* time;
    char* item;
    char* item_q;
    char* item_w;
    char* item_e;
    char* rank;
public:
    MyText();
    char* GetConfigMain();
    char* GetConfigQuestion0();
    char* GetConfigQuestion1();
    char* GetConfigQuestion2();
    char* GetConfigQuestion3();
    char* GetConfigQuestion4();
    char* GetConfigQuestionFinish();
    char* GetConfigInputResult();
    char* GetScore();
    char* GetOperations();
    char* GetCrear();
    char* GetGameOver();
    char* GetCondition();
    char* GetTime();
    char* GetItem();
    char* GetItemQ();
    char* GetItemW();
    char* GetItemE();
    char* GetRank();
};

#endif /* defined(__puzzle_test_02__my_text__) */
