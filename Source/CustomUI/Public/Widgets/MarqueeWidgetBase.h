// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "MarqueeWidgetBase.generated.h"


UENUM(BlueprintType)
enum class EMarqueeTextType : uint8
{
	NA = 0,
	Scroll				UMETA(Tooltip = "사라질 때까지 흘러갑니다"),
	DelayAndScroll		UMETA(Tooltip = "멈춰있다 흘러갑니다"),
	ScrollAndDelay		UMETA(Tooltip = "다 흐르면 멈춥니다"),
	Alternate			UMETA(Tooltip = "영역 안에서 왔다갔다 흐릅니다"),
};

UCLASS(Abstract)
class CUSTOMUI_API UMarqueeWidgetBase : public UWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UScrollBox> ScrollBox = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UNamedSlot> Content = nullptr;
	
protected:
	UPROPERTY(EditAnywhere, Category = "MarqueeTextBlock")
	EMarqueeTextType _EMarqueeTextType = EMarqueeTextType::NA;

	UPROPERTY(EditAnywhere, Category = "MarqueeTextBlock")
	TEnumAsByte<EOrientation> _Orientation = EOrientation::Orient_Horizontal;

	UPROPERTY(EditAnywhere, Category = "MarqueeTextBlock")
	float _MarqueeSpeed = 10.0f;

protected:
	virtual void NativeConstruct() override;
	virtual void SynchronizeProperties() override;

};
