#pragma once

enum EManueverDirection
{
	MD_STRAIGHT,
	MD_BANK_RIGHT,
	MD_BANK_LEFT,
	MD_HARD_RIGHT,
	MD_HARD_LEFT,
	MD_STOP
};

enum EManueverStress
{
	MS_NONE,
	MS_DESTRESS,
	MS_STRESS
};

struct ShipManuever
{
	ShipManuever() : ShipManuever(EManueverDirection::MD_STRAIGHT, EManueverStress::MS_NONE, 1) {}
	ShipManuever(const EManueverDirection manueverDirection, const EManueverStress manueverStress, const int manueverLength)
	{
		this->manueverDirection = manueverDirection;
		this->manueverStress = manueverStress;
		this->manueverLength = manueverLength;
	}

	EManueverDirection manueverDirection;
	EManueverStress manueverStress;
	int manueverLength;
};