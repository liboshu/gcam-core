#ifndef _SUPPLY_DEMAND_CURVE_H_
#define _SUPPLY_DEMAND_CURVE_H_
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
* \file supply_demand_curve.h
* \ingroup Objects
* \brief The SupplyDemandCurve class header file.
* \author Josh Lurz
*/

#include <functional>
#include <vector>

class ILogger;
class Market;
class World;
class Marketplace; 

/*!
* \ingroup Objects
* \brief A class which defines a single supply and demand curve. 
* \author Josh Lurz
*/

class SupplyDemandCurve {
public:
   SupplyDemandCurve( Market* marketIn );
   ~SupplyDemandCurve();
   void calculatePoints( const int numPoints, World* world, Marketplace* marketplace, const int period );
   void print( ILogger& aSDLog ) const;

private:
   Market* market; //!< Pointer to the market which the curve is calculating for.

/*!
* \ingroup Objects
* \brief A class which defines a single supply and demand point. 
* \author Josh Lurz
*/

class SupplyDemandPoint
{
   
public:
   SupplyDemandPoint( const double priceIn = 0, const double demandIn = 0, const double supplyIn = 0 );
   double getPrice() const;
   void print( ILogger& aSDLog ) const;
   
/*!
* \brief Binary comparison operator used for SavePoint pointers to order by increasing price. 
* \author Josh Lurz
*/  
   struct LesserPrice : public std::binary_function<SupplyDemandPoint*,SupplyDemandPoint*,bool>
   {
      //! Operator which performs comparison. 
      bool operator()( const SupplyDemandPoint* lhs, const SupplyDemandPoint* rhs ) const
      {   
         return lhs->getPrice() < rhs->getPrice();
      }
   };

   private:
      double price; //!< Fixed Price
      double demand; //!< Demand at the price.
      double supply; //!< Supply at the price. 
   };
   
   std::vector<SupplyDemandPoint*> points; //!< Vector of points. 

};

#endif // _SUPPLY_DEMAND_CURVE_H_
