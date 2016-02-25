//
//  view_play.h
//  puzzle_test_01
//
//  Created by hujita on 2016/02/23.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#ifndef __puzzle_test_01__view_play__
#define __puzzle_test_01__view_play__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <boost/format.hpp>
#include <boost/random.hpp>
#include <vector>
#include "block.h"
#include "view.h"
#include "view_top.h"

class ViewPlay {
    // ブロックの配列(9*9=81)
    //Block blocks[81];
    // 操作対象ブロック
    int current_block_index;
    double current_block_x;
    double current_block_y;
    double current_block_x_diff;
    double current_block_y_diff;
public:
    // クラス初期化
    ViewPlay();
    // ブロック初期配置
    void InitializePuzzle(int line, int row);
    // PLAY画面描画
    void Draw(View* view, ViewTop* view_top, Block* blocks);
    double GetCurrentBlockX();
    double GetCurrentBlockY();
    double GetCurrentBlockXDiff();
    double GetCurrentBlockYDiff();
    // 画面初期化
    //int Initialize(View* view);
    // 設定初期化
    //void InitializeConfig();
    // TOP画面描画
   // void Draw(View* view);
    // 設定入力
    //void ConfigInput(int qty);
    // 画面描画
    //void DrawView();
    // TOP画面
    //void DrawTop();
    // PLAY画面
    //void DrawPlay();
    // 設定画面フェイズ取得
    //int GetConfigPhase();
};

#endif /* defined(__puzzle_test_01__view_play__) */
