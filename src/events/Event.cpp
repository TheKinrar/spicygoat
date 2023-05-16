//
// Created by thekinrar on 15/03/23.
//

#include <spicygoat/events/EntityCollisionEvent.h>
#include <spicygoat/events/Event.h>
#include <spicygoat/events/PlayerChatMessageEvent.h>
#include <spicygoat/events/PlayerJoinEvent.h>
#include <spicygoat/events/PlayerUseItemEvent.h>
#include <spicygoat/events/PluginMessageEvent.h>

template <class E>
std::vector<std::weak_ptr<Listener<E>>> Event<E>::listeners = {};

template class Event<EntityCollisionEvent>;
template class Event<PlayerChatMessageEvent>;
template class Event<PlayerJoinEvent>;
template class Event<PluginMessageEvent>;
template class Event<PlayerUseItemEvent>;
