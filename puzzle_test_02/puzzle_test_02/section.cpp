//
//  section.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/03/01.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "section.h"

Section::Section(){
    // 出力元
    // 座標 & 高さ &幅
    source_x = SECTION_SOURCE_X;
    source_y = SECTION_SOURCE_Y;
    source_h = SECTION_HIGH;
    source_w = SECTION_WIDE;
    // 出力先座標
    destination_x = 0;
    destination_y = 0;
    // 種別(上下左右が行き止まり #=> 0000, 上下左右にまだブロックがある #=> 1111)
}

// 区画生成
// [param] i:行番号, j:列番号, cnt:整列番号, config: 設定インスタンス
// [return] Section
void Section::Initialize(int i, int j, int cnt, Config* config){
    // 出力元
    // 座標 & 高さ &幅
    //source_x = position[0];
    //source_y = position[1];
    //source_h = BLOCK_HIGH;
    //source_w = BLOCK_WIDE;
    // 出力先座標
    destination_x = (SECTION_WIDE * j);
    destination_y = (SECTION_HIGH * i);
}

// 区画描画
void Section::Draw(SDL_Surface* screen, SDL_Surface* section_image){
    SDL_Rect srcrect;
    SDL_Rect desrect = { (int)destination_x, (int)destination_y };
    
    srcrect.x = source_x;
    srcrect.y = source_y;
    srcrect.w = source_w;
    srcrect.h = source_h;
    
    SDL_BlitSurface(section_image, &srcrect, screen, &desrect);
}

// Getter
double Section::GetDestinationX(){
    return destination_x;
}

double Section::GetDestinationY(){
    return destination_y;
}

// Setter
void Section::SetDestinationX(double x){
    destination_x = x;
}
void Section::SetDestinationY(double y){
    destination_y = y;
}