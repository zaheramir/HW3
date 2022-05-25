#include "HealthPoints.h"

HealthPoints::HealthPoints()
{
	this->m_maxHealth = DEFAULT_MAX_HP;
	this->m_health = DEFAULT_MAX_HP;
}

HealthPoints::HealthPoints(int initialHealth)
{
	if (initialHealth <= 0)
	{
		throw InvalidArgument();
	}

	this->m_maxHealth = initialHealth;
	this->m_health = initialHealth;
}

HealthPoints& HealthPoints::operator+=(const int hp)
{
	if (this->m_health + hp >= this->m_maxHealth)
	{
		this->m_health = this->m_maxHealth;
	}
	else {
		this->m_health += hp;
	}
	return *this;
}

HealthPoints& HealthPoints::operator-=(const int hp)
{
	if (hp >= this->m_health)
	{
		this->m_health = 0;
	}
	else
	{
		this->m_health -= hp;
	}

	return *this;
}

HealthPoints HealthPoints::operator-(const int hp)
{
	HealthPoints resultHp(this->m_maxHealth);

	resultHp.m_health = this->m_health - hp;

	return resultHp;
}

HealthPoints& HealthPoints::operator=(const HealthPoints& hp)
{
	this->m_maxHealth = hp.m_maxHealth;
	this->m_health = hp.m_health;
	return *this;
}

HealthPoints operator+(const HealthPoints& hp1, const int hp2)
{
	HealthPoints result(hp1.m_maxHealth);
	if (hp1.m_health + hp2 > result.m_maxHealth)
	{
		result.m_health = result.m_maxHealth;
	}
	else
	{
		result.m_health = hp1.m_health + hp2;

	}

	return result;
}
HealthPoints operator+(const int hp1, const HealthPoints& hp2)
{

	HealthPoints result(hp2.m_maxHealth);
	if (hp2.m_health + hp1 > result.m_maxHealth)
	{
		result.m_health = result.m_maxHealth;
	}
	else
	{
		result.m_health = hp2.m_health + hp1;

	}	
	return result;
}
bool operator==(const HealthPoints& hp1, const HealthPoints& hp2)
{
	return(hp1.m_health == hp2.m_health);
}
bool operator!=(const HealthPoints& hp1, const HealthPoints& hp2)
{
	if (hp1 == hp2)
		return false;
	return true;
}
bool operator<(const HealthPoints& hp1, const HealthPoints& hp2)
{
	return(hp1.m_health < hp2.m_health);
}
bool operator<=(const HealthPoints& hp1, const HealthPoints& hp2)
{
	return(hp1.m_health <= hp2.m_health);
}
bool operator>(const HealthPoints& hp1, const HealthPoints& hp2)
{
	return(hp1.m_health > hp2.m_health);
}
bool operator>=(const HealthPoints& hp1, const HealthPoints& hp2)
{
	return(hp1.m_health >= hp2.m_health);
}
std::ostream& operator<<(std::ostream& os, const HealthPoints& hp)
{
	os << hp.m_health << '(' << hp.m_maxHealth << ')';
	return os;
}


//int main()
//{
//	HealthPoints hp1;
//	HealthPoints hp2(250);
//	HealthPoints hp3(300);
//
//	try
//	{
//		HealthPoints healthPoints3(-100);
//	}
//	catch (HealthPoints::InvalidArgument& e)
//	{
//		std::cout << "caught an invalid argument" << std::endl;
//	}
//	hp2 -= 25;
//	
//	hp2 = hp3 - 273;
//	hp2 = 50 + hp1;
//	hp2 = hp3 + 100;
//	
//
//	bool comparisonResult;
//	HealthPoints healthPoints1(100);
//	HealthPoints healthPoints2 = 100; /* 100 points out of 100 */
//	comparisonResult = (healthPoints1 == healthPoints2); /* returns true */
//	healthPoints2 = HealthPoints(150); /* has 150 points out of 150 */
//	comparisonResult = (healthPoints1 == healthPoints2); /* returns false */
//	healthPoints2 -= 50; /* now has 100 points out of 150 */
//	comparisonResult = (100 == healthPoints2); /* returns true */
//	comparisonResult = (healthPoints1 < healthPoints2); /* returns false */
//	healthPoints1 -= 50; /* now has 50 points out of 100 */
//	comparisonResult = (healthPoints1 < healthPoints2); /* returns true */
//	std::cout << healthPoints1 << ", " << healthPoints2;
//	return 0;
//}