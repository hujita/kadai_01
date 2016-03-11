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
#include <SDL_mixer.h>
#include <stdio.h>
#include <boost/timer.hpp>
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
    SDL_Surface* section_image_02;
    // ブロック画像
    SDL_Surface* block_image;
    // 粒子画像
    SDL_Surface* particle_image;
    /// フォント
    TTF_Font* font;
    /// フォント
    TTF_Font* big_font;
    // BGM
    Mix_Music* music_main;
    Mix_Chunk* music_break;
    // ゲーム初期化処理
    int Initialize();
    // 終了処理
    void Finalize();
    // メイン処理
    void MainLoop();
    // 描画処理
    void Draw(Config* config, Section* sectinos, Top* top, Play* play, PuzzleManager* puzzle_manager, Block* block, boost::timer* t);
    // 描画更新
    void Update(Config* config, PuzzleManager* puzzle_manager, Section* sectinos, Top* top, Play* play, Block* block);
public:
    // クラス初期化
    Game();
    // ゲーム開始
    int Start();
};

#endif /* defined(__puzzle_test_02__game__) */
