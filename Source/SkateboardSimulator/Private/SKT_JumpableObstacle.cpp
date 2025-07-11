// Fill out your copyright notice in the Description page of Project Settings.


#include "SKT_JumpableObstacle.h"

#include "SKT_Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ASKT_JumpableObstacle::ASKT_JumpableObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	JumpTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("JumpTrigger"));
	JumpTrigger->SetupAttachment(RootComponent);

	JumpTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	JumpTrigger->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	JumpTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	JumpTrigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	JumpTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASKT_JumpableObstacle::OnJumpTriggerOverlap);
}

void ASKT_JumpableObstacle::OnJumpTriggerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		UE_LOG(LogTemp, Log, TEXT("Jumped over the obstacle!"));

		if (ASKT_Character* PlayerCharacter = Cast<ASKT_Character>(OtherActor))
		{
			PlayerCharacter->AddXP(XPReward);
		}
		
		JumpTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ASKT_JumpableObstacle::BeginPlay()
{
	Super::BeginPlay();
}

void ASKT_JumpableObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

