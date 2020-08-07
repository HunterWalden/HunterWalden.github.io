#include "Bid.h"

Bid::Bid(string key, string title, string fund, double amount)
{
	mKey = key;
	mTitle = title;
	mFund = fund;
	mAmount = amount;
}

Bid::~Bid()
{
}

void Bid::setKey(const string& key)
{
	mKey = key;
}

void Bid::setTitle(const string& title)
{
	mTitle = title;
}

void Bid::setFund(const string& fund)
{
	mFund = fund;
}

void Bid::setAmount(const double& amount)
{
	mAmount = amount;
}

const string Bid::getKey()
{
	return mKey;
}

const string Bid::getTitle()
{
	return mTitle;
}

const string Bid::getFund()
{
	return mFund;
}

const double Bid::getAmount()
{
	return mAmount;
}

void Bid::display()
{
	cout << mKey << ": " << mTitle << " | " << mAmount << " | " << mFund << endl;
}