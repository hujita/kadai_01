//
//  puzzle.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/02/25.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "puzzle.h"

Puzzle::Puzzle(){
    state_choice = 0;
}

// パズル設定に従ってブロック生成を繰り返し、渡された配列を満たす
void Puzzle::Initialize(Block* blocks, Config* config){
    int i;
    int j;
    int cnt = 0;
    for (i = 0; i < config->GetLine(); ++i){
        for (j = 0; j < config->GetRow(); ++j){
            Block block;
            block.Initialize(i, j, cnt, config);
            blocks[cnt] = block;
            ++cnt;
        }
    }
}

// 左クリックされた座標から選択されたブロックを探してactiveにする
void Puzzle::ChoiceBlock(Block* blocks, Config* config, double event_button_x, double event_button_y){
    // 左クリックされた座標から選択されたブロックを探す
    int position_index = LookForTargetBlock(blocks, config, event_button_x, event_button_y);
    if (position_index != Invalid){
        // 選択されたブロックをアクティブにして操作対象と見做す
        blocks[position_index].Choice(event_button_x, event_button_y);
        // ステータスをブロック操作中にする
        state_choice = ON;
    }
}

// 左クリックから指を離して操作中のブロックを解放する
void Puzzle::ReleaseBlock(Block* blocks, Config* config, double event_button_x, double event_button_y){
    // パズルの外枠からブロックが出れないように補正
    if (event_button_x >= config->GetRow() * SECTION_HIGH) {
        event_button_x = config->GetRow() * SECTION_HIGH - 10;
    }
    if (event_button_y >= config->GetLine() * SECTION_WIDE){
        event_button_y = config->GetLine() * SECTION_WIDE - 10;
    }
    
    // パズルの区画内にブロックが収まるように位置を整える
    // 左クリックされた座標から選択されたブロックを探す
    int target_index = LookForTargetBlock(blocks, config, event_button_x, event_button_y);
    if (target_index != Invalid){
        blocks[target_index].Release();
    }
    
    // ステータスをオフにする
    state_choice = OFF;
    // 連鎖チェック
    //CheckChain();
}

// ブロックを操作
void Puzzle::MoveBlock(Block* blocks, Config* config, double event_button_x, double event_button_y){
    // パズルの外枠からブロックが出れないように補正
    if (event_button_x >= config->GetRow() * SECTION_HIGH) {
        event_button_x = config->GetRow() * SECTION_HIGH - 10;
    }
    if (event_button_y >= config->GetLine() * SECTION_WIDE){
        event_button_y = config->GetLine() * SECTION_WIDE - 10;
    }
    
    // 座標が他のブロックの領域に入ったら配列の中身の値を交換
    // 交換のために値を避難
    double target_destination_x = Invalid;
    double target_destination_y = Invalid;
    int target_section = Invalid;
    
    
    // 操作中のブロックを見つける
    int active_index = LookForActiveBlock(blocks, config);
    // 現座標に位置するブロックを見つける
    int target_index = LookForTargetBlock(blocks, config, event_button_x, event_button_y);
    // 移動に合わせて出力先座標更新
    blocks[active_index].Move(event_button_x, event_button_y);
    
    // 座標から取得したブロックが操作中のブロックと別のものだったら交換
    if (active_index != target_index){
        // 避難
        target_destination_x = blocks[target_index].GetDestinationX();
        target_destination_y = blocks[target_index].GetDestinationY();
        target_section = blocks[target_index].GetTargetSection();
        
        blocks[target_index].SetDestinationX(blocks[active_index].GetDestinationX());
        blocks[target_index].SetDestinationY(blocks[active_index].GetDestinationX());
        blocks[target_index].SetSection(blocks[active_index].GetDestinationX());

        blocks[active_index].SetDestinationX(target_destination_x);
        blocks[active_index].SetDestinationY(target_destination_y);
        blocks[active_index].SetSection(target_section);
    }
}

// その座標のブロック
int Puzzle::LookForTargetBlock(Block* blocks, Config* config, double event_button_x, double event_button_y){
    int i;
    for (i = 0; i < config->GetLine() * config->GetRow(); ++i) {
        if (blocks[i].GetDestinationX() <= event_button_x && event_button_x <= (blocks[i].GetDestinationX() + BLOCK_WIDE) && blocks[i].GetDestinationY() <= event_button_y && event_button_y <= (blocks[i].GetDestinationY() + BLOCK_HIGH)){
            return i;
        }
    }
    return Invalid;
}

// アクティブなブロック
int Puzzle::LookForActiveBlock(Block* blocks, Config* config){
    int i;
    for (i = 0; i < config->GetLine() * config->GetRow(); ++i) {
        if (blocks[i].GetActive() == ON){
            return i;
        }
    }
    return Invalid;
}

int Puzzle::GetStateChoice(){
    return state_choice;
}