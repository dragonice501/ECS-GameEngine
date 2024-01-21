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

struct ShipManuever
{
	ShipManuever() : ShipManuever(EManueverDirection::MD_STRAIGHT, 1) {}
	ShipManuever(const EManueverDirection manueverDirection, const int manueverLength)
	{
		this->manueverDirection = manueverDirection;
		this->manueverLength = manueverLength;
	}

	EManueverDirection manueverDirection;
	int manueverLength;
};