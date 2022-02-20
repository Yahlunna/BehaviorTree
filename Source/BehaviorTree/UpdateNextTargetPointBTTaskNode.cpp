// Fill out your copyright notice in the Description page of Project Settings.


#include "UpdateNextTargetPointBTTaskNode.h"
#include "AIEnemyCppController.h"


EBTNodeResult::Type UUpdateNextTargetPointBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	AAIEnemyCppController* AIEnemyController = Cast<AAIEnemyCppController>(OwnerComp.GetOwner());

	AIEnemyController->UpdateNextTargetPoint();

	return EBTNodeResult::Succeeded;
}


FString UUpdateNextTargetPointBTTaskNode::GetStaticDescription() const {
	return TEXT("Actualiza el siguiente punto en el recorrido");
}