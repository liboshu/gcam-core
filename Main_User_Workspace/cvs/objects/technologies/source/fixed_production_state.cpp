/*
 * LEGAL NOTICE
 * This computer software was prepared by Battelle Memorial Institute,
 * hereinafter the Contractor, under Contract No. DE-AC05-76RL0 1830
 * with the Department of Energy (DOE). NEITHER THE GOVERNMENT NOR THE
 * CONTRACTOR MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY
 * LIABILITY FOR THE USE OF THIS SOFTWARE. This notice including this
 * sentence must appear on any copies of this computer software.
 * 
 * EXPORT CONTROL
 * User agrees that the Software will not be shipped, transferred or
 * exported into any country or used in any manner prohibited by the
 * United States Export Administration Act or any other applicable
 * export laws, restrictions or regulations (collectively the "Export Laws").
 * Export of the Software may require some form of license or other
 * authority from the U.S. Government, and failure to obtain such
 * export control license may result in criminal liability under
 * U.S. laws. In addition, if the Software is identified as export controlled
 * items under the Export Laws, User represents and warrants that User
 * is not a citizen, or otherwise located within, an embargoed nation
 * (including without limitation Iran, Syria, Sudan, Cuba, and North Korea)
 *     and that User is not otherwise prohibited
 * under the Export Laws from receiving the Software.
 * 
 * All rights to use the Software are granted on condition that such
 * rights are forfeited if User fails to comply with the terms of
 * this Agreement.
 * 
 * User agrees to identify, defend and hold harmless BATTELLE,
 * its officers, agents and employees from all liability involving
 * the violation of such Export Laws, either directly or indirectly,
 * by User.
 */

/*! 
 * \file fixed_production_state.cpp
 * \ingroup Objects
 * \brief FixedProductionState class source file.
 * \author Josh Lurz
 */

#include "util/base/include/definitions.h"
#include <cassert>
#include "technologies/include/fixed_production_state.h"
#include "util/base/include/xml_helper.h"

using namespace std;

FixedProductionState::FixedProductionState(){
}

FixedProductionState* FixedProductionState::clone() const {
    return new FixedProductionState( *this );
}

bool FixedProductionState::isSameType( const string& aType ) const {
    return aType == getXMLNameStatic();
}

const string& FixedProductionState::getName() const {
    return getXMLNameStatic();
}

void FixedProductionState::toDebugXML( const int aPeriod,
                                       ostream& aOut,
                                       Tabs* aTabs ) const
{
    XMLWriteOpeningTag( getXMLNameStatic(), aOut, aTabs );
    XMLWriteElement( mFixedOutput, "base-output", aOut, aTabs );
    XMLWriteClosingTag( getXMLNameStatic(), aOut, aTabs );
}

const string& FixedProductionState::getXMLNameStatic() {
    const static string XML_NAME = "fixed-production-state";
    return XML_NAME;
}

double FixedProductionState::calcProduction( const string& aRegionName,
                                             const string& aSectorName,
                                             const double aVariableOutput,
                                             const MarginalProfitCalculator* aMarginalProfitCalc,
                                             const double aFixedOutputScaleFactor,
                                             const vector<IShutdownDecider*>& aShutdownDeciders,
                                             const int aPeriod ) const
{
    // Fixed output must be initialized.
    assert( mFixedOutput.isInited() );

    // Production is the fixed output multiplied by the scale factor.
    return mFixedOutput * aFixedOutputScaleFactor;
}

void FixedProductionState::setBaseOutput( const double aBaseOutput, const int aBaseYear ){
    assert( aBaseOutput >= 0 );
    mFixedOutput.set( aBaseOutput );
}

bool FixedProductionState::isNewInvestment() const {
    // Fixed output is converted to a vintage production state if it has a
    // lifetime longer than one timestep, so this production state always is new
    // investment.
    return true;
}

bool FixedProductionState::isOperating() const {
    return true;
}
