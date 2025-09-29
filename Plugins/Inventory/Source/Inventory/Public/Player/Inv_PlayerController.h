// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Inv_PlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class INVENTORY_API AInv_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

private:
	void PrimaryInteract();
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory|Input")
	TArray<TObjectPtr<UInputMappingContext>> DefaultIMCs;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory|Input")
	TObjectPtr<UInputAction> PrimaryInteractAction;
};
