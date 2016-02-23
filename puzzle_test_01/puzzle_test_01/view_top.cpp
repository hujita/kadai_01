//
//  view_top.cpp
//  puzzle_test_01
//
//  Created by hujita on 2016/02/23.
//  Copyright (c) 2016年 hujita. All rights reserved.
//
// TOP画面クラス

#include "view.h"
#include "view_top.h"

// クラス初期化
ViewTop::ViewTop() {
    // 画面遷移用変数(TOP:0, PLAY:1)
    //view_type = 0;
    // 設定画面フェイズ
    config_phase = 0;
    // 行数
    line = 0;
    // 列数
    row = 0;
    // ブロック種類数
    type = 0;
    // 必要連結数
    chain = 0;
    // 選択中のブロック
    //current_block_index = 999;
    
    // 画面
    //window = NULL;
    // 画面の描画領域
    //screen = NULL;
    // 背景画像
    //background_image = NULL;
    // ブロック画像
    //puzzle_block = NULL;
    // 設定画面メインテキスト
    word_main = NULL;
    // 設定画面サブテキスト
    word_sub = NULL;
    // 設定画面入力内容テキスト
    word_input = NULL;
    // 設定画面質問テキスト
    //word_0 = NULL;
    // 設定画面質問テキスト
    //word_1 = NULL;
    // 設定画面質問テキスト
    //word_2 = NULL;
    // 設定画面質問テキスト
    //word_3 = NULL;
    // 設定画面質問テキスト
    //word_4 = NULL;
    // フォント
    //font = NULL;
    // 色
    white = {0xff, 0xff, 0xff};
    // メインテキスト描画位置
    destrect_main_word = { 330, 210 };
    // サブテキスト描画位置
    destrect_sub_word = { 330, 310 };
    // 入力内容描画位置
    destrect_input_word = { 330, 410 };
}

// 設定初期化
void ViewTop::InitializeConfig(){
    // 設定画面フェイズ
    config_phase = 0;
    // 行数
    line = 0;
    // 列数
    row = 0;
    // ブロック種類数
    type = 0;
    // 必要連結数
    chain = 0;
}

void ViewTop::ConfigInput(int qty){
    switch (config_phase){
        case 0:
            line = qty;
            break;
        case 1:
            row = qty;
            break;
        case 2:
            type = qty;
            break;
        case 3:
            chain = qty;
            break;
    }
    ++config_phase;
}

// TOP画面描画
void ViewTop::Draw(View* view){
    TTF_Font* font = view->GetFont();
    SDL_Surface* screen = view->GetScreen();
    // メインテキスト描画
    SDL_Surface* word_main = TTF_RenderUTF8_Blended(font, "パズルの設定(1~9で入力)", white);
    SDL_BlitSurface(word_main, NULL, screen, &destrect_main_word);
    // サブテキスト描画
    switch (config_phase) {
        case 0:
            word_sub = TTF_RenderUTF8_Blended(font, "行数を指定してください", white);
            break;
        case 1:
            word_sub = TTF_RenderUTF8_Blended(font, "列数を指定してください", white);
            break;
        case 2:
            word_sub = TTF_RenderUTF8_Blended(font, "ブロックの種類数を指定してください", white);
            break;
        case 3:
            word_sub = TTF_RenderUTF8_Blended(font, "ブロックを繋げるべき数を指定してください", white);
            break;
        case 4:
            word_sub = TTF_RenderUTF8_Blended(font, "Enter:ゲーム開始 / 右Shift:TOPに戻る / ESC:終了", white);
            break;
    }
    SDL_BlitSurface(word_sub, NULL, screen, &destrect_sub_word);
    // 入力内容表示テキスト描画
    char buf[50];
    sprintf(buf, "行数：%d  列数：%d  ブロック：%d  連鎖：%d", line, row, type, chain);
    word_input = TTF_RenderUTF8_Blended(font, buf, white);
    SDL_BlitSurface(word_input, NULL, screen, &destrect_input_word);
}

int ViewTop::GetConfigPhase(){
    return config_phase;
}