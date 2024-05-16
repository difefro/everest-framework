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
    static inline EventConfig _cfg{"123Everest123", "A new Everest Instance successfully started.", Severity::Debug,
                                   EventGroup::Default};

public:
    explicit InstanceStarted(const std::string nodeId) noexcept : Event(_cfg) {
        addSubject(SubjectInformation(nodeId));
    }
};

class ConnectionMqttFailed : public Event {
    static inline EventConfig _cfg{"", "Instance Failed to connect to MQTT-Broker", Severity::Error,
                                   EventGroup::Default};

public:
    explicit ConnectionMqttFailed(const std::string nodeid, std::string host, int port) : Event(_cfg) {
        addSubject(SubjectInformation(nodeid));
        addMeta("Host", host);
        addMeta("Port", port);
    }
};

class LoadingConfigFailed : public Event {
    static inline EventConfig _cfg{"", "Instance failed to load its config!", Severity::Error, EventGroup::Default};

public:
    explicit LoadingConfigFailed(std::string nodeid) : Event(_cfg) {
        addSubject(SubjectInformation(nodeid));
    }
};

class InstanceModuleFailed : public Event {
    static inline EventConfig _cfg{"", "A Module of the Instance failed!", Severity::Trace, EventGroup::Default};

public:
    explicit InstanceModuleFailed(std::string nodeid, std::string moduleName, int wstatus) : Event(_cfg) {
        addSubject(SubjectInformation(nodeid));
        addMeta("Module name", moduleName);
        addMeta("ExitCode", wstatus);
    }
};

class EverestInstanceCrashed : public Event {
    static inline EventConfig _cfg{"", "Instance crashed", Severity::Fatal, EventGroup::Default};

public:
    explicit EverestInstanceCrashed(std::string nodeid) : Event(_cfg) {
        addSubject(SubjectInformation(nodeid));
    }
};

class OcppConnected : public Event {
    static inline EventConfig _cfg{"", "Instance established connection with OCPP backend.", Severity::Info,
                                   EventGroup::Default};

public:
    explicit OcppConnected(std::string nodeid) : Event(_cfg) {
        addSubject(SubjectInformation(nodeid));
    }
};

class OcppNotConnected : public Event {
    static inline EventConfig _cfg{"", "Instance has no connection to the OCPP backend.", Severity::Error,
                                   EventGroup::Default};

public:
    explicit OcppNotConnected(std::string nodeid) : Event(_cfg) {
        addSubject(SubjectInformation(nodeid));
    }
};

} // namespace events
} // namespace frostd::log
