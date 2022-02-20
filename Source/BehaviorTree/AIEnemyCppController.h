// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIEnemyCppController.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORTREE_API AAIEnemyCppController : public AAIController
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Ejercicio")
		void UpdateNextTargetPoint();

	UFUNCTION(BlueprintCallable, Category = "Ejercicio")
		void CheckNearbyEnemy();

	UFUNCTION(BlueprintCallable, Category = "Ejercicio")
		EPathFollowingRequestResult::Type MoveToEnemy();


};
