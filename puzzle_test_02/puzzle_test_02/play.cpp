//
//  play.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/03/02.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "play.h"

Play::Play():
// 一度でもブロックを操作したか
flag_operated(OFF),
// ブロックを操作した回数
number_of_operations(0),
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
// アイテム説明
//word_item(nullptr),
//word_item_q(nullptr),
//word_item_w(nullptr),
//word_item_e(nullptr),
// ランクテキスト
//word_rank(nullptr),
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
// アイテム説明描画位置
//destrect_word_item_q({ 20, 140 })
//destrect_word_item_w({ 20, 170 }),
//destrect_word_item_e({ 20, 200 }),
// ランク描画位置
//destrect_word_rank({ 20, 230 })
{}

void Play::Event(SDL_Event* event, Config* config, PuzzleManager* puzzle_manager, Section* sections, Block* blocks, boost::timer* t) {
    // キーボード操作
    if (event->type == SDL_KEYDOWN){
        if (event->key.keysym.sym == SDLK_q){
            puzzle_manager->OrderAllBlockType(config, blocks, 0);
            flag_operated = OFF;
        }
        if (event->key.keysym.sym == SDLK_w){
        }
        if (event->key.keysym.sym == SDLK_e){
        }
    }
    // マウス操作
    switch(event->type){
        case SDL_MOUSEBUTTONDOWN:
            if (puzzle_manager->FlagAllDropDrawn(config, blocks)) {
                if (event->button.button == SDL_BUTTON_LEFT && event->button.state == SDL_PRESSED){
                    // ストップウォッチ起動
                    t->restart();
                    std::cout << (int)(t->elapsed()) << std::endl;
                    // 左クリックされた座標から選択されたブロックを探してactiveにする
                    puzzle_manager->ChoiceBlock(sections, blocks, config, event->button.x, event->button.y);
                }
                ++number_of_operations;
            }
            flag_operated = ON;
            break;
        case SDL_MOUSEBUTTONUP:
            if (event->button.button == SDL_BUTTON_LEFT && event->button.state == SDL_RELEASED){
                // ブロックを解放する
                if (puzzle_manager->GetStateChoice() == ON){
                    puzzle_manager->ReleaseBlock(sections, blocks, config, event->button.x, event->button.y);
                    if (number_of_operations <= OPERATION_MAX && puzzle_manager->GetScore() >= config->GetRow() * config->GetLine() * SCORE_BLOCK * 10){
                        play_result = ON;
                    }
                }
            }
            break;
        case SDL_MOUSEMOTION:
            if (puzzle_manager->GetStateChoice() == ON) {
                puzzle_manager->MoveBlock(sections, blocks, config, event->button.x, event->button.y);
            }
            if ( puzzle_manager->GetStateChoice() == ON && config->GetTime() - t->elapsed() <= 0 ){
                // ブロックを解放する
                puzzle_manager->ReleaseBlock(sections, blocks, config, event->button.x, event->button.y);
                if (number_of_operations <= OPERATION_MAX && puzzle_manager->GetScore() >= config->GetRow() * config->GetLine() * SCORE_BLOCK * 10){
                    play_result = ON;
                }
            }
            break;
    }
}

void Play::Draw(SDL_Surface *screen, TTF_Font* font, SDL_Surface* section_image, SDL_Surface* block_image, Config* config, PuzzleManager* puzzle_manager, Section* sections, Block *blocks, boost::timer* t) {
    SDL_Surface* word_item;
    SDL_Surface* word_item_q;
    SDL_Surface* word_item_w;
    SDL_Surface* word_item_e;
    SDL_Rect destrect_word_item = { 20, 140 };
    SDL_Rect destrect_word_item_q = { 20, 170 };
    SDL_Rect destrect_word_item_w = { 20, 200 };
    SDL_Rect destrect_word_item_e = { 20, 230 };
    // 区画を描画
    int i;
    for (i = 0; i < config->GetLine() * config->GetRow(); ++i) {
        sections[i].Draw(screen, section_image, config);
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
    int remain_time = (config->GetTime() - (int)(t->elapsed()));
    if (puzzle_manager->GetStateChoice() == OFF || remain_time <= 0){
        remain_time = 0;
    }
    char buf_time[150];
    sprintf(buf_time, my_text.GetTime(), remain_time);
    word_time = TTF_RenderUTF8_Blended(font, buf_time, black);
    // アイテム
    word_item = TTF_RenderUTF8_Blended(font, my_text.GetItem(), black);
    word_item_q = TTF_RenderUTF8_Blended(font, my_text.GetItemQ(), black);
    word_item_w = TTF_RenderUTF8_Blended(font, my_text.GetItemW(), black);
    word_item_e = TTF_RenderUTF8_Blended(font, my_text.GetItemE(), black);
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
}

void Play::SetFlagOperated(int value){ flag_operated = value; }
void Play::SetNumberOfOperations(int value){ number_of_operations = value;}
void Play::SetPlayResult(int value){ play_result = value; }
int Play::GetFlagOperated(){ return flag_operated; }
int Play::GetNumberOfOperations(){ return number_of_operations; }
