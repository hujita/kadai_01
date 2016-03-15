//
//  SocketControllerObjC.mm
//  omikuji
//
//  Created by hujita on 2016/03/15.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

#include "SocketControllerObjC.h"
#include "SocketControllerCpp.h"

@implementation SocketControllerObjC {
    SocketControllerCpp * socketController;
}

-(id)init {
    self = [super init];
    socketController = new SocketControllerCpp();
    return self;
}

-(void)dealloc {
    delete socketController;
}

-(void)test {
    socketController->test();
}

@end