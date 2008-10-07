#ifndef _LUC_FLOW_IN_TO_BOX_H_
#define _LUC_FLOW_IN_TO_BOX_H_
#if defined(_MSC_VER)
#pragma once
#endif

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
 * \file luc_flow_in_to_box.h
 * \ingroup Objects
 * \brief LUCFlowInToBox class header file.
 * \author Jim Naslund and Ming Chang
 */

#include "ccarbon_model/include/acarbon_flow.h"

/*!
 * \brief A class which represents a flow from a CarbonBoxModel into one
 *        of its CarbonBoxes.
 * \details This class represents a flow of carbon due to positive land
 *          use change.  This flow should be from a CarbonBoxModel to one
 *          of its CarbonBoxes.
 *         
 *          This flow will multiply the value that should be transferred by a
 *          fraction read in from input.  This is used in case there is more
 *          than one type of a box (i.e vegetationA and vegetationB) and they
 *          should receieve different percentages.
 */
class LUCFlowInToBox : public ACarbonFlow {

public:
    LUCFlowInToBox();
    LUCFlowInToBox( ICarbonContainer* aTarget, const int aFraction );
    LUCFlowInToBox( ICarbonContainer* aTarget );
    LUCFlowInToBox( const LUCFlowInToBox& aLucFlowInToBox );
    virtual ~LUCFlowInToBox();
    virtual LUCFlowInToBox* clone() const;

    virtual bool XMLDerivedClassParse( const xercesc::DOMNode* aNode );
    virtual void toInputXMLDerived( std::ostream& aOut, Tabs* aTabs ) const;
    virtual void toDebugXMLDerived( std::ostream& aOut, Tabs* aTabs ) const;
    static const std::string& getXMLNameStatic();
    virtual void completeInit( CarbonBoxModel& aParentBoxModel );
    const std::string& getXMLName() const;

    virtual void transfer( const double aValue, const EnvironmentalInfo* aEnvInfo,
                           const int aYear, const BoxType aBoxType );

};

#endif // _LUC_FLOW_IN_TO_BOX_H_

