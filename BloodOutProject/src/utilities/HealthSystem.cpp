#include <iostream>

#include "HealthSystem.h"

HealthSystem CreateHealth(float health)
{
	HealthSystem newHeal;
	newHeal.maxHealth = health;
	newHeal.currentHealth = newHeal.maxHealth;

	return newHeal;
}

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

void SetHealth(HealthSystem& healthSystem, float health)
{
	healthSystem.currentHealth = (health > healthSystem.maxHealth) ? healthSystem.maxHealth : health;
}

void SetMaxHealth(HealthSystem& healthSystem, float maxHealth)
{
	healthSystem.maxHealth = maxHealth;
}

bool IsAlive(HealthSystem healthSystem)
{
	return healthSystem.currentHealth > 0;
}
