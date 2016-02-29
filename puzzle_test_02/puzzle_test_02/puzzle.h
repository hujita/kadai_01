//
//  puzzle.h
//  puzzle_test_02
//
//  Created by hujita on 2016/02/25.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#ifndef __puzzle_test_02__puzzle__
#define __puzzle_test_02__puzzle__

#include <stdio.h>
#include "block.h"

class Puzzle {
    // 選択中のブロックがあるか
    int state_choice;
public:
    Puzzle();
    // 設定に従いブロックを並べる
    void Initialize(Block* blocks, Config* config);
    // 左クリックを押した。座標から選択されたブロックを探してactiveにする
    void ChoiceBlock(Block* blocks, Config* config, double event_button_x, double event_button_y);
    // 左クリックを離した。座標からブロック位置をパズル区画内に補正する
    void ReleaseBlock(Block* blocks, Config* config, double event_button_x, double event_button_y);
    // ブロックを操作
    void MoveBlock(Block* blocks, Config* config, double event_button_x, double event_button_y);
    // 座標からブロックを見つける
    int LookForTargetBlock(Block* blocks, Config* config, double event_button_x, double event_button_y);
    // 操作中のブロックを見つける
    int LookForActiveBlock(Block* blocks, Config* config);
    // ゲッター
    int GetStateChoice();
    int GetTargetSection();
};


#endif /* defined(__puzzle_test_02__puzzle__) */
