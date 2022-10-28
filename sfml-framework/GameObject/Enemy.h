#pragma once
#include "SpriteObj.h"
#include "../Framework/ObjectPool.h"
#include "../Animation/Animator.h"
#include "../Animation/AnimationClip.h"

class EnemyBullet;
class Bullet;
class Player;
class Enemy :
    public SpriteObj
{
protected:
    int hp = 100;
    Vector2f position;

    Vector2f hpBarSize;
    RectangleShape hpBar;

    float ShootDelay = 1.f;
    Vector2f direction;
    float speed;
    float accelation;
    float deaccelation;

    Vector2f velocity;

    bool enemyAlive = false;

	const double Pi = 3.14159265358979323846;

	const size_t maxBullets = 3000;
	const size_t totalBullets = 16 * maxBullets;

    ObjectPool<Bullet>* bulletPool;
    EnemyBullet* bullets[48000];
    Player* player;
    Texture tex;

    FloatRect border;
    vector<VertexArray> collisionVector;
    sf::Transform transform;
    sf::RenderStates states;
	sf::VertexArray vertices;

    double counterTime = 0;
    double counterTime2 = 0;
    double counterTime3 = 0;

    double counterWave = 0;
    double counterWave2 = 0;
    double counterWave3 = 0;

    double bulletTime = 0.1;
    double bulletTime2 = 40;
    double bulletTime3 = 100;

    size_t numBullet = 0;
    size_t numBullet2 = 0;
    size_t numBullet3 = 0;

    float redBullet = 3.f;
    float BlueBullet = 2.f;
    float purpleBullet = 1.f;

    Clock clock;
    Time deltaTime;
    Time timeElapsed;

	double r = 20; // radius of the circle
public:
    Enemy();
    Enemy(Vector2f pos);
    ~Enemy();

    void SetBulletPool(ObjectPool<Bullet>* ptr) { bulletPool = ptr; }
    ObjectPool<Bullet>* GetBulletPool() { return bulletPool; }
    void SetPlayer(Player* player);
    void SetEnemyAlive(bool en) { enemyAlive = en; }
    int GetHp() { return hp; }
    bool GetEnemyAlive() { return enemyAlive;}

    virtual void Update(float dt);
    virtual void Release();
    virtual void Init();
    virtual void Draw(RenderWindow& window);

    void OnCollision(int Damage);
    void Fire();
};

