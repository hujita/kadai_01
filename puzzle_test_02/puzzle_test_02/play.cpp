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
    word_score(NULL),
    // クリア
    word_crear(NULL),
    // 操作回数テキスト
    word_operations(NULL),
    // 色
    black({0x00, 0x00, 0x00}),
    // クリアテキスト描画位置
    destrect_word_crear({ 20, 20 }),
    // 得点テキスト描画位置
    destrect_word_score({ 20, 50 }),
    // 操作回数テキスト描画位置
    destrect_word_operations({ 20, 80 })
{}

void Play::Event(SDL_Event* event, Config* config, PuzzleManager* puzzle_manager, Section* sections, Block* blocks) {
    // マウス操作
    switch(event->type){
        case SDL_MOUSEBUTTONDOWN:
            if (puzzle_manager->FlagAllDropDrawn(config, blocks)) {
                if (event->button.button == SDL_BUTTON_LEFT && event->button.state == SDL_PRESSED){
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
                puzzle_manager->ReleaseBlock(sections, blocks, config, event->button.x, event->button.y);
                if (number_of_operations <= OPERATION_MAX && puzzle_manager->GetScore() >= config->GetRow() * config->GetLine() * SCORE_BLOCK * 10){
                    play_result = ON;
                }
            }
            break;
        case SDL_MOUSEMOTION:
            if (puzzle_manager->GetStateChoice() == 1) {
                puzzle_manager->MoveBlock(sections, blocks, config, event->button.x, event->button.y);
            }
            break;
    }
}

void Play::Draw(SDL_Surface *screen, TTF_Font* font, SDL_Surface* section_image, SDL_Surface* block_image, Config* config, PuzzleManager* puzzle_manager, Section* sections, Block *blocks) {
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
    
    // 得点テキスト描画
    SDL_BlitSurface(word_score, NULL, screen, &destrect_word_score);
    // 操作回数テキスト描画
    SDL_BlitSurface(word_operations, NULL, screen, &destrect_word_operations);
    // クリアテキスト描画
    SDL_BlitSurface(word_crear, NULL, screen, &destrect_word_crear);
}

void Play::SetFlagOperated(int value){ flag_operated = value; }
void Play::SetNumberOfOperations(int value){ number_of_operations = value;}
void Play::SetPlayResult(int value){ play_result = value; }
int Play::GetFlagOperated(){ return flag_operated; }
int Play::GetNumberOfOperations(){ return number_of_operations; }
