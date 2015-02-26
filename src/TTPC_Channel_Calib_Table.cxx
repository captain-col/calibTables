#include "TTPC_Channel_Calib_Table.hxx"

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
template class  CP::TResultSetHandle<CP::TTPC_Channel_Calib_Table>;
template class  CP::TDbiResultSetHandle<CP::TTPC_Channel_Calib_Table>;

ClassImp(CP::TTPC_Channel_Calib_Table);

CP::TTPC_Channel_Calib_Table::TTPC_Channel_Calib_Table() {}

CP::TTPC_Channel_Calib_Table::TTPC_Channel_Calib_Table(
    const CP::TTPC_Channel_Calib_Table& rhs) {*this = rhs;}

CP::TTPC_Channel_Calib_Table::~TTPC_Channel_Calib_Table() {}

void CP::TTPC_Channel_Calib_Table::Fill(CP::TResultInputStream& ris) {
    Int_t channelId;
    ris >> channelId >> fDigitizerSlope >> fASICRiseShape >> fASICFallShape;
    fChannelId = CP::TTPCChannelId((UInt_t) channelId);
}

void CP::TTPC_Channel_Calib_Table::Print(const Option_t*) const {
    CaptLog("   Channel calibration row " << fChannelId.AsString() 
            << " <--> " << fDigitizerSlope
            << " " << fASICRiseShape
            << " " << fASICFallShape);
}

