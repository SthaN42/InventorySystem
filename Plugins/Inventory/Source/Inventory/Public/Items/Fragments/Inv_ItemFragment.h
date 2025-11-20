// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Inv_FragmentTags.h"
#include "StructUtils/InstancedStruct.h"
#include "Widgets/Composite/Inv_CompositeBase.h"
#include "Windows/WindowsApplication.h"
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

	virtual void Manifest() {}

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
struct FInv_ImageFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()

	FInv_ImageFragment()
	{
		SetFragmentTag(FragmentTags::IconFragment);
	}

	UTexture2D* GetIcon() const { return Icon; }

	virtual void Assimilate(UInv_CompositeBase* Composite) const override;

private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TObjectPtr<UTexture2D> Icon{nullptr};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FVector2D IconSize{44.f, 44.f};
};

USTRUCT(BlueprintType, DisplayName = "Text Fragment")
struct FInv_TextFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()

	FText GetText() const { return FragmentText; }
	void SetText(const FText& Text) { FragmentText = Text; }

	virtual void Assimilate(UInv_CompositeBase* Composite) const override;

private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FText FragmentText{};
};

USTRUCT(BlueprintType, DisplayName = "Labeled Number Fragment")
struct FInv_LabeledNumberFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()

	virtual void Manifest() override;
	virtual void Assimilate(UInv_CompositeBase* Composite) const override;

	// When manifesting the first time, this fragment will randomize. However, once equipped
	// and dropped, an item should retain the same value, so randomization should not occur.
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (DisplayAfter = "bCollapseValue", EditCondition = "!bCollapseValue", EditConditionHides))
	bool bRandomizeValueOnManifest{true};

	float GetValue() const { return Value; }

private:
	UPROPERTY(EditAnywhere, Category = "Inventory|Label")
	bool bCollapseLabel{false};

	UPROPERTY(EditAnywhere, Category = "Inventory|Label", meta = (EditCondition = "!bCollapseLabel"))
	FText Text_Label{};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	bool bCollapseValue{false};

	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (EditCondition = "!bCollapseValue && !bRandomizeValueOnManifest"))
	float Value{0.f};

	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (EditCondition = "!bCollapseValue && bRandomizeValueOnManifest", EditConditionHides))
	float Min{0.f};

	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (EditCondition = "!bCollapseValue && bRandomizeValueOnManifest", EditConditionHides))
	float Max{0.f};

	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (EditCondition = "!bCollapseValue", EditConditionHides))
	int32 MinFractionalDigits{1};

	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (EditCondition = "!bCollapseValue", EditConditionHides))
	int32 MaxFractionalDigits{1};
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// Consumables
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


USTRUCT(BlueprintType, DisplayName = "Consume Modifier")
struct FInv_ConsumeModifier : public FInv_LabeledNumberFragment
{
	GENERATED_BODY()
	
	virtual void OnConsume(APlayerController* PC) {}
};

USTRUCT(BlueprintType, DisplayName = "Consumable Fragment")
struct FInv_ConsumableFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()

	FInv_ConsumableFragment()
	{
		SetFragmentTag(FragmentTags::ConsumableFragment);
	}

	virtual void Assimilate(UInv_CompositeBase* Composite) const override;
	virtual void Manifest() override;

	virtual void OnConsume(APlayerController* PC);
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (ExcludeBaseStruct))
	TArray<TInstancedStruct<FInv_ConsumeModifier>> ConsumeModifiers;
};

USTRUCT(BlueprintType, DisplayName = "Health Potion Fragment")
struct FInv_HealthPotionFragment : public FInv_ConsumeModifier
{
	GENERATED_BODY()

	virtual void OnConsume(APlayerController* PC) override;
};

USTRUCT(BlueprintType, DisplayName = "Mana Potion Fragment")
struct FInv_ManaPotionFragment : public FInv_ConsumeModifier
{
	GENERATED_BODY()

	virtual void OnConsume(APlayerController* PC) override;
};
