// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "Components/TextBlock.h"
#include "Components/RichTextBlock.h"
#include "TextBlockBase.generated.h"


UCLASS(Abstract)
class CUSTOMUI_API UTextBlockBase : public UWidgetBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UWidgetSwitcher> WS_TextBlock = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<URichTextBlock> RichTextBlock = nullptr;

protected:
	UPROPERTY(EditAnywhere)
	FText _Text = FText();

	UPROPERTY(EditAnywhere)
	FTextBlockStyle _TextStyle;

	UPROPERTY(EditAnywhere)
	float _MinDesiredWidth = 0.0f;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ETextJustify::Type> _Justification;

	UPROPERTY(EditAnywhere)
	bool _ApplyLineHeightToBottomLine = true;

	UPROPERTY(EditAnywhere)
	FMargin _Margin = FMargin();

	UPROPERTY(EditAnywhere)
	float _LineHeightPercentage = 1.0f;

	UPROPERTY(EditAnywhere)
	bool _AutoWrapText = true;

	UPROPERTY(EditAnywhere)
	ETextWrappingPolicy _WrappingPolicy = ETextWrappingPolicy::DefaultWrapping;

	UPROPERTY(EditAnywhere)
	bool _UseRichText = false;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<URichTextBlockDecorator>> _DecoratorClasses;

protected:
	virtual void NativeConstruct() override;
	virtual void SynchronizeProperties() override;

protected:
	bool CheckWidgetSwitcherValid() const;

	void UpdateTextBlockStyle();
	void UpdateRichTextBlockStyle();
};
