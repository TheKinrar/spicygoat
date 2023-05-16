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

#include <spicygoat/entities/EntityMetadata.h>
#include <spicygoat/protocol/ClientBoundPacket.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketDestroyEntities.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketSetEntityMetadata.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketSpawnEntity.h>
#include <spicygoat/tracking/EntityTracker.h>
#include <spicygoat/world/geo/Location.h>
#include <spicygoat/world/geo/RayCast.h>
#include <spicygoat/world/geo/Vector3d.h>

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

    [[nodiscard]]
    const Vector3d& getVelocity() const {
        return velocity;
    }

    void setVelocity(const Vector3d& velocity) {
        Entity::velocity = velocity;
    }

    RayCast move(Vector3d movement, bool slippery = false);

    virtual EntityMetadata toMetadata() {
        return {};
    }

    virtual std::unique_ptr<ClientBoundPacket> createPacket() {
        return std::make_unique<PacketSpawnEntity>(getEID(), getUuid(), getProtocolType(), getLocation(), 0,
                                                   getVelocity());
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

    bool operator==(const Entity& rhs) const {
        return eid == rhs.eid;
    }

    bool operator!=(const Entity& rhs) const {
        return !(rhs == *this);
    }

   protected:
    virtual void chunkChanged();

   private:
    int32_t eid;
    uuids::uuid uuid;

    Location location;
    bool onGround = false;
    Vector3d velocity;
    bool noClip = false;

    Location nextLocation;
    bool nextOnGround = false;

    std::mutex m_nextLocation;

    std::unique_ptr<EntityTracker> tracker;
};

#endif  // SPICYGOAT_ENTITY_H
