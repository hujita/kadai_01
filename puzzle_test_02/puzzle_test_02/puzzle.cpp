//
//  puzzle.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/02/25.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "puzzle.h"

// パズル設定に従ってブロック生成を繰り返し、渡された配列を満たす
void Puzzle::Initialize(Block* blocks, Config* config){
    int i;
    int j;
    int cnt = 0;
    for (i = 0; i < config->GetLine(); ++i){
        for (j = 0; j < config->GetRow(); ++j){
            Block block;
            block.Initialize(i, j, cnt, config);
            blocks[cnt] = block;
            ++cnt;
        }
    }
}