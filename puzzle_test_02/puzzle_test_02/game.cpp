//
//  game.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/02/24.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "game.h"



// クラス初期化
Game::Game() {
    // 画面遷移用変数(TOP:0, PLAY:1)
    view_type = 0;
    
    // 画面
    window = NULL;
    // 画面の描画領域
    screen = NULL;
    // 区画画像
    section_image = NULL;
    // ブロック画像
    block_image = NULL;
    // フォント
    font = NULL;
}

// ゲーム処理
// 初期化 -> メイン処理 -> 終了処理
int Game::Start() {
    // 初期化
    if (Initialize() < 0)
        return -1;
    // メイン処理
    MainLoop();
    // 終了処理
    Finalize();
    return 0;
}

// 初期化
// 成功したときは0を、失敗したときは-1を返す。
int Game::Initialize(void) {
    // 初期化
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
        fprintf(stderr, "SDLの初期化に失敗しました：%s\n", SDL_GetError());
        return -1;
    }
    if (TTF_Init() < 0) {
        fprintf(stderr, "TTFの初期化に失敗しました：%s\n", TTF_GetError());
        return -1;
    }
    window = SDL_CreateWindow("パズルゲーム", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1400,850,0);
    screen = SDL_GetWindowSurface(window);
    if (screen == NULL) {
        fprintf(stderr, "画面の初期化に失敗しました：%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    
    /* 画像を読み込む */
    section_image = IMG_Load("section_image.png");
    if (section_image == NULL) {
        fprintf(stderr, "画像の読み込みに失敗しました：%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    block_image = IMG_Load("block_image.png");
    if (block_image == NULL) {
        fprintf(stderr, "画像の読み込みに失敗しました：%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    
    /* フォント読み込む */
    font = TTF_OpenFont("AquaKana.ttc", 24);
    if (font == NULL) {
        fprintf(stderr, "fontの取得に失敗しました：%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    return 0;
}

// 終了処理を行う
void Game::Finalize(void) {
    // 解放する
    SDL_FreeSurface(block_image);
    SDL_FreeSurface(section_image);
    TTF_CloseFont(font);
    
    // 終了する
    TTF_Quit();
    SDL_Quit();
}

// メインループ
void Game::MainLoop(void) {
    // イベント
    SDL_Event event;
    // TOP画面
    Top top;
    // PLAY画面
    Play play;
    // ゲーム設定
    Config config;
    // パズルの区画やブロックを並べる
    PuzzleManager puzzle_manager;
    // ブロックの集合
    Block blocks[BLOCK_MAX] = {};
    // 区画の集合
    Section sections[SECTION_MAX] = {};
    
    for (;;) {
        // すべてのイベントを処理する
        while (SDL_PollEvent(&event)) {
            // QUIT イベントが発生するか、ESC キーが押されたら終了する
            if ((event.type == SDL_QUIT) ||
                (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
                return;
            
            // TOP画面
            if (view_type == VIEW_TOP){
                // イベント処理
                view_type = top.Event(&event, &config, &puzzle_manager, sections, blocks);
            }
            
            // PLAY画面
            if (view_type == VIEW_PLAY){
                // イベント処理
                play.Event(&event, &config, &puzzle_manager, sections, blocks);
            }
  
            // 全画面共通
            // キーボード操作
            if (event.type == SDL_KEYDOWN){
                // 右Shift
                if (event.key.keysym.sym == SDLK_RSHIFT){
                    // 設定初期化
                    config.Reset();
                    // TOP画面へ遷移
                    view_type = VIEW_TOP;
                }
            }
            
            // 描画処理
            Draw(&config, sections, &top, &play, blocks);
        }
    }
}

void Game::Draw(Config* config, Section* sections, Top* top, Play* play, Block* blocks){
    
    // 背景を描画
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 192, 203));
    
    // TOP画面
    if (view_type == VIEW_TOP){
        top->Draw(screen, config, font);
    }
    
    // PLAY画面
    if (view_type == VIEW_PLAY){
        play->Draw(screen, section_image, block_image, config, sections, blocks);
    }
    
    // 画面を更新する
    SDL_UpdateWindowSurface(window);
}