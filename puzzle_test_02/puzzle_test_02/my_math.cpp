//
//  my_math.cpp
//  puzzle_test_02
//
//  Created by hujita on 2016/02/29.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "my_math.h"

// lower 以上 upper 以下の乱数を返す
int MyMath::Random(int lower, int upper, int cnt){
    using namespace boost;
    // 「メルセンヌツイスター」( Seed=現在時刻 ) で
    // 「小さな整数の一様乱数」( lower ~ upper ) を生成
    mt19937            gen( (int)static_cast<unsigned long>(time(0)) * (cnt + 1));
    uniform_smallint<> dst( lower, upper );
    variate_generator<
    mt19937&, uniform_smallint<>
    > rand( gen, dst );
    
    return rand();
}