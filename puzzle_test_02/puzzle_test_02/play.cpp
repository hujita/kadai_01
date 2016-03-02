//
//  play.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/03/02.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "play.h"

void Play::Event(SDL_Event* event, Config* config, PuzzleManager* puzzle_manager, Section* sections, Block* blocks) {
    // マウス操作
    switch(event->type){
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT && event->button.state == SDL_PRESSED){
                // 左クリックされた座標から選択されたブロックを探してactiveにする
                puzzle_manager->ChoiceBlock(sections, blocks, config, event->button.x, event->button.y);
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (event->button.button == SDL_BUTTON_LEFT && event->button.state == SDL_RELEASED){
                // ブロックを解放する
                puzzle_manager->ReleaseBlock(sections, blocks, config, event->button.x, event->button.y);
            }
            break;
        case SDL_MOUSEMOTION:
            if (puzzle_manager->GetStateChoice() == 1) {
                puzzle_manager->MoveBlock(sections, blocks, config, event->button.x, event->button.y);
            }
            break;
    }
}

void Play::Draw(SDL_Surface *screen, SDL_Surface* section_image, SDL_Surface* block_image, Config* config, Section* sections, Block *blocks) {
    // 区画を描画
    int i;
    for (i = 0; i < config->GetLine() * config->GetRow(); ++i) {
        sections[i].Draw(screen, section_image);
    };
    
    // ブロックを描画
    int j;
    // マウスで選択中のブロック
    int target_index = Invalid;
    for (j = 0; j < config->GetLine() * config->GetRow(); ++j) {
        if (blocks[j].GetActive() == OFF){
            blocks[j].Draw(screen, block_image, sections);
        }
        if (blocks[j].GetActive() == ON){
            target_index = j;
        }
    }
    if (target_index != Invalid){
        blocks[target_index].Draw(screen, block_image, sections);
    }
}