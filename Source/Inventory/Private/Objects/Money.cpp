// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/Money.h"
#include <Structs/MoneyType.h>

AMoney::AMoney()
{
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
    RootComponent = Mesh;
}


