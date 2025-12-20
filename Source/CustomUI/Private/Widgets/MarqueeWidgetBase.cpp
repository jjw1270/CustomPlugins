// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MarqueeWidgetBase.h"
#include "Components/ScrollBox.h"
#include "Components/NamedSlot.h"

void UMarqueeWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(ScrollBox))
	{
		ScrollBox->SetScrollBarVisibility(ESlateVisibility::Collapsed);
	}
}

void UMarqueeWidgetBase::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (IsAnyInvalid(ScrollBox, Content))
		return;

	ScrollBox->SetOrientation(_Orientation);

}
