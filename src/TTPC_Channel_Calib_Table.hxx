#ifndef TTPC_Channel_Calib_Table_hxx_seen
#define TTPC_Channel_Calib_Table_hxx_seen

#include "TChannelId.hxx"
#include "TResultSetHandle.hxx"
#include "TTableRow.hxx"

namespace CP {
    class TTPC_Channel_Calib_Table;
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
class CP::TTPC_Channel_Calib_Table : public CP::TTableRow {

    using TTableRow::Fill;

public:

    /// Required default constructor
    TTPC_Channel_Calib_Table();

    /// Required copy constructor
    TTPC_Channel_Calib_Table(const TTPC_Channel_Calib_Table& from);

    virtual ~TTPC_Channel_Calib_Table();

    /// Return the unique "Natural Index" of row in table to define how data
    /// is found in the table.  This is used by the DBI to build a map between
    /// the channel number (or other index), and the row number.  The map is
    /// then available to the user of the table to quickly access values of
    /// the index from a DBI result set.  For instance, a result set for
    /// TTPC_Channel_Calib_Table.hxx is indexed by the channel id, so code
    /// might look like this:
    ///
    /// \code
    /// CP::TResultSetHandle<CP::TTPC_Channel_Calib_Table> chanTable(context);
    ///
    /// const CP::TTPC_Channel_Calib_Table* chanRow
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

    UInt_t GetChannelStatus() const {
        return fChannelStatus;
    }
    
    /// Return the digitizer slope for the channel (units: counts/mV).
    Float_t GetDigitizerSlope() const {
        return fDigitizerSlope;
    }

    /// Return the ASIC shaping factor for the rising edge of the pulse.
    Float_t GetASICRiseShape() const {
        return fASICRiseShape;
    }

    /// Return the ASIC shaping factor for the falling edge of the pulse.
    Float_t GetASICFallShape() const {
        return fASICFallShape;
    }
    
    /// Required method to create new row.
    virtual CP::TTableRow* MakeTableRow() const {
        return new TTPC_Channel_Calib_Table;
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

private:

    /// The channel id for this object.  This is a calculated value is filled
    /// from a signed integer saved in the DB table.
    CP::TChannelId fChannelId;

    /// Status flags associated with the channel.
    UInt_t fChannelStatus;
    
    /// The digitizer conversion factor (count/mV)
    Float_t fDigitizerSlope;

    /// The shape factor for the rising edge of the shaped pulse.  This is
    /// independent of the rise time.
    Float_t fASICRiseShape;

    /// The shape factor for the falling edge of the shaped pulse.  This is
    /// independent of the fall time.
    Float_t fASICFallShape;
    
    ClassDef(TTPC_Channel_Calib_Table,1)
};
#endif
