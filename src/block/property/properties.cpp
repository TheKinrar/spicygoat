//
// Created by thekinrar on 19/01/23.
//

#include <spicygoat/block/properties/properties.h>

namespace Properties {

const BooleanProperty attached = BooleanProperty("attached");
const BooleanProperty berries = BooleanProperty("berries");
const BooleanProperty bloom = BooleanProperty("bloom");
const BooleanProperty bottom = BooleanProperty("bottom");
const BooleanProperty can_summon = BooleanProperty("can_summon");
const BooleanProperty conditional = BooleanProperty("conditional");
const BooleanProperty cracked = BooleanProperty("cracked");
const BooleanProperty disarmed = BooleanProperty("disarmed");
const BooleanProperty down = BooleanProperty("down");
const BooleanProperty drag = BooleanProperty("drag");
const BooleanProperty east = BooleanProperty("east");
const BooleanProperty enabled = BooleanProperty("enabled");
const BooleanProperty extended = BooleanProperty("extended");
const BooleanProperty eye = BooleanProperty("eye");
const BooleanProperty falling = BooleanProperty("falling");
const BooleanProperty hanging = BooleanProperty("hanging");
const BooleanProperty has_book = BooleanProperty("has_book");
const BooleanProperty has_bottle_0 = BooleanProperty("has_bottle_0");
const BooleanProperty has_bottle_1 = BooleanProperty("has_bottle_1");
const BooleanProperty has_bottle_2 = BooleanProperty("has_bottle_2");
const BooleanProperty has_record = BooleanProperty("has_record");
const BooleanProperty in_wall = BooleanProperty("in_wall");
const BooleanProperty inverted = BooleanProperty("inverted");
const BooleanProperty lit = BooleanProperty("lit");
const BooleanProperty locked = BooleanProperty("locked");
const BooleanProperty north = BooleanProperty("north");
const BooleanProperty occupied = BooleanProperty("occupied");
const BooleanProperty open = BooleanProperty("open");
const BooleanProperty persistent = BooleanProperty("persistent");
const BooleanProperty powered = BooleanProperty("powered");
const BooleanProperty short_head = BooleanProperty("short");
const BooleanProperty shrieking = BooleanProperty("shrieking");
const BooleanProperty signal_fire = BooleanProperty("signal_fire");
const BooleanProperty slot_0_occupied = BooleanProperty("slot_0_occupied");
const BooleanProperty slot_1_occupied = BooleanProperty("slot_1_occupied");
const BooleanProperty slot_2_occupied = BooleanProperty("slot_2_occupied");
const BooleanProperty slot_3_occupied = BooleanProperty("slot_3_occupied");
const BooleanProperty slot_4_occupied = BooleanProperty("slot_4_occupied");
const BooleanProperty slot_5_occupied = BooleanProperty("slot_5_occupied");
const BooleanProperty snowy = BooleanProperty("snowy");
const BooleanProperty south = BooleanProperty("south");
const BooleanProperty triggered = BooleanProperty("triggered");
const BooleanProperty unstable = BooleanProperty("unstable");
const BooleanProperty up = BooleanProperty("up");
const BooleanProperty vine_end = BooleanProperty("vine_end");
const BooleanProperty waterlogged = BooleanProperty("waterlogged");
const BooleanProperty west = BooleanProperty("west");

const EnumProperty<Attachment> attachment("attachment", Attachment::values);
const EnumProperty<Axis> axis("axis", Axis::values);
const EnumProperty<Axis> horizontal_axis("axis", {Axis::x, Axis::z});
const EnumProperty<BambooLeaves> bamboo_leaves("leaves", BambooLeaves::values);
const EnumProperty<BedPart> bed_part("part", BedPart::values);
const EnumProperty<BlockHalf> block_half("half", BlockHalf::values);
const EnumProperty<ChestType> chest_type("type", ChestType::values);
const EnumProperty<ComparatorMode> comparator_mode("mode", ComparatorMode::values);
const EnumProperty<Direction> facing("facing", Direction::values);
const EnumProperty<Direction> hopper_facing("facing", {Direction::down, Direction::north, Direction::south,
                                                       Direction::west, Direction::east});
const EnumProperty<Direction> horizontal_facing("facing",
                                                {Direction::north, Direction::south, Direction::west, Direction::east});
const EnumProperty<Direction> vertical_direction("vertical_direction", {Direction::up, Direction::down});
const EnumProperty<DoorHinge> door_hinge("hinge", DoorHinge::values);
const EnumProperty<DoubleBlockHalf> double_block_half("half", DoubleBlockHalf::values);
const EnumProperty<Instrument> instrument("instrument", Instrument::values);
const EnumProperty<JigsawOrientation> jigsaw_orientation("orientation", JigsawOrientation::values);
const EnumProperty<PistonType> piston_type("type", PistonType::values);
const EnumProperty<RailShape> rail_shape("shape", RailShape::values);
const EnumProperty<RailShape> straight_rail_shape("shape", {RailShape::north_south, RailShape::east_west,
                                                            RailShape::ascending_east, RailShape::ascending_west,
                                                            RailShape::ascending_north, RailShape::ascending_south});
const EnumProperty<SculkSensorPhase> sculk_sensor_phase("sculk_sensor_phase", SculkSensorPhase::values);
const EnumProperty<SlabType> slab_type("type", SlabType::values);
const EnumProperty<StairShape> stair_shape("shape", StairShape::values);
const EnumProperty<StructureBlockMode> structure_block_mode("mode", StructureBlockMode::values);
const EnumProperty<Thickness> thickness("thickness", Thickness::values);
const EnumProperty<Tilt> tilt("tilt", Tilt::values);
const EnumProperty<WallMountLocation> wall_mount_location("face", WallMountLocation::values);
const EnumProperty<WallShape> east_wall_shape("east", WallShape::values);
const EnumProperty<WallShape> north_wall_shape("north", WallShape::values);
const EnumProperty<WallShape> south_wall_shape("south", WallShape::values);
const EnumProperty<WallShape> west_wall_shape("west", WallShape::values);
const EnumProperty<WireConnection> east_wire_connection("east", WireConnection::values);
const EnumProperty<WireConnection> north_wire_connection("north", WireConnection::values);
const EnumProperty<WireConnection> south_wire_connection("south", WireConnection::values);
const EnumProperty<WireConnection> west_wire_connection("west", WireConnection::values);

const IntProperty age_1 = IntProperty("age", 0, 1);
const IntProperty age_15 = IntProperty("age", 0, 15);
const IntProperty age_2 = IntProperty("age", 0, 2);
const IntProperty age_25 = IntProperty("age", 0, 25);
const IntProperty age_3 = IntProperty("age", 0, 3);
const IntProperty age_4 = IntProperty("age", 0, 4);
const IntProperty age_5 = IntProperty("age", 0, 5);
const IntProperty age_7 = IntProperty("age", 0, 7);
const IntProperty bites = IntProperty("bites", 0, 6);
const IntProperty candles = IntProperty("candles", 1, 4);
const IntProperty charges = IntProperty("charges", 0, 4);
const IntProperty delay = IntProperty("delay", 1, 4);
const IntProperty distance_0_7 = IntProperty("distance", 0, 7);
const IntProperty distance_1_7 = IntProperty("distance", 1, 7);
const IntProperty dusted = IntProperty("dusted", 0, 3);
const IntProperty eggs = IntProperty("eggs", 1, 4);
const IntProperty flower_amount = IntProperty("flower_amount", 1, 4);
const IntProperty hatch = IntProperty("hatch", 0, 2);
const IntProperty honey_level = IntProperty("honey_level", 0, 5);
const IntProperty layers = IntProperty("layers", 1, 8);
const IntProperty level_15 = IntProperty("level", 0, 15);
const IntProperty level_1_8 = IntProperty("level", 1, 8);
const IntProperty level_3 = IntProperty("level", 1, 3);
const IntProperty level_8 = IntProperty("level", 0, 8);
const IntProperty moisture = IntProperty("moisture", 0, 7);
const IntProperty note = IntProperty("note", 0, 24);
const IntProperty pickles = IntProperty("pickles", 1, 4);
const IntProperty power = IntProperty("power", 0, 15);
const IntProperty rotation = IntProperty("rotation", 0, 15);
const IntProperty stage = IntProperty("stage", 0, 1);

}  // namespace Properties
