//
//  puzzle_manager.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/03/01.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "puzzle_manager.h"

PuzzleManager::PuzzleManager(){
    score = 0;
    state_choice = 0;
    // ドロップ中は操作不能に
    state_drop = 0;
    freeze = 0;
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
    // 全ブロックを順に確認
    for (i = 0; i < config->GetLine() * config->GetRow(); ++i) {
        // 連鎖確認の標的になっているブロックのインデックス
        int chain_result_row = i;
        int chain_result_line = i;
        // 連結しているブロックのインデックスを追加していく
        std::vector<int> array_row;
        std::vector<int> array_line;
        // 必要連鎖数だけ確認する
        // タテ
        for (j = 0; j < config->GetChain(); ++j){
            // 連結が終わっていたら処理しない
            if (chain_result_row != Invalid){
                // 最初の一つ目は配列に加える
                if (j == 0){
                    array_row.push_back(i);
                }
                // 真上のブロックが同じ種類なら真上のブロックのインデックスを返す
                chain_result_row = CheckRowChain(config, blocks, chain_result_row);
                // 真上のブロックが同じ種類なら配列にインデックスを追加
                if (chain_result_row != Invalid)
                    array_row.push_back(chain_result_row);
                // 必要連結回数目もchain_resultが−1になっていなければ配列内のブロックを全て消滅させる
                if (j == (config->GetChain() - 1)){
                    for (cnt = 0; cnt < config->GetChain(); ++cnt){
                        blocks[array_row[cnt]].SetAlive(OFF);
                    }
                }
            }
        }
        // ヨコ
        for (j = 0; j < config->GetChain(); ++j){
            // 連結が終わっていたら処理しない
            if (chain_result_line != Invalid){
                // 最初の一つ目は配列に加える
                if (j == 0){
                    array_line.push_back(i);
                }
                // 真上のブロックが同じ種類なら真上のブロックのインデックスを返す
                chain_result_line = CheckLineChain(config, blocks, chain_result_line);
                // 真上のブロックが同じ種類なら配列にインデックスを追加
                if (chain_result_line != Invalid)
                    array_line.push_back(chain_result_line);
                // 必要連結回数目もchain_resultが−1になっていなければ配列内のブロックを全て消滅させる
                if (j == (config->GetChain() - 1)){
                    for (cnt = 0; cnt < config->GetChain(); ++cnt){
                        blocks[array_line[cnt]].SetAlive(OFF);
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

// 自分より下にある死亡ブロックの個数だけ落下回数に + 区画高さ
void PuzzleManager::CheckDrop(Config *config, Block *blocks){
    // block[i]とblock[j]は同じ列にあり、iはjよりも上の行に位置する。
    int i;
    int j;
    // blocks[i]
    for (i = 0; i < config->GetRow() * config->GetLine(); ++i){
        // blocks[j]
        for (j = 0; j < config->GetLine() * config->GetRow(); ++j){
            // blocks[i]より下の行、もしくは右の列、にあるblocks[j]を見つける
            if (blocks[j].GetSectionIndex() > blocks[i].GetSectionIndex()
                // blocks[i]とblocoks[j]は同じ列になければいけない
                && blocks[i].GetSectionIndex() / config->GetRow() == blocks[j].GetSectionIndex() / config->GetRow()){
                // jが死んでいたらiの落下回数に +1
                if (blocks[j].GetAlive() == OFF){
                    blocks[i].AddCountDrop(SECTION_HIGH);
                }
            }
        }
    }
}

void PuzzleManager::DropBlock(Config* config, Section* sections,Block* blocks){
    // 描画位置の落下補正
    int block_index;
    for (block_index = 0; block_index < config->GetLine() * config->GetRow(); ++block_index){
        blocks[block_index].DropDraw();
    }
    // 全て落下描画済みなら
    if (FlagAllDropDrawn(config, blocks) == ON){
        int droped;
        int i;
        // 描画位置落下補正をリセットする
        for (i = 0; i < config->GetLine() * config->GetRow(); ++i){
            blocks[i].ResetDropDraw();
        }
        // 一段落下を(列数-1)回繰り返す
        for (droped = 0; droped < config->GetRow(); ++droped){
            AllDrop(config, blocks);
        }
        // ブロックの蘇生
        ReCreate(config, blocks);
    }
}

void PuzzleManager::ReCreate(Config* config, Block* blocks){
    int block_index;
    for (block_index = 0; block_index < config->GetLine() * config->GetRow(); ++block_index) {
        if (blocks[block_index].GetAlive() == OFF){
            blocks[block_index].ReCreate(config, block_index);
            score += 100;
        }
    }
}

// ドロップシーンの描画が完了しているか
int PuzzleManager::FlagAllDropDrawn(Config *config, Block *blocks){
    int result = ON;
    int block_index;
    for (block_index = 0; block_index < config->GetLine() * config->GetRow(); ++block_index){
        if (blocks[block_index].GetCountDrop() > 0){
            result = OFF;
        }
    }
    return result;
}

// 実際に1段だけ落下させる
void PuzzleManager::AllDrop(Config *config, Block *blocks){
    int block_index;
    int section_index;
    // 右下から左上に処理していく
    for (section_index = (config->GetRow() * config->GetLine() - 1); section_index >= 0; --section_index){
        int block_index_a = Invalid;
        int block_index_b = Invalid;
        for (block_index = 0; block_index < config->GetRow() * config->GetLine(); ++block_index) {
            if (blocks[block_index].GetSectionIndex() == section_index){
                block_index_a = block_index;
            }
            if (blocks[block_index].GetSectionIndex() == (section_index - 1)){
                block_index_b = block_index;
            }
        }

        // 対象となるブロック2つがあったら
        if (block_index_a != Invalid && block_index_b != Invalid){
            // 死んでたらブロック上下入れ替える
            // 最上段だったら入れ替えない
            if (blocks[block_index_a].GetAlive() == OFF && section_index % config->GetRow() != 0){
                // 所属区画を交換する
                blocks[block_index_a].SetSectionIndex(section_index - 1);
                blocks[block_index_b].SetSectionIndex(section_index);
            }
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
    //CheckChain(config, blocks);
    // 落下チェック
    //CheckDrop(config, blocks);
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

void PuzzleManager::AddFreeze(int value){
    freeze += value;
}

void PuzzleManager::ResetScore(){
    score = 0;
}

// Getter
int PuzzleManager::GetStateChoice(){ return state_choice; }
int PuzzleManager::GetFreeze(){ return freeze; }
int PuzzleManager::GetScore(){ return score; }