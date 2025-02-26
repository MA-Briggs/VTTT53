// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "CharSheet.generated.h"

/**
 * 
 */


/** Structure that defines a level up table entry */
USTRUCT(BlueprintType)
struct FCharStatData : public FTableRowBase { 
GENERATED_USTRUCT_BODY() 	
public: 		
	//FLevelUpData() : XPtoLvl(0), AdditionalHP(0) {} 	
	/** The 'Name' column is the same as the XP Level */ 		
	/** XP to get to the given level from the previous level */	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharSheet)		
	int32 Ints = NULL; 		/** Icon to use for Achivement */		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharSheet)		
	bool Bool = NULL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharSheet)		
	FString Text = ""; 
};

UCLASS()
class VTT53_API UCharSheet : public UUserWidget
{
	GENERATED_BODY()
	
};
