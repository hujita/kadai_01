//
//  play.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/03/02.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "play.h"

Play::Play():
mode(0),
// 一度でもブロックを操作したか
flag_operated(OFF),
// ブロックを操作した回数
number_of_operations(0),
// アイテムを使用した回数
number_of_use_item(0),
// 残り時間2倍スイッチ
time_double(OFF),
// クリアしたか失敗したか
play_result(OFF),
// 得点テキスト
word_score(nullptr),
// 操作回数テキスト
word_operations(nullptr),
// クリア
word_crear(nullptr),
// 残り秒数
word_time(nullptr),
// 色
black({0x00, 0x00, 0x00}),
// クリアテキスト描画位置
destrect_word_crear({ 20, 20 }),
// 得点テキスト描画位置
destrect_word_score({ 20, 50 }),
// 操作回数テキスト描画位置
destrect_word_operations({ 20, 80 }),
// 残り秒数テキスト描画位置
destrect_word_time({ 20, 110 })
{}

void Play::Event(SDL_Event* event, Config* config, PuzzleManager* puzzle_manager, Section* sections, Block* blocks, boost::timer* t) {
    // キーボード操作
    if (event->type == SDL_KEYDOWN){
        // アイテム：全ブロック染め
        if (event->key.keysym.sym == SDLK_q){
            puzzle_manager->OrderAllBlockType(config, blocks, 0);
            flag_operated = OFF;
            ++number_of_use_item;
        }
        // アイテム：操作回数＋１
        if (event->key.keysym.sym == SDLK_w){
            --number_of_operations;
            ++number_of_use_item;
        }
        // アイテム：操作秒数2倍
        if (event->key.keysym.sym == SDLK_e){
            time_double = ON;
            ++number_of_use_item;
        }
        // モード：通常モード
        if (event->key.keysym.sym == SDLK_z){
            mode = MODE_PLAY;
        }
        // モード：編集モード(ブロック停止)
        if (event->key.keysym.sym == SDLK_x){
            mode = MODE_DELETE;
        }
        // モード：編集モード(ブロック再起動)
        if (event->key.keysym.sym == SDLK_c){
            mode = MODE_REBORN;
        }
    }
    // マウス操作
    switch(event->type){
        case SDL_MOUSEBUTTONDOWN:
            if (mode == MODE_PLAY){
            if (puzzle_manager->FlagAllDropDrawn(config, blocks)) {
                if (event->button.button == SDL_BUTTON_LEFT && event->button.state == SDL_PRESSED){
                    // ストップウォッチ起動
                    t->restart();
                    // 左クリックされた座標から選択されたブロックを探してactiveにする
                    puzzle_manager->ChoiceBlock(sections, blocks, config, event->button.x, event->button.y);
                }
                ++number_of_operations;
            }
            flag_operated = ON;
            }
            if (mode == MODE_DELETE){
                // 左クリッックされた座標から選択されたブロックを探して非実在にする
                // その座標のブロックを見つける
                int index = puzzle_manager->LookForPositionBlock(sections, blocks, config, event->button.x, event->button.y);
                blocks[index].SetAlive(OFF);
                blocks[index].SetExist(OFF);
                // 区画も消す
                if ( index != Invalid){
                    sections[blocks[index].GetSectionIndex()].SetExist(OFF);
                }
            }
            if (mode == MODE_REBORN){
                // 左クリッックされた座標から選択されたブロックを探して非実在にする
                // その座標のブロックを見つける
                int index = puzzle_manager->LookForPositionBlock(sections, blocks, config, event->button.x, event->button.y);
                blocks[index].SetAlive(ON);
                blocks[index].SetExist(ON);
                // 区画も復活
                if ( index != Invalid){
                    sections[blocks[index].GetSectionIndex()].SetExist(ON);
                }
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (mode == MODE_PLAY){
                if (event->button.button == SDL_BUTTON_LEFT && event->button.state == SDL_RELEASED){
                    time_double = OFF;
                    // ブロックを解放する
                    if (puzzle_manager->GetStateChoice() == ON){
                        puzzle_manager->ReleaseBlock(sections, blocks, config, event->button.x, event->button.y);
                        if (number_of_operations <= OPERATION_MAX && puzzle_manager->GetScore() >= config->GetRow() * config->GetLine() * SCORE_BLOCK * 10){
                            play_result = ON;
                        }
                    }
                }
            }
            break;
        case SDL_MOUSEMOTION:
            if (mode == MODE_PLAY){
                if (puzzle_manager->GetStateChoice() == ON) {
                    puzzle_manager->MoveBlock(sections, blocks, config, event->button.x, event->button.y);
                }
                int my_time = time_double == ON ? config->GetTime() * 2 : config->GetTime();
                if ( puzzle_manager->GetStateChoice() == ON && my_time - t->elapsed() <= 0 ){
                    // ブロックを解放する
                    time_double = OFF;
                    puzzle_manager->ReleaseBlock(sections, blocks, config, event->button.x, event->button.y);
                    if (number_of_operations <= OPERATION_MAX && puzzle_manager->GetScore() >= config->GetRow() * config->GetLine() * SCORE_BLOCK * 10){
                        play_result = ON;
                    }
                }
            }
            break;
    }
}

void Play::Draw(SDL_Surface *screen, TTF_Font* font, TTF_Font* big_font, SDL_Surface* section_image, SDL_Surface* section_image_02, SDL_Surface* block_image, Config* config, PuzzleManager* puzzle_manager, Section* sections, Block *blocks, boost::timer* t) {
    // アイテム
    SDL_Surface* word_item;
    SDL_Surface* word_item_q;
    SDL_Surface* word_item_w;
    SDL_Surface* word_item_e;
    SDL_Surface* word_rank;
    SDL_Rect destrect_word_item = { 20, 180 };
    SDL_Rect destrect_word_item_q = { 20, 210 };
    SDL_Rect destrect_word_item_w = { 20, 240 };
    SDL_Rect destrect_word_item_e = { 20, 270 };
    SDL_Rect destrect_word_rank = { 20, 140 };
    // モード
    SDL_Surface* word_mode;
    SDL_Surface* word_mode_z;
    SDL_Surface* word_mode_x;
    SDL_Surface* word_mode_c;
    SDL_Surface* word_mode_x_description;
    SDL_Surface* word_mode_c_description;
    SDL_Rect destrect_word_mode = { 20, 300 };
    SDL_Rect destrect_word_mode_z = { 20, 330 };
    SDL_Rect destrect_word_mode_x = { 20, 360 };
    SDL_Rect destrect_word_mode_c = { 20, 390 };
    SDL_Rect destrect_word_mode_x_description = { 500, 20 };
    SDL_Rect destrect_word_mode_c_description = { 500, 20 };
    
    // 区画を描画
    int i;
    for (i = 0; i < config->GetLine() * config->GetRow(); ++i) {
        sections[i].Draw(screen, section_image, section_image_02, config);
    };
    
    // ブロックを描画
    int j;
    // マウスで選択中のブロック
    int target_index = Invalid;
    for (j = 0; j < config->GetLine() * config->GetRow(); ++j) {
        if (blocks[j].GetActive() == OFF){
            blocks[j].Draw(screen, block_image, sections, config);
        }
        if (blocks[j].GetActive() == ON){
            target_index = j;
        }
    }
    if (target_index != Invalid){
        blocks[target_index].Draw(screen, block_image, sections, config);
    }
    MyText my_text;
    // 得点テキスト用意
    char buf[150];
    sprintf(buf, my_text.GetScore(), puzzle_manager->GetScore());
    word_score = TTF_RenderUTF8_Blended(font, buf, black);
    // 操作回数テキスト用意
    char buf_operations[150];
    int num = number_of_operations;
    if (num > OPERATION_MAX)
        num = OPERATION_MAX;
    sprintf(buf_operations, my_text.GetOperations(), OPERATION_MAX - num);
    word_operations = TTF_RenderUTF8_Blended(font, buf_operations, black);
    // クリアテキスト用意
    if (number_of_operations < OPERATION_MAX){
        char buf_crear[150];
        sprintf(buf_crear, my_text.GetCondition(), config->GetRow() * config->GetLine() * SCORE_BLOCK * 10);
        word_crear = TTF_RenderUTF8_Blended(font, buf_crear, black);
    }
    if (number_of_operations > OPERATION_MAX && play_result == OFF) {
        word_crear = TTF_RenderUTF8_Blended(font, my_text.GetGameOver(), black);
    }
    if (play_result == ON) {
        word_crear = TTF_RenderUTF8_Blended(font, my_text.GetCrear(), black);
    }
    // 残り秒数テキスト用意
    int my_time = time_double == ON ? config->GetTime() * 2 : config->GetTime();
    int remain_time = (my_time - (int)(t->elapsed()));
    if (puzzle_manager->GetStateChoice() == OFF || remain_time <= 0){
        remain_time = my_time;
    }
    char buf_time[150];
    sprintf(buf_time, my_text.GetTime(), remain_time);
    word_time = TTF_RenderUTF8_Blended(font, buf_time, black);
    // アイテム
    word_item = TTF_RenderUTF8_Blended(font, my_text.GetItem(), black);
    word_item_q = TTF_RenderUTF8_Blended(font, my_text.GetItemQ(), black);
    word_item_w = TTF_RenderUTF8_Blended(font, my_text.GetItemW(), black);
    word_item_e = TTF_RenderUTF8_Blended(font, my_text.GetItemE(), black);
    // ランク
    char tmp_rank;
    switch (number_of_use_item) {
        case 0:
            tmp_rank = 'S';
            break;
        case 1:
            tmp_rank = 'A';
            break;
        default:
            tmp_rank = 'B';
            break;
    }
    char buf_rank[150];
    sprintf(buf_rank, my_text.GetRank(), tmp_rank);
    word_rank = TTF_RenderUTF8_Blended(big_font, buf_rank, black);
    
    // モード
    word_mode = TTF_RenderUTF8_Blended(font, my_text.GetMode(), black);
    word_mode_z = TTF_RenderUTF8_Blended(font, my_text.GetModeZ(), black);
    word_mode_x = TTF_RenderUTF8_Blended(font, my_text.GetModeX(), black);
    word_mode_c = TTF_RenderUTF8_Blended(font, my_text.GetModeC(), black);
    word_mode_x_description = TTF_RenderUTF8_Blended(font, my_text.GetModeXDescription(), black);
    word_mode_c_description = TTF_RenderUTF8_Blended(font, my_text.GetModeCDescription(), black);
    
    // 得点テキスト描画
    SDL_BlitSurface(word_score, NULL, screen, &destrect_word_score);
    // 操作回数テキスト描画
    SDL_BlitSurface(word_operations, NULL, screen, &destrect_word_operations);
    // クリアテキスト描画
    SDL_BlitSurface(word_crear, NULL, screen, &destrect_word_crear);
    // 残り秒数の描画
    SDL_BlitSurface(word_time, NULL, screen, &destrect_word_time);
    // アイテム説明テキスト描画
    SDL_BlitSurface(word_item, NULL, screen, &destrect_word_item);
    SDL_BlitSurface(word_item_q, NULL, screen, &destrect_word_item_q);
    SDL_BlitSurface(word_item_w, NULL, screen, &destrect_word_item_w);
    SDL_BlitSurface(word_item_e, NULL, screen, &destrect_word_item_e);
    // ランク
    SDL_BlitSurface(word_rank, NULL, screen, &destrect_word_rank);
    // モード
    SDL_BlitSurface(word_mode, NULL, screen, &destrect_word_mode);
    SDL_BlitSurface(word_mode_z, NULL, screen, &destrect_word_mode_z);
    SDL_BlitSurface(word_mode_x, NULL, screen, &destrect_word_mode_x);
    SDL_BlitSurface(word_mode_c, NULL, screen, &destrect_word_mode_c);
    if (mode == MODE_DELETE){
        SDL_BlitSurface(word_mode_x_description, NULL, screen, &destrect_word_mode_x_description);
    }
    if (mode == MODE_REBORN){
        SDL_BlitSurface(word_mode_c_description, NULL, screen, &destrect_word_mode_c_description);
    }


}

// プレイ状況リセット
void Play::Reset(){
    number_of_use_item = OFF;
}

void Play::SetFlagOperated(int value){ flag_operated = value; }
void Play::SetNumberOfOperations(int value){ number_of_operations = value;}
void Play::SetPlayResult(int value){ play_result = value; }
int Play::GetFlagOperated(){ return flag_operated; }
int Play::GetNumberOfOperations(){ return number_of_operations; }
