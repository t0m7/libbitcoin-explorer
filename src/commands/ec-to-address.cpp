/**
 * Copyright (c)2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "precompile.hpp"
#include <explorer/commands/ec-to-address.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <explorer/define.hpp>
#include <explorer/primitives/address.hpp>

using namespace bc;
using namespace explorer;
using namespace explorer::commands;
using namespace explorer::primitives;

// 100% coverage by line, loc ready.
console_result ec_to_address::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& point = get_ec_public_key_argument();
    const auto version = get_version_option();

    // Get the public key's payment address.
    const auto ripemd160 = bitcoin_short_hash(point);

    // TESTNET VERSION MAY REQUIRE RECOMPILE
    payment_address pay_address(version, ripemd160);

    output << address(pay_address) << std::endl;
    return console_result::okay;
}