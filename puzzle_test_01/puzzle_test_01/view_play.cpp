//
//  view_play.cpp
//  puzzle_test_01
//
//  Created by hujita on 2016/02/23.
//  Copyright (c) 2016年 hujita. All rights reserved.
//
// プレイ画面クラス

#include "view_play.h"
#include "view.h"
#include "view_top.h"
#include "block.h"

// クラス初期化
ViewPlay::ViewPlay() {
    // ブロックの配列
    //blocks[81] = {};
    // 操作対象ブロック
    current_block_index = 999;
    current_block_x = 0;
    current_block_y = 0;
    current_block_x_diff = 0;
    current_block_y_diff = 0;
}

// ブロックの初期配置
/*void ViewPlay::InitializePuzzle(int line, int row){
    int i;
    int j;
    int cnt = 0;
    for (i = 0; i < line; ++i){
        for (j = 0; j < row; ++j){
            Block block;
            block.Create(i, j, cnt);
            blocks[cnt] = block;
            ++cnt;
        }
    }
}*/

void ViewPlay::Draw(View* view, ViewTop* view_top, Block* blocks){
    //SDL_Surface* screen = view->GetScreen();
    // ブロックを描画する
    int i;
    //SDL_BlitSurface(view->puzzle_block, NULL, screen, NULL);
    for (i = 0; i < view_top->GetLine() * view_top->GetRow(); ++i) {
        if (i != current_block_index)
            blocks[i].Draw(this, false);
    }
    if (current_block_index != 999)
        //DrawBlock(current_block_index);
        blocks[current_block_index].Draw(this, true);

    //SDL_BlitSurface(word_input, NULL, screen, &destrect_input_word);
}

double ViewPlay::GetCurrentBlockX(){
    return current_block_x;
}

double ViewPlay::GetCurrentBlockXDiff(){
    return current_block_x_diff;
}

double ViewPlay::GetCurrentBlockY(){
    return current_block_y;
}

double ViewPlay::GetCurrentBlockYDiff(){
    return current_block_y_diff;
}
/*
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
*/