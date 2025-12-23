// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Components/TextBlockBase.h"
#include "Components/WidgetSwitcher.h"
#include "WidgetHelper.h"


void UTextBlockBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsAnyInvalid(TextBlock, RichTextBlock))
		return;

	TextBlock->SetText(FText::GetEmpty());
	RichTextBlock->SetText(FText::GetEmpty());
}

void UTextBlockBase::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (IsAnyInvalid(WS_TextBlock, TextBlock, RichTextBlock))
		return;

	if (CheckWidgetSwitcherValid() == false)
		return;

	if (_UseRichText)
	{
		WS_TextBlock->SetActiveWidget(RichTextBlock);

		UpdateRichTextBlockStyle();
		RichTextBlock->SetDecorators(_DecoratorClasses);
		RichTextBlock->SetText(_Text);
	}
	else
	{
		WS_TextBlock->SetActiveWidget(TextBlock);

		UpdateTextBlockStyle();
		TextBlock->SetText(_Text);
	}
}

bool UTextBlockBase::CheckWidgetSwitcherValid() const
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

void UTextBlockBase::UpdateTextBlockStyle()
{
	TextBlock->SetFont(_TextStyle.Font);
	TextBlock->SetColorAndOpacity(_TextStyle.ColorAndOpacity);
	TextBlock->SetShadowOffset(_TextStyle.ShadowOffset);
	TextBlock->SetShadowColorAndOpacity(_TextStyle.ShadowColorAndOpacity);
	TextBlock->SetTextTransformPolicy(_TextStyle.TransformPolicy);
	TextBlock->SetMinDesiredWidth(_MinDesiredWidth);
	TextBlock->SetJustification(_Justification);
	TextBlock->SetApplyLineHeightToBottomLine(_ApplyLineHeightToBottomLine);
	TextBlock->SetMargin(_Margin);
	TextBlock->SetLineHeightPercentage(_LineHeightPercentage);
	TextBlock->SetAutoWrapText(_AutoWrapText);
	TextBlock->SetWrappingPolicy(_WrappingPolicy);
}

void UTextBlockBase::UpdateRichTextBlockStyle()
{
	if (RichTextBlock->GetCurrentDefaultTextStyle().IsIdenticalTo(_TextStyle) == false)
	{
		RichTextBlock->SetDefaultTextStyle(_TextStyle);
		RichTextBlock->SetTextTransformPolicy(_TextStyle.TransformPolicy);
	}

	RichTextBlock->SetMinDesiredWidth(_MinDesiredWidth);
	RichTextBlock->SetJustification(_Justification);
	RichTextBlock->SetApplyLineHeightToBottomLine(_ApplyLineHeightToBottomLine);
	RichTextBlock->SetMargin(_Margin);
	RichTextBlock->SetLineHeightPercentage(_LineHeightPercentage);
	RichTextBlock->SetAutoWrapText(_AutoWrapText);
	RichTextBlock->SetWrappingPolicy(_WrappingPolicy);
}
