// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/GridSlots/Inv_GridSlot.h"

#include "Components/Image.h"
#include "Items/Inv_InventoryItem.h"

void UInv_GridSlot::SetInventoryItem(UInv_InventoryItem* Item)
{
	InventoryItem = Item;
}

void UInv_GridSlot::SetTexture(const EInv_GridSlotState SlotState)
{
	GridSlotState = SlotState;

	FSlateBrush NewBrush;
	switch (SlotState)
	{
	case EInv_GridSlotState::Unoccupied:
		NewBrush = Brush_Unoccupied;
		break;
	case EInv_GridSlotState::Occupied:
		NewBrush = Brush_Occupied;
		break;
	case EInv_GridSlotState::Selected:
		NewBrush = Brush_Selected;
		break;
	case EInv_GridSlotState::GrayedOut:
		NewBrush = Brush_GrayedOut;
		break;
	}

	Image_GridSlot->SetBrush(NewBrush);
}
