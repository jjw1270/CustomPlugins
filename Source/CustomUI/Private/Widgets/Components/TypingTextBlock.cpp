// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Components/TypingTextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Components/RichTextBlock.h"
#include "WidgetHelper.h"


void UTypingTextBlock::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsAnyInvalid(TextBlock, RichTextBlock))
		return;

	RichTextBlock->SetText(FText::GetEmpty());
	TextBlock->SetText(FText::GetEmpty());

	_TypedTextStr.Empty();
}

void UTypingTextBlock::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (IsAnyInvalid(WS_TextBlock, TextBlock, RichTextBlock))
		return;

	if (CheckWidgetSwitcherValid() == false)
		return;

	_FullTextStr = _Text.ToString();

	if (UWidgetHelper::IsDesignTime(this))
	{
		RichTextBlock->SetText(_Text);
		TextBlock->SetText(_Text);
	}

	if (_UseRichText)
	{
		WS_TextBlock->SetActiveWidget(RichTextBlock);
	}
	else
	{
		WS_TextBlock->SetActiveWidget(TextBlock);
	}
}

void UTypingTextBlock::NativeTick(const FGeometry& _geo, float _delta)
{
	Super::NativeTick(_geo, _delta);


}

bool UTypingTextBlock::CheckWidgetSwitcherValid() const
{
	int32 valid_child_cnt = 0;

	for (const auto child : WS_TextBlock->GetAllChildren())
	{
		if (child == TextBlock || child == RichTextBlock)
		{
			valid_child_cnt++;
		}
		else
		{
			return false;
		}
	}

	return valid_child_cnt == 2;
}
