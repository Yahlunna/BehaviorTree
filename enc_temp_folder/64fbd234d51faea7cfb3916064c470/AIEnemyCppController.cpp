// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemyCppController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIEnemyTargetPoint.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Public/EngineGlobals.h"
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
		EDrawDebugTrace::ForOneFrame,
		OutHits,
		true
	);

	for (FHitResult outHit : OutHits) {
		AActor* target = outHit.GetActor();
		FVector targetposition = target->GetActorLocation();



	}











	UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();

	if (bResult) 
	{
		for (int32 i = 0; i < OutHits.Num(); ++i)
		{
			FHitResult Hit = OutHits[i];
			APawn* pPlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

			if (Hit.GetActor() == pPlayerPawn) {
			
				BlackboardComponent->SetValueAsObject("TargetActorToFollow", pPlayerPawn);
				break;
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

