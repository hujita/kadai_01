// TOP画面

//  top.h
//  puzzle_test_02
//
//  Created by hujita on 2016/03/02.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#ifndef __puzzle_test_02__top__
#define __puzzle_test_02__top__

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "config.h"
#include "puzzle_manager.h"
#include "section.h"
#include "block.h"
#include "my_keyboard.h"

class Top {
    // 移動差分
    double x_move_difference;
    // 移動量
    double x_move_amount;
    // TOP画面メインテキスト(案内)
    SDL_Surface* word_main;
    // TOP画面サブテキスト(質問)
    SDL_Surface* word_sub;
    // TOP画面入力内容テキスト
    SDL_Surface* word_input;
    // 色
    SDL_Color black;
    // メインテキスト描画位置
    SDL_Rect destrect_main_word;
    // サブテキスト描画位置
    SDL_Rect destrect_sub_word;
    // 入力内容描画位置
    SDL_Rect destrect_input_word;
public:
    Top();
    // イベント処理
    int Event(SDL_Event* event, Config* config, PuzzleManager* puzzle_manager, Section* sections, Block* blocks);
    // 描画処理
    void Draw(SDL_Surface* screen, SDL_Surface* section_image, SDL_Surface* block_image, Config* config, TTF_Font* font, TTF_Font* big_font);
};

#endif /* defined(__puzzle_test_02__top__) */
