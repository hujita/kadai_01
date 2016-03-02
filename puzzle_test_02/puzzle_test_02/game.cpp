//
//  game.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/02/24.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "game.h"
#include <iostream>
#include "config.h"

// ゲーム開始
int Start();
// ゲーム初期化
int Initialize();
// 終了処理
void Finalize();
// メイン処理
void MainLoop();
// 描画処理
void Draw();

// クラス初期化
Game::Game() {
    // 画面遷移用変数(TOP:0, PLAY:1)
    view_type = 0;
    // 設定画面フェイズ
    config_phase = 0;
    // 行数
    line = 0;
    // 列数
    row = 0;
    // ブロック種類数
    type = 0;
    // 必要連結数
    chain = 0;

    
    // 画面
    window = NULL;
    // 画面の描画領域
    screen = NULL;
    // 背景画像
    background_image = NULL;
    // 区画画像
    section_image = NULL;
    // ブロック画像
    block_image = NULL;
    // 設定画面メインテキスト
    word_main = NULL;
    // 設定画面サブテキスト
    word_sub = NULL;
    // 設定画面入力内容テキスト
    word_input = NULL;
    // フォント
    font = NULL;
    // 色
    black = {0x00, 0x00, 0x00};
    white = {0xff, 0xff, 0xff};
    // メインテキスト描画位置
    destrect_main_word = { 330, 210 };
    // サブテキスト描画位置
    destrect_sub_word = { 330, 310 };
    // 入力内容描画位置
    destrect_input_word = { 330, 410 };
}

// ゲーム処理
// 初期化 -> メイン処理 -> 終了処理
int Game::Start(){
    // 初期化
    if (Initialize() < 0)
        return -1;
    // メイン処理
    MainLoop();
    // 終了処理
    Finalize();
    return 0;
}

// 初期化する。
// 成功したときは0を、失敗したときは-1を返す。
int Game::Initialize(void)
{
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
    
    /* フォント読み込み */
    font = TTF_OpenFont("AquaKana.ttc", 24);
    if (font == NULL) {
        fprintf(stderr, "fontの取得に失敗しました：%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    return 0;
}

// 終了処理を行う
void Game::Finalize(void)
{
    SDL_FreeSurface(background_image);
    SDL_FreeSurface(block_image);
    TTF_CloseFont(font);
    
    // 終了する
    TTF_Quit();
    SDL_Quit();
}

// メインループ
void Game::MainLoop(void)
{
    SDL_Event event;
    // ゲーム設定
    Config config;
    // キーボード入力変換機
    MyKeyboard my_keyboard;
    // ブロック群
    Block blocks[BLOCK_MAX] = {};
    // パズルの区画やブロックを並べる
    PuzzleManager puzzle_manager;
    // 区画
    Section sections[SECTION_MAX] = {};
    // パズル
    //Puzzle puzzle;
    
    for (;;) {
        // すべてのイベントを処理する
        while (SDL_PollEvent(&event)) {
            // QUIT イベントが発生するか、ESC キーが押されたら終了する
            if ((event.type == SDL_QUIT) ||
                (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
                return;
            
            // TOP画面
            if (view_type == VIEW_TOP){
                // キーボード操作
                if (event.type == SDL_KEYDOWN){
                    // 数値キーなら
                    // 数値に変換
                    int input_value = my_keyboard.CastIntFromKey(event.key.keysym.sym);
                    // ゲームの設定更新
                    if (input_value < 10){
                        config.Set(input_value);
                    }
                    // エンターキーなら
                    if (event.key.keysym.sym == SDLK_RETURN){
                        // 設定が終了しているなら
                        if (config.GetState() >= CONFIG_STATE_MAX) {
                            // 初期ブロック配置
                            //puzzle.Initialize(blocks, &config);
                            // パズル生成
                            puzzle_manager.CreatePuzzle(sections, blocks, &config);
                            // PLAY画面へ遷移
                            view_type = VIEW_PLAY;
                        }
                    }
                }
            }
            
            // PLAY画面
            if (view_type == VIEW_PLAY){
                // マウス操作
                switch(event.type){
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_PRESSED){
                            // 左クリックされた座標から選択されたブロックを探してactiveにする
                            puzzle_manager.ChoiceBlock(sections, blocks, &config, event.button.x, event.button.y);
                            //std::cout << "左ボタン押した" << std::endl;
                        }
                        break;
                    case SDL_MOUSEBUTTONUP:
                        if (event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_RELEASED){
                            // ブロックを解放する
                            puzzle_manager.ReleaseBlock(sections, blocks, &config, event.button.x, event.button.y);
                            //std::cout << "左ボタンはなした" << std::endl;
                        }
                        break;
                    case SDL_MOUSEMOTION:
                        if (puzzle_manager.GetStateChoice() == 1) {
                            puzzle_manager.MoveBlock(sections, blocks, &config, event.button.x, event.button.y);
                            // std::cout << "動かした" << std::endl;
                        }
                        break;
                }
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
                    //current_block_index = 999;
                }
            }
            
            // 描画処理
            Draw(&config, sections, blocks);
        }
    }
}

void Game::Draw(Config* config, Section* sections, Block* blocks){
    
    // 背景を描画
    //SDL_BlitSurface(background_image, NULL, screen, NULL);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 192, 203));
    
    // TOP画面
    if (view_type == VIEW_TOP){
        // メインテキスト用意
        word_main = TTF_RenderUTF8_Blended(font, "パズルの設定(1~9で入力)", black);
        // サブテキスト用意
        word_sub = TTF_RenderUTF8_Blended(font, config->GetQuestion(), black);
        // 入力内容表示テキスト用意
        //config->GetResult();戻り値がうまくいかず
        char buf[50];
        sprintf(buf, "行数：%d  列数：%d  ブロック：%d  連鎖：%d",
                config->GetLine(), config->GetRow(), config->GetType(), config->GetChain());
        word_input = TTF_RenderUTF8_Blended(font, buf, black);
        
        // メインテキスト描画
        SDL_BlitSurface(word_main, NULL, screen, &destrect_main_word);
        // サブテキスト描画
        SDL_BlitSurface(word_sub, NULL, screen, &destrect_sub_word);
        // 入力内容表示テキスト描画
        SDL_BlitSurface(word_input, NULL, screen, &destrect_input_word);
    }
    
    // PLAY画面
    if (view_type == VIEW_PLAY){
        // 区画を描画
        int i;
        for (i = 0; i < config->GetLine() * config->GetRow(); ++i) {
            sections[i].Draw(screen, section_image);
        };
        
        // ブロックを描画
        int j;
        // マウスで選択中のブロック
        int target_index = Invalid;
        for (j = 0; j < config->GetLine() * config->GetRow(); ++j) {
            if (blocks[j].GetActive() == OFF){
                blocks[j].Draw(screen, block_image, sections);
            }
            if (blocks[j].GetActive() == ON){
                target_index = j;
            }
        }
        if (target_index != Invalid){
            blocks[target_index].Draw(screen, block_image,  sections);
        }
    }
    
    // 画面を更新する
    SDL_UpdateWindowSurface(window);
}