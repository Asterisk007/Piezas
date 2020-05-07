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

// Ensure that we can check where a piece is.
TEST(PiezasTest, piece_at_test){
	Piezas obj;
	obj.dropPiece(0);
	obj.dropPiece(1);
	ASSERT_TRUE(obj.pieceAt(0, 0) == X);
	ASSERT_TRUE(obj.pieceAt(0, 1) == O);
}

// Ensure that if we check an area out of bounds, we get Invalid.
TEST(PiezasTest, piece_at_test_invalid){
	Piezas obj;
	ASSERT_TRUE(obj.pieceAt(4, 5) == Invalid);
}

// Ensure that one cannot drop a piece in a full column.
TEST(PiezasTest, full_column_returns_blank){
	Piezas obj;
	obj.dropPiece(0);
	obj.dropPiece(0);
	obj.dropPiece(0);
	// A full column should return blank.
	ASSERT_EQ(obj.dropPiece(0), Blank);
	// Do this twice for code coverage.
	ASSERT_EQ(obj.dropPiece(0), Blank);
}

// Ensure that one cannot drop a piece out of bounds (e.g. column -1 or column 4)
TEST(PiezasTest, out_of_bounds_column_returns_invalid){
	Piezas obj;
	// An out-of-bounds column should return Invalid.
	ASSERT_EQ(obj.dropPiece(-1), Invalid);
	ASSERT_EQ(obj.dropPiece(4), Invalid);
}

// Ensure that if a game is not yet complete, the board returns Invalid
// as the current game state.
TEST(PiezasTest, unfinished_game_returns_invalid){
	Piezas obj;
	obj.dropPiece(0);
	ASSERT_TRUE(obj.gameState() == Invalid);
}

// Esure that resetting the board causes all spaces to be Blank
TEST(PiezasTest, reset_board_is_blank){
	Piezas obj;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 4; j++){
			obj.dropPiece(j);
		}
	}
	obj.reset();
	bool actual = true;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 4; j++){
			if (obj.pieceAt(i, j) != Blank){
				actual = false;
			}
		}
	}
	ASSERT_TRUE(actual);
}

/* Testing game win patterns */
// All patterns being tested here are the result of
// games where each player makes a valid move each turn.

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
	ASSERT_TRUE(obj.gameState() == Blank);
}

// Testing a pattern where X wins
/* Pattern:
	XOOX
	OXXX
	OOOX
*/
TEST(PiezasTest, X_wins_3x1_middle_right){
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
	ASSERT_TRUE(obj.gameState() == X);
}

// Testing a pattern where O wins
/* Pattern:
	OXXO
	XXOX
	OOOX
*/
TEST(PiezasTest, O_wins_3x1_bottom_left){
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
	ASSERT_TRUE(obj.gameState() == O);
}
// Testing a pattern where X wins
// For the sake of satisfying the code coverage
/* Pattern:
	OXOX
	XXXO
	OOXO
*/
TEST(PiezasTest, X_wins_3x1_middle_left){
	Piezas obj;
	obj.dropPiece(2);
	obj.dropPiece(1);
	obj.dropPiece(1);
	obj.dropPiece(3);

	obj.dropPiece(2);
	obj.dropPiece(0);
	obj.dropPiece(0);
	obj.dropPiece(3);

	obj.dropPiece(3);
	obj.dropPiece(2);
	obj.dropPiece(1);
	obj.dropPiece(0);

	ASSERT_TRUE(obj.gameState() == X);
}
// Testing a tied pattern
/* Pattern:
	XOOX
	OOOX
	XXXO
*/
TEST(PiezasTest, tie_game_1){
	Piezas obj;
	obj.dropPiece(0);
	obj.dropPiece(0);
	obj.dropPiece(1);
	obj.dropPiece(1);

	obj.dropPiece(2);
	obj.dropPiece(3);
	obj.dropPiece(3);
	obj.dropPiece(2);

	obj.dropPiece(0);
	obj.dropPiece(1);
	obj.dropPiece(3);
	obj.dropPiece(2);

	ASSERT_TRUE(obj.gameState() == Blank);
}

// Now for some dummy patterns (i.e. completely irregular games, but ensures that the class
// can determine that a game where both players forming the same number of lines is counted as a tie)

// This game is a tie
/* Pattern:
	XOXO
	XOXO
	XOXO
*/
TEST(PiezasTest, tie_game_columns){
	Piezas obj;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 4; j++){
			obj.dropPiece(j);
		}
	}
	// Players have an equal number of columns. Thus,
	// the game is a tie.
	ASSERT_TRUE(obj.gameState() == Blank);
}

// This game is also a tie, but using another pattern
/* Pattern:
	XOXO
	OOOO
	XXXX
*/
TEST(PiezasTest, tie_game_rows){
	Piezas obj;
	
	obj.dropPiece(0);
	obj.dropPiece(0);
	obj.dropPiece(1);
	obj.dropPiece(1);

	obj.dropPiece(2);
	obj.dropPiece(2);
	obj.dropPiece(3);
	obj.dropPiece(3);

	obj.dropPiece(0);
	obj.dropPiece(1);
	obj.dropPiece(2);
	obj.dropPiece(3);

	// Players have an equal number of rows.
	// Thus, the game is a tie.
	ASSERT_TRUE(obj.gameState() == Blank);
}