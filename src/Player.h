#ifndef NULLSPACE_PLAYER_H_
#define NULLSPACE_PLAYER_H_

#include "Math.h"
#include "Types.h"
#include "render/Animation.h"

namespace null {

using PlayerId = u16;

enum StatusFlag {
  Status_Stealth = (1 << 0),
  Status_Cloak = (1 << 1),
  Status_XRadar = (1 << 2),
  Status_Antiwarp = (1 << 3),
  Status_Flash = (1 << 4),
  Status_Safety = (1 << 5),
  Status_UFO = (1 << 6),
  Status_InputChange = (1 << 7)
};

struct WeaponData {
  u16 type : 5;
  u16 level : 2;
  u16 shrapbouncing : 1;
  u16 shraplevel : 2;
  u16 shrap : 5;
  u16 alternate : 1;
};

struct Player {
  char name[20];
  char squad[20];

  s32 flag_points;
  s32 kill_points;

  PlayerId id;
  u16 frequency;

  Vector2f position;
  Vector2f velocity;

  Vector2f lerp_velocity;
  float lerp_time;

  u16 wins;
  u16 losses;

  u16 bounty;
  u16 s2c_latency;

  u16 timers;
  union {
    struct {
      u32 items;
    };
    struct {
      u32 shields : 1;
      u32 super : 1;
      u32 bursts : 4;
      u32 repels : 4;
      u32 thors : 4;
      u32 bricks : 4;
      u32 decoys : 4;
      u32 rockets : 4;
      u32 portals : 4;
      u32 padding : 2;
    };
  };

  float energy;
  float orientation;

  u8 ship;
  u8 togglables;
  u8 ping;
  u8 koth;

  u32 last_bounce_tick;

  u16 attach_parent;
  u16 flags;

  u16 timestamp;
  WeaponData weapon;

  float enter_delay;

  Animation warp_animation;
  Animation explode_animation;
};

}  // namespace null

#endif
