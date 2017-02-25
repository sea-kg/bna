#include "or.h"

namespace reversehash {
	
	OperationOr::~OperationOr(){
	}
	
	// -----------------------------------------------------------------
	
	QString OperationOr::type(){
		return QString("|");
	};
	
	// -----------------------------------------------------------------
	
	bool OperationOr::calc(bool b1, bool b2){
		return b1|b2;
	};
}
