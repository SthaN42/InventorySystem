// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/GridSlots/Inv_GridSlot.h"

#include "Components/Image.h"
#include "Items/Inv_InventoryItem.h"
#include "Widgets/ItemPopUp/Inv_ItemPopUp.h"

FReply UInv_GridSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	GridSlotClicked.Broadcast(TileIndex, InMouseEvent);
	return FReply::Handled();
}

void UInv_GridSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	GridSlotHovered.Broadcast(TileIndex, InMouseEvent);
}

void UInv_GridSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	GridSlotUnhovered.Broadcast(TileIndex, InMouseEvent);
}

void UInv_GridSlot::SetInventoryItem(UInv_InventoryItem* Item)
{
	InventoryItem = Item;
}

UInv_ItemPopUp* UInv_GridSlot::GetItemPopUp() const
{
	return ItemPopUp.Get();
}

void UInv_GridSlot::SetItemPopUp(UInv_ItemPopUp* PopUp)
{
	ItemPopUp = PopUp;
	ItemPopUp->SetGridIndex(GetTileIndex());
	ItemPopUp->OnNativeDestruct.AddUObject(this, &ThisClass::OnItemPopUpDestruct);
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

void UInv_GridSlot::OnItemPopUpDestruct(UUserWidget* Menu)
{
	ItemPopUp.Reset();
}
