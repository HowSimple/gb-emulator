#include "pch.h"
#include "utils.h"

TEST(BIT, bit01)
{
	u8 value = 0b10011000;
	EXPECT_EQ(1, gb::bit(7, value));
	EXPECT_EQ(0, gb::bit(0, value));
	EXPECT_EQ(1, gb::bit(3, value));
}
TEST(BIT, set_bit01)
{
	u8 value = 0;
	gb::set_bit(3, value);
	EXPECT_EQ(0b00001000, value);
	gb::set_bit(0, value);
	EXPECT_EQ(0b00001001, value);

	
}
TEST(BIT, unset_bit01)
{
	u8 value = 0b10000000;
	gb::unset_bit(7, value);
	EXPECT_EQ(0, value);
	 value = 0b11111111;
	gb::unset_bit(0, value);
	EXPECT_EQ(0b11111110, value);
}