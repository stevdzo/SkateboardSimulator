// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SKT_Character.generated.h"

class UInputAction;
class UInputComponent;
class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;

struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnXPChanged, int32, NewXP);

UCLASS()
class SKATEBOARDSIMULATOR_API ASKT_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASKT_Character();

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnXPChanged OnXPChanged;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputAction> ActionMove = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputAction> ActionLook = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputAction> ActionJump = nullptr;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void UpdateRotation(const float DeltaTime);
	
public:
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AddXP(int32 Amount);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<USpringArmComponent> CameraBoom = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> SkateboardMesh = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 CurrentXP = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float MaxSpeed = 1200.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnDirection = 0.0f;
	
};
