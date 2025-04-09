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
USTRUCT(BlueprintType)
struct FCharWeaponData : public FTableRowBase { 
GENERATED_USTRUCT_BODY() 	
public: 		
	//FLevelUpData() : XPtoLvl(0), AdditionalHP(0) {} 	
	/** The 'Name' column is the same as the XP Level */ 		
	/** XP to get to the given level from the previous level */	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharSheet)		
	FString AttackBonus = ""; 		/** Icon to use for Achivement */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharSheet)		
	FString Damage = ""; 
};
USTRUCT(BlueprintType)
struct FCharSpellData : public FTableRowBase {
	GENERATED_USTRUCT_BODY()
public:
	//FLevelUpData() : XPtoLvl(0), AdditionalHP(0) {} 	
	/** The 'Name' column is the same as the XP Level */
	/** XP to get to the given level from the previous level */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharSheet)
	int32 Level = NULL; 		/** Icon to use for Achivement */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharSheet)
	FString School = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharSheet)
	FString Damage = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharSheet)
	FString SavingThrow = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharSheet)
	bool AttackRoll = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharSheet)
	FString CastingTime = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharSheet)
	FString Range = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharSheet)
	bool Verbal = NULL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharSheet)
	bool Somatic = NULL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharSheet)
	bool Material = NULL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharSheet)
	FString Component = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharSheet)
	FString Duration = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharSheet)
	FString Description = "";
};

UCLASS()
class VTT53_API UCharSheet : public UUserWidget
{
	GENERATED_BODY()
	
};
