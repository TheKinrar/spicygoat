//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_ENTITY_H
#define SPICYGOAT_ENTITY_H

#include <cstdint>
#include <mutex>
#include <set>
#include <string>

class EntityTracker;

#include "../protocol/packets/ClientBoundPacket.h"
#include "../protocol/packets/play/clientbound/PacketDestroyEntities.h"
#include "../protocol/packets/play/clientbound/PacketSetEntityMetadata.h"
#include "../protocol/packets/play/clientbound/PacketSpawnEntity.h"
#include "../tracking/EntityTracker.h"
#include "../world/geo/Location.h"
#include "EntityMetadata.h"

class Entity {
   public:
    explicit Entity();
    explicit Entity(const uuids::uuid& uuid);
    virtual ~Entity() = default;

    int32_t getEID();

    [[nodiscard]]
    const uuids::uuid& getUuid() const {
        return uuid;
    }

    virtual std::string getType() = 0;
    virtual int getProtocolType();

    [[nodiscard]]
    EntityTracker& getTracker() const {
        return *tracker;
    }

    [[nodiscard]]
    const Location getLocation() const;

    [[nodiscard]]
    bool isOnGround() const;

    void setLocation(Location loc) {
        this->location = loc;
        this->nextLocation = loc;
    }

    void setNextLocation(Location loc);
    void setNextPosition(double x, double y, double z);
    void setNextLook(float yaw, float pitch);
    void setNextOnGround(bool onGround);

    virtual EntityMetadata toMetadata() {
        return {};
    }

    virtual std::unique_ptr<ClientBoundPacket> createPacket() {
        return std::make_unique<PacketSpawnEntity>(getEID(), getUuid(), getProtocolType(), getLocation(), 0, 0, 0, 0);
    };

    std::optional<std::unique_ptr<ClientBoundPacket>> metadataPacket() {
        auto metadata = toMetadata();
        if(metadata.entries.empty())
            return {};
        else
            return std::make_unique<PacketSetEntityMetadata>(getEID(), toMetadata());
    };

    virtual std::unique_ptr<ClientBoundPacket> removePacket() {
        return std::make_unique<PacketDestroyEntities>(getEID());
    };

    virtual void tick();

    virtual std::string toString();

    bool operator==(const Entity &rhs) const {
        return eid == rhs.eid;
    }

    bool operator!=(const Entity &rhs) const {
        return !(rhs == *this);
    }

   protected:
    virtual void chunkChanged();

   private:
    int32_t eid;
    uuids::uuid uuid;

    Location location;
    bool onGround = false;

    Location nextLocation;
    bool nextOnGround = false;

    std::mutex m_nextLocation;

    std::unique_ptr<EntityTracker> tracker;
};

#endif  // SPICYGOAT_ENTITY_H
