//
// Created by thekinrar on 15/03/23.
//

#pragma once

#include <uuid.h>

#include <spicygoat/entities/types/EntityPlayer.h>

class BossBar {
   public:
    enum class Color {
        Pink,
        Blue,
        Red,
        Green,
        Yellow,
        Purple,
        White
    };

    enum class Division {
        None,
        Six,
        Ten,
        Twelve,
        Twenty
    };

   private:
    const uuids::uuid id;

    std::string title;
    float health{};
    Color color{};
    Division division{};

    std::vector<std::weak_ptr<EntityPlayer>> players;

   public:
    explicit BossBar();
    virtual ~BossBar();

    [[nodiscard]]
    const uuids::uuid& getId() const {
        return id;
    }

    [[nodiscard]]
    const std::string& getTitle() const {
        return title;
    }

    [[nodiscard]]
    float getHealth() const {
        return health;
    }

    [[nodiscard]]
    Color getColor() const {
        return color;
    }

    [[nodiscard]]
    Division getDivision() const {
        return division;
    }

    void setTitle(const std::string& title);
    void setHealth(float health);
    void setColor(Color color);
    void setDivision(Division division);

    void addPlayer(const std::weak_ptr<EntityPlayer>& player);
    void removePlayer(const std::weak_ptr<EntityPlayer>& player);
    void removeAllPlayers();

   private:
    void broadcastPacket(const ClientBoundPacket& packet);
};
