#ifndef HEALTH_SYSTEM
#define HEALTH_SYSTEM

struct HealthSystem
{
	float maxHealth;
	float currentHealth;
};

void Heal(HealthSystem& healthSystem, float heal);
void TakeDamage(HealthSystem& healthSystem, float dmg);

bool IsAlive(HealthSystem healthSystem);

#endif // !HEALTH_SYSTEM
