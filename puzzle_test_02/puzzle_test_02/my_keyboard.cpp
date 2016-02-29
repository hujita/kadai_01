//
//  my_keyboard.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/02/29.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "my_keyboard.h"

int MyKeyboard::CastIntFromKey(int key){
    int value = 999;
    switch (key) {
        case SDLK_0:
            value = 0;
            break;
        case SDLK_1:
            value = 1;
            break;
        case SDLK_2:
            value = 2;
            break;
        case SDLK_3:
            value = 3;
            break;
        case SDLK_4:
            value = 4;
            break;
        case SDLK_5:
            value = 5;
            break;
        case SDLK_6:
            value = 6;
            break;
        case SDLK_7:
            value = 7;
            break;
        case SDLK_8:
            value = 8;
            break;
        case SDLK_9:
            value = 9;
            break;
        default:
            break;
    }
    return value;
}