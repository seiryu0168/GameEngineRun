#pragma once
#include "Engine/GameObject.h"


//�����V�[�����Ǘ�����N���X
class PlayScene : public GameObject
{
private:
	int elapsedFrame_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	int GetTime() { return elapsedFrame_; }
};