// ゲーム支配人

//  game.h
//  puzzle_test_02
//
//  Created by hujita on 2016/02/24.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#ifndef __puzzle_test_02__game__
#define __puzzle_test_02__game__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "settings.h"
#include "config.h"
#include "puzzle_manager.h"
#include "block.h"
#include "top.h"
#include "play.h"

class Game {
    // 画面遷移用変数(TOP:0, PLAY:1)
    int view_type;

    // 画面
    SDL_Window* window;
    // 画面の描画領域
    SDL_Surface* screen;
    // 区画画像
    SDL_Surface* section_image;
    // ブロック画像
    SDL_Surface* block_image;
    /// フォント
    TTF_Font* font;
    
    // ゲーム初期化処理
    int Initialize();
    // 終了処理
    void Finalize();
    // メイン処理
    void MainLoop();
    // 描画処理
    void Draw(Config* config, Section* sectinos, Top* top, Play* play, Block* block);
public:
    // クラス初期化
    Game();
    // ゲーム開始
    int Start();
};

#endif /* defined(__puzzle_test_02__game__) */
