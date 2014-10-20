#include "TTPC_Wire_Geometry_Table.hxx"

#include <TCaptLog.hxx>
#include <TTPCChannelId.hxx>
#include <CaptGeomId.hxx>

#include <TResultInputStream.hxx>
#include <TResultSetHandle.cxx>

//  Instantiate associated CP::TResultSetHandle and CP::TDbiResultSetHandle
//  classes.
//
// The TableRow subclass' *.cxx must request the instantiation of the
// templated CP::TResultSetHandle class it as the supplied class.  However
// CP::TResultSetHandle inherits from the backend CP::TDbiResultSetHandle so an
// instatiation of it is also required.
template class  CP::TResultSetHandle<CP::TTPC_Wire_Geometry_Table>;
template class  CP::TDbiResultSetHandle<CP::TTPC_Wire_Geometry_Table>;

ClassImp(CP::TTPC_Wire_Geometry_Table);

CP::TTPC_Wire_Geometry_Table::TTPC_Wire_Geometry_Table() {}

CP::TTPC_Wire_Geometry_Table::TTPC_Wire_Geometry_Table(
    const CP::TTPC_Wire_Geometry_Table& rhs) {*this = rhs;}

CP::TTPC_Wire_Geometry_Table::~TTPC_Wire_Geometry_Table() {}

void CP::TTPC_Wire_Geometry_Table::Fill(CP::TResultInputStream& ris) {
    ris >> fTPCWire >> fGeomPlane >> fGeomWire;
    fGeometryId = CP::GeomId::Captain::Wire(fGeomPlane,fGeomWire);
}

void CP::TTPC_Wire_Geometry_Table::Print(const Option_t*) const {
    CaptLog("   TPC geometry row " 
            << fGeometryId.GetSubsystemName()
            << " " << CP::GeomId::Captain::GetWirePlane(fGeometryId)
            << "-" << CP::GeomId::Captain::GetWireNumber(fGeometryId)
            << " <--> " << fTPCWire);
}

