#pragma once
#include"Engine/GameObject.h"
#include<list>

class ObjectSetter : public GameObject
{
private:

public:
        //�R���X�g���N�^
        ObjectSetter(GameObject* parent);

        //�f�X�g���N�^
        ~ObjectSetter();

        //������
        void Initialize() override;

        //�X�V
        void Update() override;

       //�`��
        void Draw() override;

        void Release() override;

};

