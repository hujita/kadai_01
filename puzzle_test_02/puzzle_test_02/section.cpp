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
}

// 区画生成
void Section::Initialize(int i, int j, int cnt, Config* config){
    // 出力先座標
    destination_x = (SECTION_WIDE * i);
    destination_y = (SECTION_HIGH * j);
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
double Section::GetDestinationX(){ return destination_x; }
double Section::GetDestinationY(){ return destination_y; }
