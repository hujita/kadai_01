//
//  GameScene.swift
//  omikuji
//
//  Created by hujita on 2016/03/15.
//  Copyright (c) 2016年 hujita. All rights reserved.
//

import SpriteKit

class GameScene: SKScene {
    let mySprite = SKSpriteNode(imageNamed: "omikuji.png")
    let btnSprite = SKSpriteNode(imageNamed: "button.png")
    let myLabel = SKLabelNode(fontNamed: "Verdana-bold")
    
    override func didMoveToView(view: SKView) {
        
        //super.viewDidLoad()
        let socketController = SocketControllerObjC();
        socketController.test();
        
        
        // 背景表示
        self.backgroundColor = SKColor.whiteColor()
        // イラスト表示
        mySprite.position = CGPoint(x: 375, y: 900)
        addChild(mySprite)
        // ボタン表示
        btnSprite.position = CGPoint(x: 375, y:200)
        self.addChild(btnSprite)
        // おみくじ結果用ラベルを表示する
        myLabel.text = "???"
        myLabel.fontSize = 65
        myLabel.fontColor = SKColor.blackColor()
        myLabel.position = CGPoint(x:375, y:500)
        self.addChild(myLabel)
    }
    
    override func touchesBegan(touches: NSSet, withEvent event: UIEvent) {
        for touch: AnyObject in touches {
            // タッチされた位置にあるものを調べて
            let location = touch.locationInNode(self)
            let touchNode = self.nodeAtPoint(location)
            // もしボタンなら
            if touchNode == btnSprite {
                myLabel.text = "???"
                shakeOmikuji()
            }
        }
    }
   
    func shakeOmikuji() {
        let action1 = SKAction.rotateToAngle(-0.3, duration: 0.2)
        let action2 = SKAction.rotateToAngle(0.3, duration: 0.2)
        let action3 = SKAction.rotateToAngle(3.14, duration: 0.2)
        let actionS = SKAction.sequence(
            [action1, action2, action1, action2, action1, action3])
        
        mySprite.runAction(actionS, completion: showOmikuji)
    }
    
    func showOmikuji() {
        var omikuji = ["大吉", "中吉", "吉", "凶"]
        var r = Int(arc4random_uniform(4))
        myLabel.text = omikuji[r]
    }
    
    override func update(currentTime: CFTimeInterval) {
        /* Called before each frame is rendered */
    }
}
