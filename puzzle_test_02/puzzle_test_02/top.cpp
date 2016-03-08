//
//  top.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/03/02.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "top.h"

Top::Top() {
    // 移動差分
    x_move_difference = 0;
    x_move_amount = MOVE_AMOUNT;
    // 設定画面メインテキスト
    word_main = NULL;
    // 設定画面サブテキスト
    word_sub = NULL;
    // 設定画面入力内容テキスト
    word_input = NULL;
    // 色
    black = {0x00, 0x00, 0x00};
    // メインテキスト(案内)描画位置
    destrect_main_word = { 300, 210 };
    // サブテキスト(質問)描画位置
    destrect_sub_word = { 300, 310 };
    // 入力内容描画位置
    destrect_input_word = { 300, 390 };
}

int Top::Event(SDL_Event* event, Config* config, PuzzleManager* puzzle_manager, Section* sections, Block* blocks) {
    // TOP画面での入力が完了したか
    int view_next = OFF;
    // キーボード入力変換機
    MyKeyboard my_keyboard;
    
    // キーボード操作
    if (event->type == SDL_KEYDOWN){
        // 数値キーなら数値に変換
        int input_value = my_keyboard.CastIntFromKey(event->key.keysym.sym);
        
        // ゲームの設定値更新
        if (input_value < 10){
            config->Set(input_value);
        }
        // エンターキーなら
        if (event->key.keysym.sym == SDLK_RETURN){
            // 設定が終了しているなら
            if (config->FlagFinish() == ON) {
                // パズル生成
                puzzle_manager->CreatePuzzle(sections, blocks, config);
                // PLAY画面へ遷移
                view_next = ON;
            }
            // 設定が終了していないなら
            if (config->FlagFinish() == OFF){
                // 設定フェイズの更新
                config->UpdateState();
            }
        }
    }
    
    return view_next;
}

void Top::Draw(SDL_Surface* screen, SDL_Surface* section_image, SDL_Surface* block_image, Config* config, TTF_Font* font, TTF_Font* big_font){
    // TOP画面背景用の区画描画
    int i;
    int j;
    for (i = 0; i < CONFIG_LINE_MAX; ++i) {
        for (j = 0; j < CONFIG_ROW_MAX; ++j) {
            SDL_Rect srcrect;
            SDL_Rect desrect = { i * SECTION_WIDE, j * SECTION_HIGH + 10 };
            SDL_Rect desrect_move = { (int)(i * SECTION_WIDE + x_move_difference), (int)(j * SECTION_HIGH + 10) };
            
            srcrect.x = SECTION_SOURCE_X;
            srcrect.y = SECTION_SOURCE_Y;
            srcrect.w = SECTION_WIDE;
            srcrect.h = SECTION_HIGH;
            
            if (j >= 8 || (i + j) >= 21) {
                SDL_BlitSurface(section_image, &srcrect, screen, &desrect);
            }
            if (i == 0 && j == 7){
                SDL_BlitSurface(section_image, &srcrect, screen, &desrect_move);
            }
        }
    }
    
    // TOP画面背景用のブロック描画
    int block_i;
    int block_j;
    for (block_i = 0; block_i < CONFIG_LINE_MAX; ++block_i) {
        for (block_j = 0; block_j < CONFIG_ROW_MAX; ++block_j) {
            SDL_Rect srcrect;
            SDL_Rect desrect = { block_i * SECTION_WIDE + SECTION_SPACE_WIDE, block_j * SECTION_HIGH + SECTION_SPACE_HIGH + 10 };
            SDL_Rect desrect_move = { (int)(block_i * SECTION_WIDE + SECTION_SPACE_WIDE + x_move_difference), block_j * SECTION_HIGH + SECTION_SPACE_HIGH + 10 };
            
            srcrect.x = BLOCK_POSITION_00_X;
            srcrect.y = BLOCK_POSITION_00_Y;
            srcrect.w = BLOCK_WIDE;
            srcrect.h = BLOCK_HIGH;
            
            if (block_j >=  8 || (block_i + block_j) >= 21) {
                SDL_BlitSurface(block_image, &srcrect, screen, &desrect);
            }
            if (block_i == 0 && block_j == 7){
                SDL_BlitSurface(block_image, &srcrect, screen, &desrect_move);
            }
        }
    }
    
    MyText my_text;
    // メインテキスト用意
    word_main = TTF_RenderUTF8_Blended(big_font, my_text.GetConfigMain(), black);
    // サブテキスト用意
    word_sub = TTF_RenderUTF8_Blended(font, config->GetQuestion(), black);
    // 入力内容表示テキスト用意
    char buf[150];
    sprintf(buf, my_text.GetConfigInputResult(),
            config->GetLine(), config->GetRow(), config->GetType(), config->GetChain());
    word_input = TTF_RenderUTF8_Blended(font, buf, black);
    
    // メインテキスト描画
    SDL_BlitSurface(word_main, NULL, screen, &destrect_main_word);
    // サブテキスト描画
    SDL_BlitSurface(word_sub, NULL, screen, &destrect_sub_word);
    // 入力内容表示テキスト描画
    SDL_BlitSurface(word_input, NULL, screen, &destrect_input_word);
    
    
    
    if (x_move_difference >= WINDOW_WIDE / CONFIG_LINE_MAX * 13) {
        x_move_amount = -MOVE_AMOUNT;
    }
    if (x_move_difference <= 0) {
        x_move_amount = MOVE_AMOUNT;
    }
    x_move_difference += x_move_amount;
}
