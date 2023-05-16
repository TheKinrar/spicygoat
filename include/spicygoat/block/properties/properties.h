//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include <spicygoat/block/enums/Attachment.h>
#include <spicygoat/block/enums/BambooLeaves.h>
#include <spicygoat/block/enums/BedPart.h>
#include <spicygoat/block/enums/BlockHalf.h>
#include <spicygoat/block/enums/ChestType.h>
#include <spicygoat/block/enums/ComparatorMode.h>
#include <spicygoat/block/enums/DoorHinge.h>
#include <spicygoat/block/enums/DoubleBlockHalf.h>
#include <spicygoat/block/enums/Instrument.h>
#include <spicygoat/block/enums/JigsawOrientation.h>
#include <spicygoat/block/enums/PistonType.h>
#include <spicygoat/block/enums/RailShape.h>
#include <spicygoat/block/enums/SculkSensorPhase.h>
#include <spicygoat/block/enums/SlabType.h>
#include <spicygoat/block/enums/StairShape.h>
#include <spicygoat/block/enums/StructureBlockMode.h>
#include <spicygoat/block/enums/Thickness.h>
#include <spicygoat/block/enums/Tilt.h>
#include <spicygoat/block/enums/WallMountLocation.h>
#include <spicygoat/block/enums/WallShape.h>
#include <spicygoat/block/enums/WireConnection.h>
#include <spicygoat/block/properties/BooleanProperty.h>
#include <spicygoat/block/properties/EnumProperty.h>
#include <spicygoat/block/properties/IntProperty.h>
#include <spicygoat/world/geo/Axis.h>
#include <spicygoat/world/geo/Direction.h>

namespace Properties {

extern const BooleanProperty attached;
extern const BooleanProperty berries;
extern const BooleanProperty bloom;
extern const BooleanProperty bottom;
extern const BooleanProperty can_summon;
extern const BooleanProperty conditional;
extern const BooleanProperty cracked;
extern const BooleanProperty disarmed;
extern const BooleanProperty down;
extern const BooleanProperty drag;
extern const BooleanProperty east;
extern const BooleanProperty enabled;
extern const BooleanProperty extended;
extern const BooleanProperty eye;
extern const BooleanProperty falling;
extern const BooleanProperty hanging;
extern const BooleanProperty has_book;
extern const BooleanProperty has_bottle_0;
extern const BooleanProperty has_bottle_1;
extern const BooleanProperty has_bottle_2;
extern const BooleanProperty has_record;
extern const BooleanProperty in_wall;
extern const BooleanProperty inverted;
extern const BooleanProperty lit;
extern const BooleanProperty locked;
extern const BooleanProperty north;
extern const BooleanProperty occupied;
extern const BooleanProperty open;
extern const BooleanProperty persistent;
extern const BooleanProperty powered;
extern const BooleanProperty short_head;
extern const BooleanProperty shrieking;
extern const BooleanProperty signal_fire;
extern const BooleanProperty slot_0_occupied;
extern const BooleanProperty slot_1_occupied;
extern const BooleanProperty slot_2_occupied;
extern const BooleanProperty slot_3_occupied;
extern const BooleanProperty slot_4_occupied;
extern const BooleanProperty slot_5_occupied;
extern const BooleanProperty snowy;
extern const BooleanProperty south;
extern const BooleanProperty triggered;
extern const BooleanProperty unstable;
extern const BooleanProperty up;
extern const BooleanProperty vine_end;
extern const BooleanProperty waterlogged;
extern const BooleanProperty west;

extern const EnumProperty<Attachment> attachment;
extern const EnumProperty<Axis> axis;
extern const EnumProperty<Axis> horizontal_axis;
extern const EnumProperty<BambooLeaves> bamboo_leaves;
extern const EnumProperty<BedPart> bed_part;
extern const EnumProperty<BlockHalf> block_half;
extern const EnumProperty<ChestType> chest_type;
extern const EnumProperty<ComparatorMode> comparator_mode;
extern const EnumProperty<Direction> facing;
extern const EnumProperty<Direction> hopper_facing;
extern const EnumProperty<Direction> horizontal_facing;
extern const EnumProperty<Direction> vertical_direction;
extern const EnumProperty<DoorHinge> door_hinge;
extern const EnumProperty<DoubleBlockHalf> double_block_half;
extern const EnumProperty<Instrument> instrument;
extern const EnumProperty<JigsawOrientation> jigsaw_orientation;
extern const EnumProperty<PistonType> piston_type;
extern const EnumProperty<RailShape> rail_shape;
extern const EnumProperty<RailShape> straight_rail_shape;
extern const EnumProperty<SculkSensorPhase> sculk_sensor_phase;
extern const EnumProperty<SlabType> slab_type;
extern const EnumProperty<StairShape> stair_shape;
extern const EnumProperty<StructureBlockMode> structure_block_mode;
extern const EnumProperty<Thickness> thickness;
extern const EnumProperty<Tilt> tilt;
extern const EnumProperty<WallMountLocation> wall_mount_location;
extern const EnumProperty<WallShape> east_wall_shape;
extern const EnumProperty<WallShape> north_wall_shape;
extern const EnumProperty<WallShape> south_wall_shape;
extern const EnumProperty<WallShape> west_wall_shape;
extern const EnumProperty<WireConnection> east_wire_connection;
extern const EnumProperty<WireConnection> north_wire_connection;
extern const EnumProperty<WireConnection> south_wire_connection;
extern const EnumProperty<WireConnection> west_wire_connection;

extern const IntProperty age_1;
extern const IntProperty age_15;
extern const IntProperty age_2;
extern const IntProperty age_25;
extern const IntProperty age_3;
extern const IntProperty age_4;
extern const IntProperty age_5;
extern const IntProperty age_7;
extern const IntProperty bites;
extern const IntProperty candles;
extern const IntProperty charges;
extern const IntProperty delay;
extern const IntProperty distance_0_7;
extern const IntProperty distance_1_7;
extern const IntProperty dusted;
extern const IntProperty eggs;
extern const IntProperty flower_amount;
extern const IntProperty hatch;
extern const IntProperty honey_level;
extern const IntProperty layers;
extern const IntProperty level_15;
extern const IntProperty level_1_8;
extern const IntProperty level_3;
extern const IntProperty level_8;
extern const IntProperty moisture;
extern const IntProperty note;
extern const IntProperty pickles;
extern const IntProperty power;
extern const IntProperty rotation;
extern const IntProperty stage;

}  // namespace Properties
