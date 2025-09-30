// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryManagement/FastArray/Inv_FastArray.h"


TArray<FInv_InventoryEntry> FInv_InventoryFastArray::GetAllItems() const
{
}

void FInv_InventoryFastArray::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
}

void FInv_InventoryFastArray::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
}

UInv_InventoryItem* FInv_InventoryFastArray::AddEntry(UInv_ItemComponent* ItemComponent)
{
}

UInv_InventoryItem* FInv_InventoryFastArray::AddEntry(UInv_InventoryItem* Item)
{
}

void FInv_InventoryFastArray::RemoveEntry(UInv_InventoryItem* Item)
{
}
