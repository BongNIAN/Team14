#ifndef OBSERVER_H
#define OBSERVER_H

#include <memory>


struct PlayerHp;

struct PlayerHp {
    int CurrentHp = -1;
    int MaxHp = -1;
};

class IPlayerObserver {
public:
    virtual ~IPlayerObserver() = default;
    virtual void UpdatePlayer(PlayerHp) = 0;
};

class PlayerObserver : public IPlayerObserver {
public:
    void UpdatePlayer(PlayerHp) override;
};

class GameOverHandler : public IPlayerObserver {
public:
    void UpdatePlayer(PlayerHp) override;
};



#endif // OBSERVER_H
