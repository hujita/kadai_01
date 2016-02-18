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

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <boost/format.hpp>
#include <boost/random.hpp>

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

typedef struct {
    double x, y;        /* 出力先座標 */
    int type;           /* 0:doctor, 1:girl, 2:hanamiju, 3:madam, 4:boy, 5:UMA, 6:woman, 7:worker, 8:yankee */
} Block;

typedef struct {
    double x, y, w, h;        /* 取得先ノ座標幅高 */
} BlockType;

/* ブロック数。最大で9*(9+1)=90 */
Block blocks[90];
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

SDL_Window* window = NULL;                  /* 画面 */
SDL_Surface* screen = NULL;                 /* 画面の描画領域 */
SDL_Surface* background_image = NULL;       /* 背景画像 */
SDL_Surface* puzzle_block = NULL;           /* ブロック */

SDL_Surface* word_main = NULL;              /* メインテキスト */
SDL_Surface* word_sub = NULL;               /* サブテキスト */
SDL_Surface* word_input = NULL;             /* 入力内容テキスト */
SDL_Surface* word_0 = NULL;                 /* テキスト */
SDL_Surface* word_1 = NULL;                 /* テキスト */
SDL_Surface* word_2 = NULL;                 /* テキスト */
SDL_Surface* word_3 = NULL;                 /* テキスト */
SDL_Surface* word_4 = NULL;                 /* テキスト */

TTF_Font* font;                             /* フォント */
SDL_Color white = {0xff, 0xff, 0xff};       /* 色 */
SDL_Rect destrect_main_word = { 330, 210 }; /* コメント位置 */
SDL_Rect destrect_sub_word = { 330, 310 };  /* サブコメント位置 */
SDL_Rect destrect_input_word = { 330, 410 };  /* 入力内容表示位置 */

int view_type = 0;                          /* 0:TOP, 1:Play */
int config_phase = 0;                       /* 設定の段階 */
int line = 0;                               /* 行数 */
int row = 0;                                /* 列数 */
int type = 0;                               /* ブロック種類数 */
int chain = 0;                                /* 必要連鎖数 */
double x, y;                                /* 音符の座標 */
const int TOP_VIEW = 0;
const int PLAY_VIEW = 1;

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

/* lower 以上 upper 以下の乱数を返す */
int Random(int lower, int upper, int cnt)
{
    using namespace boost;
    //return ((double)rand() / RAND_MAX) * (upper - lower) + lower;
    // 「メルセンヌツイスター」( Seed=現在時刻 ) で
    // 「小さな整数の一様乱数」( 1～6 ) を生成
    // 現在時刻なので1秒間に60回呼び出されるので60個同じ数値が連続で生まれてしまう…
    mt19937            gen( SDL_GetTicks() * cnt );
    uniform_smallint<> dst( lower, upper );
    variate_generator<
    mt19937&, uniform_smallint<>
    > rand( gen, dst );
    
    return rand();
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

void DrawBlock(int index){
    SDL_Rect srcrect;
    SDL_Rect desrect = { (int)blocks[index].x, (int)blocks[index].y };
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
    //std::cout << block_types[0].w << std::endl;
    SDL_BlitSurface(puzzle_block, &srcrect, screen, &desrect);
}


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

void InitBlock(){
    int i;
    int j;
    int cnt = 0;
    for (i = 0; i < line; ++i){
        for (j = 0; j < row; ++j){
            blocks[cnt].x = (95 * i);
            blocks[cnt].y = (95 * j);
            blocks[cnt].type = Random(0, type - 1, cnt);
            ++cnt;
        }
    }
    std::cout << line << std::endl;
    std::cout << row << std::endl;
}

/* PLAY画面更新 */
void UpdatePlay(void)
{
    
    //InitBlock();
    //CreateBlock(320, 240, Random(0, 8));
}
/* 描画する */
void Draw(void)
{

    /* 背景を描画する */
    SDL_BlitSurface(background_image, NULL, screen, NULL);
    /* TOP画面の描画 */
    if (view_type == TOP_VIEW) {
        /* メインテキスト描画 */
        SDL_BlitSurface(word_main, NULL, screen, &destrect_main_word);
        /* サブテキスト描画 */
        switch (config_phase) {
            case 0:
                word_sub = word_0;
                break;
            case 1:
                word_sub = word_1;
                break;
            case 2:
                word_sub = word_2;
                break;
            case 3:
                word_sub = word_3;
                break;
            case 4:
                word_sub = word_4;
                break;
        }
        SDL_BlitSurface(word_sub, NULL, screen, &destrect_sub_word);
    
        /* 入力内容表示テキスト描画 */
        char buf[50];
        sprintf(buf, "行数：%d  列数：%d  ブロック：%d  連鎖：%d", line, row, type, chain);
        word_input = TTF_RenderUTF8_Blended(font, buf, white);
        SDL_BlitSurface(word_input, NULL, screen, &destrect_input_word);
    }
    /* PLAY画面の描画 */
    if (view_type == PLAY_VIEW){
        /* ブロックを描画する */
        int i;
        //SDL_BlitSurface(puzzle_block, NULL, screen, NULL);
        for (i = 0; i < line * row; ++i) {
            DrawBlock(i);
        }
        //DrawBlock(2);
    }
    
    /* 画面を更新する */
    SDL_UpdateWindowSurface(window);
}


/* 初期化する。
 * 成功したときは0を、失敗したときは-1を返す。
 */
int Initialize(void)
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
    
    /* 文字作成 */
    word_main = TTF_RenderUTF8_Blended(font, "パズルの設定(1~9で入力)", white);
    word_0 = TTF_RenderUTF8_Blended(font, "行数を指定してください", white);
    word_1 = TTF_RenderUTF8_Blended(font, "列数を指定してください", white);
    word_2 = TTF_RenderUTF8_Blended(font, "ブロックの種類数を指定してください", white);
    word_3 = TTF_RenderUTF8_Blended(font, "ブロックを繋げるべき数を指定してください", white);
    word_4 = TTF_RenderUTF8_Blended(font, "Enter:ゲーム開始 / 右Shift:TOPに戻る / ESC:終了", white);
    
    return 0;
}

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


/* メインループ */
void MainLoop(void)
{
    SDL_Event event;
    double next_frame = SDL_GetTicks();
    double wait = 1000.0 / 60;
    
    for (;;) {
        /* すべてのイベントを処理する */
        while (SDL_PollEvent(&event)) {
            /* QUIT イベントが発生するか、ESC キーが押されたら終了する */
            if ((event.type == SDL_QUIT) ||
                (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
                return;
            /* TOP画面でのキー入力 */
            if (view_type == TOP_VIEW && event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym) {
                    case SDLK_1:
                        ConfigTopInput(1);
                        break;
                    case SDLK_2:
                        ConfigTopInput(2);
                        break;
                    case SDLK_3:
                        ConfigTopInput(3);
                        break;
                    case SDLK_4:
                        ConfigTopInput(4);
                        break;
                    case SDLK_5:
                        ConfigTopInput(5);
                        break;
                    case SDLK_6:
                        ConfigTopInput(6);
                        break;
                    case SDLK_7:
                        ConfigTopInput(7);
                        break;
                    case SDLK_8:
                        ConfigTopInput(8);
                        break;
                    case SDLK_9:
                        ConfigTopInput(9);
                        break;
                    case SDLK_RETURN:
                        if (config_phase >= 4) {
                            /* 初期ブロック配置 */
                            InitBlock();
                            view_type = PLAY_VIEW;
                            break;
                        }
                }
            }
            /* 全画面共通のキー入力 */
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RSHIFT){
                line = 0;
                row = 0;
                type = 0;
                chain = 0;
                config_phase = 0;
                view_type = TOP_VIEW;
            }
        }
        /* 1秒間に60回Updateされるようにする */
        if (SDL_GetTicks() >= next_frame) {
            if (view_type == TOP_VIEW) {
                UpdateTop();
            } else if (view_type == PLAY_VIEW) {
                UpdatePlay();
            };
            //Update();
            /* 時間がまだあるときはDrawする */
            if (SDL_GetTicks() < next_frame + wait)
                Draw();
            next_frame += wait;
            SDL_Delay(0);
        }
    }
}


/* 終了処理を行う */
void Finalize(void)
{
    SDL_FreeSurface(background_image);
    SDL_FreeSurface(puzzle_block);
    TTF_CloseFont(font);
    
    /* 終了する */
    TTF_Quit();
    SDL_Quit();
}


/* メイン関数 */
/* 初期化 -> メイン処理 -> 終了処理 */
int main(int argc, char* argv[])
{
    if (Initialize() < 0)
        return -1;
    MainLoop();
    Finalize();
    return 0;
}