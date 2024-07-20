// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Money.generated.h"


UCLASS()
class INVENTORY_API AMoney : public AActor
{
	GENERATED_BODY()
	
public:	
	AMoney();

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DataTable")
	FDataTableRowHandle RowHandle;

public:
	UFUNCTION(BlueprintCallable)
	FDataTableRowHandle GetDataTable() { return RowHandle; };
};
