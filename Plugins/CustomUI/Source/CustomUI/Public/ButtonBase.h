// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "ButtonBase.generated.h"

class USoundCue;

UENUM(BlueprintType)
enum class EButtonType : uint8
{
	Click,
	Toggle
};

UENUM(BlueprintType)
enum class EButtonState : uint8
{
	Normal = 0,
	Hovered,
	Pressed,
	Disabled
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDM_OnButtonClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDM_OnButtonDoubleClicked);

UCLASS(Abstract)
class CUSTOMUI_API UButtonBase : public UWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
		TObjectPtr<class UImage> Img_ButtonStyle = nullptr;

protected:
	UPROPERTY(EditAnywhere, Category = "Button")
	EButtonType _ButtonType = EButtonType::Click;

	UPROPERTY(EditAnywhere, Category = "Button")
	TMap<EButtonState, FSlateBrush> _ButtonStyle;

	UPROPERTY(EditAnywhere, Category = "Button|Sound")
	TObjectPtr<USoundCue> _HoverSound = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Button|Sound")
	TObjectPtr<USoundCue> _ClickSound = nullptr;

public:
	UPROPERTY(BlueprintAssignable)
	FDM_OnButtonClicked _OnButtonClicked;

	UPROPERTY(BlueprintAssignable, meta=(Tooltip="Click 타입만 가능"))
	FDM_OnButtonDoubleClicked _OnButtonDoubleClicked;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EButtonState _ButtonState = EButtonState::Normal;

protected:
	virtual void NativeConstruct() override;
	virtual void SynchronizeProperties() override;

	virtual void NativeOnMouseEnter(const FGeometry& _geo, const FPointerEvent& _mouse_event) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& _mouse_event) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& _geo, const FPointerEvent& _mouse_event) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& _geo, const FPointerEvent& _mouse_event) override;
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& _geo, const FPointerEvent& _mouse_event) override;

public:
	UFUNCTION(BlueprintCallable)
	void ResetButton();

protected:
	void SetButtonState(EButtonState _state);
	void OnButtonStateChanged();
};
