//
//  math.h
//  puzzle_test_02
//
//  Created by hujita on 2016/02/25.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#ifndef __puzzle_test_02__math__
#define __puzzle_test_02__math__

#include <stdio.h>
#include <boost/random.hpp>
// lower 以上 upper 以下の乱数を返す
int Random(int lower, int upper, int cnt){
    using namespace boost;
    //return ((double)rand() / RAND_MAX) * (upper - lower) + lower;
    // 「メルセンヌツイスター」( Seed=現在時刻 ) で
    // 「小さな整数の一様乱数」( 1～6 ) を生成
    mt19937            gen( (int)static_cast<unsigned long>(time(0)) * (cnt + 1));
    uniform_smallint<> dst( lower, upper );
    variate_generator<
    mt19937&, uniform_smallint<>
    > rand( gen, dst );
    
    return rand();
}

#endif /* defined(__puzzle_test_02__math__) */
