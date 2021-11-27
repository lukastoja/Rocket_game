// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Municija.generated.h"

UCLASS()
class ROCKET_GAME_API AMunicija : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMunicija();

	void SetMunicija(int metak, int raketa);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	int municija_metak;

	UPROPERTY(EditAnywhere, Category = "Components")
	int municija_raketa;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UBoxComponent* MyBoxComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	FRotator okretanje;

	UPROPERTY(EditAnywhere, Category = "Components")
	float rotacija;

	UPROPERTY(EditAnywhere, Category = "Components")
	float koliko;

	UPROPERTY(EditAnywhere, Category = "Material")
	class UMaterial* MaterialMunicija;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
