//
//  main.mm
//  puzzle_test_02
//
//  Created by hujita on 2016/02/24.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "game.h"



/* メイン関数 */
/* 初期化 -> メイン処理 -> 終了処理 */
int main(int argc, char* argv[])
{
    // ゲームスタート
    Game game;
    // 初期化に失敗すると戻り値は -1
    if (game.Start() < 0)
        return -1;
}