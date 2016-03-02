// 設定
//
//  config.h
//  puzzle_test_02
//
//  Created by hujita on 2016/02/24.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#ifndef __puzzle_test_02__config__
#define __puzzle_test_02__config__

#include <stdio.h>

class Config {
    // 進行フェーズ
    int state;
    // ゲーム設定パラメータ
    int line;
    int row;
    int type;
    int chain;
public:
    Config();
    // 設定を更新する
    void Set(int value);
    // 設定を初期化
    void Reset();
    // 設定の質問文を取得
    char* GetQuestion();
    // 設定の現在値を取得
    // 戻り値がうまく取得できず
    //char* GetResult();
    
    // Getter
    int GetState();
    int GetLine();
    int GetRow();
    int GetType();
    int GetChain();
};

#endif /* defined(__puzzle_test_02__config__) */
