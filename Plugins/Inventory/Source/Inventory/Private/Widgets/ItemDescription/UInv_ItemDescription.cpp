// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ItemDescription/UInv_ItemDescription.h"

#include "Components/SizeBox.h"

FVector2D UUInv_ItemDescription::GetBoxSize() const
{
	return SizeBox->GetDesiredSize();
}
