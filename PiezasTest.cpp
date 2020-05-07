/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

// A sanity check to ensure that the GTest suite is working
TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

// Ensure that dropping a piece works.
TEST(PiezasTest, drop_test){
	Piezas obj;
	// Assuming no invalid moves, odd pieces are always an X.
	ASSERT_EQ(obj.dropPiece(0), X);
	// Assuming the same, even pieces are always an O.
	ASSERT_EQ(obj.dropPiece(0), O);
}

// Ensure that one cannot drop a piece in a full column.
TEST(PiezasTest, full_column_returns_blank){
	Piezas obj;
	obj.dropPiece(0);
	obj.dropPiece(0);
	obj.dropPiece(0);
	// A full column should return blank.
	ASSERT_EQ(obj.dropPiece(0), Blank);
}

// Ensure that one cannot drop a piece out of bounds (e.g. column -1 or column 4)
TEST(PiezasTest, out_of_bounds_column_returns_invalid){
	Piezas obj;
	// An out-of-bounds column should return Invalid.
	ASSERT_EQ(obj.dropPiece(-1), Invalid);
	ASSERT_EQ(obj.dropPiece(4), Invalid);
}

// Testing game win states

// All patterns being tested are the result of normal
// games where each player makes a valid move each turn.

// Other tests ensure that the program works correctly, i.e. giving
// the opponent their turn if either player submits an invalid move.

// Testing a pattern where no one wins (tie)
/* Pattern:
	XOXO
	OXOX
	XOXO
*/
TEST(PiezasTest, tie_game){
	Piezas obj;
	bool alternate = false;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 4; j++){
			if (alternate){
				obj.dropPiece(3-j);
			} else {
				obj.dropPiece(j);
			}
		}
		alternate = !alternate;
	}
	ASSERT_EQ(obj.gameState, Blank);
}

// Testing a pattern where X wins
/* Pattern:
	XOOX
	OXXX
	OOOX
*/
TEST(PiezasTest, X_wins_pattern1){
	Piezas obj;
	obj.dropPiece(3);
	obj.dropPiece(2);
	obj.dropPiece(3);
	obj.dropPiece(1);

	obj.dropPiece(2);
	obj.dropPiece(0);
	obj.dropPiece(1);
	obj.dropPiece(0);

	obj.dropPiece(0);
	obj.dropPiece(1);
	obj.dropPiece(3);
	obj.dropPiece(2);
	/*
	Board should now have the specified pattern
	*/
	ASSERT_EQ(obj.gameState, X);
}

// Testing a pattern where O wins by a hair
/* Pattern:
	OXXO
	XXOX
	OOOX
*/
TEST(PiezasTest, O_wins_pattern1){
	Piezas obj;
	obj.dropPiece(3);
	obj.dropPiece(0);
	obj.dropPiece(0);
	obj.dropPiece(1);

	obj.dropPiece(1);
	obj.dropPiece(2);
	obj.dropPiece(3);
	obj.dropPiece(2);

	obj.dropPiece(2);
	obj.dropPiece(3);
	obj.dropPiece(1);
	obj.dropPiece(0);
	// O should win by the horizontal 3x1 line in the lower
	// left corner of the board.
	ASSERT_EQ(obj.gameState, O);
}