// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category = "Money", meta = (ClampMin = "0"))
	int32 MoneyAmount;	
	
	UPROPERTY(BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0"))
	float Health;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0"))
	float MaxHealth = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> InventoryWidget;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> HealthbarWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> HealthbarWidget;

	UPROPERTY()
	TObjectPtr<ACharacter> PlayerCharacter;
	

	UFUNCTION(BlueprintCallable)
	void DecreaseHeath(float Value);	

	UFUNCTION(BlueprintCallable)
	void IncreaseHeath(float Value);

public:	
	/** Called for open|closing inventory */
	UFUNCTION()
	void InventoryEvent(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	int32 GetMoneyAmount() const { return MoneyAmount; }	
	
	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const { return Health; }	
	
	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
