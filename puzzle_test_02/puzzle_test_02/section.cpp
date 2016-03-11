//
//  section.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/03/01.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "section.h"

Section::Section():
// 出力元
// 座標 & 高さ &幅
source_x(SECTION_SOURCE_X),
source_y(SECTION_SOURCE_Y),
source_h(SECTION_HIGH),
source_w(SECTION_WIDE),
// 出力先座標
destination_x(0),
destination_y(0),
exist(ON)
{}

// 区画生成
void Section::Initialize(int i, int j, int cnt, Config* config){
    // パズル全体を中央に寄せる
    int x_center_difference = (WINDOW_WIDE / 2) - (((WINDOW_WIDE / 2) / CONFIG_LINE_MAX) * config->GetLine());
    int y_center_difference = (WINDOW_HIGH / 2) - (((WINDOW_HIGH / 2) / CONFIG_ROW_MAX) * config->GetRow());
    
    // 出力先座標
    destination_x = (SECTION_WIDE * i + x_center_difference);
    destination_y = (SECTION_HIGH * j + y_center_difference);
}

// 区画描画
void Section::Draw(SDL_Surface* screen, SDL_Surface* section_image, SDL_Surface* section_image_02, Config* config){
    SDL_Rect srcrect;
    SDL_Rect desrect = { (int)(destination_x) , (int)(destination_y) };
    
    srcrect.x = source_x;
    srcrect.y = source_y;
    srcrect.w = source_w;
    srcrect.h = source_h;
    
    if (exist == ON){
        SDL_BlitSurface(section_image, &srcrect, screen, &desrect);
    }
    if (exist == OFF){
        SDL_BlitSurface(section_image_02, &srcrect, screen, &desrect);
    }
    
    
}

// Getter
double Section::GetDestinationX(){ return destination_x; }
double Section::GetDestinationY(){ return destination_y; }
// Setter
void Section::SetExist(int value){ exist = value; }
