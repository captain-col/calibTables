#include "TTPC_Bad_Channel_Table.hxx"

#include <TCaptLog.hxx>
#include <TTPCChannelId.hxx>
#include <TMCChannelId.hxx>
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
template class  CP::TResultSetHandle<CP::TTPC_Bad_Channel_Table>;
template class  CP::TDbiResultSetHandle<CP::TTPC_Bad_Channel_Table>;

ClassImp(CP::TTPC_Bad_Channel_Table);

CP::TTPC_Bad_Channel_Table::TTPC_Bad_Channel_Table() {}

CP::TTPC_Bad_Channel_Table::TTPC_Bad_Channel_Table(
    const CP::TTPC_Bad_Channel_Table& rhs) {*this = rhs;}

CP::TTPC_Bad_Channel_Table::~TTPC_Bad_Channel_Table() {}

void CP::TTPC_Bad_Channel_Table::Fill(CP::TResultInputStream& ris) {
    Int_t crate, card, channel;
    Int_t channelStatus;
    ris >> crate;
    ris >> card;
    ris >> channel;
    ris >> channelStatus;
    fChannelId = CP::TTPCChannelId(crate,card,channel);
    fChannelMCId = CP::TMCChannelId(crate,card,channel);
    fChannelStatus = (Int_t) channelStatus;
}

void CP::TTPC_Bad_Channel_Table::Print(const Option_t*) const {
    CaptLog("   TPC bad channel row " << fChannelId.AsString() 
            << " <-> " << fChannelStatus);
}
void CP::TTPC_Bad_Channel_Table::PrintMC(const Option_t*) const {
    CaptLog("   MC bad channel row " << fChannelMCId.AsString() 
            << " <-> " << fChannelStatus);
}

