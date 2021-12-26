// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Prateci_zid.generated.h"

UCLASS()
class ROCKET_GAME_API APrateci_zid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APrateci_zid();

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* zid;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere, Category = "Components")
	int udaljenost;

	bool flag;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
