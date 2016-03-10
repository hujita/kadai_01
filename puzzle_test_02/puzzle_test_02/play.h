// PLAY画面

//  play.h
//  puzzle_test_02
//
//  Created by hujita on 2016/03/02.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#ifndef __puzzle_test_02__play__
#define __puzzle_test_02__play__

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "config.h"
#include "puzzle_manager.h"
#include "section.h"
#include "block.h"
#include <boost/timer.hpp>

class Play {
    // 一度でもブロックを操作したか
    int flag_operated;
    // ブロックを操作した回数
    int number_of_operations;
    // クリアしたか失敗したか
    int play_result;
    // 得点テキスト
    SDL_Surface* word_score;
    // 操作回数テキスト
    SDL_Surface* word_operations;
    // クリア
    SDL_Surface* word_crear;
    // 経過時間
    SDL_Surface* word_time;
    // アイテム説明テキスト
    //SDL_Surface* word_item;
    //SDL_Surface* word_item_q;
    //SDL_Surface* word_item_w;
    //SDL_Surface* word_item_e;
    // ランクテキスト
    //SDL_Surface* word_rank;
    // 色
    SDL_Color black;
    // 得点テキスト描画位置
    SDL_Rect destrect_word_score;
    // 操作回数テキスト描画位置
    SDL_Rect destrect_word_operations;
    // 操作回数テキスト描画位置
    SDL_Rect destrect_word_crear;
    // 操作回数テキスト描画位置
    SDL_Rect destrect_word_time;
    // アイテム説明テキスト描画位置
    //SDL_Rect destrect_word_item_q;
    //SDL_Rect destrect_word_item_w;
    //SDL_Rect destrect_word_item_e;
    // ランクテキスト描画位置
    //SDL_Rect destrect_word_rank;
public:
    Play();
    // イベント処理
    void Event(SDL_Event* event, Config* config, PuzzleManager* puzzle_manager, Section* sections, Block* blocks, boost::timer* t);
    // 描画処理
    void Draw(SDL_Surface* screen, TTF_Font* font, SDL_Surface* section_image, SDL_Surface* block_image, Config* config, PuzzleManager* puzzle_manager, Section* sections, Block* blocks, boost::timer* t);
    // Getter
    int GetFlagOperated();
    int GetNumberOfOperations();
    // Setter
    void SetFlagOperated(int value);
    void SetNumberOfOperations(int value);
    void SetPlayResult(int value);
};

#endif /* defined(__puzzle_test_02__play__) */
