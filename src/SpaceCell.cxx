#include "WireCellData/SpaceCell.h"
#include <vector>
using namespace WireCell;

SpaceCell::SpaceCell(int ncluster, GeomCell& cell, float x, float q, float thickness)
  : _x(x),
    _q(q),
    _thickness(thickness),
    _ncluster(ncluster)
{
  _y = cell.center().y;
  _z = cell.center().z;
  _area = cell.cross_section();
  _boundary = cell.boundary();
}
