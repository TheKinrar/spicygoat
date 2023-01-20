//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include "../../world/geo/Axis.h"
#include "../../world/geo/Direction.h"
#include "../enums/Attachment.h"
#include "../enums/BambooLeaves.h"
#include "../enums/BedPart.h"
#include "../enums/BlockHalf.h"
#include "../enums/ChestType.h"
#include "../enums/ComparatorMode.h"
#include "../enums/DoorHinge.h"
#include "../enums/DoubleBlockHalf.h"
#include "../enums/Instrument.h"
#include "../enums/JigsawOrientation.h"
#include "../enums/PistonType.h"
#include "../enums/RailShape.h"
#include "../enums/SculkSensorPhase.h"
#include "../enums/SlabType.h"
#include "../enums/StairShape.h"
#include "../enums/StructureBlockMode.h"
#include "../enums/Thickness.h"
#include "../enums/Tilt.h"
#include "../enums/WallMountLocation.h"
#include "../enums/WallShape.h"
#include "../enums/WireConnection.h"
#include "BooleanProperty.h"
#include "EnumProperty.h"
#include "IntProperty.h"

namespace Properties {

inline const BooleanProperty attached("attached");
inline const BooleanProperty berries("berries");
inline const BooleanProperty bloom("bloom");
inline const BooleanProperty bottom("bottom");
inline const BooleanProperty can_summon("can_summon");
inline const BooleanProperty conditional("conditional");
inline const BooleanProperty disarmed("disarmed");
inline const BooleanProperty down("down");
inline const BooleanProperty drag("drag");
inline const BooleanProperty east("east");
inline const BooleanProperty enabled("enabled");
inline const BooleanProperty extended("extended");
inline const BooleanProperty eye("eye");
inline const BooleanProperty falling("falling");
inline const BooleanProperty hanging("hanging");
inline const BooleanProperty has_book("has_book");
inline const BooleanProperty has_bottle_0("has_bottle_0");
inline const BooleanProperty has_bottle_1("has_bottle_1");
inline const BooleanProperty has_bottle_2("has_bottle_2");
inline const BooleanProperty has_record("has_record");
inline const BooleanProperty in_wall("in_wall");
inline const BooleanProperty inverted("inverted");
inline const BooleanProperty lit("lit");
inline const BooleanProperty locked("locked");
inline const BooleanProperty north("north");
inline const BooleanProperty occupied("occupied");
inline const BooleanProperty open("open");
inline const BooleanProperty persistent("persistent");
inline const BooleanProperty powered("powered");
inline const BooleanProperty short_head("short");
inline const BooleanProperty shrieking("shrieking");
inline const BooleanProperty signal_fire("signal_fire");
inline const BooleanProperty slot_0_occupied("slot_0_occupied");
inline const BooleanProperty slot_1_occupied("slot_1_occupied");
inline const BooleanProperty slot_2_occupied("slot_2_occupied");
inline const BooleanProperty slot_3_occupied("slot_3_occupied");
inline const BooleanProperty slot_4_occupied("slot_4_occupied");
inline const BooleanProperty slot_5_occupied("slot_5_occupied");
inline const BooleanProperty snowy("snowy");
inline const BooleanProperty south("south");
inline const BooleanProperty triggered("triggered");
inline const BooleanProperty unstable("unstable");
inline const BooleanProperty up("up");
inline const BooleanProperty vine_end("vine_end");
inline const BooleanProperty waterlogged("waterlogged");
inline const BooleanProperty west("west");

inline const EnumProperty<Attachment> attachment("attachment", Attachment::values);
inline const EnumProperty<Axis> axis("axis", Axis::values);
inline const EnumProperty<Axis> horizontal_axis("axis", {Axis::x, Axis::z});
inline const EnumProperty<BambooLeaves> bamboo_leaves("leaves", BambooLeaves::values);
inline const EnumProperty<BedPart> bed_part("part", BedPart::values);
inline const EnumProperty<BlockHalf> block_half("half", BlockHalf::values);
inline const EnumProperty<ChestType> chest_type("type", ChestType::values);
inline const EnumProperty<ComparatorMode> comparator_mode("mode", ComparatorMode::values);
inline const EnumProperty<Direction> facing("facing", Direction::values);
inline const EnumProperty<Direction> hopper_facing("facing", {Direction::down, Direction::north, Direction::south, Direction::west, Direction::east});
inline const EnumProperty<Direction> horizontal_facing("facing", {Direction::north, Direction::south, Direction::west, Direction::east});
inline const EnumProperty<Direction> vertical_direction("vertical_direction", {Direction::up, Direction::down});
inline const EnumProperty<DoorHinge> door_hinge("hinge", DoorHinge::values);
inline const EnumProperty<DoubleBlockHalf> double_block_half("half", DoubleBlockHalf::values);
inline const EnumProperty<Instrument> instrument("instrument", Instrument::values);
inline const EnumProperty<JigsawOrientation> jigsaw_orientation("orientation", JigsawOrientation::values);
inline const EnumProperty<PistonType> piston_type("type", PistonType::values);
inline const EnumProperty<RailShape> rail_shape("shape", RailShape::values);
inline const EnumProperty<RailShape> straight_rail_shape("shape", {RailShape::north_south, RailShape::east_west, RailShape::ascending_east, RailShape::ascending_west, RailShape::ascending_north, RailShape::ascending_south});
inline const EnumProperty<SculkSensorPhase> sculk_sensor_phase("sculk_sensor_phase", SculkSensorPhase::values);
inline const EnumProperty<SlabType> slab_type("type", SlabType::values);
inline const EnumProperty<StairShape> stair_shape("shape", StairShape::values);
inline const EnumProperty<StructureBlockMode> structure_block_mode("mode", StructureBlockMode::values);
inline const EnumProperty<Thickness> thickness("thickness", Thickness::values);
inline const EnumProperty<Tilt> tilt("tilt", Tilt::values);
inline const EnumProperty<WallMountLocation> wall_mount_location("face", WallMountLocation::values);
inline const EnumProperty<WallShape> east_wall_shape("east", WallShape::values);
inline const EnumProperty<WallShape> north_wall_shape("north", WallShape::values);
inline const EnumProperty<WallShape> south_wall_shape("south", WallShape::values);
inline const EnumProperty<WallShape> west_wall_shape("west", WallShape::values);
inline const EnumProperty<WireConnection> east_wire_connection("east", WireConnection::values);
inline const EnumProperty<WireConnection> north_wire_connection("north", WireConnection::values);
inline const EnumProperty<WireConnection> south_wire_connection("south", WireConnection::values);
inline const EnumProperty<WireConnection> west_wire_connection("west", WireConnection::values);

inline const IntProperty age_1("age", 0, 1);
inline const IntProperty age_15("age", 0, 15);
inline const IntProperty age_2("age", 0, 2);
inline const IntProperty age_25("age", 0, 25);
inline const IntProperty age_3("age", 0, 3);
inline const IntProperty age_4("age", 0, 4);
inline const IntProperty age_5("age", 0, 5);
inline const IntProperty age_7("age", 0, 7);
inline const IntProperty bites("bites", 0, 6);
inline const IntProperty candles("candles", 1, 4);
inline const IntProperty charges("charges", 0, 4);
inline const IntProperty delay("delay", 1, 4);
inline const IntProperty distance_0_7("distance", 0, 7);
inline const IntProperty distance_1_7("distance", 1, 7);
inline const IntProperty eggs("eggs", 1, 4);
inline const IntProperty hatch("hatch", 0, 2);
inline const IntProperty honey_level("honey_level", 0, 5);
inline const IntProperty layers("layers", 1, 8);
inline const IntProperty level_15("level", 0, 15);
inline const IntProperty level_1_8("level", 1, 8);
inline const IntProperty level_3("level", 1, 3);
inline const IntProperty level_8("level", 0, 8);
inline const IntProperty moisture("moisture", 0, 7);
inline const IntProperty note("note", 0, 24);
inline const IntProperty pickles("pickles", 1, 4);
inline const IntProperty power("power", 0, 15);
inline const IntProperty rotation("rotation", 0, 15);
inline const IntProperty stage("stage", 0, 1);

}
