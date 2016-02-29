//
//  block.h
//  puzzle_test_02
//
//  Created by hujita on 2016/02/25.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#ifndef __puzzle_test_02__block__
#define __puzzle_test_02__block__

#include <stdio.h>
#include "settings.h"
#include "config.h"
#include "my_math.h"

class Block {
    // 出力元
    // 座標 & 高さ &幅
    double source_x;
    double source_y;
    double source_h;
    double source_w;
    // 出力先座標
    double destinaiton_x;
    double destination_y;
    // ブロック種別
    int block_type;
    // 現在位置している区画(整列番号)
    int section;
    // 生存
    int alive;
    // アクティブ(選択されている)
    int active;
    // 出力先座標とマウスポインタ座標の誤差(アクティブ時のみ使用)
    double x_difference;
    double y_difference;
public:
    Block();
    void Initialize(int i, int j, int cnt, Config* config);
    void GetSourcePosition(int type_block, int* position);
};

#endif /* defined(__puzzle_test_02__block__) */
