#ifndef WIRECELL_WIRECELLMAP
#define WIRECELL_WIRECELLMAP

#include "WireCellData/GeomCell.h"
#include "WireCellData/GeomWire.h"

#include <map>

namespace WireCell {

    /**
       Taken together, a (geometry) wire and a cell map provides a
       "binodal mesh" consisting of nodes of type GeomCell and
       Geomwire which connect to each other but not themselves.  Nodes
       hold pointers to the actual objects maintained elsewhere (see
       GeomCellSet and GeomWireSet).
     */

    typedef std::map<const GeomCell*, GeomWireSelection> GeomCellMap;
    typedef std::map<const GeomWire*, GeomCellSelection> GeomWireMap;
    
}

#endif