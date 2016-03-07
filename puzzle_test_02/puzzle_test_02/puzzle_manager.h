// パズル進行役

//  puzzle_manager.h
//  puzzle_test_02
//
//  Created by hujita on 2016/03/01.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#ifndef __puzzle_test_02__puzzle_manager__
#define __puzzle_test_02__puzzle_manager__

#include <stdio.h>
#include <vector>
#include "section.h"
#include "block.h"

class PuzzleManager {
    // 得点
    int score;
    // 選択中のブロックがあるか
    int state_choice;
    // ブロック落下中か
    int state_drop;
    // ブロックの消滅から次の連鎖発生までの停止時間
    int freeze;
    // 真下のブロックが同種か確認
    int CheckRowChain(Config* config, Block* blocks, int before_index);
    // 右横のブロックが同種か確認
    int CheckLineChain(Config* config, Block* blocks, int before_index);
    // 座標からブロックを見つける
    int LookForPositionBlock(Section* sections, Block* blocks, Config* config, double event_button_x, double event_button_y);
    // 操作中のブロックを見つける
    int LookForActiveBlock(Block* blocks, Config* config);
public:
    PuzzleManager();
    // パズル生成
    void CreatePuzzle(Section* sections, Block* blocks, Config* config);
    // 連鎖成立確認
    void CheckChain(Config* config, Block* blocks);
    // 落下成立確認
    void CheckDrop(Config* config, Block* blocks);
    // 落下描画済みか確認
    int FlagAllDropDrawn(Config* config, Block* blocks);
    // 落下させる
    void AllDrop(Config* config, Block* blocks);
    // 落下
    void DropBlock(Config* config, Section* sections,Block* blocks);
    // ブロックの再生
    void ReCreate(Config* config, Block* blocks);
    // 左クリックを押した。座標から選択されたブロックを探してactiveにする
    void ChoiceBlock(Section* sections, Block* blocks, Config* config, double event_button_x, double event_button_y);
    // 左クリックを離した。操作中のブロックを解放する
    void ReleaseBlock(Section* sections, Block* blocks, Config* config, double event_button_x, double event_button_y);
    // マウスを動かした。ブロックを操作
    void MoveBlock(Section* sections, Block* blocks, Config* config, double event_button_x, double event_button_y);
    void AddFreeze(int value);
    void ResetScore();
    // Getter
    int GetStateChoice();
    int GetFreeze();
    int GetScore();
};

#endif /* defined(__puzzle_test_02__puzzle_manager__) */
