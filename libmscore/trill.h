//=============================================================================
//  MuseScore
//  Music Composition & Notation
//  $Id: trill.h 5226 2012-01-18 10:52:02Z wschweer $
//
//  Copyright (C) 2002-2011 Werner Schweer
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2
//  as published by the Free Software Foundation and appearing in
//  the file LICENCE.GPL
//=============================================================================

#ifndef __TRILL_H__
#define __TRILL_H__

#include "line.h"

class Trill;
class Accidental;
class QPainter;


// subtypes:
enum TrillType {
      TRILL_LINE, UPPRALL_LINE, DOWNPRALL_LINE, PRALLPRALL_LINE
      };

//---------------------------------------------------------
//   @@ TrillSegment
//---------------------------------------------------------

class TrillSegment : public LineSegment {
      Q_OBJECT

   protected:
   public:
      TrillSegment(Score* s) : LineSegment(s) {}
      Trill* trill() const                { return (Trill*)spanner(); }
      virtual ElementType type() const    { return TRILL_SEGMENT; }
      virtual TrillSegment* clone() const { return new TrillSegment(*this); }
      virtual void draw(QPainter*) const;
      virtual bool acceptDrop(MuseScoreView*, const QPointF&, Element*) const;
      virtual Element* drop(const DropData&);
      virtual void layout();
      };

//---------------------------------------------------------
//   @@ Trill
//---------------------------------------------------------

class Trill : public SLine {
      Q_OBJECT

      TrillType _subtype;
      ElementList _el;        // accidentals etc.

   public:
      Trill(Score* s);
      virtual Trill* clone() const     { return new Trill(*this); }
      virtual ElementType type() const { return TRILL; }

      virtual void layout();
      virtual LineSegment* createLineSegment();
      virtual void add(Element*);
      virtual void remove(Element*);
      virtual void write(Xml&) const;
      virtual void read(const QDomElement&);

      void setSubtype(const QString& s);
      void setSubtype(TrillType tt)     { _subtype = tt; }
      TrillType subtype() const         { return _subtype; }
      QString subtypeName() const;

      Segment* segment() const          { return (Segment*)parent(); }
      virtual void scanElements(void* data, void (*func)(void*, Element*), bool all=true);
      };

#endif

