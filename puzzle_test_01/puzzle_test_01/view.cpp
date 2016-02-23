//
//  view.cpp
//  puzzle_test_01
//
//  Created by hujita on 2016/02/23.
//  Copyright (c) 2016年 hujita. All rights reserved.
//
// 画面ベースクラス


#include "view.h"
#include "view_top.h"

// クラス初期化
View::View() {
    // 画面遷移用変数(TOP:0, PLAY:1)
    view_type = 0;
    // 設定画面フェイズ
    //config_phase = 0;
    // 行数
    //line = 0;
    // 列数
    //row = 0;
    // ブロック種類数
    //type = 0;
    // 必要連結数
    //chain = 0;
    // 選択中のブロック
    //current_block_index = 999;
    
    // 画面
    window = NULL;
    // 画面の描画領域
    screen = NULL;
    // 背景画像
    background_image = NULL;
    // ブロック画像
    puzzle_block = NULL;
    // 設定画面メインテキスト
    //word_main = NULL;
    // 設定画面サブテキスト
    //word_sub = NULL;
    // 設定画面入力内容テキスト
    //word_input = NULL;
    // 設定画面質問テキスト
    //word_0 = NULL;
    // 設定画面質問テキスト
    //word_1 = NULL;
    // 設定画面質問テキスト
    //word_2 = NULL;
    // 設定画面質問テキスト
    //word_3 = NULL;
    // 設定画面質問テキスト
    //word_4 = NULL;
    // フォント
    font = NULL;
    // 色
    //white = {0xff, 0xff, 0xff};
    // メインテキスト描画位置
    //destrect_main_word = { 330, 210 };
    // サブテキスト描画位置
    //destrect_sub_word = { 330, 310 };
    // 入力内容描画位置
    //destrect_input_word = { 330, 410 };
}

// 画面初期化
int View::Initialize(void)
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
    font = TTF_OpenFont("AquaKana.ttc", 24);
    if (font == NULL) {
        fprintf(stderr, "fontの取得に失敗しました：%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    
    /* 文字作成
    word_main = TTF_RenderUTF8_Blended(font, "パズルの設定(1~9で入力)", white);
    word_0 = TTF_RenderUTF8_Blended(font, "行数を指定してください", white);
    word_1 = TTF_RenderUTF8_Blended(font, "列数を指定してください", white);
    word_2 = TTF_RenderUTF8_Blended(font, "ブロックの種類数を指定してください", white);
    word_3 = TTF_RenderUTF8_Blended(font, "ブロックを繋げるべき数を指定してください", white);
    word_4 = TTF_RenderUTF8_Blended(font, "Enter:ゲーム開始 / 右Shift:TOPに戻る / ESC:終了", white); */
    
    return 0;
}

// 背景描画
void View::DrawBackGround(void)
{
    SDL_BlitSurface(background_image, NULL, screen, NULL);
}

// 画面描画 //
void View::Draw(void)
{
        
        /* 背景を描画する */
        DrawBackGround();
        //SDL_BlitSurface(background_image, NULL, screen, NULL);
        /* TOP画面の描画 */
        //DrawView();
        //    if (view->view_type == TOP_VIEW) {
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
        /* 画面を更新する */
        //    SDL_UpdateWindowSurface(window);

    // TODO: 0か1の直書きで処理を分けるのではなくTOP_VIEWのような定数で
    // TOP画面の描画
    //if (view_type == 0){
    //    view_top.Draw(this);
    //}
    /* PLAY画面の描画 */
    //if (view_type == 1)
        //DrawPlay();
    //SDL_UpdateWindowSurface(window);
}

/* メインループ
void View::MainLoop(void){
    SDL_Event event;
    double next_frame = SDL_GetTicks();
    double wait = 1000.0 / 60;
    // TOP画面
    ViewTop view_top;
    
    for (;;) {
        /* すべてのイベントを処理する
        while (SDL_PollEvent(&event)) {
            /* QUIT イベントが発生するか、ESC キーが押されたら終了する
            if ((event.type == SDL_QUIT) ||
                (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
                return;
            /* TOP画面でのキー入力
            //if (view_type == TOP_VIEW && event.type == SDL_KEYDOWN){
            if (event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym) {
                    case SDLK_1:
                        view_top.ConfigInput(1);
                        break;
                    case SDLK_2:
                        view_top.ConfigInput(2);
                        break;
                    case SDLK_3:
                        view_top.ConfigInput(3);
                        break;
                    case SDLK_4:
                        view_top.ConfigInput(4);
                        break;
                    case SDLK_5:
                        view_top.ConfigInput(5);
                        break;
                    case SDLK_6:
                        view_top.ConfigInput(6);
                        break;
                    case SDLK_7:
                        view_top.ConfigInput(7);
                        break;
                    case SDLK_8:
                        view_top.ConfigInput(8);
                        break;
                    case SDLK_9:
                        view_top.ConfigInput(9);
                        break;
                    case SDLK_RETURN:
                        if (view_top.GetConfigPhase() >= 4) {
                            /* 初期ブロック配置
                            //InitBlock();
                            view_type = 1;
                            break;
                        }
                }
            }
            /* PLAY画面でのマウスイベント
            //if (view_type == PLAY_VIEW)
            if (false){
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
         //                   std::cout << "動かした" << std::endl;
 //                       }
                        break;
                }
            }
            /* 全画面共通のキー入力 */
   /*         if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RSHIFT){
                /* 初期化 *//*
                line = 0;
                row = 0;
                type = 0;
                chain = 0;
                config_phase = 0;
                //view_type = TOP_VIEW;
                current_block_index = 999;
            } */
        //}
        /* 1秒間に60回Updateされるようにする
        if (SDL_GetTicks() >= next_frame) {
            //if (view_type == TOP_VIEW) {
            //    UpdateTop();
            //} else if (view_type == PLAY_VIEW) {
            //    UpdatePlay();
            //};
            //Update();
            /* 時間がまだあるときはDrawする
            if (SDL_GetTicks() < next_frame + wait)
                Draw(this);
            next_frame += wait;
            SDL_Delay(0);
        }
    }
} */

// TOP画面描画
//void View::DrawTop(void){
//    // メインテキスト描画
//    SDL_BlitSurface(word_main, NULL, screen, &destrect_main_word);
    // サブテキスト描画
//    switch (config_phase) {
//        case 0:
//            word_sub = word_0;
//            break;
//        case 1:
//            word_sub = word_1;
//            break;
//        case 2:
//            word_sub = word_2;
//            break;
//        case 3:
//            word_sub = word_3;
//            break;
//        case 4:
//            word_sub = word_4;
//            break;
//    }
//    SDL_BlitSurface(word_sub, NULL, screen, &destrect_sub_word);
//
//    // 入力内容表示テキスト描画
//    char buf[50];
//    sprintf(buf, "行数：%d  列数：%d  ブロック：%d  連鎖：%d", line, row, type, chain);
//    word_input = TTF_RenderUTF8_Blended(font, buf, white);
//    SDL_BlitSurface(word_input, NULL, screen, &destrect_input_word);
//}

// PLAY画面描画
/* void View::DrawPlay(){
    /* ブロックを描画する *
    int i;
    for (i = 0; i < line * row; ++i) {
        if (i != current_block_index)
            DrawBlock(i);
    }
    if (current_block_index != 999)
        DrawBlock(current_block_index);
} */

/* void View::DrawBlock(int index){
    SDL_Rect srcrect;
//    SDL_Rect desrect = { (int)blocks[index].x, (int)blocks[index].y };
    if (index == current_block_index){
//        desrect = { (int)(current_block_x - current_block_x_diff), (int)(current_block_y - current_block_y_diff) };
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
    }
    if (blocks[index].alive == 1)
        SDL_BlitSurface(puzzle_block, &srcrect, screen, &desrect);
} */

int View::GetViewType(){
    return view_type;
}

void View::SetViewType(int value){
    view_type = value;
}

TTF_Font* View::GetFont(void){
    return font;
}

SDL_Window* View::GetWindow(void){
    return window;
}

SDL_Surface* View::GetScreen(void){
    return screen;
}

SDL_Surface* View::GetBackgroundImage(void){
    return background_image;
}

SDL_Surface* View::GetPuzzleBlock(void){
    return puzzle_block;
}