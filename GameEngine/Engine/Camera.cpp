#include "Camera.h"

//�ϐ�
XMVECTOR position_;	//�J�����̈ʒu�i���_�j
XMVECTOR target_;	//����ʒu�i�œ_�j
XMVECTOR upVector_;
XMMATRIX viewMatrix_;	//�r���[�s��
XMMATRIX projMatrix_;	//�v���W�F�N�V�����s��
XMMATRIX billBoardMatrix_;

//������
void Camera::Initialize(float width,float height)
{
	position_ = XMVectorSet(0, 3, -10, 0);	//�J�����̈ʒu
	target_ = XMVectorSet(0, 0, 0, 0);	//�J�����̏œ_
	upVector_ = XMVectorSet(0, 1, 0, 0);

	// �v���W�F�N�V�����s��
		projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)width / (FLOAT)height, 0.1f, 1000.0f);
}

//�X�V
void Camera::Update()
{
	//�r���[�s��̍쐬
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, upVector_);

	billBoardMatrix_ = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), target_ - position_, upVector_);
	billBoardMatrix_ = XMMatrixInverse(nullptr, billBoardMatrix_);
}

//�ʒu��ݒ�
void Camera::SetPosition(XMVECTOR position)
{
	position_ = position;
}

//�œ_��ݒ�
void Camera::SetTarget(XMVECTOR target)
{
	target_ = target;
}

void Camera::SetUpVector(XMVECTOR upVector)
{
	upVector_ = upVector;
}

void Camera::SetProjection(float aov, float aspectRadio, float nearZ, float farZ)
{
	projMatrix_ = XMMatrixPerspectiveFovLH(aov, aspectRadio, nearZ, farZ);
}

//���_(�J�����̈ʒu)���擾
XMFLOAT3 Camera::GetPosition()
{
	XMFLOAT3 cameraPosition;
	XMStoreFloat3(&cameraPosition, position_);
	return cameraPosition;
}
//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix()
{
	return viewMatrix_;
}

XMMATRIX Camera::GetBillBoardMatrix()
{
	return billBoardMatrix_;
}
//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix()
{
	return projMatrix_;
}