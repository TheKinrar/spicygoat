//
// Created by thekinrar on 15/03/23.
//

#include "Event.h"

#include "PlayerChatMessageEvent.h"
#include "PlayerJoinEvent.h"
#include "PluginMessageEvent.h"

template <class E>
std::vector<std::weak_ptr<Listener<E>>> Event<E>::listeners = {};

template class Event<PlayerChatMessageEvent>;
template class Event<PlayerJoinEvent>;
template class Event<PluginMessageEvent>;
