//
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
#include "my_keyboard.h"
#include "block.h"
#include "puzzle.h"
#include "puzzle_manager.h"

class Game {
    // 画面遷移用変数(TOP:0, PLAY:1)
    int view_type;
    // 設定画面フェイズ
    int config_phase;
    // 行数
    int line;
    // 列数
    int row;
    // ブロック種類数
    int type;
    // 必要連結数
    int chain;

    // 画面
    SDL_Window* window;
    // 画面の描画領域
    SDL_Surface* screen;
    // 背景画像
    SDL_Surface* background_image;
    // 区画画像
    SDL_Surface* section_image;
    // ブロック画像
    SDL_Surface* block_image;
    // 設定画面メインテキスト
    SDL_Surface* word_main;
    // 設定画面サブテキスト(質問文)
    SDL_Surface* word_sub;
    // 設定画面入力内容テキスト
    SDL_Surface* word_input;
    /// フォント
    TTF_Font* font;
    // 色
    SDL_Color white;
    // メインテキスト描画位置
    SDL_Rect destrect_main_word;
    // サブテキスト描画位置
    SDL_Rect destrect_sub_word;
    // 入力内容描画位置
    SDL_Rect destrect_input_word;
public:
    // クラス初期化
    Game();
    // ゲーム開始
    int Start();
    // ゲーム初期化
    int Initialize();
    // 終了処理
    void Finalize();
    // メイン処理
    void MainLoop();
    // 描画処理
    void Draw(Config* config, Section* sectinos, Block* block);
    //void Draw(int config_state, int line, int row, int type, int chain);
};

#endif /* defined(__puzzle_test_02__game__) */
