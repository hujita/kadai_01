//
//  puzzle_manager.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/03/01.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "puzzle_manager.h"

//
//  puzzle.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/02/25.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "puzzle_manager.h"

PuzzleManager::PuzzleManager(){
    state_choice = 0;
}

// パズル生成
void PuzzleManager::CreatePuzzle(Section* sections, Block* blocks, Config* config){
    int i;
    int j;
    int cnt = 0;
    for (i = 0; i < config->GetLine(); ++i){
        for (j = 0; j < config->GetRow(); ++j){
            // 区画配置
            Section section;
            section.Initialize(i, j, cnt, config);
            sections[cnt] = section;
            // ブロック配置
            Block block;
            block.Initialize(i, j, cnt, config);
            blocks[cnt] = block;
            ++cnt;
        }
    }
}

// 左クリックされた座標から選択されたブロックを探してactiveにする
void PuzzleManager::ChoiceBlock(Section* sections, Block* blocks, Config* config, double event_button_x, double event_button_y){
    // 左クリックされた座標から選択されたブロックを探す
    int position_index = LookForPositionBlock(sections, blocks, config, event_button_x, event_button_y);
    if (position_index != Invalid){
        // 選択されたブロックをアクティブにして操作対象と見做す
        blocks[position_index].Choice(sections, event_button_x, event_button_y);
        // ステータスをブロック操作中にする
        state_choice = ON;
    }
}

// 左クリックから指を離して操作中のブロックを解放する
void PuzzleManager::ReleaseBlock(Section* sections, Block* blocks, Config* config, double event_button_x, double event_button_y){
    // パズルの外枠からブロックが出れないように補正
    if (event_button_x >= config->GetRow() * SECTION_HIGH) {
        event_button_x = config->GetRow() * SECTION_HIGH - 10;
    }
    if (event_button_y >= config->GetLine() * SECTION_WIDE){
        event_button_y = config->GetLine() * SECTION_WIDE - 10;
    }
    
    // パズルの区画内にブロックが収まるように位置を整える
    // 左クリックされた座標から選択されたブロックを探す
    int active_index = LookForActiveBlock(blocks, config);
    if (active_index != Invalid){
        blocks[active_index].Release();
    }
    
    // ステータスをオフにする
    state_choice = OFF;
    // 連鎖チェック
    //CheckChain();
}

// ブロックを操作
void PuzzleManager::MoveBlock(Section* sections, Block* blocks, Config* config, double event_button_x, double event_button_y){
    // パズルの外枠からブロックが出れないように補正
    if (event_button_x >= config->GetRow() * SECTION_HIGH) {
        event_button_x = config->GetRow() * SECTION_HIGH - 10;
    }
    if (event_button_y >= config->GetLine() * SECTION_WIDE){
        event_button_y = config->GetLine() * SECTION_WIDE - 10;
    }
    
    // 座標が他のブロックの領域に入ったら配列の中身の値を交換
    // 交換のために値を避難
    int target_section_index = Invalid;
    
    
    // 操作中のブロックを見つける
    int active_index = LookForActiveBlock(blocks, config);
    // 現座標に位置するブロックを見つける
    int position_index = LookForPositionBlock(sections, blocks, config, event_button_x, event_button_y);
    // 移動に合わせて出力先座標更新
    blocks[active_index].Move(event_button_x, event_button_y);
    
    std::cout << "position_index=" << position_index << std::endl;
    std::cout << "active_index=" << active_index << std::endl;
    
    // 座標から取得したブロックが操作中のブロックと別のものだったら交換
    if (position_index != active_index && position_index != Invalid){
        // 所属する区画インデックスを交換

        target_section_index = blocks[position_index].GetSectionIndex();
        blocks[position_index].SetSectionIndex(blocks[active_index].GetSectionIndex());
        blocks[active_index].SetSectionIndex(target_section_index);
    }
}

// その座標のブロック
int PuzzleManager::LookForPositionBlock(Section* sections, Block* blocks, Config* config, double event_button_x, double event_button_y){
    int i;

    for (i = 0; i < config->GetLine() * config->GetRow(); ++i) {
        
        std::cout << "event_button_x" << event_button_x << std::endl;
        std::cout << "sections[blocks[i].GetSectionIndex()].GetDestinationX()" << sections[blocks[i].GetSectionIndex()].GetDestinationX() << std::endl;
        std::cout << "sections[blocks[i].GetSectionIndex()].GetDestinationY()" << sections[blocks[i].GetSectionIndex()].GetDestinationY() << std::endl;
        
        // i番目のブロックの出力座標X
        double destination_x = sections[blocks[i].GetSectionIndex()].GetDestinationX();
        // i番目のブロックの出力座標Y
        double destination_y = sections[blocks[i].GetSectionIndex()].GetDestinationY();
        if (destination_x <= event_button_x && event_button_x <= (destination_x + BLOCK_WIDE) && destination_y <= event_button_y && event_button_y <= (destination_y + BLOCK_HIGH)){
            return i;
        }
    }
    return Invalid;
}

// アクティブなブロック
int PuzzleManager::LookForActiveBlock(Block* blocks, Config* config){
    int i;
    for (i = 0; i < config->GetLine() * config->GetRow(); ++i) {
        if (blocks[i].GetActive() == ON){
            return i;
        }
    }
    return Invalid;
}

int PuzzleManager::GetStateChoice(){
    return state_choice;
}