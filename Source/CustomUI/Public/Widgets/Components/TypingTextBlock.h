// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "TypingTextBlock.generated.h"


UCLASS(Abstract)
class CUSTOMUI_API UTypingTextBlock : public UWidgetBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UWidgetSwitcher> WS_TextBlock = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBlock = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class URichTextBlock> RichTextBlock = nullptr;

protected:
	UPROPERTY(EditAnywhere)
	bool _UseRichText = false;

	UPROPERTY(EditAnywhere)
	FText _Text = FText();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _TypeSpeed = 50.0f;

protected:
	FString _FullTextStr = FString();
	FString _TypedTextStr = FString();


	float _TypeTimer = 0.0f;

protected:
	virtual void NativeConstruct() override;
	virtual void SynchronizeProperties() override;
	virtual void NativeTick(const FGeometry& _geo, float _delta) override;

protected:
	bool CheckWidgetSwitcherValid() const;
};
