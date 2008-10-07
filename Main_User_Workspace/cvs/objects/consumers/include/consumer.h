#ifndef _CONSUMER_H_
#define _CONSUMER_H_
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
* \file consumer.h
* \ingroup Objects
* \brief Consumer class header file.
* \author Pralit Patel
* \author Sonny Kim
*/

#include <string>
#include <xercesc/dom/DOMNode.hpp>

#include "technologies/include/base_technology.h"

class NationalAccount;
class Demographic;
class Tabs;
class MoreSectorInfo;
class IVisitor;
class IExpectedProfitRateCalculator;
/*! 
* \ingroup Objects
* \brief A type of SGM technology representing purchases of good by consumers.
* \details CHANGE
* \author Pralit Patel, Sonny Kim
*/
class Consumer : public BaseTechnology
{
    friend class SGMGenTable;
public:
    Consumer();
    virtual Consumer* clone() const = 0;
    virtual ~Consumer() {};

    virtual void copyParam( const BaseTechnology* baseTech,
                            const int aPeriod ) = 0;

    virtual void completeInit( const std::string& aRegionName,
                               const std::string& aSectorName,
                               const std::string& aSubsectorName ) = 0;
    
    virtual void initCalc( const MoreSectorInfo* aMoreSectorInfo,
                           const std::string& aRegionName, 
                           const std::string& aSectorName,
                           NationalAccount& nationalAccount,
                           const Demographic* aDemographics,
                           const double aCapitalStock,
                           const int aPeriod ) = 0;

    virtual void operate( NationalAccount& aNationalAccount, const Demographic* aDemographics, 
        const MoreSectorInfo* aMoreSectorInfo, const std::string& aRegionName, 
        const std::string& aSectorName, const bool aIsNewVintageMode, const int aPeriod ) = 0;

    virtual void updateMarketplace( const std::string& aSectorName, const std::string& aRegionName,
                                    const int aPeriod );
    virtual void postCalc( const std::string& aRegionName, const std::string& aSectorName, 
                           const int aPeriod ){} // do nothing for now.
    virtual void csvSGMOutputFile( std::ostream& aFile, const int period ) const = 0;
    virtual void accept( IVisitor* aVisitor, const int aPeriod ) const;
    
    // Consumer should be contained directly in Subsector and then all these functions could be removed.
    double getExpectedProfitRate( const NationalAccount& aNationalAccount,
                                  const std::string& aRegionName,
                                  const std::string& aSectorName,
                                  const IExpectedProfitRateCalculator* aExpProfitRateCalc,
                                  const double aInvestmentLogitExp,
                                  const bool aIsShareCalc,
                                  const int aPeriod ) const
    { 
        return 0; 
    }

    double getCapitalOutputRatio( const IDistributor* aDistributor,
                                  const IExpectedProfitRateCalculator* aExpProfitRateCalc,
                                  const NationalAccount& aNationalAccount,
                                  const std::string& aRegionName,
                                  const std::string& aSectorName, 
                                  const int aPeriod ) const
    {
        return 0;
    }

    double getAnnualInvestment( const int aPeriod ) const { 
        return 0;
    }
    double setInvestment( const std::string& aRegionName, const double aAnnualInvestment,
                          const double aTotalInvestment, const int aPeriod )
    { 
        return 0; 
    }
    double getFixedInvestment( const int aPeriod ) const {
        return 0;
    }
    double getOutput( const int aPeriod ) const {
        return 0;
    }
    double getCapital() const {
        return 0;
    }
    double distributeInvestment( const IDistributor* aDistributor,
        NationalAccount& aNationalAccount,
        const IExpectedProfitRateCalculator* aExpProfitRateCalc,
        const std::string& aRegionName,
        const std::string& aSectorName,
        const double aNewInvestment,
        const int aPeriod )
    {
        return 0;
    };
    void setTypeHelper( TechnologyType* aTechType ){}
protected:
    void calcInputDemand( double aConsumption, const std::string& aRegionName, 
        const std::string& aSectorName, int aPeriod );
    
    void calcEmissions( const std::string& aGoodName, const std::string& aRegionName, const int aPeriod );
    virtual const std::string& getXMLName() const = 0;
    virtual bool XMLDerivedClassParse( const std::string& nodeName, const xercesc::DOMNode* curr ) = 0;
    virtual void toInputXMLDerived( std::ostream& out, Tabs* tabs ) const = 0;
    virtual void toDebugXMLDerived( const int period, std::ostream& out, Tabs* tabs ) const = 0;
};

#endif // _CONSUMER_H_

