// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemyCppController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIEnemyTargetPoint.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Public/EngineGlobals.h"
#include "Engine/World.h"
#include "EngineUtils.h"

void AAIEnemyCppController::UpdateNextTargetPoint() {

	UBlackboardComponent* pBlackboardComponent = BrainComponent->GetBlackboardComponent();

	int32 iTargetPointIndex = pBlackboardComponent->GetValueAsInt("TargetPointIndex");

	if (iTargetPointIndex >= 4)
	{
		iTargetPointIndex = 0;
		pBlackboardComponent->SetValueAsInt("TargetPointIndex", iTargetPointIndex);
	}

	for (TActorIterator<AAIEnemyTargetPoint> It(GetWorld()); It; ++It) {
		AAIEnemyTargetPoint* enemyTargetPoint = *It;

		if (iTargetPointIndex == enemyTargetPoint->m_iPosition) {
			pBlackboardComponent->SetValueAsVector("TargetPointPosition", enemyTargetPoint->GetActorLocation());
			break;
		}
	}

	pBlackboardComponent->SetValueAsInt("TargetPointIndex", (iTargetPointIndex + 1));

}


void AAIEnemyCppController::CheckNearbyEnemy() {

	APawn* pPawn = GetPawn();
	FVector MultiSphereStart = pPawn->GetActorLocation();

	FVector MultiSphereEnd = MultiSphereStart + FVector(0, 0, 15.0f);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(pPawn);

	TArray<FHitResult> OutHits;

	bool bResult = UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(),
		MultiSphereStart,
		MultiSphereEnd,
		700,
		ObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		OutHits,
		true
	);

	UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();

	if (bResult)
	{

		for (FHitResult outHit : OutHits) {
			AActor* sphereOutHit = outHit.GetActor();
			FVector targetPosition = sphereOutHit->GetActorLocation();
			FHitResult rayOutHit;

			bResult = UKismetSystemLibrary::LineTraceSingle(
				GetWorld(),
				MultiSphereStart,
				targetPosition,
				UEngineTypes::ConvertToTraceType(ECC_Camera),
				false,
				ActorsToIgnore,
				EDrawDebugTrace::ForDuration,
				rayOutHit,
				true
			);

			if (sphereOutHit == rayOutHit.GetActor()) {
				BlackboardComponent->SetValueAsObject("TargetActorToFollow", sphereOutHit);
				break;
			}
			else {
				BlackboardComponent->SetValueAsObject("TargetActorToFollow", NULL);
			}
		}
	}
	else
	{
		BlackboardComponent->SetValueAsObject("TargetActorToFollow", NULL);
	}

}

EPathFollowingRequestResult::Type AAIEnemyCppController::MoveToEnemy() {

	UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();

	AActor* HeroCharacterActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActorToFollow"));

	EPathFollowingRequestResult::Type MoveToActorResult = MoveToActor(HeroCharacterActor);

	return MoveToActorResult;
}

