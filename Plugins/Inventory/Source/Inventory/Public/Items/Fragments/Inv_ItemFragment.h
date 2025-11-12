// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Inv_FragmentTags.h"
#include "Widgets/Composite/Inv_CompositeBase.h"
#include "Inv_ItemFragment.generated.h"

class UInv_CompositeBase;
/**
 *
 */
USTRUCT(BlueprintType)
struct FInv_ItemFragment
{
	GENERATED_BODY()

	FInv_ItemFragment() {}
	FInv_ItemFragment(const FInv_ItemFragment&) = default;
	FInv_ItemFragment& operator=(const FInv_ItemFragment&) = default;
	FInv_ItemFragment(FInv_ItemFragment&&) = default;
	FInv_ItemFragment& operator=(FInv_ItemFragment&&) = default;
	virtual ~FInv_ItemFragment() {}

	FGameplayTag GetFragmentTag() const { return FragmentTag; }
	void SetFragmentTag(FGameplayTag Tag) { FragmentTag = Tag; }

private:
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (Categories = "FragmentTags"))
	FGameplayTag FragmentTag = FGameplayTag::EmptyTag;
};

/**
 * Item Fragment specifically for assimilation into a widget.
 */
USTRUCT(BlueprintType, DisplayName = "Inventory Item Fragment")
struct FInv_InventoryItemFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	virtual void Assimilate(UInv_CompositeBase* Composite) const;

protected:
	bool MatchesWidgetTag(const UInv_CompositeBase* Composite) const;
};

USTRUCT(BlueprintType, DisplayName = "Grid Fragment")
struct FInv_GridFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	FInv_GridFragment()
	{
		SetFragmentTag(FragmentTags::GridFragment);
	}

	FIntPoint GetGridSize() const { return GridSize; }
	void SetGridSize(const FIntPoint& Size) { GridSize = Size; }

	float GetGridPadding() const { return GridPadding; }
	void SetGridPadding(float Padding) { GridPadding = Padding; }

private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FIntPoint GridSize{1, 1};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	float GridPadding{0.f};
};

USTRUCT(BlueprintType, DisplayName = "Image Fragment")
struct FInv_ImageFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	FInv_ImageFragment()
	{
		SetFragmentTag(FragmentTags::IconFragment);
	}

	UTexture2D* GetIcon() const { return Icon; }

private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TObjectPtr<UTexture2D> Icon{nullptr};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FVector2D IconSize{44.f, 44.f};
};

USTRUCT(BlueprintType, DisplayName = "Stackable Fragment")
struct FInv_StackableFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	FInv_StackableFragment()
	{
		SetFragmentTag(FragmentTags::StackableFragment);
	}

	int32 GetMaxStackSize() const { return MaxStackSize; }
	
	int32 GetStackCount() const { return StackCount; }
	void SetStackCount(const int32 Count) { StackCount = Count; }

private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 MaxStackSize{1};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 StackCount{1};
};

USTRUCT(BlueprintType, DisplayName = "Consumable Fragment")
struct FInv_ConsumableFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	FInv_ConsumableFragment()
	{
		SetFragmentTag(FragmentTags::ConsumableFragment);
	}

	virtual void OnConsume(APlayerController* PC) {}
};

USTRUCT(BlueprintType, DisplayName = "Health Potion Fragment")
struct FInv_HealthPotionFragment : public FInv_ConsumableFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Inventory")
	float HealAmount{20.f};

	virtual void OnConsume(APlayerController* PC) override;
};

USTRUCT(BlueprintType, DisplayName = "Mana Potion Fragment")
struct FInv_ManaPotionFragment : public FInv_ConsumableFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Inventory")
	float ManaAmount{20.f};

	virtual void OnConsume(APlayerController* PC) override;
};
