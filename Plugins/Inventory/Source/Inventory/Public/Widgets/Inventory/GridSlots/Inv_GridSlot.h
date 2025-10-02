// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_GridSlot.generated.h"

class UInv_InventoryItem;
class UImage;

UENUM(BlueprintType)
enum class EInv_GridSlotState : uint8
{
	Unoccupied,
	Occupied,
	Selected,
	GrayedOut
};

/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_GridSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	int32 GetTileIndex() const { return TileIndex; }
	void SetTileIndex(const int32 Index) { TileIndex = Index; }

	int32 GetStackCount() const { return StackCount; }
	void SetStackCount(const int32 Count) { StackCount = Count; }

	int32 GetUpperLeftIndex() const { return UpperLeftIndex; }
	void SetUpperLeftIndex(const int32 Index) { UpperLeftIndex = Index; }

	TWeakObjectPtr<UInv_InventoryItem> GetInventoryItem() const { return InventoryItem; }
	void SetInventoryItem(UInv_InventoryItem* Item);

	bool IsAvailable() const { return bAvailable; }
	void SetIsAvailable(const bool bIsAvailable) { bAvailable = bIsAvailable; }

	EInv_GridSlotState GetGridSlotState() const { return GridSlotState; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetTexture(const EInv_GridSlotState SlotState);

private:
	int32 TileIndex;
	int32 StackCount;
	int32 UpperLeftIndex{INDEX_NONE};
	TWeakObjectPtr<UInv_InventoryItem> InventoryItem;
	bool bAvailable;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_GridSlot;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FSlateBrush Brush_Unoccupied;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FSlateBrush Brush_Occupied;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FSlateBrush Brush_Selected;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FSlateBrush Brush_GrayedOut;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Inventory")
	EInv_GridSlotState GridSlotState;
};
