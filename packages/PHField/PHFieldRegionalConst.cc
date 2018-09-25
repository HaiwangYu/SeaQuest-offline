
#include "PHFieldRegionalConst.h"

//root framework
#include <TFile.h>
#include <TNtuple.h>

#include <set>
#include <iostream>

using namespace std;
using namespace CLHEP;// units

PHFieldRegionalConst::PHFieldRegionalConst(const double field, const double magfield_rescale, const int verb) :
    PHField(verb),
		_mean_x(0*cm), _mean_y(0*cm), _mean_z(0*cm),
		_maxy(4*cm), _miny(-4*cm),
		_maxr(22.225*cm), _minr(0*cm),
		_field_val(field*tesla)
{
}

void PHFieldRegionalConst::GetFieldValue(const double point[4], double *Bfield ) const
{
  double x = point[0];
  double y = point[1];
  double z = point[2];
	double r = sqrt((x-_mean_x)*(x-_mean_x) + (z-_mean_z)*(z-_mean_z));

	Bfield[0] = 0;
	Bfield[1] = 0;
	Bfield[2] = 0;

	if( r > _minr and r < _maxr and
			y - _mean_y > _miny and y - _mean_y < _maxy) {
		Bfield[1] = _field_val;
	}

//	std::cout
//	<< "PHFieldRegionalConst::GetFieldValue: "
//	<< "{" << x/cm << ", " << y/cm << ", " << z/cm << ","  << r/cm << "}"
//	<< "\t {" << Bfield[0]/tesla << ", " << Bfield[1]/tesla << ", " << Bfield[2]/tesla << "}"
//	<< std::endl;

  return;
}

