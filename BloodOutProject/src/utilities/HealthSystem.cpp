#include <iostream>

#include "HealthSystem.h"

void Heal(HealthSystem& healthSystem, float heal)
{
	heal = abs(heal);

	healthSystem.currentHealth = (healthSystem.currentHealth + heal > healthSystem.maxHealth) ? healthSystem.maxHealth : healthSystem.currentHealth + heal;
}

void TakeDamage(HealthSystem& healthSystem, float dmg)
{
	dmg = abs(dmg);

	healthSystem.currentHealth -= (healthSystem.currentHealth > dmg) ? dmg : healthSystem.currentHealth;
}

bool IsAlive(HealthSystem healthSystem)
{
	return healthSystem.currentHealth > 0;
}
