//
//  puzzle_manager.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/03/01.
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

// 連鎖成立しているか確認
void PuzzleManager::CheckChain(Config* config, Block* blocks){
    // 縦方向に連結していたらブロック消滅
    int i;
    int j;
    int cnt;
    // 全ブロックを確認
    for (i = 0; i < config->GetLine() * config->GetRow(); ++i) {
        // 連鎖確認の標的
        int chain_result = i;
        // 連結しているブロックのインデックスを追加していく
        std::vector<int> array;
        // i番目のブロックの連結について確認
        // 指定されたchain数だけ確認する
        for (j = 0; j < config->GetChain(); ++j){
            // 連結が終わっていたら処理しない
            if (chain_result != Invalid){
                // 最初の一つ目は配列に加える
                if (j == 0){
                    array.push_back(i);
                }
                // 真上のブロックが同じ種類なら真上のブロックのインデックスを返す
                chain_result = CheckRowChain(config, blocks, chain_result);
                // 真上のブロックが同じ種類なら配列にインデックスを追加
                if (chain_result != Invalid)
                    array.push_back(chain_result);
                // 必要連結回数目もchain_resultが−1になっていなければ配列内のブロックを全て消滅させる
                if (j == (config->GetChain() - 1)){
                    for (cnt = 0; cnt < config->GetChain(); ++cnt){
                        blocks[array[cnt]].SetAlive(OFF);
                    }
                }
            }
        }
    }
    
    // 横方向に連結していたらブロック消滅
    // 全ブロックを確認
    for (i = 0; i < config->GetLine() * config->GetRow(); ++i) {
        // 連鎖確認の標的
        int chain_result = i;
        // 連結しているブロックのインデックスを追加していく
        std::vector<int> array;
        // i番目のブロックの連結について確認
        // 指定されたchain数だけ確認する
        for (j = 0; j < config->GetChain(); ++j){
            // 連結が終わっていたら処理しない
            if (chain_result != Invalid){
                // 最初の一つ目は配列に加える
                if (j == 0){
                    array.push_back(i);
                }
                // 真上のブロックが同じ種類なら真上のブロックのインデックスを返す
                chain_result = CheckLineChain(config, blocks, chain_result);
                // 真上のブロックが同じ種類なら配列にインデックスを追加
                if (chain_result != Invalid)
                    array.push_back(chain_result);
                // 必要連結回数目もchain_resultが−1になっていなければ配列内のブロックを全て消滅させる
                if (j == (config->GetChain() - 1)){
                    for (cnt = 0; cnt < config->GetChain(); ++cnt){
                        blocks[array[cnt]].SetAlive(OFF);
                    }
                }
            }
        }
    }
}

// 縦の連鎖チェック
int PuzzleManager::CheckRowChain(Config* config, Block* blocks, int before_index){
    int i;
    // 全ブロックの中から
    for (i = 0; i < config->GetLine() * config->GetRow(); ++i){
        // 真下のブロックを見つける && そのブロックが次の行の最上段のブロックではない
        if (blocks[i].GetSectionIndex() == (blocks[before_index].GetSectionIndex() + 1) && blocks[i].GetSectionIndex() % config->GetRow() != 0){
            // ブロックの種類が同じなら真上のブロックのインデックスを返す
            if (blocks[i].GetBlockType() == blocks[before_index].GetBlockType()){
                return i;
            }
            
        }
    }
    return Invalid;
}

// 縦の連鎖チェック
int PuzzleManager::CheckLineChain(Config* config, Block* blocks, int before_index){
    int i;
    // 全ブロックの中から
    for (i = 0; i < config->GetLine() * config->GetRow(); ++i){
        // 右のブロックを見つける && そのブロックが次の列の最左のブロックではない
        if (blocks[i].GetSectionIndex() == (blocks[before_index].GetSectionIndex() + config->GetRow()) && blocks[i].GetSectionIndex() % config->GetRow() < config->GetRow()){
            // ブロックの種類が同じなら真上のブロックのインデックスを返す
            if (blocks[i].GetBlockType() == blocks[before_index].GetBlockType()){
                return i;
            }
            
        }
    }
    return Invalid;
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
    if (event_button_x >= config->GetLine() * SECTION_HIGH) {
        event_button_x = config->GetLine() * SECTION_HIGH - SECTION_LIMIT;
    }
    if (event_button_y >= config->GetRow() * SECTION_WIDE){
        event_button_y = config->GetRow() * SECTION_WIDE - SECTION_LIMIT;
    }
    
    // 操作中のブロックを探す
    int active_index = LookForActiveBlock(blocks, config);
    // パズルの区画内にブロックが収まるように位置を整える
    if (active_index != Invalid){
        blocks[active_index].Release();
    }
    
    // ステータスをオフにする
    state_choice = OFF;
    // 連鎖チェック
    CheckChain(config, blocks);
}

// ブロックを操作
void PuzzleManager::MoveBlock(Section* sections, Block* blocks, Config* config, double event_button_x, double event_button_y){
    // パズルの外枠からブロックが出れないように補正
    if (event_button_x >= config->GetLine() * SECTION_HIGH) {
        event_button_x = config->GetLine() * SECTION_HIGH - SECTION_LIMIT;
    }
    if (event_button_y >= config->GetRow() * SECTION_WIDE){
        event_button_y = config->GetRow() * SECTION_WIDE - SECTION_LIMIT;
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
    
    // 座標から取得したブロックが操作中のブロックと別のものだったら交換
    if (position_index != active_index && position_index != Invalid){
        // 所属する区画インデックスを交換
        target_section_index = blocks[position_index].GetSectionIndex();
        blocks[position_index].SetSectionIndex(blocks[active_index].GetSectionIndex());
        blocks[active_index].SetSectionIndex(target_section_index);
    }
}

// その座標に在るブロック
int PuzzleManager::LookForPositionBlock(Section* sections, Block* blocks, Config* config, double event_button_x, double event_button_y){
    int i;
    for (i = 0; i < config->GetLine() * config->GetRow(); ++i) {
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

// 操作中のブロックを探す
int PuzzleManager::LookForActiveBlock(Block* blocks, Config* config){
    int i;
    for (i = 0; i < config->GetLine() * config->GetRow(); ++i) {
        if (blocks[i].GetActive() == ON){
            return i;
        }
    }
    return Invalid;
}

// Getter
int PuzzleManager::GetStateChoice(){ return state_choice; }