//////////////////////////////////////////////////////////////////////////
//
// SneezyMUD - All rights reserved, SneezyMUD Coding Team
//
//
//////////////////////////////////////////////////////////////////////////

#ifndef __OBJ_COMMODITY_H
#define __OBJ_COMMODITY_H

#include "obj.h"

class TCommodity : public TObj {
  private:
  public:
    virtual void assignFourValues(int, int, int, int);
    virtual void getFourValues(int *, int *, int *, int *) const;
    virtual string statObjInfo() const;
    virtual itemTypeT itemType() const { return ITEM_RAW_MATERIAL; }

    virtual void lowCheck();
    virtual void logMe(const TBeing *, const char *) const {}
    virtual void buyMe(TBeing *, TMonster *, int, int);
    virtual void sellMe(TBeing *, TMonster *, int);
    virtual int sellCommod(TBeing *, TMonster *, int, TThing *);
    virtual void valueMe(TBeing *, TMonster *, int);
    virtual const string shopList(const TBeing *, const char *, int, int, int, int, int, unsigned long int) const;
    virtual int shopPrice(int, int, int, int *) const;
    virtual int sellPrice(int, int, int *);

    int pricePerUnit() const;
    int numUnits() const;

    TCommodity();
    TCommodity(const TCommodity &a);
    TCommodity & operator=(const TCommodity &a);
    virtual ~TCommodity();
};


#endif
