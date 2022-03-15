//
// Created by milerius on 07/01/2022.
//

//! Dependencies
#include <nlohmann/json.hpp>

//! Project Headers
#include "rpc.enable.solana.with.tokens.hpp"

namespace mm2::api
{
    void
    to_json(nlohmann::json& j, const spl_token_request& cfg)
    {
        j["ticker"] = cfg.ticker;
    }

    void
    to_json(nlohmann::json& j, const enable_solana_with_tokens_request& cfg)
    {
        nlohmann::json obj = nlohmann::json::object();
        obj["ticker"] = cfg.ticker;
        obj["client_url"] = cfg.urls[0];
        obj["confirmation_commitment"] = "finalized";
        obj["tx_history"] = cfg.tx_history;
        obj["spl_tokens_requests"] = cfg.spl_token_requests;
        if (j.contains("mmrpc") && j.at("mmrpc").get<std::string>() == "2.0")
        {
            j["params"] = obj;
        }
    }

    void
    from_json(const nlohmann::json& j, solana_address_infos& answer)
    {
        answer.derivation_method = j.at("derivation_method").get<derivation_infos>();
        answer.pubkey = j.at("pubkey").get<std::string>();
        answer.balances = j.at("balances").get<balance_infos>();
    }

    void
    from_json(const nlohmann::json& j, spl_address_infos& answer)
    {
        answer.derivation_method = j.at("derivation_method").get<derivation_infos>();
        answer.pubkey = j.at("pubkey").get<std::string>();
        answer.balances = j.at("balances").get<std::unordered_map<std::string, balance_infos>>();
    }

    void
    from_json(const nlohmann::json& j, enable_solana_with_tokens_answer_success& answer)
    {
        answer.current_block = j.at("current_block").get<std::size_t>();
        answer.solana_addresses_infos = j.at("solana_addresses_infos").get<solana_addresses_infos_registry>();
        answer.spl_addresses_infos = j.at("spl_addresses_infos").get<spl_addresses_infos_registry>();
    }

    void
    from_json(const nlohmann::json& j, enable_solana_with_tokens_answer& answer)
    {
        if (j.count("error") >= 1)
        {
            answer.error = j;
        }
        else
        {
            if (j.contains("result") && j.contains("mmrpc") && j.at("mmrpc").get<std::string>() == "2.0")
            {
                answer.result = j.at("result").get<enable_solana_with_tokens_answer_success>();
            }
        }
    }
}