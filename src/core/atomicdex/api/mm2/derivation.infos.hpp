#pragma once

#include <nlohmann/json_fwd.hpp>

namespace mm2::api
{
    struct derivation_infos
    {
        std::string type;
    };

    void from_json(const nlohmann::json& j, derivation_infos& answer);
}