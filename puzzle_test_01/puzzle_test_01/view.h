//
//  view.h
//  puzzle_test_01
//
//  Created by hujita on 2016/02/23.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#ifndef __puzzle_test_01__view__
#define __puzzle_test_01__view__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <boost/format.hpp>
#include <boost/random.hpp>
#include <vector>

class View {
    // 画面遷移用変数(TOP:0, PLAY:1)
    int view_type;
    // 設定画面フェイズ
    //int config_phase;
    // 行数
    //int line;
    // 列数
    //int row;
    // ブロック種類数
    //int type;
    // 必要連結数
    //int chain;
    // 選択中のブロック
    //int current_block_index;
    // 画面
    SDL_Window* window;
    // 画面の描画領域
    SDL_Surface* screen;
    // 背景画像
    SDL_Surface* background_image;
    // ブロック画像
    SDL_Surface* puzzle_block;
    // 設定画面メインテキスト
    //SDL_Surface* word_main;
    // 設定画面サブテキスト(質問文)
    //SDL_Surface* word_sub;
    // 設定画面入力内容テキスト
    //SDL_Surface* word_input;
    // 設定画面質問テキスト
    //SDL_Surface* word_0;
    // 設定画面質問テキスト
    //SDL_Surface* word_1;
    // 設定画面質問テキスト
    //SDL_Surface* word_2;
    // 設定画面質問テキスト
    //SDL_Surface* word_3;
    // 設定画面質問テキスト
    //SDL_Surface* word_4;
    /// フォント
    TTF_Font* font;
    // 色
    //SDL_Color white;
    // メインテキスト描画位置
    //SDL_Rect destrect_main_word;
    // サブテキスト描画位置
    //SDL_Rect destrect_sub_word;
    // 入力内容描画位置
    //SDL_Rect destrect_input_word;
    
    //void DrawBlock(int index);
public:
    // クラス初期化
    View();
    // 画面初期化
    int Initialize();
    void Finalize();
    void MainLoop();
    // 背景描画
    void DrawBackGround();
    // 画面描画
    void Draw();
    // TOP画面
    void DrawTop();
    // PLAY画面
    void DrawPlay();
    TTF_Font* GetFont();
    SDL_Window* GetWindow();
    SDL_Surface* GetScreen();
    SDL_Surface* GetBackgroundImage();
    SDL_Surface* GetPuzzleBlock();
    void SetViewType(int value);
    int GetViewType();
};

#endif /* defined(__puzzle_test_01__view__) */
