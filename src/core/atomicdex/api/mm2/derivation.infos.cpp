#include <nlohmann/json.hpp>
#include "derivation.infos.hpp"

namespace mm2::api
{
    void
    from_json(const nlohmann::json& j, derivation_infos& answer)
    {
        answer.type = j.at("type").get<std::string>();
    }
}