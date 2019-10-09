/*
 * SatisfactionLink.cc
 *
 * Copyright (C) 2014-2016 Linas Vepstas
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3 as
 * published by the Free Software Foundation and including the
 * exceptions
 * at http://opencog.org/wiki/Licenses
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public
 * License
 * along with this program; if not, write to:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <opencog/atoms/atom_types/NameServer.h>
#include <opencog/atomspace/AtomSpace.h>
#include <opencog/query/Satisfier.h>

#include "SatisfactionLink.h"

using namespace opencog;

void SatisfactionLink::init(void)
{
	Type t = get_type();
	if (not nameserver().isA(t, SATISFACTION_LINK))
	{
		const std::string& tname = nameserver().getTypeName(t);
		throw InvalidParamException(TRACE_INFO,
			"Expecting a SatisfactionLink, got %s", tname.c_str());
	}
}

SatisfactionLink::SatisfactionLink(const HandleSeq& hseq, Type t)
	: PatternLink(hseq, t)
{
	init();
}

SatisfactionLink::SatisfactionLink(const Link &l)
	: PatternLink(l)
{
	init();
}

TruthValuePtr SatisfactionLink::evaluate(AtomSpace* as, bool silent)
{
	if (nullptr == as) as = _atom_space;
	Satisfier sater(as);
	satisfy(sater);

#define PLACE_RESULTS_IN_ATOMSPACE
#ifdef PLACE_RESULTS_IN_ATOMSPACE
	// Shoot. XXX FIXME. Most of the unit tests require that the atom
	// that we return is in the atomspace. But it would be nice if we
	// could defer this indefinitely, until its really needed.
	Handle satgrd = as->add_atom(sater._ground);
#endif /* PLACE_RESULTS_IN_ATOMSPACE */

	return sater._result;
}

DEFINE_LINK_FACTORY(SatisfactionLink, SATISFACTION_LINK)

/* ===================== END OF FILE ===================== */
