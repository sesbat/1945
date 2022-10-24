#pragma once
#include "SpriteObj.h"
#include "../Framework/ObjectPool.h"

class Bullet;
class Player;
class Enemy :
    public SpriteObj
{
protected:
    int hp = 100;
    Vector2f dir;
    Vector2f position;

    float ShootDelay = 1.f;
    float speed = 1000.f;

    bool enemyAlive = false;

    ObjectPool<Bullet>* bulletPool;

    Player* player;
public:
    Enemy();
    Enemy(Vector2f pos);
    ~Enemy();

    void SetBulletPool(ObjectPool<Bullet>* ptr) { bulletPool = ptr; }
    ObjectPool<Bullet>* GetBulletPool() { return bulletPool; }
    void SetPlayer(Player* player);

    virtual void Update(float dt);
    virtual void Release();
    virtual void Init();
    virtual void Draw(RenderWindow& window);

    void OnCollision(int Damage);
    void Fire();
};

