#ifndef EX3_HealthPoints_H
#define EX3_HealthPoints_H

#include <iostream>

#define DEFAULT_MAX_HP 100



class HealthPoints
{
public:
	HealthPoints();
	HealthPoints(int initialHealth);
	HealthPoints& operator=(const HealthPoints& hp);
	HealthPoints& operator+=(const int hp);
	HealthPoints& operator-=(const int hp);
	
	HealthPoints operator-(const int hp);
	
	friend bool operator==(const HealthPoints& hp1, const HealthPoints& hp2);
	friend bool operator!=(const HealthPoints& hp1, const HealthPoints& hp2);
	friend bool operator<(const HealthPoints& hp1, const HealthPoints& hp2);
	friend bool operator<=(const HealthPoints& hp1, const HealthPoints& hp2);
	friend bool operator>(const HealthPoints& hp1, const HealthPoints& hp2);
	friend bool operator>=(const HealthPoints& hp1, const HealthPoints& hp2);
	friend HealthPoints operator+(const int hp1, const HealthPoints& hp2);
	friend HealthPoints operator+(const HealthPoints& hp1, const int hp2);
	friend std::ostream& operator<<(std::ostream& os, const HealthPoints& hp);



	class InvalidArgument {};


private:
	int m_health;
	int m_maxHealth;
};


#endif //EX2_HealthPoints_H
