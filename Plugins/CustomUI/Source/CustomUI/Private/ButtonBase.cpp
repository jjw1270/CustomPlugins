// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonBase.h"
#include "Sound/SoundCue.h"
#include "Components/Image.h"

void UButtonBase::NativeConstruct()
{
	Super::NativeConstruct();

	SetButtonState(EButtonState::Normal);
}

void UButtonBase::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (_ButtonType == EButtonType::Toggle && _OnButtonDoubleClicked.IsBound())
	{
		TRACE_ERROR(TEXT("Click 타입만 더블클릭 이벤트가 가능합니다."));
	}

	OnButtonStateChanged();
}

void UButtonBase::NativeOnMouseEnter(const FGeometry& _geo, const FPointerEvent& _mouse_event)
{
	Super::NativeOnMouseEnter(_geo, _mouse_event);

	if (_ButtonType == EButtonType::Toggle && _ButtonState == EButtonState::Pressed)
		return;

	SetButtonState(EButtonState::Hovered);
}

void UButtonBase::NativeOnMouseLeave(const FPointerEvent& _mouse_event)
{
	Super::NativeOnMouseLeave(_mouse_event);

	if (_ButtonType == EButtonType::Toggle && _ButtonState == EButtonState::Pressed)
		return;

	SetButtonState(EButtonState::Normal);
}

FReply UButtonBase::NativeOnMouseButtonDown(const FGeometry& _geo, const FPointerEvent& _mouse_event)
{
	FReply reply = Super::NativeOnMouseButtonDown(_geo, _mouse_event);

	if (_ButtonType == EButtonType::Toggle)
	{
		if (_OnButtonClicked.IsBound())
			_OnButtonClicked.Broadcast();
	}

	SetButtonState(EButtonState::Pressed);

	return MoveTemp(reply);
}

FReply UButtonBase::NativeOnMouseButtonUp(const FGeometry& _geo, const FPointerEvent& _mouse_event)
{
	FReply reply = Super::NativeOnMouseButtonUp(_geo, _mouse_event);

	if(_ButtonType == EButtonType::Click)
	{
		if (_OnButtonClicked.IsBound())
			_OnButtonClicked.Broadcast();

		SetButtonState(EButtonState::Hovered);
	}

	return MoveTemp(reply);
}

FReply UButtonBase::NativeOnMouseButtonDoubleClick(const FGeometry& _geo, const FPointerEvent& _mouse_event)
{
	FReply reply = Super::NativeOnMouseButtonDoubleClick(_geo, _mouse_event);
	
	if (_ButtonType == EButtonType::Click)
	{
		// double click은 button state에서 예외
		PlaySound(_ClickSound);

		if (_OnButtonDoubleClicked.IsBound())
			_OnButtonDoubleClicked.Broadcast();
	}

	return MoveTemp(reply);
}

void UButtonBase::ResetButton()
{
	SetButtonState(EButtonState::Normal);
}

void UButtonBase::SetButtonState(EButtonState _state)
{
	if(_ButtonState == _state)
		return;
	_ButtonState = _state;

	OnButtonStateChanged();
}

void UButtonBase::OnButtonStateChanged()
{
	// sound
	switch (_ButtonState)
	{
	case EButtonState::Hovered:
		PlaySound(_HoverSound);
		break;
	case EButtonState::Pressed:
		PlaySound(_ClickSound);
		break;
	default:
		break;
	}

	// style
	if (IsValid(Img_ButtonStyle))
	{
		auto style_ptr = _ButtonStyle.Find(_ButtonState);
		if (IsValid(style_ptr))
		{
			Img_ButtonStyle->SetBrush(*style_ptr);
		}
	}
}
