//////////////////////////////////////////////////////////////////////////
//
// SneezyMUD - All rights reserved, SneezyMUD Coding Team
//
// $Log: disc_theology.cc,v $
// Revision 5.4  2002/01/09 23:27:03  peel
// More splitting up of obj2.h
// renamed food.cc to obj_food.cc
// renamed organic.cc to obj_organic.cc
//
// Revision 5.3  2001/11/11 06:48:49  brutius
// *** empty log message ***
//
// Revision 5.2  2001/09/07 07:07:34  peel
// changed TThing->stuff to getStuff() and setStuff()
//
// Revision 5.1.1.1  1999/10/16 04:32:20  batopr
// new branch
//
// Revision 5.1  1999/10/16 04:31:17  batopr
// new branch
//
// Revision 1.1  1999/09/12 17:24:04  sneezy
// Initial revision
//
//
//////////////////////////////////////////////////////////////////////////


// DISC_THEOLOGY.cc
// Part of SneezyMUD 4.5

#include "stdsneezy.h"
#include "disc_theology.h"

#include "obj_symbol.h"
void TBeing::doAttune(const char *argument)
{
  char name_buf[256];
  TThing *obj;

  only_argument(argument, name_buf);

  if (!*name_buf) {
    sendTo("What is it you intend to attune?\n\r");
    return;
  }

  if (!hasClass(CLASS_CLERIC) && !hasClass(CLASS_DEIKHAN)) {
    sendTo("Only clerical types can attune objects.\n\r");
  }

  if (!(obj = equipment[getPrimaryHold()]) || !isname(name_buf, obj->name)) {
    sendTo("You'll have to be holding that in your primary hand to attune it.\n\r");
    return;
  }

  if (!doesKnowSkill(SKILL_ATTUNE)) {
    sendTo("You know nothing about attuning symbols.\n\r");
    return;
  }
  if (getPosition() > POSITION_SITTING) {
    sendTo("You can not attune symbols unless you are sitting comfortably.\n\r");
    return;
  }
  attune(this, obj);
}

void TThing::attuneMe(TBeing *caster, TVial *)
{
  caster->sendTo("You can only attune symbols.\n\r");
}

void TSymbol::attuneMe(TBeing *caster, TVial *obj)
{
  if (getSymbolFaction() != FACT_UNDEFINED) {
    caster->sendTo(COLOR_OBJECTS, "But %s has already been attuned!\n\r", getName());
    return;
  }

  int reqUses = 0;
  int uses = 0;
 
  if (!checkAttuneUsage(caster, &uses, &reqUses, &obj, this))
    return;

  if (caster->getMove() < 10) {
    act("You are much too tired to attune $p.", FALSE, caster, this, NULL, TO_CHAR);
    return;
  }

  act("You place $p carefully on your lap.",FALSE, caster, this, NULL, TO_CHAR);
  act("$n places $p carefully on $s lap.",FALSE, caster, this, NULL, TO_ROOM);
  act("You say a small prayer as you sprinkle some drops from $P on $p and begin attuning it.", FALSE, caster, this, obj, TO_CHAR);
  act("$n sprinkles some drops from $P on $p and begins to pray.", FALSE, caster, this, obj, TO_ROOM);
  // terminate sitting tasks
  if ((caster->task) && caster->getPosition() <= POSITION_SITTING)
    caster->stopTask();

  ubyte rounds =  (ubyte) (getSymbolLevel() / 2 + 1);
  start_task(caster, (TObj *) this, NULL, TASK_ATTUNE, NULL, 0, (ushort) caster->in_room, rounds, 0, 0);
}


void attune(TBeing * caster, TThing * sym) 
{
  TVial *best = NULL;
  TThing *obj = NULL;

  if (caster->fight()) {
    caster->sendTo("Not while fighting..\n\r");
    return;
  }
  
  for (obj = caster->getStuff(); obj; obj = obj->nextThing) 
    obj->getBestVial(&best);
  
  if (!best) {
    caster->sendTo("You need more holy water to attempt this attune.\n\r");
    //caster->sendTo("You need to own some holy water.\n\r");
    return;
  }
  sym->attuneMe(caster, best);
}


