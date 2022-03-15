#pragma once

#include "generic.error.hpp"
#include "balance.infos.hpp"
#include "derivation.infos.hpp"

namespace mm2::api
{
    struct spl_token_request
    {
        std::string                ticker;
    };

    void to_json(nlohmann::json& j, const spl_token_request& cfg);

    struct enable_solana_with_tokens_request
    {
        // string, mandatory. Ticker of the platform solana protocol coin.
        std::string ticker;

        // solana cluster urls
        std::vector<std::string> urls;

        // bool, optional. Whether to enable tx history - if "true", spawns a background loop to store the local cache of address(es) transactions.
        // Defaults to "false".
        bool tx_history{false};

        // Array of spl activation requests, mandatory. spl activation requests contain mandatory ticker and optional required_confirmations fields.
        // If required_confirmations is not set for a token, then MM2 will use the confirmations setting from its coins config or platform coin.
        std::vector<spl_token_request> spl_token_requests;
    };

    void to_json(nlohmann::json& j, const enable_solana_with_tokens_request& cfg);

    struct solana_address_infos
    {
        derivation_infos derivation_method;
        std::string      pubkey;
        balance_infos    balances;
    };

    void from_json(const nlohmann::json& j, solana_address_infos& answer);

    using solana_addresses_infos_registry = std::unordered_map<std::string, solana_address_infos>;

    struct spl_address_infos
    {
        derivation_infos                               derivation_method;
        std::string                                    pubkey;
        std::unordered_map<std::string, balance_infos> balances;
    };

    void from_json(const nlohmann::json& j, spl_address_infos& answer);

    using spl_addresses_infos_registry = std::unordered_map<std::string, spl_address_infos>;

    struct enable_solana_with_tokens_answer_success
    {
        std::size_t                  current_block;
        solana_addresses_infos_registry solana_addresses_infos;
        spl_addresses_infos_registry spl_addresses_infos;
    };

    void from_json(const nlohmann::json& j, enable_solana_with_tokens_answer_success& answer);

    struct enable_solana_with_tokens_answer
    {
        std::optional<enable_solana_with_tokens_answer_success> result;
        std::optional<generic_answer_error>                  error;
        std::string                                          raw_result;      ///< internal
        int                                                  rpc_result_code; ///< internal
    };

    void from_json(const nlohmann::json& j, enable_solana_with_tokens_answer& answer);
} // namespace mm2::api

namespace atomic_dex
{
    using t_enable_solana_with_tokens_request        = ::mm2::api::enable_solana_with_tokens_request;
    using t_enable_solana_with_tokens_answer         = ::mm2::api::enable_solana_with_tokens_answer;
    using t_enable_solana_with_tokens_answer_success = ::mm2::api::enable_solana_with_tokens_answer_success;
} // namespace atomic_dex