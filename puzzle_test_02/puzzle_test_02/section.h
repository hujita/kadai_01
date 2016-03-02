// 区画

//  section.h
//  puzzle_test_02
//
//  Created by hujita on 2016/03/01.
//  Copyright (c) 2016年 hujita. All rights reserved.
//
// パズルの区画
// これが並んでパズルのボードになる。1区画につき1ブロックを持つ。

#ifndef __puzzle_test_02__section__
#define __puzzle_test_02__section__

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "config.h"
#include "settings.h"

class Section {
    // 出力元
    // 座標 & 高さ &幅
    double source_x;
    double source_y;
    double source_h;
    double source_w;
    // 出力先座標
    double destination_x;
    double destination_y;
public:
    Section();
    void Initialize(int i, int j, int cnt, Config* config);
    // 区画描画
    void Draw(SDL_Surface* screen, SDL_Surface* section_image);
    // Getter
    double GetDestinationX();
    double GetDestinationY();
};

#endif /* defined(__puzzle_test_02__section__) */
