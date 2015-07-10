#include "TTPC_Wire_Channel_Table.hxx"

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
template class  CP::TResultSetHandle<CP::TTPC_Wire_Channel_Table>;
template class  CP::TDbiResultSetHandle<CP::TTPC_Wire_Channel_Table>;

ClassImp(CP::TTPC_Wire_Channel_Table);

CP::TTPC_Wire_Channel_Table::TTPC_Wire_Channel_Table() {}

CP::TTPC_Wire_Channel_Table::TTPC_Wire_Channel_Table(
    const CP::TTPC_Wire_Channel_Table& rhs) {*this = rhs;}

CP::TTPC_Wire_Channel_Table::~TTPC_Wire_Channel_Table() {}

void CP::TTPC_Wire_Channel_Table::Fill(CP::TResultInputStream& ris) {
    ris >> fMotherBoard >> fASIC >> fASICChannel
        >> fCrate >> fCard >> fChannel
        >> fWire;
    fChannelId = CP::TTPCChannelId(fCrate,fCard,fChannel);
}

void CP::TTPC_Wire_Channel_Table::Print(const Option_t*) const {
    CaptLog("   Channel map row " << fChannelId.AsString() 
            << " (MB: " <<fMotherBoard
            << ", ASIC: " << fASIC
            << ", Chan:" << fASICChannel<< ")"
            << " <--> " << fWire);
}

