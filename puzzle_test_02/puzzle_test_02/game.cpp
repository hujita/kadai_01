//
//  game.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/02/24.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "game.h"



// クラス初期化
Game::Game():
// 画面遷移用変数(TOP:0, PLAY:1)
view_type(0),
// 画面
window(nullptr),
// 画面の描画領域
screen(nullptr),
// 区画画像
section_image(nullptr),
// ブロック画像
block_image(nullptr),
// 粒子画像
particle_image(nullptr),
// フォント
font(nullptr),
big_font(nullptr),
music_main(nullptr),
music_break(nullptr)
{}


// ゲーム処理
int Game::Start() {
    // 初期化
    if (Initialize() < 0)
        return -1;
    // メインループ
    MainLoop();
    // 終了
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
    window = SDL_CreateWindow("パズルゲーム", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDE,WINDOW_HIGH,0);
    screen = SDL_GetWindowSurface(window);
    if (screen == NULL) {
        fprintf(stderr, "画面の初期化に失敗しました：%s\n", SDL_GetError());
        Finalize();
        return -1;
    }
    
    /* 画像を読み込む */
    section_image = IMG_Load("section_image.png");
    if (section_image == NULL) {
        fprintf(stderr, "画像の読み込みに失敗しました：%s\n", SDL_GetError());
        Finalize();
        return -1;
    }
    block_image = IMG_Load("block_image.png");
    if (block_image == NULL) {
        fprintf(stderr, "画像の読み込みに失敗しました：%s\n", SDL_GetError());
        Finalize();
        return -1;
    }
    particle_image = IMG_Load("particle_image.png");
    if (particle_image == NULL) {
        fprintf(stderr, "画像の読み込みに失敗しました：%s\n", SDL_GetError());
        Finalize();
        return -1;
    }
    
    // フォント読み込む
    font = TTF_OpenFont("AquaKana.ttc", 24);
    if (font == NULL) {
        fprintf(stderr, "fontの取得に失敗しました：%s\n", SDL_GetError());
        Finalize();
        return -1;
    }
    big_font = TTF_OpenFont("AquaKana.ttc", 36);
    if (big_font == NULL) {
        fprintf(stderr, "big_fontの取得に失敗しました：%s\n", SDL_GetError());
        Finalize();
        return -1;
    }
    
    // SDL_Mixerオープン
    Mix_OpenAudio(22050,AUDIO_S16,2,4096);
    // BGM読み込み
    music_main = Mix_LoadMUS("music_main.mp3");
    if (music_main == NULL) {
        fprintf(stderr, "music_mainの取得に失敗しました：%s\n", SDL_GetError());
        Finalize();
        return -1;
    }
    // ブロック破壊音読み込み
    music_break = Mix_LoadWAV("music_break.mp3");
    if (music_break == NULL) {
        fprintf(stderr, "music_breakの取得に失敗しました：%s\n", SDL_GetError());
        Finalize();
        return -1;
    }
    
    // 音量調節
    Mix_VolumeMusic(10);
    Mix_Volume(-1,5);
    
    
    return 0;
}

// 終了処理を行う
void Game::Finalize(void) {
    // 解放する
    SDL_FreeSurface(block_image);
    SDL_FreeSurface(section_image);
    SDL_FreeSurface(particle_image);
    TTF_CloseFont(font);
    TTF_CloseFont(big_font);
    Mix_FreeMusic(music_main);
    
    // 終了する
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}

// メインループ
void Game::MainLoop(void) {
    // 音楽再生
    Mix_PlayMusic(music_main,-1);
    // イベント
    SDL_Event event;
    double next_frame = SDL_GetTicks();
    double wait = 1000.0 / 60;
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
    // ストップウォッチ
    boost::timer t;
    
    for (;;) {
        // すべてのイベントを処理する
        while (SDL_PollEvent(&event)) {
            // 終了 (QUIT イベントが発生するか、ESC キーが押されたら)
            if ((event.type == SDL_QUIT) ||
                (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
                return;

            // TOP画面
            if (view_type == VIEW_TOP){
                // イベント処理
                int result = top.Event(&event, &config, &puzzle_manager, sections, blocks);
                if (result == ON){
                    view_type = VIEW_PLAY;
                }
            }
            
            // PLAY画面
            if (view_type == VIEW_PLAY){
                // イベント処理
                play.Event(&event, &config, &puzzle_manager, sections, blocks, &t);
            }
  
            // 全画面共通
            // キーボード操作
            if (event.type == SDL_KEYDOWN){
                // 右Shift
                if (event.key.keysym.sym == SDLK_RSHIFT){
                    // 設定初期化
                    config.Reset();
                    // ブロック未操作
                    play.SetFlagOperated(OFF);
                    // 得点リセット
                    puzzle_manager.ResetScore();
                    // 操作回数リセット
                    play.SetNumberOfOperations(OFF);
                    // クリア状況リセット
                    play.SetPlayResult(OFF);
                    // プレイ状況リセット
                    play.Reset();
                    // TOP画面へ遷移
                    view_type = VIEW_TOP;
                }
            }
        }
        
        // 1秒間に60回Updateされるようにする
        if (SDL_GetTicks() >= next_frame) {
            Update(&config, &puzzle_manager, sections, &top, &play, blocks);
            // 描画
            Draw(&config, sections, &top, &play, &puzzle_manager, blocks, &t);
            next_frame += wait;
            SDL_Delay(0);
        }
    }
}

// 描画
void Game::Draw(Config* config, Section* sections, Top* top, Play* play, PuzzleManager* puzzle_manager, Block* blocks, boost::timer* t){
    
    // 背景
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 192, 203));
    
    // TOP画面
    if (view_type == VIEW_TOP){
        top->Draw(screen, section_image, block_image, config, font, big_font);
    }
    
    // PLAY画面
    if (view_type == VIEW_PLAY){
        play->Draw(screen, font, section_image, block_image, config, puzzle_manager, sections, blocks, t);
    }

    // 画面を更新する
    SDL_UpdateWindowSurface(window);
}

// 更新
void Game::Update(Config* config, PuzzleManager* puzzle_manager, Section* sections, Top* top, Play* play, Block* blocks){
    // PLAY画面
    if (view_type == VIEW_PLAY && puzzle_manager->GetStateChoice() == OFF){
        // クリア
        if (play->GetNumberOfOperations() <= OPERATION_MAX && puzzle_manager->GetScore() >= SCORE_CREAR){
            play->SetPlayResult(ON);
        }
        if (play->GetFlagOperated() == ON) {
            // ブロック落下
            puzzle_manager->DropBlock(config, sections, blocks);
            // 連鎖が早すぎて見づらいので止める
            if (puzzle_manager->GetFreeze() == 0){
                puzzle_manager->AddFreeze(50);
            }
            puzzle_manager->AddFreeze(-1);
            // 全て描画済みなら次の描画を始める
            if (puzzle_manager->FlagAllDropDrawn(config, blocks) == ON && puzzle_manager->GetFreeze() == 0){
                // 連鎖チェック
                puzzle_manager->CheckChain(config, blocks, music_break);
                // 描画位置落下補正準備
                puzzle_manager->CheckDrop(config, blocks);
                // 落下処理
                //puzzle_manager->DropBlock(config, sections, blocks);
            }
        }
    }
}
