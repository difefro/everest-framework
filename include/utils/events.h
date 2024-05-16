///
/// \file        events.h
/// \author      Felix Dilly
/// \date        Created at: 2024-05-08
/// \date        Last modified at: 2024-05-16
/// ---
/// \copyright   Copyright 2024 Fronius International GmbH.
///              https://www.fronius.com
///

#pragma once

#include <cmath>
#include <frostd/log/event/event_types.h>
#include <frostd/log/event_logger.h>

namespace frostd::log {
static PresetEventLogger logger;

namespace events {
class InstanceStarted : public Event {
    static inline EventConfig _cfg{"54efd4cc-03ff-4491-9a39-c29f8fd9d02d",
                                   "A new Everest Instance successfully started.", Severity::Debug,
                                   EventGroup::Default};

public:
    explicit InstanceStarted(const std::string nodeId) noexcept : Event(_cfg) {
        addSubject(SubjectInformation(nodeId));
    }
};

class ConnectionMqttFailed : public Event {
    static inline EventConfig _cfg{"f2c6ca2c-214e-48c0-ba6a-1f9534420ad7", "Instance Failed to connect to MQTT-Broker",
                                   Severity::Error, EventGroup::Default};

public:
    explicit ConnectionMqttFailed(const std::string nodeid, std::string host, int port) : Event(_cfg) {
        addSubject(SubjectInformation(nodeid));
        addMeta("Host", host);
        addMeta("Port", port);
    }
};

class LoadingConfigFailed : public Event {
    static inline EventConfig _cfg{"f3d11fa4-013a-42d9-b7d8-1e60b8bfde59", "Instance failed to load its config!",
                                   Severity::Error, EventGroup::Default};

public:
    explicit LoadingConfigFailed(std::string nodeid) : Event(_cfg) {
        addSubject(SubjectInformation(nodeid));
    }
};

class InstanceModuleFailed : public Event {
    static inline EventConfig _cfg{"494cd1bf-c161-4bbe-84f9-b6857e04a30a", "A Module of the Instance failed!",
                                   Severity::Trace, EventGroup::Default};

public:
    explicit InstanceModuleFailed(std::string nodeid, std::string moduleName, int wstatus) : Event(_cfg) {
        addSubject(SubjectInformation(nodeid));
        addMeta("Module name", moduleName);
        addMeta("ExitCode", wstatus);
    }
};

class EverestInstanceCrashed : public Event {
    static inline EventConfig _cfg{"bd3adf23-9af4-45df-b967-e049d167416d", "Instance crashed", Severity::Fatal,
                                   EventGroup::Default};

public:
    explicit EverestInstanceCrashed(std::string nodeid) : Event(_cfg) {
        addSubject(SubjectInformation(nodeid));
    }
};

class OcppConnected : public Event {
    static inline EventConfig _cfg{"b7263f4b-21be-4828-9cb7-fb93d1f075f0",
                                   "Instance established connection with OCPP backend.", Severity::Info,
                                   EventGroup::Default};

public:
    explicit OcppConnected(std::string nodeid) : Event(_cfg) {
        addSubject(SubjectInformation(nodeid));
    }
};

class OcppNotConnected : public Event {
    static inline EventConfig _cfg{"9b5a3f65-f92e-4822-a186-1b0f2dd12d7f",
                                   "Instance has no connection to the OCPP backend.", Severity::Error,
                                   EventGroup::Default};

public:
    explicit OcppNotConnected(std::string nodeid) : Event(_cfg) {
        addSubject(SubjectInformation(nodeid));
    }
};

} // namespace events
} // namespace frostd::log
