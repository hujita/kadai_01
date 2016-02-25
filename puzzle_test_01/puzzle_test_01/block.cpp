//
//  block.cpp
//  puzzle_test_01
//
//  Created by hujita on 2016/02/24.
//  Copyright (c) 2016年 hujita. All rights reserved.
//
#include "view_play.h"
#include "block.h"
#include "view.h"
#include "view_top.h"
#include "math.h"
#include "settings.h"


// クラス初期化
Block::Block() {
    // 出力先座標
    x = 0;
    y = 0;
    // ブロック種類
    type = 999;
    // TODO: 初期化時に0が既に使われているからといって999は違和感
    // 最左上から右に向かって順に何番目に位置しているか
    place = 999;
    // 0:消滅中, 1:生存中
    alive = 0;
}

// ブロック生成(i:所属行数, j:所属列数, cnt:何番目のブロック)
void Block::Create(int i, int j, int cnt){
    x = (95 * i);
    y = (95 * j);
    type = Random(0, type - 1, cnt);
    place = cnt;
    alive = 1;
}

void Block::Draw(ViewPlay* view_play, bool is_current){
    SDL_Rect srcrect;
    SDL_Rect desrect = { (int)x, (int)y };
    if (is_current){
        desrect = { (int)(view_play->GetCurrentBlockX() - view_play->GetCurrentBlockXDiff()),
                    (int)(view_play->GetCurrentBlockY() - view_play->GetCurrentBlockYDiff())
        };
    }
    switch (type) {
        case 0:
            srcrect.x = block_types[0][0];
            srcrect.y = block_types[0][1];
            srcrect.w = block_types[0][2];
            srcrect.h = block_types[0][3];
            break;
        case 1:
            srcrect.x = block_types[1][0];
            srcrect.y = block_types[1][1];
            srcrect.w = block_types[1][2];
            srcrect.h = block_types[1][3];
            break;
        case 2:
            srcrect.x = block_types[2][0];
            srcrect.y = block_types[2][1];
            srcrect.w = block_types[2][2];
            srcrect.h = block_types[2][3];
            break;
        case 3:
            srcrect.x = block_types[3][0];
            srcrect.y = block_types[3][1];
            srcrect.w = block_types[3][2];
            srcrect.h = block_types[3][3];
            break;
        case 4:
            srcrect.x = block_types[4][0];
            srcrect.y = block_types[4][1];
            srcrect.w = block_types[4][2];
            srcrect.h = block_types[4][3];
            break;
        case 5:
            srcrect.x = block_types[5][0];
            srcrect.y = block_types[5][1];
            srcrect.w = block_types[5][2];
            srcrect.h = block_types[5][3];
            break;
        case 6:
            srcrect.x = block_types[6][0];
            srcrect.y = block_types[6][1];
            srcrect.w = block_types[6][2];
            srcrect.h = block_types[6][3];
            break;
        case 7:
            srcrect.x = block_types[7][0];
            srcrect.y = block_types[7][1];
            srcrect.w = block_types[7][2];
            srcrect.h = block_types[7][3];
            break;
        case 8:
            srcrect.x = block_types[8][0];
            srcrect.y = block_types[8][1];
            srcrect.w = block_types[8][2];
            srcrect.h = block_types[8][3];
            break;
    }
            //std::cout << "i,type,place=" << index << "," << blocks[index].type << "," << blocks[index].place << std::endl;
            //if (blocks[index].alive == 1)
            //SDL_BlitSurface(puzzle_block, &srcrect, screen, &desrect);
}