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
#include "settings.h"
#include "my_text.h"

class Config {
    // 進行フェーズ
    int state;
    // ゲーム設定パラメータ
    int line;
    int row;
    int type;
    int chain;
    int time;
public:
    Config();
    // ステータス更新
    void UpdateState();
    // 設定値更新
    void Set(int value);
    // リセット
    void Reset();
    // 質問文章を取得
    char* GetQuestion();
    // 設定終了しているか
    int FlagFinish();
    
    // Getter
    int GetLine();
    int GetRow();
    int GetType();
    int GetChain();
    int GetTime();
};

#endif /* defined(__puzzle_test_02__config__) */
