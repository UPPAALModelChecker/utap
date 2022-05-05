// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2020 Aalborg University.
   Copyright (C) 2006 Uppsala University and Aalborg University.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License
   as published by the Free Software Foundation; either version 2.1 of
   the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA
*/

#ifndef UTAP_POSITION
#define UTAP_POSITION

#include <iosfwd>
#include <limits>
#include <string>
#include <vector>

namespace UTAP
{
    /** Records the absolute position in the source file.
     * The position can later be translated into XPath and line:column numbers by using class Positions. */
    struct position_t
    {
        /** Start and end absolute offsets in the original source file.
         * Both INT_MAX indicate an unknown location, or outside the source file
         * (e.g. built-in, engine utility, or introduced by LSC translation) */
        uint32_t start{std::numeric_limits<int32_t>::max()}, end{std::numeric_limits<int32_t>::max()};
        // Java Integer cannot parse UINT_MAX, thus use INT_MAX.
        position_t() = default;
        position_t(uint32_t start, uint32_t end): start{start}, end{end} {}
    };

    /**
     * A container for information about lines and positions in the input
     * file.
     *
     * Elements in the container contain information about the
     * position in the input file of the first character of a line and
     * the XPath to the XML element containing the line. In general,
     * the line number refers to the line inside the XML element and
     * is not a global numbering of the lines in the input file. Also
     * the offset of the first character relative to the beginning of
     * the XML element is stored.
     *
     * If the input file is not an XML document, the path element of a
     * line is the empty string, the offset equals the position, and
     * the line numbers refer to the line number in the input file. In
     * essence, the whole input file is treated as if it were a single
     * XML element.
     */
    class Positions
    {
    public:
        struct line_t
        {
            uint32_t position;
            uint32_t offset;
            uint32_t line;
            std::string path;
            line_t(uint32_t position, uint32_t offset, uint32_t line, std::string path):
                position(position), offset(offset), line(line), path{std::move(path)}
            {}
        };

    private:
        std::vector<line_t> elements;
        const line_t& find(uint32_t position, uint32_t first, uint32_t last) const;

    public:
        /** Add information about a line to the container. */
        void add(uint32_t position, uint32_t offset, uint32_t line, std::string path);

        /**
         * Retrieves information about the line containing the given
         * position. The last line in the container is considered to
         * extend to inifinity (until another line is added).
         */
        const line_t& find(uint32_t position) const;

        /** Dump table to stdout. */
        void dump();
    };

    struct error_t
    {
        using line_t = Positions::line_t;
        line_t start;
        line_t end;
        position_t position;
        std::string msg;
        std::string context;

        error_t(line_t start, line_t end, position_t pos, std::string msg, std::string ctx = {}):
            start{std::move(start)}, end{std::move(end)}, position{pos}, msg{std::move(msg)}, context{std::move(ctx)}
        {}
        std::string toString() const;
    };
}  // namespace UTAP

std::ostream& operator<<(std::ostream& out, const UTAP::error_t&);

#endif
