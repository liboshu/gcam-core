#ifndef _SCENARIO_H_
#define _SCENARIO_H_
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
* \file scenario.h
* \ingroup Objects
* \brief The Scenario class header file.
* \author Sonny Kim
*/
#include <vector>
#include <map>
#include <memory>
#include <string>

#include "util/base/include/iparsable.h"
#include "util/base/include/ivisitable.h"
#include "util/base/include/iround_trippable.h"

// Forward declarations
class Modeltime;
class Marketplace;
class World;
class Curve;
class Tabs;
class Solver;
class GHGPolicy;
class IClimateModel;
class OutputMetaData;

/*!
* \ingroup Objects
* \brief A class which defines a model scenario.
* \details The Scenario class object is the outermost container for all the
*          data, parameters, and results that defines a complete model run. A
*          scenario object contains the World object (which itself contains
*          regions, and so on) the Marketplace object, the Modeltime object, the
*          Solver object, and the FunctionManager object. The Scenario class
*          contains the highest levels methods for initializing data and running
*          the model, which trigger methods defined at more detailed levels
*          inside container relationships. As such, the scenario object has
*          special importance, and is defined globally (for now), as it is the
*          primary interface between key controlling parts of the model (like
*          the Main program and Solver) and the model details.
* \author Sonny Kim
*/

class Scenario: public IParsable, public IVisitable, public IRoundTrippable
{
public:
    Scenario();
    ~Scenario();
    const Modeltime* getModeltime() const;
    const Marketplace* getMarketplace() const;
    Marketplace* getMarketplace();
    const World* getWorld() const;
    World* getWorld();
    bool XMLParse( const xercesc::DOMNode* node );
    void completeInit();
    void setName(std::string newName);
    void toInputXML( std::ostream& out, Tabs* tabs ) const;

    const std::string& getName() const;
    bool run( const int aSinglePeriod, const bool aPrintDebugging, const std::string& aFilenameEnding = "" );
    void setTax( const GHGPolicy* aTax );
    const std::map<const std::string, const Curve*> getEmissionsQuantityCurves( const std::string& ghgName ) const;
    const std::map<const std::string, const Curve*> getEmissionsPriceCurves( const std::string& ghgName ) const;
    void writeOutputFiles() const;
    void dbOutput() const;
    void accept( IVisitor* aVisitor, const int aPeriod ) const;
    const IClimateModel* getClimateModel() const;
    static const std::string& getXMLNameStatic();
    void printOutputXML() const;

    //! Constant which when passed to the run method means to run all model periods.
    const static int RUN_ALL_PERIODS = -1;
private:
    //! A vector booleans, one per period, which denotes whether each period is valid.
    std::vector<bool> mIsValidPeriod;
    std::auto_ptr<Modeltime> modeltime; //!< The modeltime for the scenario
    std::auto_ptr<World> world; //!< The world object
    std::auto_ptr<Marketplace> marketplace; //!< The goods and services marketplace.
    std::auto_ptr<Solver> solver; //!< Pointer to a solution mechanism.

    //! A container of meta-data pertinent to outputting data.
    std::auto_ptr<OutputMetaData> mOutputMetaData;

    std::string name; //!< Scenario name.
    std::string scenarioSummary; //!< A summary of the purpose of the Scenario.
    std::vector<int> unsolvedPeriods; //!< Unsolved periods. 

    bool solve( const int period );

    bool calculatePeriod( const int aPeriod,
        std::ostream& aXMLDebugFile,
        std::ostream& aSGMDebugFile,
        Tabs* aTabs,
        const bool aPrintDebugging );

    void printGraphs( const int aPeriod ) const;
    void printLandAllocatorGraph( const int aPeriod, const bool aPrintValues ) const;
    void csvSGMGenFile( std::ostream& aFile ) const;
    void csvSGMOutputFile( std::ostream& aSGMDebugFile, const int aPeriod ) const;

    void openDebugXMLFile( std::ofstream& aXMLDebugFile,
        Tabs* aTabs,
        const std::string& aFileNameEnding ) const;

    void toDebugXMLOpen( std::ostream& aXMLDebugFile, Tabs* aTabs ) const;
    void toDebugXMLClose( std::ostream& aXMLDebugFile, Tabs* aTabs ) const;

    void logRunBeginning() const;
    void logPeriodBeginning( const int aPeriod ) const;
    void logPeriodEnding( const int aPeriod ) const;
    void logRunEnding() const;

    void openDebuggingFiles( std::ofstream& aXMLDebugFile,
        std::ofstream& aSGMDebugFile,
        Tabs* aTabs,
        const std::string& aFileNameEnding ) const;

    void writeDebuggingFiles( std::ostream& aXMLDebugFile,
        std::ostream& aSGMDebugFile,
        Tabs* aTabs,
        const int aPeriod ) const;

    void closeDebuggingFiles( std::ofstream& aXMLDebugFile,
        std::ofstream& aSGMDebugFile,
        Tabs* aTabs ) const;
};

#endif // _SCENARIO_H_

