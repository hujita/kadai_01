//
//  view_top.h
//  puzzle_test_01
//
//  Created by hujita on 2016/02/23.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#ifndef __puzzle_test_01__view_top__
#define __puzzle_test_01__view_top__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <boost/format.hpp>
#include <boost/random.hpp>
#include <vector>

class ViewTop {
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
    // 設定画面メインテキスト
    SDL_Surface* word_main;
    // 設定画面サブテキスト(質問文)
    SDL_Surface* word_sub;
    // 設定画面入力内容テキスト
    SDL_Surface* word_input;
    // 色
    SDL_Color white;
    // メインテキスト描画位置
    SDL_Rect destrect_main_word;
    // サブテキスト描画位置
    SDL_Rect destrect_sub_word;
    // 入力内容描画位置
    SDL_Rect destrect_input_word;
    
    void DrawBlock(int index);
public:
    // クラス初期化
    ViewTop();
    // 画面初期化
    int Initialize(View* view);
    // 設定初期化
    void InitializeConfig();
    // TOP画面描画
    void Draw(View* view);
    // 設定入力
    void ConfigInput(int qty);
    // 画面描画
    void DrawView();
    // TOP画面
    void DrawTop();
    // PLAY画面
    void DrawPlay();
    // 設定画面フェイズ取得
    int GetConfigPhase();
    // 行数
    int GetLine();
    // 列数
    int GetRow();
};

#endif /* defined(__puzzle_test_01__view_top__) */
