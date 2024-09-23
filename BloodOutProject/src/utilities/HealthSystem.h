#ifndef HEALTH_SYSTEM
#define HEALTH_SYSTEM

struct HealthSystem
{
	float maxHealth;
	float currentHealth;
};

HealthSystem CreateHealth(float health);

void Heal(HealthSystem& healthSystem, float heal);
void TakeDamage(HealthSystem& healthSystem, float dmg);
void SetHealth(HealthSystem& healthSystem, float health);
void SetMaxHealth(HealthSystem& healthSystem, float maxHealth);

bool IsAlive(HealthSystem healthSystem);

#endif // !HEALTH_SYSTEM
