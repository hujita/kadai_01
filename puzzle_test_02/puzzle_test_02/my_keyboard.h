// キーボード入力変換機

//  my_keyboard.h
//  puzzle_test_02
//
//  Created by hujita on 2016/02/29.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#ifndef __puzzle_test_02__my_keyboard__
#define __puzzle_test_02__my_keyboard__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>


class MyKeyboard {
public:
    int CastIntFromKey(int key);
};

#endif /* defined(__puzzle_test_02__my_keyboard__) */
