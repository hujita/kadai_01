//
//  block.h
//  puzzle_test_01
//
//  Created by hujita on 2016/02/24.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#ifndef __puzzle_test_01__block__
#define __puzzle_test_01__block__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <boost/format.hpp>
#include <boost/random.hpp>
#include <vector>
#include "view_play.h"
#include "view_top.h"

class Block {
    // 出力先座標
    double x, y;
    // ブロック種類
    int type;
    // 最左上から右に向かって順に何番目に位置しているか
    int place;
    // 0:消滅中, 1:生存中
    int alive = 0;

    //void DrawBlock(int index);
public:
    // クラス初期化
    Block();
    // 生成
    void Create(int i, int j, int cnt);
    // 描画
    void Draw(ViewPlay* view_play, bool is_current);
    // 画面初期化
    //int Initialize(View* view);
    // 設定初期化
    //void InitializeConfig();
    // TOP画面描画
    //void Draw(View* view);
    // 設定入力
    //void ConfigInput(int qty);
    // 画面描画
    //void DrawView();
    // TOP画面
    //void DrawTop();
    // PLAY画面
    //void DrawPlay();
    // 設定画面フェイズ取得
    //int GetConfigPhase();
};

#endif /* defined(__puzzle_test_01__block__) */