#pragma once
#include "Engine/GameObject.h"
#include"Engine/Fbx.h"
#include"Engine/BillBoard.h"
#include"Engine/Particle.h"
class Test : public GameObject
{
    int hModel_;
    //Particle* pParticle_;
public:
    //�R���X�g���N�^
    Test(GameObject* parent);

    //�f�X�g���N�^
    ~Test();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;
    void FixedUpdate() override;
    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void OnCollision(GameObject* pTarget) override;
};

