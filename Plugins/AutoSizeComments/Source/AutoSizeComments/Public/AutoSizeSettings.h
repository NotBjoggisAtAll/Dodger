// Copyright 2018 fpwong, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AutoSizeSettings.generated.h"


UCLASS(config = AutoSizeComments, defaultconfig)
class AUTOSIZECOMMENTS_API UAutoSizeSettings : public UObject
{
	GENERATED_BODY()
		
public:
	UAutoSizeSettings(const FObjectInitializer& ObjectInitializer);

	/** Amount of padding for around the contents of a comment node */
	UPROPERTY(EditAnywhere, config, Category = Default)
	FVector2D CommentNodePadding;

	/** If enabled, comment boxes will spawn with a random color */
	UPROPERTY(EditAnywhere, config, Category = Default)
	bool bUseRandomColor;

	/** If Use Random Color is not enabled, comment boxes will spawn with this default color */
	UPROPERTY(EditAnywhere, config, Category = Default)
	FLinearColor DefaultCommentColor;

	/** If enabled, empty comment boxes will move out of the way of other comment boxes */
	UPROPERTY(EditAnywhere, config, Category = Default)
	bool bMoveEmptyCommentBoxes;

	/** The speed at which empty comment boxes move */
	UPROPERTY(EditAnywhere, config, Category = Default)
	float CollisionMovementSpeed;
};
