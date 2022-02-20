// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckNearbyEnemyBTService.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIEnemyTargetPoint.h"
#include "AIEnemyCppController.h"
#include "Runtime/Engine/Public/EngineUtils.h"


void UCheckNearbyEnemyBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIEnemyCppController* AIEnemyController = Cast<AAIEnemyCppController>(OwnerComp.GetOwner());

	AIEnemyController->CheckNearbyEnemy();

}