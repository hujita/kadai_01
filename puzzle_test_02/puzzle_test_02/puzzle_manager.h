//
//  puzzle_manager.h
//  puzzle_test_02
//
//  Created by hujita on 2016/03/01.
//  Copyright (c) 2016年 hujita. All rights reserved.
//
// パズルの区画やブロックを並べる人

#ifndef __puzzle_test_02__puzzle_manager__
#define __puzzle_test_02__puzzle_manager__

#include <stdio.h>
#include "section.h"
#include "block.h"

class PuzzleManager {
    // 選択中のブロックがあるか
    int state_choice;
public:
    PuzzleManager();
    // パズル生成
    void CreatePuzzle(Section* sections, Block* blocks, Config* config);
    // 設定に従い区画を並べる
    //void InitializeSection(Section* sections, Config* config);
    // 設定に従いブロックを並べる
    //void InitializeBlock(Block* blocks, Config* config);
    // 左クリックを押した。座標から選択されたブロックを探してactiveにする
    void ChoiceBlock(Section* sections, Block* blocks, Config* config, double event_button_x, double event_button_y);
    // 左クリックを離した。座標からブロック位置をパズル区画内に補正する
    void ReleaseBlock(Section* sections, Block* blocks, Config* config, double event_button_x, double event_button_y);
    // ブロックを操作
    void MoveBlock(Section* sections, Block* blocks, Config* config, double event_button_x, double event_button_y);
    // 座標からブロックを見つける
    int LookForPositionBlock(Section* sections, Block* blocks, Config* config, double event_button_x, double event_button_y);
    // 操作中のブロックを見つける
    int LookForActiveBlock(Block* blocks, Config* config);
    // ゲッター
    int GetStateChoice();
    int GetTargetSection();
};

#endif /* defined(__puzzle_test_02__puzzle_manager__) */
