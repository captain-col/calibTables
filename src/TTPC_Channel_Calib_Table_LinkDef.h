#ifdef __CINT__

// The row sub class.
#pragma link C++ class CP::TTPC_Channel_Calib_Table+;

// The TableRow subclass' *_LinkDef.h must request a dictionary for
// the templated CP::TResultSetHandle instantiated on it.  However that
// class inherits from the backend CP::TDbiResultSetHandle so that dictionary
// is also needed.
#pragma link C++ class CP::TDbiResultSetHandle<CP::TTPC_Channel_Calib_Table>+;

// The direct class set handle dictionary.  This must be declared after the
// TDbiResultSetHandle.
#pragma link C++ class CP::TResultSetHandle<CP::TTPC_Channel_Calib_Table>+;

#endif
