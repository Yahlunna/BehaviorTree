// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToEnemyBTTaskNode.h"
#include "BehaviorTree/AIEnemyCppController.h"




EBTNodeResult::Type UMoveToEnemyBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
	return EBTNodeResult::InProgress;
}

void UMoveToEnemyBTTaskNode::TickTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
	AAIEnemyCppController* AIEnemyController = Cast<AAIEnemyCppController>(OwnerComp.GetOwner());

	EPathFollowingRequestResult::Type MoveToActorResult = AIEnemyController->MoveToEnemy();		//TODO: Fix

	

	if (MoveToActorResult == EPathFollowingRequestResult::AlreadyAtGoal) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, TEXT("AlreadyAtGoal"));
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else if (MoveToActorResult == EPathFollowingRequestResult::Failed) {
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, TEXT("Failed"));
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	else if(MoveToActorResult == EPathFollowingRequestResult::RequestSuccessful){
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, TEXT("RS"));
	}
}

FString UMoveToEnemyBTTaskNode::GetStaticDescription() const 
{
	return TEXT("Persigue al personaje principal");
}