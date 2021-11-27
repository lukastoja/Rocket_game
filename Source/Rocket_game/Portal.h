// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class ROCKET_GAME_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

	UFUNCTION()
	void DestroyPortal();

	UPROPERTY(EditAnywhere, Category = "Components")
	FTimerHandle DestroyHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* PortalUnutar;


	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* PortalVani;


	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* PortalTrokut;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere, Category = "rotiranje")
	int spin;

	int x, y, z;

public:	
	FORCEINLINE class UStaticMeshComponent* GetPortalUnutar() const { return PortalUnutar; }

	FORCEINLINE class UStaticMeshComponent* GetPortalVani() const { return PortalVani; }

	FORCEINLINE class UStaticMeshComponent* GetPortalTrokut() const { return PortalTrokut; }

	FORCEINLINE class UBoxComponent* GetBoxComp() const { return BoxComp; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
