#ifndef TTPC_Wire_Channel_Table_hxx_seen
#define TTPC_Wire_Channel_Table_hxx_seen

#include "TChannelId.hxx"
#include "TResultSetHandle.hxx"
#include "TTableRow.hxx"

namespace CP {
    class TTPC_Wire_Channel_Table;
    class TResultInputStream;
    class TTableRow;
};

/// Provide a map between channels, wires and geometry objects.  This
/// interfaces to the table TPC_WIRE_TABLE, and the validity table
/// TPC_WIRE_TABLEVLD.
///
/// This is also an example table using TTableRow subclass rows and can be
/// used as the starting point for other subclasses.
///
/// For table XXX_YYY (all tables names are upper case) the corresponding
/// TTableRow subclass is
/// \code
///     CP::TXxx_Yyy  (arbitrary capitalisation, but try to stick to this one).
/// \endcode
/// Notice that the class naming convention for the tables is different than
/// for the rest of the software. 
class CP::TTPC_Wire_Channel_Table : public CP::TTableRow {

    using TTableRow::Fill;

public:

    /// Required default constructor
    TTPC_Wire_Channel_Table();

    /// Required copy constructor
    TTPC_Wire_Channel_Table(const TTPC_Wire_Channel_Table& from);

    virtual ~TTPC_Wire_Channel_Table();

    /// Get the channel identifier.  This is specified by the crate, card and
    /// channel of the adc for this channel.
    TChannelId GetChannelId() const {
        return fChannelId;
    }

    /// Get the mother board for this channel.
    int GetMotherBoard() const {
        return fMotherBoard;
    }

    /// Get the ASIC on the mother board for this channel.
    int GetASIC() const {
        return fASIC;
    }

    /// Get the channel on the ASIC for this channel.
    int GetASICChannel() const {
        return fASICChannel;
    }

    /// Get the crate for this channel
    int GetCrate() const {
        return fCrate;
    }

    /// Get the card in the crate for this channel.
    int GetCard() const {
        return fCard;
    }

    /// Get the ADC on the card for this channel.
    int GetADC() const {
        return fChannel;
    }
    
    /// Get the TPC wire number.  This is the numbering of the wires as
    /// specified in the TPC documentation and runs from 1 to maxWire.  It can
    /// be used to look up the geometry identifier in WIRE_GEOMETRY_TABLE.
    int GetWire() const {
        return fWire;
    }

    /// Return the unique "Natural Index" of row in table to define how data
    /// is found in the table.  This is used by the DBI to build a map between
    /// the channel number (or other index), and the row number.  The map is
    /// then available to the user of the table to quickly access values of
    /// the index from a DBI result set.  For instance, a result set for
    /// TTPC_Wire_Channel_Table.hxx is indexed by the channel id, so code
    /// might look like this:
    ///
    /// \code
    /// CP::TResultSetHandle<CP::TTPC_Wire_Channel_Table> chanTable(context);
    ///
    /// const CP::TTPC_Wire_Channel_Table* chanRow
    ///                     = chanTable.GetRowByIndex(chanId.AsUInt());
    /// \endcode
    ///
    /// This class is used by the DBI, and is not expected to be called by
    /// normal user code.
    virtual UInt_t GetIndex(UInt_t defIndex) const {
        return fChannelId.AsUInt();
    }

    /// Required method to create new row.
    virtual CP::TTableRow* MakeTableRow() const {
        return new TTPC_Wire_Channel_Table;
    }

    /// Fill a row for the table using the ResultInputStream.  The input
    /// stream is an object with operator >> methods for most basic types.
    ///
    /// Individual data items are read from it in the order in which they
    /// appear in the database table but notice that the first two rows (SEQNO
    /// and ROW_COUNTER) which are not part of the row's state, do not have to
    /// be skipped.
    ///
    /// Also notice how the row state can include other types objects even
    /// though the stored state can only store basic types.  These can be
    /// filled using the /// rest of the object based on the input values.
    virtual           void Fill(CP::TResultInputStream& ris);

    /// Print the state of the row.  This should use the "CaptLog" functions.
    ///
    /// Programming note: The arg isn't used but is there so as to avoid
    /// compiler warnings about hidden method TObject::Print(const Option_t*).
    virtual           void Print(const Option_t* = "") const;

private:

    /// The channel id for this object.  This is a calculated value that isn't
    /// saved in the DB table.
    CP::TChannelId fChannelId;

    /// Column MOTHERBOARD SMALLINT:  The motherboard holding the ASIC.
    Int_t fMotherBoard;

    /// Column ASIC SMALLINT:  The Asic mounted on the motherboard.
    Int_t fASIC;

    /// Column ASIC_CHANNEL SMALLINT:  The channel on the ASIC
    Int_t fASICChannel;

    /// Column CRATE SMALLINT: The crate number for this channel.
    Int_t fCrate;

    /// Column CARD SMALLINT: The card number in the crate for this channel.
    Int_t fCard;

    /// Column CHANNEL SMALLINT: The number of the channel the card.
    Int_t fChannel;

    /// Column WIRE SMALLINT: The wire number in the tpc.  For miniCAPTAIN,
    /// these are numbered is U 1-332 V 332-664 X 665-996.
    Int_t fWire;

    ClassDef(TTPC_Wire_Channel_Table,1)
};
#endif
