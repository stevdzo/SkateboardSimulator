// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SKT_JumpableObstacle.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

struct FHitResult;

UCLASS()
class SKATEBOARDSIMULATOR_API ASKT_JumpableObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASKT_JumpableObstacle();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent = nullptr;

	// The trigger box above the obstacle to detect jump overs
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> JumpTrigger = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float XPReward = 100.0f;
	
	UFUNCTION()
	void OnJumpTriggerOverlap(UPrimitiveComponent* OverlappedComp, 
							 AActor* OtherActor, 
							 UPrimitiveComponent* OtherComp, 
							 int32 OtherBodyIndex, 
							 bool bFromSweep, 
							 const FHitResult& SweepResult);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
