#ifndef TTPC_Bad_Channel_Table_hxx_seen
#define TTPC_Bad_Channel_Table_hxx_seen

#include "TChannelId.hxx"
#include "TResultSetHandle.hxx"
#include "TTableRow.hxx"

namespace CP {
    class TTPC_Bad_Channel_Table;
    class TResultInputStream;
    class TTableRow;
};

/// Provide a list of channels that have been marked as bad.  The channels are
/// marked by hand, and specifically override channels that may be marked as
/// good during calibration.  This
/// interfaces to the table TPC_BAD_CHANNEL_TABLE, and the validity table
/// TPC_BAD_CHANNEL_TABLEVLD.
class CP::TTPC_Bad_Channel_Table : public CP::TTableRow {

    using TTableRow::Fill;

public:

    /// Required default constructor
    TTPC_Bad_Channel_Table();

    /// Required copy constructor
    TTPC_Bad_Channel_Table(const TTPC_Bad_Channel_Table& from);

    virtual ~TTPC_Bad_Channel_Table();

    /// Return the unique "Natural Index" of row in table to define how data
    /// is found in the table.  This is used by the DBI to build a map between
    /// the channel number (or other index), and the row number.  The map is
    /// then available to the user of the table to quickly access values of
    /// the index from a DBI result set.  For instance, a result set for
    /// TTPC_Bad_Channel_Table.hxx is indexed by the channel id, so code
    /// might look like this:
    ///
    /// \code
    /// CP::TResultSetHandle<CP::TTPC_Bad_Channel_Table> chanTable(context);
    ///
    /// const CP::TTPC_Bad_Channel_Table* chanRow
    ///                     = chanTable.GetRowByIndex(chanId.AsUInt());
    /// \endcode
    ///
    /// This class is used by the DBI, and is not expected to be called by
    /// normal user code.
    virtual UInt_t GetIndex(UInt_t defIndex) const {
        return fChannelId.AsUInt();
    }

    /// Return the channel identifier for the current row.
    TChannelId GetChannelId() const {
        return fChannelId;
    }

    TChannelId GetChannelMCId() const {
        return fChannelMCId;
    }

    UInt_t GetChannelStatus() const {
        return fChannelStatus;
    }
    
    /// Required method to create new row.
    virtual CP::TTableRow* MakeTableRow() const {
        return new TTPC_Bad_Channel_Table;
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
    /// filled using the rest of the object based on the input values.
    virtual           void Fill(CP::TResultInputStream& ris);

    /// Print the state of the row.  This should use the "CaptLog" functions.
    ///
    /// Programming note: The arg isn't used but is there so as to avoid
    /// compiler warnings about hidden method TObject::Print(const Option_t*).
    virtual           void Print(const Option_t* = "") const;
    virtual           void PrintMC(const Option_t* = "") const;

private:

    /// The channel id for this object.  This is a calculated value is filled
    /// from a signed integer saved in the DB table.
    CP::TChannelId fChannelId;
    CP::TChannelId fChannelMCId;

    /// The bad channel flag associated with the channel.
    UInt_t fChannelStatus;
    
    ClassDef(TTPC_Bad_Channel_Table,1)
};
#endif
