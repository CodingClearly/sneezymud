//////////////////////////////////////////////////////////////////////////
//
// SneezyMUD - All rights reserved, SneezyMUD Coding Team
//
//
//////////////////////////////////////////////////////////////////////////


#include "stdsneezy.h"
#include "obj_base_container.h"
#include "obj_potion.h"
#include "shop.h"

TPotion::TPotion() :
  TBaseCup()
{
}

TPotion::TPotion(const TPotion &a) :
  TBaseCup(a)
{
}

TPotion & TPotion::operator=(const TPotion &a)
{
  if (this == &a) return *this;
  TBaseCup::operator=(a);
  return *this;
}

TPotion::~TPotion()
{
}



int TPotion::sellPrice(int shop_nr, float, int *)
{
  int cost_per;
  int price;

  cost_per = DrinkInfo[getDrinkType()]->price;
  price = (int) (getDrinkUnits() * cost_per * shop_index[shop_nr].profit_sell);

  if (obj_flags.cost <= 1) {
    price = max(0, price);
  } else {
    price = max(1, price);
  }

  return price;
}

int TPotion::shopPrice(int num, int shop_nr, float, int *) const
{
  int cost_per;
  int price;

  cost_per = DrinkInfo[getDrinkType()]->price;
  price = (int) (num * cost_per * shop_index[shop_nr].profit_buy);
  price = max(1, price);

  return price;
}

