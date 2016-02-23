//
//  Initialize.cpp
//  puzzle_test_01
//
//  Created by hujita on 2016/02/23.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "Initialize.h"

int Initialize::Execute(void)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
        fprintf(stderr, "SDLの初期化に失敗しました：%s\n", SDL_GetError());
        return -1;
    }
    if (TTF_Init() < 0) {
        fprintf(stderr, "TTFの初期化に失敗しました：%s\n", TTF_GetError());
        return -1;
    }
    
    window = SDL_CreateWindow("パズルゲーム", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1000,850,0);
    screen = SDL_GetWindowSurface(window);
    if (screen == NULL) {
        fprintf(stderr, "画面の初期化に失敗しました：%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    
    /* 画像を読み込む */
    background_image = IMG_Load("background.gif");
    if (background_image == NULL) {
        fprintf(stderr, "画像の読み込みに失敗しました：%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    puzzle_block = IMG_Load("puzzle_block.jpg");
    if (puzzle_block == NULL) {
        fprintf(stderr, "画像の読み込みに失敗しました：%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    
    /* フォント読み込み */
    font = TTF_OpenFont("AquaKana.ttc", 24);
    if (font == NULL) {
        fprintf(stderr, "fontの取得に失敗しました：%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    
    /* 文字作成 */
    word_main = TTF_RenderUTF8_Blended(font, "パズルの設定(1~9で入力)", white);
    word_0 = TTF_RenderUTF8_Blended(font, "行数を指定してください", white);
    word_1 = TTF_RenderUTF8_Blended(font, "列数を指定してください", white);
    word_2 = TTF_RenderUTF8_Blended(font, "ブロックの種類数を指定してください", white);
    word_3 = TTF_RenderUTF8_Blended(font, "ブロックを繋げるべき数を指定してください", white);
    word_4 = TTF_RenderUTF8_Blended(font, "Enter:ゲーム開始 / 右Shift:TOPに戻る / ESC:終了", white);
    
    return 0;
}