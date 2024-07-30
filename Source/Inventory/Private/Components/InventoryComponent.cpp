// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InventoryComponent.h"

#include "Blueprint/UserWidget.h"
#include "InputActionValue.h"
#include <Kismet/GameplayStatics.h>

#include <Inventory/InventoryCharacter.h>
#include "Components/CapsuleComponent.h"

#include <Objects/Money.h>
#include <Structs/MoneyType.h>


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MoneyAmount = 0;

	InventoryWidgetClass = nullptr;
	InventoryWidget = nullptr;
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if (InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UUserWidget>(GetWorld(), InventoryWidgetClass);
	}

	PlayerCharacter = Cast<AInventoryCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UCapsuleComponent* PlayerComponent = PlayerCharacter->GetCapsuleComponent();

	if (PlayerCharacter && PlayerComponent)
	{
		PlayerComponent->OnComponentBeginOverlap.AddDynamic(this, &UInventoryComponent::OnOverlapBegin);
	}

}

void UInventoryComponent::InventoryEvent(const FInputActionValue& Value)
{
	if (InventoryWidget)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (!PlayerController)
			return;

		InventoryWidget->AddToViewport();
		PlayerController->SetShowMouseCursor(true);

		const TSharedPtr<SWidget> SInventoryWidget = InventoryWidget->TakeWidget();
		PlayerController->SetInputMode(FInputModeUIOnly().SetWidgetToFocus(SInventoryWidget));
	}
}

void UInventoryComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin called for actor: %s"), *OtherActor->GetName());
	if (OtherActor && OtherActor->IsA(AMoney::StaticClass()))
	{
		auto Money = Cast<AMoney>(OtherActor);

		if (Money)
		{
			auto MoneyAmountRaw = Money->GetDataTable();
			if (MoneyAmountRaw.DataTable)
			{
				auto MoneyRow = MoneyAmountRaw.DataTable->FindRow<FMoneyType>(MoneyAmountRaw.RowName, "");

				if (MoneyRow)
				{
					MoneyAmount += MoneyRow->Amount;
					UE_LOG(LogTemp, Warning, TEXT("Amount: %d"), MoneyAmount);
				}
				
			}
		}

		OtherActor->Destroy();
	}
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

