//
//  Initialize.h
//  puzzle_test_01
//
//  Created by hujita on 2016/02/23.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#ifndef __puzzle_test_01__Initialize__
#define __puzzle_test_01__Initialize__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <boost/format.hpp>
#include <boost/random.hpp>
#include <vector>

#define MAX_BLOCK_TYPE_COUNT 9
#define MAX_BLOCK_COUNT 90

class Initialize {
    SDL_Window* window = NULL;                  /* 画面 */
    SDL_Surface* screen = NULL;                 /* 画面の描画領域 */
    SDL_Surface* background_image = NULL;       /* 背景画像 */
    SDL_Surface* puzzle_block = NULL;           /* ブロック画像 */
    
    SDL_Surface* word_main = NULL;              /* メインテキスト */
    SDL_Surface* word_sub = NULL;               /* サブテキスト */
    SDL_Surface* word_input = NULL;             /* 入力内容テキスト */
    SDL_Surface* word_0 = NULL;                 /* 設定テキスト */
    SDL_Surface* word_1 = NULL;                 /* 設定テキスト */
    SDL_Surface* word_2 = NULL;                 /* 設定テキスト */
    SDL_Surface* word_3 = NULL;                 /* 設定テキスト */
    SDL_Surface* word_4 = NULL;                 /* 設定テキスト */
    
    TTF_Font* font;                             /* フォント */
    SDL_Color white = {0xff, 0xff, 0xff};       /* 色 */
    SDL_Rect destrect_main_word = { 330, 210 }; /* コメント位置 */
    SDL_Rect destrect_sub_word = { 330, 310 };  /* サブコメント位置 */
    SDL_Rect destrect_input_word = { 330, 410 };  /* 入力内容表示位置 */
    
public:
    int Execute();
};

#endif /* defined(__puzzle_test_01__Initialize__) */
