// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Prepreka_zid.generated.h"

UCLASS()
class ROCKET_GAME_API APrepreka_zid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APrepreka_zid();

	void SetHealth(int hp);
	int GetHealth();
	void SetMovement(float x1, float y1, float z1);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* zid;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere, Category = "Health")
	int health;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	FVector MoveDirection;

	UPROPERTY(EditAnywhere, Category = "Components")
	float MoveScale;

	UPROPERTY(EditAnywhere, Category = "Components")
	float x;

	UPROPERTY(EditAnywhere, Category = "Components")
	float y;

	UPROPERTY(EditAnywhere, Category = "Components")
	float z;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class UBoxComponent* GetBoxComp() const { return BoxComp; }

	FORCEINLINE class UStaticMeshComponent* GetZid() const { return zid; }

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
