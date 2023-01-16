#pragma once
#include"Engine/GameObject.h"
#include<list>

class ObjectSetter : public GameObject
{
private:

public:
        //コンストラクタ
        ObjectSetter(GameObject* parent);

        //デストラクタ
        ~ObjectSetter();

        //初期化
        void Initialize() override;

        //更新
        void Update() override;

       //描画
        void Draw() override;

        void Release() override;

};

