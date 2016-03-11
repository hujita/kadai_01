//
//  block.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/02/25.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "block.h"

Block::Block():
// 出力元
// 座標 & 高さ &幅
source_x(0),
source_y(0),
source_h(BLOCK_HIGH),
source_w(BLOCK_WIDE),
// ブロック種別
block_type(0),
// 現在位置している区画のインデックス
section_index(0),
// 生存
alive(0),
// 存在
exist(ON),
// アクティブ(マウス左クリックで選択されている)
active(0),
// 出力先座標とマウスポインタ座標の誤差(アクティブ時のみ使用)
difference_x(0),
difference_y(0),
// ブロックのクリックされている座標(アクティブ時のみ使用)
click_x(0),
click_y(0),
// 落下分誤差
drop_difference(0),
// 下方向に死んでるブロックがある
count_drop(0),
// 下方向に非実在ブロックがある
count_exist(0)
{}

// ブロック生成
// 1列目を埋めてから2列目と埋めていく
// [param] i:行番号, j:列番号, cnt:整列番号, config: 設定インスタンス
// [return] Block
void Block::Initialize(int i, int j, int cnt, Config* config){
    MyMath my_math;
    
    // ブロック種別
    block_type = my_math.Random(0, config->GetType() - 1, cnt);
    // 出力元
    // 座標 & 高さ &幅
    int position[2] = {};
    SourcePosition(block_type, position);
    source_x = position[0];
    source_y = position[1];
    source_h = BLOCK_HIGH;
    source_w = BLOCK_WIDE;
    // 現在位置している区画(整列番号)
    section_index = cnt;
    // 生存
    alive = ON;
    // アクティブ(マウス左クリックで選択されている)
    active = 0;
    // 出力先座標とマウスポインタ座標の誤差(アクティブ時のみ使用)
    difference_x = 0;
    difference_y = 0;
    // ブロックのクリックされている座標(アクティブ時のみ使用)
    click_x = 0;
    click_y = 0;
}

// ブロック再生成
void Block::ReCreate(Config* config, int cnt){
    MyMath my_math;
    block_type = my_math.Random(0, config->GetType() - 1, cnt);
    // 出力元
    // 座標 & 高さ &幅
    int position[2] = {};
    SourcePosition(block_type, position);
    source_x = position[0];
    source_y = position[1];
    source_h = BLOCK_HIGH;
    source_w = BLOCK_WIDE;
    // 生存
    alive = ON;
}

// 出力元画像の座標を取得
void Block::SourcePosition(int block_type, int* position){
    switch (block_type) {
        case 0:
            position[0] = BLOCK_POSITION_00_X;
            position[1] = BLOCK_POSITION_00_Y;
            break;
        case 1:
            position[0] = BLOCK_POSITION_01_X;
            position[1] = BLOCK_POSITION_01_Y;
            break;
        case 2:
            position[0] = BLOCK_POSITION_02_X;
            position[1] = BLOCK_POSITION_02_Y;
            break;
        case 3:
            position[0] = BLOCK_POSITION_03_X;
            position[1] = BLOCK_POSITION_03_Y;
            break;
        case 4:
            position[0] = BLOCK_POSITION_04_X;
            position[1] = BLOCK_POSITION_04_Y;
            break;
        case 5:
            position[0] = BLOCK_POSITION_05_X;
            position[1] = BLOCK_POSITION_05_Y;
            break;
        case 6:
            position[0] = BLOCK_POSITION_06_X;
            position[1] = BLOCK_POSITION_06_Y;
            break;
        case 7:
            position[0] = BLOCK_POSITION_07_X;
            position[1] = BLOCK_POSITION_07_Y;
            break;
        case 8:
            position[0] = BLOCK_POSITION_08_X;
            position[1] = BLOCK_POSITION_08_Y;
            break;
        default:
            break;
    }
}

// 描画位置の落下補正
void Block::DropDraw(){
    // 1000ms/60 あたりの落下距離
    double drop_qty = ((SECTION_HIGH / 60) + (SECTION_HIGH % 60)) / 2.5;
    if (count_drop > 0){
        drop_difference += drop_qty;
        count_drop = count_drop - drop_qty;
    }
}

// 描画位置の落下補正値のリセット
void Block::ResetDropDraw(){
    count_drop = 0;
    drop_difference = 0;
}

void Block::Draw(SDL_Surface* screen, SDL_Surface* block_image, Section* sections, Config* config){
    SDL_Rect srcrect;
    // 操作対象でないブロックは、自身が所属している区画の出力座標位置を参考に、自身の出力位置を決める
    double destination_x = sections[section_index].GetDestinationX();
    double destination_y = sections[section_index].GetDestinationY();
    SDL_Rect desrect = { (int)(destination_x + SECTION_SPACE_WIDE), (int)(destination_y + SECTION_SPACE_HIGH + drop_difference) };
    // 操作中のブロックは、
    if (active == ON){
        desrect = { (int)(click_x - difference_x), (int)(click_y - difference_y) };
    }

    srcrect.x = source_x;
    srcrect.y = source_y;
    srcrect.w = source_w;
    srcrect.h = source_h;
    
    if (alive == ON){
        SDL_BlitSurface(block_image, &srcrect, screen, &desrect);
    }
}

void Block::Choice(Section* sections, double event_button_x, double event_button_y){
    if (exist == ON){
        active = ON;
        // 出力先座標とマウスポインタ座標の誤差(アクティブ時のみ使用)
        difference_x = (event_button_x - sections[section_index].GetDestinationX());
        difference_y = (event_button_y - sections[section_index].GetDestinationY());
        // ブロックのクリックされている座標(アクティブ時のみ使用)
        click_x = event_button_x;
        click_y = event_button_y;
    }
}

void Block::Release(){
    active = OFF;
    // 出力先座標とマウスポインタ座標の誤差戻す(アクティブ時のみ使用)
    difference_x = OFF;
    difference_y = OFF;
    // ブロックのクリックされている座標(アクティブ時のみ使用)
    click_x = OFF;
    click_y = OFF;
}

void Block::Move(double event_button_x, double event_button_y){
    click_x = event_button_x;
    click_y = event_button_y;
}

void Block::AddCountDrop(int value){
    count_drop += value;
}

void Block::AddCountExist(int value){
    count_exist += value;
}

void Block::ChangeType(int type){
    // ブロック種別
    block_type = type;
    // 出力元
    // 座標 & 高さ &幅
    int position[2] = {};
    SourcePosition(block_type, position);
    source_x = position[0];
    source_y = position[1];
}

// Getter
int Block::GetActive() { return active; }
int Block::GetSectionIndex(){ return section_index; }
int Block::GetBlockType(){ return block_type; }
int Block::GetAlive(){ return alive; }
int Block::GetExist(){ return exist; }
double Block::GetCountDrop(){ return count_drop; }
// Setter
void Block::SetSectionIndex(int value){ section_index = value; }
void Block::SetAlive(int value){ alive = value; }
void Block::SetExist(int value){ exist = value; }

