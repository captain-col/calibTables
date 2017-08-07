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
    Int_t crate, card, channel;
    Int_t channelStatus;
    ris >> crate;
    ris >> card;
    ris >> channel;
    ris >> channelStatus;
    ris >> fDigitizerPedestal;
    ris >> fASICGain;
    ris >> fASICPeakTime;
    ris >> fASICRiseShape;
    ris >> fASICFallShape;
    fChannelId = CP::TTPCChannelId(crate,card,channel);
    fChannelStatus = (UInt_t) channelStatus;
}

void CP::TTPC_Channel_Calib_Table::Print(const Option_t*) const {
    CaptLog("   TPC calib row " << fChannelId.AsString() 
            << " <-> " << fChannelStatus
            << " " << fDigitizerPedestal
            << " " << fASICGain
            << " " << fASICPeakTime
            << " " << fASICRiseShape
            << " " << fASICFallShape);
}

