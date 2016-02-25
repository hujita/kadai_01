//
//  main.m
//  puzzle_test_01
//
//  Created by hujita on 2016/02/17.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

//
//  main.m
//  key_test_01
//
//  Created by hujita on 2016/02/17.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "view.h"
#include "view_top.h"
#include "view_play.h"
#include "block.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <boost/format.hpp>
#include <boost/random.hpp>
#include <vector>

#define MAX_BLOCK_TYPE_COUNT 9
#define MAX_BLOCK_COUNT 90

/* 入力データ */
typedef struct {
    int left;
    int up;
    int right;
    int down;
    int button1;
    int button2;
} InputData;

//typedef struct {
//    double x, y;        /* 出力先座標 */
//    int type;           /* 0:doctor, 1:girl, 2:hanamiju, 3:madam, 4:boy, 5:UMA, 6:woman, 7:worker, 8:yankee */
//    int place;    /* 現在何番目のブロックか */
//    int alive = 0; /* 0:消滅中, 1:生存中 */
//} Block;

typedef struct {
    double x, y, w, h;        /* 取得先ノ座標幅高 */
} BlockType;

/* ブロック数。最大で9*(9+1)=90 */
Block blocks[90];
/* 入れ替わり対象 */
Block block_target[1];
/* 元画像の座標 */
BlockType block_types[9] = {
    {13, 35, 90, 90},       /* 1.1 */
    {255, 35, 90, 90},       /* 1.4 */
    {336, 35, 90, 90},       /* 1.5 */
    {13, 127, 90, 90},       /* 2.1 */
    {174, 127, 100, 100},       /* 2.3 */
    {255, 127, 100, 100},       /* 2.4 */
    {336, 127, 100, 100},       /* 2.5 */
    {13, 200, 100, 100},       /* 3.1 */
    {174, 200, 100, 100},       /* 3.3 */
};

InputData current_input, prev_input;        /* 入力データ */

//SDL_Window* window = NULL;                  /* 画面 */
//SDL_Surface* screen = NULL;                 /* 画面の描画領域 */
//SDL_Surface* background_image = NULL;       /* 背景画像 */
//SDL_Surface* puzzle_block = NULL;           /* ブロック */

//SDL_Surface* word_main = NULL;              /* メインテキスト */
//SDL_Surface* word_sub = NULL;               /* サブテキスト */
//SDL_Surface* word_input = NULL;             /* 入力内容テキスト */
//SDL_Surface* word_0 = NULL;                 /* テキスト */
//SDL_Surface* word_1 = NULL;                 /* テキスト */
//SDL_Surface* word_2 = NULL;                 /* テキスト */
//SDL_Surface* word_3 = NULL;                 /* テキスト */
//SDL_Surface* word_4 = NULL;                 /* テキスト */

//TTF_Font* font;                             /* フォント */
//SDL_Color white = {0xff, 0xff, 0xff};       /* 色 */
//SDL_Rect destrect_main_word = { 330, 210 }; /* コメント位置 */
//SDL_Rect destrect_sub_word = { 330, 310 };  /* サブコメント位置 */
//SDL_Rect destrect_input_word = { 330, 410 };  /* 入力内容表示位置 */

//int view_type = 0;                          /* 0:TOP, 1:Play */
int config_phase = 0;                       /* 設定の段階 */
int line = 0;                               /* 行数 */
int row = 0;                                /* 列数 */
int type = 0;                               /* ブロック種類数 */
int chain = 0;                                /* 必要連鎖数 */
double x, y;                                /* 音符の座標 */
const int TOP_VIEW = 0;
const int PLAY_VIEW = 1;
int current_block_index = 999;                    /* 現在マークしているブロックのインデックス。初期値は999で何もマークしていない */
double current_block_x = 0;
double current_block_y = 0;
double current_block_x_diff = 0;
double current_block_y_diff = 0;
int block_state = 0;
int blocks_index[9];

/* 入力データを更新する */
void UpdateInput(void)
{
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    
    prev_input = current_input;
    current_input.left = keys[SDL_SCANCODE_LEFT] | keys[SDL_SCANCODE_H];        /* [←], [H] */
    current_input.up = keys[SDL_SCANCODE_UP] | keys[SDL_SCANCODE_K];            /* [↑], [K] */
    current_input.right = keys[SDL_SCANCODE_RIGHT] | keys[SDL_SCANCODE_L];      /* [→], [L] */
    current_input.down = keys[SDL_SCANCODE_DOWN] | keys[SDL_SCANCODE_J];        /* [↓], [J] */
    current_input.button1 = keys[SDL_SCANCODE_LSHIFT] | keys[SDL_SCANCODE_Z];   /* 左Shift, [Z] */
    current_input.button2 = keys[SDL_SCANCODE_LCTRL] | keys[SDL_SCANCODE_X];    /* 左Ctrl, [X] */
}

/* 更新する */
void Update(void)
{
    int speed = 6;
    
    UpdateInput();
    
    /* ボタン1が押されているときは低速 */
    if (current_input.button1)
        speed = 2;
    /* ボタン2が押されたら(0, 0)に移動 */
    if (current_input.button2 && !prev_input.button2)   /* 押された瞬間のみ */
        x = y = 0;
    
    /* 入力にしたがって移動する */
    if (current_input.left)
        x -= speed;
    if (current_input.right)
        x += speed;
    if (current_input.up)
        y -= speed;
    if (current_input.down)
        y += speed;
    
    /* 画面外に出ないようにする */
    if (x < 0)
        x = 0;
    else if (x > 640 - 64)
        x = 640 - 64;
    if (y < 0)
        y = 0;
    else if (y > 480 - 64)
        y = 480 - 64;
}

/* TOP画面更新 */
void UpdateTop(void)
{
}

/* void DrawBlock(int index){
    SDL_Rect srcrect;
    SDL_Rect desrect = { (int)blocks[index].x, (int)blocks[index].y };
    if (index == current_block_index){
        desrect = { (int)(current_block_x - current_block_x_diff), (int)(current_block_y - current_block_y_diff) };
    }
    switch (blocks[index].type) {
        case 0:
            srcrect.x = block_types[0].x;
            srcrect.y = block_types[0].y;
            srcrect.w = block_types[0].w;
            srcrect.h = block_types[0].h;
            break;
        case 1:
            srcrect.x = block_types[1].x;
            srcrect.y = block_types[1].y;
            srcrect.w = block_types[1].w;
            srcrect.h = block_types[1].h;
            break;
        case 2:
            srcrect.x = block_types[2].x;
            srcrect.y = block_types[2].y;
            srcrect.w = block_types[2].w;
            srcrect.h = block_types[2].h;
            break;
        case 3:
            srcrect.x = block_types[3].x;
            srcrect.y = block_types[3].y;
            srcrect.w = block_types[3].w;
            srcrect.h = block_types[3].h;
            break;
        case 4:
            srcrect.x = block_types[4].x;
            srcrect.y = block_types[4].y;
            srcrect.w = block_types[4].w;
            srcrect.h = block_types[4].h;
            break;
        case 5:
            srcrect.x = block_types[5].x;
            srcrect.y = block_types[5].y;
            srcrect.w = block_types[5].w;
            srcrect.h = block_types[5].h;
            break;
        case 6:
            srcrect.x = block_types[6].x;
            srcrect.y = block_types[6].y;
            srcrect.w = block_types[6].w;
            srcrect.h = block_types[6].h;
            break;
        case 7:
            srcrect.x = block_types[7].x;
            srcrect.y = block_types[7].y;
            srcrect.w = block_types[7].w;
            srcrect.h = block_types[7].h;
            break;
        case 8:
            srcrect.x = block_types[8].x;
            srcrect.y = block_types[8].y;
            srcrect.w = block_types[8].w;
            srcrect.h = block_types[8].h;
            break;
    } */
    //std::cout << "i,type,place=" << index << "," << blocks[index].type << "," << blocks[index].place << std::endl;
    //if (blocks[index].alive == 1)
        //SDL_BlitSurface(puzzle_block, &srcrect, screen, &desrect);
//}


//int CreateBlock(double x, double y, int rdm_type){
//    int i;
 //
//    /* 死んでるブロックを探す */
//    for (i = 0; i < MAX_BLOCK_COUNT; ++i) {
//        if (!blocks[i].alive)
//            break;
//    }
//    if (i < MAX_BLOCK_COUNT) {   /* 見つかった */
//        blocks[i].alive = 1;
//        blocks[i].x = x;
//        blocks[i].y = y;
//        blocks[i].type = rdm_type;
//        return i;
//    } else {                        /* 見つからなかった */
//        return -1;
//    }
//}

/* void InitializeBlock(){
    int i;
    int j;
    int cnt = 0;
    for (i = 0; i < line; ++i){
        for (j = 0; j < row; ++j){
            blocks[cnt].x = (95 * i);
            blocks[cnt].y = (95 * j);
            blocks[cnt].type = Random(0, type - 1, cnt);
            blocks[cnt].place = cnt;
            blocks[cnt].alive = 1;
            //std::cout << blocks[cnt].type << std::endl;
            ++cnt;
        }
    }
    std::cout << blocks[0].type << std::endl;
} */

/*Block InitializeBlock(){
    Block blocks[81] = {};
    int i;
    int j;
    int cnt = 0;
    for (i = 0; i < line; ++i){
        for (j = 0; j < row; ++j){
            Block block;
            block.Create(i, j, cnt);
            blocks[cnt] = block;
            ++cnt;
        }
    }
    return blocks;
}
 */
/* PLAY画面更新 */
void UpdatePlay(void)
{
    
    //InitBlock();
    //CreateBlock(320, 240, Random(0, 8));
}
// 描画する
void Draw(View* view, ViewTop* view_top, ViewPlay* view_play, Block* blocks)
{

    /* 背景を描画する */
//    view->DrawBackGround();
    //SDL_BlitSurface(background_image, NULL, screen, NULL);
    /* 画面の基礎描画 */
    view->Draw();

    if (view->GetViewType() == 0) {
        // TOP画面描画
        view_top->Draw(view);
    }
    if (view->GetViewType() == 1){
        // PLAY画面描画
        view_play->Draw(view, view_top, blocks);
    }
//        /* メインテキスト描画 */
//        SDL_BlitSurface(word_main, NULL, screen, &destrect_main_word);
//        /* サブテキスト描画 */
//        switch (config_phase) {
//            case 0:
//                word_sub = word_0;
//                break;
//            case 1:
//                word_sub = word_1;
//                break;
//            case 2:
//                word_sub = word_2;
//                break;
//            case 3:
//                word_sub = word_3;
//                break;
//            case 4:
//                word_sub = word_4;
//                break;
//        }
//        SDL_BlitSurface(word_sub, NULL, screen, &destrect_sub_word);
    
//        /* 入力内容表示テキスト描画 */
//        char buf[50];
//        sprintf(buf, "行数：%d  列数：%d  ブロック：%d  連鎖：%d", line, row, type, chain);
//        word_input = TTF_RenderUTF8_Blended(font, buf, white);
//        SDL_BlitSurface(word_input, NULL, screen, &destrect_input_word);
//    }
//    /* PLAY画面の描画 */
//    if (view_type == PLAY_VIEW){
//        /* ブロックを描画する */
//        int i;
        //SDL_BlitSurface(puzzle_block, NULL, screen, NULL);
//        for (i = 0; i < line * row; ++i) {
//            if (i != current_block_index)
//                DrawBlock(i);
//        }
//        if (current_block_index != 999)
//            DrawBlock(current_block_index);
//    }
//
    // 画面を更新する
    SDL_UpdateWindowSurface(view->GetWindow());
}


/* 初期化する。
 * 成功したときは0を、失敗したときは-1を返す。
 */
/*
int Initializea(void)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
        fprintf(stderr, "SDLの初期化に失敗しました：%s\n", SDL_GetError());
        return -1;
    }
    if (TTF_Init() < 0) {
        fprintf(stderr, "TTFの初期化に失敗しました：%s\n", TTF_GetError());
        return -1;
    }

    window = SDL_CreateWindow("パズルゲーム", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1000,850,0);
    screen = SDL_GetWindowSurface(window);
    if (screen == NULL) {
        fprintf(stderr, "画面の初期化に失敗しました：%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    
    /* 画像を読み込む */
/*
    background_image = IMG_Load("background.gif");
    if (background_image == NULL) {
        fprintf(stderr, "画像の読み込みに失敗しました：%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    puzzle_block = IMG_Load("puzzle_block.jpg");
    if (puzzle_block == NULL) {
        fprintf(stderr, "画像の読み込みに失敗しました：%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    
    /* フォント読み込み */
/*
    font = TTF_OpenFont("AquaKana.ttc", 24);
    if (font == NULL) {
        fprintf(stderr, "fontの取得に失敗しました：%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    
    /* 文字作成 *//*
    word_main = TTF_RenderUTF8_Blended(font, "パズルの設定(1~9で入力)", white);
    word_0 = TTF_RenderUTF8_Blended(font, "行数を指定してください", white);
    word_1 = TTF_RenderUTF8_Blended(font, "列数を指定してください", white);
    word_2 = TTF_RenderUTF8_Blended(font, "ブロックの種類数を指定してください", white);
    word_3 = TTF_RenderUTF8_Blended(font, "ブロックを繋げるべき数を指定してください", white);
    word_4 = TTF_RenderUTF8_Blended(font, "Enter:ゲーム開始 / 右Shift:TOPに戻る / ESC:終了", white);
    
    return 0;
} */

/*
void ConfigTopInput(int n){
    switch (config_phase){
        case 0:
            line = n;
            break;
        case 1:
            row = n;
            break;
        case 2:
            type = n;
            break;
        case 3:
            chain = n;
            break;
    }
    ++config_phase;
}

void ConfigTop(SDL_Event event){
    int value = 0;
    switch (event.key.keysym.sym) {
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
    }
    ConfigTopInput(value);
    ++config_phase;
}

void ChooseBlock(double x, double y){
    std::cout << "x,y=" << x << "," << y << std::endl;
    
    int i;
    for (i = 0; i < line * row; ++i) {
        if (blocks[i].x <= x && x <= (blocks[i].x + 90) && blocks[i].y <= y && y <= (blocks[i].y + 90)){
            current_block_index = i;
            //for (i = 0; i < line * row; ++i) {
              //  if (blocks[i].x <= x && x <= (blocks[i].x + 90) && blocks[i].y <= y && y <= (blocks[i].y + 90)){
                    current_block_x_diff = (x - blocks[i].x);
                    current_block_y_diff = (y - blocks[i].y);
                    current_block_x = x;
                    current_block_y = y;
                //}
            //}
        }
    }
    std::cout << "x,y=" << x << "," << y << std::endl;
    std::cout << "current_block_index=" << current_block_index << std::endl;
}

// 縦の連結チェック
int CheckRowChain(int before_index){
    int i;
    for (i = 0; i < line * row; ++i){
        if (blocks[i].place == (blocks[before_index].place  - 1) && blocks[before_index].place % row != 0){
            if (blocks[i].type == blocks[before_index].type){
                return i;
            }
            
        }
    }
    return 999;
}

// 横の連結チェック
int CheckLineChain(int before_index){
    int i;
    for (i = 0; i < line * row; ++i){
        if (blocks[i].place == (blocks[before_index].place  - line) && blocks[before_index].place % line != 0){
            if (blocks[i].type == blocks[before_index].type){
                //std::cout << "i=" << i << std::endl;
                return i;
            }
            
        }
    }
    return 999;
}

void CheckChain(){
    // 縦方向に連結していたらブロック消滅
    int i;
    int j;
    int cnt;
    for (i = 0; i < line * row; ++i){
        int chain_result = i;
        std::vector<int> ary;
        // i番目のブロックの連結について確認
        // 指定されたchain数だけ確認する
        for (j = 0; j < chain; ++j){
            // 連結が終わっていたら処理しない
            if (chain_result != 999){
                // 最初の一つ目は配列に加える
                if (j == 0)
                    ary.push_back(i);
                // 真上のブロックが同じ種類なら真上のブロックのインデックスを返す
                chain_result = CheckRowChain(chain_result);
                // 真上のブロックが同じ種類なら配列にインデックスを追加
                if (chain_result != 999)
                    ary.push_back(chain_result);
                // 必要連結回数目もchain_resultが999になっていなければ配列内のブロックを全て消滅させる
                if (j == (chain - 1)){
                    for (cnt = 0; cnt < chain; ++cnt){
                        //std::cout << ary[cnt] << std::endl;
                        blocks[ary[cnt]].alive = 0;
                    }
                }
            }
        }
    }

    // 横方向に連結していたらブロック消滅
    int i2;
    int j2;
    int cnt2;
    for (i2 = 0; i2 < line * row; ++i2){
        int chain_result = i2;
        std::vector<int> ary2;
        // i番目のブロックの連結について確認
        // 指定されたchain数だけ確認する
        for (j2 = 0; j2 < chain; ++j2){
            // 連結が終わっていたら処理しない
            if (chain_result != 999){
                // 最初の一つ目は配列に加える
                if (j2 == 0)
                    ary2.push_back(i2);
                // 左隣のブロックが同じ種類なら左と也のブロックのインデックスを返す
                chain_result = CheckLineChain(chain_result);
                // 左隣のブロックが同じ種類なら配列にインデックスを追加
                if (chain_result != 999)
                    ary2.push_back(chain_result);
                // 必要連結回数目もchain_resultが999になっていなければ配列内のブロックを全て消滅させる
                if (j2 == (chain - 1)){
                    for (cnt2 = 0; cnt2 < chain; ++cnt2){
                        //std::cout << ary[cnt] << std::endl;
                        blocks[ary2[cnt2]].alive = 0;
                    }
                }
            }
        }
    }

}
*/
/* 指を離した *//*
void ReleaseBlock(double x, double y){
    if (x >= row * 95) {
        x = row * 95 - 10;
    }
    if (y >= line * 95){
        y = line * 95 -10;
    }
    
    // 位置を整える
    int i;
    for (i = 0; i < line * row; ++i) {
        if (blocks[i].x <= x && x <= (blocks[i].x + 90) && blocks[i].y <= y && y <= (blocks[i].y + 90)){
            current_block_index = i;
                    current_block_x_diff = (x - blocks[i].x);
                    current_block_y_diff = (y - blocks[i].y);
                    current_block_x = x;
                    current_block_y = y;
        }
    }
    block_state = 0;
    CheckChain();
}

void OverBlock(double x, double y){
    // 位置を整える
//    int i;
//    int j;
//    int n;
    /* x座標が超えた場合 *//*
//    if (row * 95 <= x){
//        for (i = 0; i < line; ++i){
//            for (j = 0; j < line * row; ++j){
//                if (blocks[j].place == i){
//                    if (blocks[j].y <= y && y <= (blocks[j].y + 90)){
//                        std::cout << "j=" << j << std::endl;
//                        /* 一番外 */
//                        int last_index = i + (line * row - (row - 1));
//                        for (n = 0; n < line * row; ++n){
//                            if (blocks[n].place == last_index){
//                                std::cout << "n=" << n << std::endl;
//                                current_block_x = (blocks[n].x + current_block_x_diff);
//                                current_block_y = (blocks[n].y + current_block_y_diff);
//                            }
//                        }
//                    }
//                }
//            }
//        }
        //current_block_x_diff = (x - blocks[i].x);
        //current_block_y_diff = (y - blocks[i].y);
        //current_block_x = x;
        //current_block_y = y;
//    }
    //current_block_index = 999;
/*
}

void MoveBlock(double x, double y){
    //座標が他のブロックに入ったら配列の中身を交換
    if (x >= row * 95) {
        x = row * 95 - 10;
        //ReleaseBlock(x, y);
    }
    if (y >= line * 95){
        y = line * 95 -10;
        //ReleaseBlock(x, y);
    }
    
    current_block_x = x;
    current_block_y = y;
    int i;
    double target_x = 0;
    double target_y = 0;
    int target_place = 0;

    /* パズルの枠外にでたら指を離したと見做す *//*
    //if (x > row * 95 || y > line * 95){
    //    OverBlock(x, y);
    //    block_state = 0;
    //}
    
    /* 他の石の領域に侵入したら交換 *//*
    for (i = 0; i < line * row; ++i) {
        if (blocks[i].x <= x && x <= (blocks[i].x + 90) && blocks[i].y <= y && y <= (blocks[i].y + 90)){
            if (i != current_block_index){
                target_x = blocks[i].x;
                target_y = blocks[i].y;
                target_place = blocks[i].place;
                
                blocks[i].x = blocks[current_block_index].x;
                blocks[i].y = blocks[current_block_index].y;
                blocks[i].place = blocks[current_block_index].place;
                
                blocks[current_block_index].x = target_x;
                blocks[current_block_index].y = target_y;
                blocks[current_block_index].place = target_place;
            }
            //current_block_x_diff = (x - blocks[i].x);
            //current_block_y_diff = (y - blocks[i].y);
            //current_block_x = x;
            //current_block_y = y;
            //std::cout << i << std::endl;
            //std::cout << x << std::endl;
            //std::cout << current_block_x_diff << std::endl;
            //std::cout << current_block_index << std::endl;
        }
    }

}
*/
/* メインループ */
void MainLoop(View* view, ViewTop* view_top, ViewPlay* view_play){
    SDL_Event event;
    double next_frame = SDL_GetTicks();
    double wait = 1000.0 / 60;
    Block blocks[81] = {};
    
    for (;;) {
        /* すべてのイベントを処理する */
        while (SDL_PollEvent(&event)) {
            /* QUIT イベントが発生するか、ESC キーが押されたら終了する */
            if ((event.type == SDL_QUIT) ||
                (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
                return;
            /* TOP画面でのキー入力 */
            if (view->GetViewType() == TOP_VIEW && event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym) {
                    case SDLK_1:
                        view_top->ConfigInput(1);
                        break;
                    case SDLK_2:
                        view_top->ConfigInput(2);
                        break;
                    case SDLK_3:
                        view_top->ConfigInput(3);
                        break;
                    case SDLK_4:
                        view_top->ConfigInput(4);
                        break;
                    case SDLK_5:
                        view_top->ConfigInput(5);
                        break;
                    case SDLK_6:
                        view_top->ConfigInput(6);
                        break;
                    case SDLK_7:
                        view_top->ConfigInput(7);
                        break;
                    case SDLK_8:
                        view_top->ConfigInput(8);
                        break;
                    case SDLK_9:
                        view_top->ConfigInput(9);
                        break;
                    case SDLK_RETURN:
                        if (view_top->GetConfigPhase() >= 4) {
                            /* 初期ブロック配置 */
                            view_play->InitializePuzzle(view_top->GetLine(), view_top->GetRow());
                            /*int i;
                            int j;
                            int cnt = 0;
                            for (i = 0; i < line; ++i){
                                for (j = 0; j < row; ++j){
                                    Block block;
                                    block.Create(i, j, cnt);
                                    blocks[cnt] = block;
                                    ++cnt;
                                }
                            }
                             */
                            view->SetViewType(1);
                            break;
                        }
                }
            }
            /* PLAY画面でのマウスイベント */
            if (view->GetViewType() == 1){
                switch(event.type){
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_PRESSED){
                            //                            ChooseBlock(event.button.x, event.button.y);
                            //                            block_state = 1;
                            std::cout << "左ボタン押した" << std::endl;
                        }
                        break;
                    case SDL_MOUSEBUTTONUP:
                        if (event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_RELEASED){
                            //                           ReleaseBlock(event.button.x, event.button.y);
                            std::cout << "左ボタンはなした" << std::endl;
                        }
                        break;
                    case SDL_MOUSEMOTION:
                        //                       if (block_state == 1) {
                        //                          MoveBlock(event.button.x, event.button.y);
                                           std::cout << "動かした" << std::endl;
                        //                       }
                        break;
                }
            }
            // 全画面共通のキー入力
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RSHIFT){
            // 初期化
            view_top->InitializeConfig();
            //           line = 0;
              //         row = 0;
                //       type = 0;
                  //     chain = 0;
                    //   config_phase = 0;
                       //view_type = TOP_VIEW;
                       //current_block_index = 999;
            }
        }
        /* 1秒間に60回Updateされるようにする */
        if (SDL_GetTicks() >= next_frame) {
            //if (view_type == TOP_VIEW) {
            //    UpdateTop();
            //} else if (view_type == PLAY_VIEW) {
            //    UpdatePlay();
            //};
            //Update();
            /* 時間がまだあるときはDrawする */
            if (SDL_GetTicks() < next_frame + wait)
                Draw(view, view_top, view_play, blocks);
            next_frame += wait;
            SDL_Delay(0);
        }
    }
}


/* 初期化する。
 * 成功したときは0を、失敗したときは-1を返す。
 */
int Initialize(View* view){
    return view->Initialize();
}

/* 終了処理を行う */
void Finalize(View* view)
{
    SDL_FreeSurface(view->GetBackgroundImage());
    SDL_FreeSurface(view->GetPuzzleBlock());
    TTF_CloseFont(view->GetFont());
    
    /* 終了する */
    TTF_Quit();
    SDL_Quit();
}


/* メイン関数 */
/* 初期化 -> メイン処理 -> 終了処理 */
int main(int argc, char* argv[])
{
    // 画面インスタンス
    View view;
    // TOP画面インスタンス
    ViewTop view_top;
    // PLAY画面インスタンス
    ViewPlay view_play;
    if (Initialize(&view) < 0)
        return -1;
    MainLoop(&view, &view_top, &view_play);
    Finalize(&view);
    return 0;
}