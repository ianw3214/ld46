#pragma once
#include "oasis.h"
#include "entity.hpp"

class Earth : public PlayerEntity
{
public:
    Earth();

    virtual void Update() override;
private:
};