// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forward and backward */
	void MoveForward(float Value);

	/** Called side to side input */ 
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @Param Rate this is a normalized rate, i.e. 1.0 means 100% of desired turn rate 
	*/
	void TurnAtRate(float Rate);

	/**
	 * Called via input to Look Up/Down at a given rate.
	 * @Param Rate this is a normalized rate, i.e. 1.0 means 100% of desired turn rate 
	*/
	void LookUpAtRate(float Rate);

	/**
	 * Rotate controller based on mouse X movement
	 * @Param Value the input value from mouse movement
	*/
	void Turn(float Value);

	/**
	 * Rotate controller based on mouse Y movement
	 * @Param Value the input value from mouse movement
	*/
	void LookUp(float Value);

	/**Called when the Fire Button is pressed*/
	void FireWeapon();

	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FVector& OutBeamLocation);

	/**Set bAming to true or false with buton press*/
	void AimingButtonPressed();
	void AimingButtonReleased();

	void CameraInterpZoom(float DeltaTime);

	/**Set BaseTurnRate and BaseLookUpRate base on aiming*/
	void SetLookRates();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/** Camera boom positioning the camera behind the character*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/*Camera that follows the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;
	/** Base Look Uo/Down rate, in deg/sec. Other scaling may affect final turn rate */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;


	/**Turn rate while not aiming*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float HipTurnRate;
	/**Look Up rate while not aiming*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float HipLookUpRate;
	/**Turn rate while aiming */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float AimingTurnRate;
	/**Look Up rate while aiming */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float AimingLookUpRate;


	/**Scale factor for mouse look sensitivity .Turn rate while not aiming*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseHipTurnRate;
	/**Scale factor for mouse look sensitivity. Look Up rate while not aiming*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseHipLookUpRate;
	/**Scale factor for mouse look sensitivity. Turn rate while aiming */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseAimingTurnRate;
	/**Scale factor for mouse look sensitivity. Look Up rate while aiming */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseAimingLookUpRate;


	/**Randomized gunshot sound cue*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class USoundCue* FireSound;

	/**Flash spawned at BarrelSocket*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* MuzzleFlash;

	/**Montage for firing the weapon*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* HipFireMontage;

	/**Particles spawned upon bullet impact*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* ImpactParticles;

	/**Smoke Trail for Bullets*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* BeamParticles;

	/**True when aiming*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool bAiming;

	/**Default camera field of view value*/
	float CameraDefaultFOV;

	/**Field of view value for when zoomed in*/
	float CameraZoomedFOV;

	/**Current Field of view this frame*/
	float CameraCurrentFOV;

	/**Interp speed for zooming when aiming*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float ZoomInterpSpeed;

public:
	/** Return CameraBoom Subobject */
	FORCEINLINE USpringArmComponent* GetCameraBoom() const {return CameraBoom;}

	/** Return FollowCamera Subobject */
	FORCEINLINE UCameraComponent* GetFollowCamera() const {return FollowCamera;}

	/** Return Aiming Subobject */
	FORCEINLINE bool GetAiming() const {return bAiming;}

};
