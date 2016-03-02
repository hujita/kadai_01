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

class Play {
public:
    // イベント処理
    void Event(SDL_Event* event, Config* config, PuzzleManager* puzzle_manager, Section* sections, Block* blocks);
    // 描画処理
    void Draw(SDL_Surface* screen, SDL_Surface* section_image, SDL_Surface* block_image, Config* config, Section* sections, Block* blocks);
};

#endif /* defined(__puzzle_test_02__play__) */
