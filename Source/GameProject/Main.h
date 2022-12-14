// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Main.generated.h"

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal		UMETA(DisplayName="Normal"),
	EMS_Sprinting	UMETA(DisplayName="Sprinting"),
	
	EMS_MAX			UMETA(DisplayName="DefaultMAX")
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_Normal					UMETA(DisplayName="Normal"),
	ESS_BelowMinimum			UMETA(DisplayName="BelowMinimum"),
	ESS_Exhausted				UMETA(DisplayName="Exhausted"),
	ESS_ExhaustedRecovering		UMETA(DisplayName="ExhaustedRecovering"),
	
	ESS_MAX						UMETA(DisplayName="DefaultMAX")
};

UCLASS()
class GAMEPROJECT_API AMain : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMain();

	//TArray for debugging purposes
	TArray<FVector> PickupLocations;
	UFUNCTION(BlueprintCallable)
	void ShowPickupLocations();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Enums")
	EMovementStatus MovementStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Enums")
	EStaminaStatus StaminaStatus;

	FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float StaminaDrainRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MinSprintStamina;
	
	/** Set movement status and running speed */
	void SetMovementStatus(EMovementStatus Status);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Running")
	float RunningSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Running")
	float SprintingSpeed;

	bool bShiftKeyDown;

	/** Press down to enable sprinting */
	void ShiftKeyDown();
	
	/** release to stop sprinting */
	void ShiftKeyUp();

	/** Camera boom positioning the camera behind the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** Base turn rates to scale turning functions for the camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	float BaseLookUpRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for forwards/Backwards input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Called via input to turn at a given rate
	 * @param Rate This is a normalized rate. i.e 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/** Called via input to look up/down at a given rate
	* @param Rate This is a normalized rate. i.e 1.0 means 100% of desired look up/down rate
	*/
	void LookUpAtRate(float Rate);

	void LMBDown();
	bool bLMBDown;
	void LMBUp();
	bool bLMBUp;

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//equipped weapon
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Items")
	class AWeapon* EquippedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Items")
	class AItem* ActiveOverlappingItem;

	void SetEquippedWeapon(AWeapon* WeaponToSet);
	//setter for equipped weapon
	FORCEINLINE AWeapon* GetEquippedWeapon(){ return EquippedWeapon; }
	FORCEINLINE void SetActiveOverlappingItem(AItem* Item){ ActiveOverlappingItem = Item; }

	/**
	/*
	/* Player stats
	/* 
	**/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Stats")
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Stats")
	float Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Player Stats")
	float MaxStamina;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Player Stats")
	float Stamina;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Player Stats")
	int32 Coins;

	void DecrementHealth(float Amount);

	void IncrementCoins(int32 Amount);

	void Die();
};
