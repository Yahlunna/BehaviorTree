// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MoveToEnemyBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORTREE_API UMoveToEnemyBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

	UMoveToEnemyBTTaskNode() {
		bNotifyTick = true;
	}

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual FString GetStaticDescription() const override;


};
