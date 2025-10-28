// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ItemPopUp/Inv_ItemPopup.h"

#include "Components/Button.h"
#include "Components/Slider.h"

void UInv_ItemPopup::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Split->OnClicked.AddDynamic(this, &ThisClass::SplitButtonClicked);
	Button_Drop->OnClicked.AddDynamic(this, &ThisClass::DropButtonClicked);
	Button_Consume->OnClicked.AddDynamic(this, &ThisClass::ConsumeButtonClicked);
	Slider_Split->OnValueChanged.AddDynamic(this, &ThisClass::SliderValueChanged);
}

void UInv_ItemPopup::SplitButtonClicked()
{
}

void UInv_ItemPopup::DropButtonClicked()
{
}

void UInv_ItemPopup::ConsumeButtonClicked()
{
}

void UInv_ItemPopup::SliderValueChanged(float Value)
{
}
