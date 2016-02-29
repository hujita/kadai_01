//
//  block.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/02/25.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "block.h"

Block::Block(){
    // 出力元
    // 座標 & 高さ &幅
    source_x = 0;
    source_y = 0;
    source_h = BLOCK_HIGH;
    source_w = BLOCK_WIDE;
    // 出力先座標
    destination_x = 0;
    destination_y = 0;
    // ブロック種別
    block_type = 0;
    // 現在位置している区画(整列番号)
    section = 0;
    // 生存
    alive = 0;
    // アクティブ(マウス左クリックで選択されている)
    active = 0;
    // 出力先座標とマウスポインタ座標の誤差(アクティブ時のみ使用)
    x_difference = 0;
    y_difference = 0;
}

// ブロック生成
// [param] i:行番号, j:列番号, cnt:整列番号, config: 設定インスタンス
// [return] Block
void Block::Initialize(int i, int j, int cnt, Config* config){
    MyMath my_math;
    
    // ブロック種別
    block_type = my_math.Random(0, config->GetType() - 1, cnt);
    // 出力元
    // 座標 & 高さ &幅
    int position[2] = {};
    SetSourcePosition(block_type, position);
    source_x = position[0];
    source_y = position[1];
    source_h = BLOCK_HIGH;
    source_w = BLOCK_WIDE;
    // 出力先座標
    destination_x = (SECTION_WIDE * j);
    destination_y = (SECTION_HIGH * i);
    // 現在位置している区画(整列番号)
    section = cnt;
    // 生存
    alive = 0;
    // アクティブ(マウス左クリックで選択されている)
    active = 0;
    // 出力先座標とマウスポインタ座標の誤差(アクティブ時のみ使用)
    x_difference = 0;
    y_difference = 0;
}

// 出力元画像の座標を取得
void Block::SetSourcePosition(int block_type, int* position){
    switch (block_type) {
        case 0:
            position[0] = BLOCK_POSITION_00_X;
            position[1] = BLOCK_POSITION_00_Y;
            break;
        case 1:
            position[0] = BLOCK_POSITION_01_X;
            position[1] = BLOCK_POSITION_01_Y;
            break;
        case 2:
            position[0] = BLOCK_POSITION_02_X;
            position[1] = BLOCK_POSITION_02_Y;
            break;
        case 3:
            position[0] = BLOCK_POSITION_03_X;
            position[1] = BLOCK_POSITION_03_Y;
            break;
        case 4:
            position[0] = BLOCK_POSITION_04_X;
            position[1] = BLOCK_POSITION_04_Y;
            break;
        case 5:
            position[0] = BLOCK_POSITION_05_X;
            position[1] = BLOCK_POSITION_05_Y;
            break;
        case 6:
            position[0] = BLOCK_POSITION_06_X;
            position[1] = BLOCK_POSITION_06_Y;
            break;
        case 7:
            position[0] = BLOCK_POSITION_07_X;
            position[1] = BLOCK_POSITION_07_Y;
            break;
        case 8:
            position[0] = BLOCK_POSITION_08_X;
            position[1] = BLOCK_POSITION_08_Y;
            break;
        default:
            break;
    }
}

void Block::Draw(SDL_Surface* screen, SDL_Surface* block_image){
    SDL_Rect srcrect;
    SDL_Rect desrect = { (int)destination_x, (int)destination_y };
    if (active == ON){
        desrect = { (int)(destination_x - x_difference), (int)(destination_y - y_difference) };
    }

    srcrect.x = source_x;
    srcrect.y = source_y;
    srcrect.w = source_w;
    srcrect.h = source_h;

    SDL_BlitSurface(block_image, &srcrect, screen, &desrect);
}

int Block::GetActive() {
    return active;
}