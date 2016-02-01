//
//  EnemyMovements.h
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-29.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef EnemyMovements_h
#define EnemyMovements_h

class Enemy;

extern void EnemyMovement_00_FollowDirection( Enemy* _pTarget );
extern void EnemyMovement_01_Sinus_MoveLeft( Enemy* _pTarget );

#endif /* EnemyMovements_h */