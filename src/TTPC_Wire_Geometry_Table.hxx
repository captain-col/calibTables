#ifndef TTPC_Wire_Geometry_Table_hxx_seen
#define TTPC_Wire_Geometry_Table_hxx_seen

#include <TGeometryId.hxx>
#include <TResultSetHandle.hxx>
#include <TTableRow.hxx>

namespace CP {
    class TTPC_Wire_Geometry_Table;
    class TResultInputStream;
    class TTableRow;
};

/// Provide a map between channels, wires and geometry objects.  This
/// interfaces to the table TPC_WIRE_GEOMETRY_TABLE, and the validity table
/// TPC_WIRE_GEOMETRY_TABLEVLD.
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
class CP::TTPC_Wire_Geometry_Table : public CP::TTableRow {

    using TTableRow::Fill;

public:

    /// Required default constructor
    TTPC_Wire_Geometry_Table();

    /// Required copy constructor
    TTPC_Wire_Geometry_Table(const TTPC_Wire_Geometry_Table& from);

    virtual ~TTPC_Wire_Geometry_Table();

    /// Standard Getters (here they just give access to the row's state but
    /// could equally well perform services based on that state e.g. apply
    /// calibration.)
    TGeometryId GetGeometryId() const {
        return fGeometryId;
    }

    int GetWire() const {
        return fTPCWire;
    }

    /// Return unique "Natural Index" of row in table.  Optional, the default
    /// is to return the row position, which is unique but arbitrary.
    virtual UInt_t GetIndex(UInt_t defIndex) const {
        return fTPCWire;
    }

    /// Required method to create new row.
    virtual CP::TTableRow* MakeTableRow() const {
        return new TTPC_Wire_Geometry_Table;
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

    /// The geometry id for this object.  This is a calculated value that
    /// isn't saved in the DB table.
    CP::TGeometryId fGeometryId;

    /// Column TPCWIRE SMALLINT: The wire number in the tpc.  These are
    /// numbered in a counter clock wise direction starting with the U plane.
    /// The numbering is U 1-335 V 336-670 X 671-1005.
    Int_t fTPCWire;

    /// Column GEOMPLANE SMALLINT: The plane number this wire.  (X==0, V==1,
    /// U==2)
    Int_t fGeomPlane;

    /// Column GEOMWIRE SMALLINT: The wire number in the geometry.
    Int_t fGeomWire;

    ClassDef(TTPC_Wire_Geometry_Table,1)
};
#endif
