//
//  top.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/03/02.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "top.h"

Top::Top() {
    // 設定画面メインテキスト
    word_main = NULL;
    // 設定画面サブテキスト
    word_sub = NULL;
    // 設定画面入力内容テキスト
    word_input = NULL;
    // 色
    black = {0x00, 0x00, 0x00};
    // メインテキスト(案内)描画位置
    destrect_main_word = { 330, 210 };
    // サブテキスト(質問)描画位置
    destrect_sub_word = { 330, 310 };
    // 入力内容描画位置
    destrect_input_word = { 330, 410 };
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
        if (input_value > 0 && input_value < 10){
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

void Top::Draw(SDL_Surface* screen, Config* config, TTF_Font* font){
    // メインテキスト用意
    word_main = TTF_RenderUTF8_Blended(font, "パズルの設定", black);
    // サブテキスト用意
    //char buff = *config->GetQuestion();
    //std::cout << "kkk" << config->GetQuestion() << std::endl;
    word_sub = TTF_RenderUTF8_Blended(font, config->GetQuestion(), black);
    // 入力内容表示テキスト用意
    //config->GetResult();戻り値がうまくいかず
    char buf[150];
    sprintf(buf, "行数：%d  列数：%d  ブロック：%d  連鎖：%d",
            config->GetLine(), config->GetRow(), config->GetType(), config->GetChain());
    word_input = TTF_RenderUTF8_Blended(font, buf, black);
    
    // メインテキスト描画
    SDL_BlitSurface(word_main, NULL, screen, &destrect_main_word);
    // サブテキスト描画
    SDL_BlitSurface(word_sub, NULL, screen, &destrect_sub_word);
    // 入力内容表示テキスト描画
    SDL_BlitSurface(word_input, NULL, screen, &destrect_input_word);
}
