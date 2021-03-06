/*************************************************************************
** PdfSpecialHandler.hpp                                                **
**                                                                      **
** This file is part of dvisvgm -- a fast DVI to SVG converter          **
** Copyright (C) 2005-2018 Martin Gieseking <martin.gieseking@uos.de>   **
**                                                                      **
** This program is free software; you can redistribute it and/or        **
** modify it under the terms of the GNU General Public License as       **
** published by the Free Software Foundation; either version 3 of       **
** the License, or (at your option) any later version.                  **
**                                                                      **
** This program is distributed in the hope that it will be useful, but  **
** WITHOUT ANY WARRANTY; without even the implied warranty of           **
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the         **
** GNU General Public License for more details.                         **
**                                                                      **
** You should have received a copy of the GNU General Public License    **
** along with this program; if not, see <http://www.gnu.org/licenses/>. **
*************************************************************************/

#ifndef PDFSPECIALHANDLER_HPP
#define PDFSPECIALHANDLER_HPP

#include "SpecialHandler.hpp"

class StreamInputReader;

class PdfSpecialHandler : public SpecialHandler, public DVIPositionListener, public DVIEndPageListener {
	public:
		PdfSpecialHandler ();
		const char* info () const override {return "PDF hyperlink, font map, and pagesize specials";}
		const char* name () const override {return "pdf";}
		const std::vector<const char*> prefixes () const override;
		void preprocess (const char *prefix, std::istream &is, SpecialActions &actions) override;
		bool process (const char *prefix, std::istream &is, SpecialActions &actions) override;

	protected:
		// handlers for corresponding PDF specials
		void preprocessBeginAnn (StreamInputReader &ir, SpecialActions &actions);
		void preprocessDest (StreamInputReader &ir, SpecialActions &actions);
		void preprocessPagesize (StreamInputReader &ir, SpecialActions &actions);
		void processBeginAnn (StreamInputReader &ir, SpecialActions &actions);
		void processEndAnn (StreamInputReader &ir, SpecialActions &actions);
		void processDest (StreamInputReader &ir, SpecialActions &actions);
		void processMapfile (StreamInputReader &ir, SpecialActions &actions);
		void processMapline (StreamInputReader &ir, SpecialActions &actions);

		void dviMovedTo (double x, double y, SpecialActions &actions) override;
		void dviEndPage (unsigned pageno, SpecialActions &actions) override;

	private:
		bool _active;
		bool _maplineProcessed;  ///< true if a mapline or mapfile special has already been processed
};

#endif
