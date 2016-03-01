//
//  block.h
//  puzzle_test_02
//
//  Created by hujita on 2016/02/25.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#ifndef __puzzle_test_02__block__
#define __puzzle_test_02__block__

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "settings.h"
#include "config.h"
#include "my_math.h"

class Block {
    // 出力元
    // 座標 & 高さ &幅
    double source_x;
    double source_y;
    double source_h;
    double source_w;
    // 出力先座標
    double destination_x;
    double destination_y;
    // ブロック種別
    int block_type;
    // 現在位置している区画(整列番号)
    int section;
    // 生存
    int alive;
    // アクティブ(選択されている)
    int active;
    // 出力先座標とマウスポインタ座標の誤差(アクティブ時のみ使用)
    double x_difference;
    double y_difference;
    // ブロックのクリックされている座標
    double current_position_x;
    double current_position_y;
public:
    Block();
    void Initialize(int i, int j, int cnt, Config* config);
    void SetSourcePosition(int type_block, int* position);
    void Draw(SDL_Surface* screen, SDL_Surface* block_image);
    /* void Draw(SDL_Surface* screen, SDL_Surface* block_image, double click_x, double click_y); */
    // ブロックをactiveにして操作対象にする。座標誤差値も更新する
    void Choice(double event_button_x, double event_button_y);
    // ブロックを解放して操作対象ではなくする。
    void Release();
    // ブロックの移動による座標の更新
    void Move(double event_button_x, double event_button_y);
    // ゲッター
    int GetActive();
    double GetDestinationX();
    double GetDestinationY();
    int GetTargetSection();
    // セッター
    void SetDestinationX(double x);
    void SetDestinationY(double y);
    void SetSection(int value);
};

#endif /* defined(__puzzle_test_02__block__) */
