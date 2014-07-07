/**
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#ifndef BASE58_HPP
#define BASE58_HPP

#include <array>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <bitcoin/bitcoin.hpp>
#include <sx/utility/console.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

/**
 * Serialization helper to convert between data_chunk and base58.
 */
class base58
{
public:

    /**
     * Constructor.
     */
    base58()
        : value() {}

    /**
     * Initialization constructor.
     * 
     * @param[in]  chunk  The value to initialize with.
     */
    base58(const bc::data_chunk& chunk)
        : value(chunk) {}

    /**
     * Initialization constructor.
     * 
     * @param[in]  base58  The value to initialize with.
     */
    base58(const std::string& base58)
    {
        std::stringstream(base58) >> *this;
    }

    /**
     * Copy constructor.
     *
     * @param[in]  argument  The object to copy into self on construct.
     */
    base58(const base58& argument)
        : value(argument.value) {}

    /**
     * Overload cast to std::string.
     *
     * @return  This object's value cast to bc::data_chunk.
     */
    operator const bc::data_chunk() const
    {
        return value; 
    }

    /**
     * Return a reference to the data member.
     *
     * @return  A reference to the object's internal data.
     */
    bc::data_chunk& data()
    {
        return value;
    }

    /**
     * Overload stream in. Throws if input is invalid.
     *
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, base58& argument)
    {
        std::string base58;
        input >> base58;
        argument.value = bc::decode_base58(base58);
        return input;
    }

    /**
     * Overload stream out.
     *
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output, 
        const base58& argument)
    {
        output << bc::encode_base58(argument.value);
        return output;
    }

private:

    /**
     * The state of this object.
     */
    bc::data_chunk value;
};

} // sx
} // serializer

#endif