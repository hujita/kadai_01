//
//  main.mm
//  puzzle_test_02
//
//  Created by hujita on 2016/02/24.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include <stdio.h>
#include "game.h"
#include <iostream>

/* メイン関数 */
/* 初期化 -> メイン処理 -> 終了処理 */
int main(int argc, char* argv[])
{
    // ゲームスタート
    Game game;
    if (game.Start() < 0)
        return -1;
}
