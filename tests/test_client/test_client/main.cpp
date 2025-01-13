#include <gtest/gtest.h>
#include "GameLogic.h"
#include <fstream>
#include <sstream>

TEST(GameStateTest, UpdateXML_CreatesValidFile) {
    std::string player = "X";
    std::string gameType = "Man vs Man";
    std::vector<std::vector<char>> board = { {'X', '_', '_'}, {'_', 'O', '_'}, {'_', '_', '_'} };

    updateXML(player, gameType, board);

    std::ifstream file("game_state.xml");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string fileContents = buffer.str();

    ASSERT_NE(fileContents.find("<Player>X</Player>"), std::string::npos);
    ASSERT_NE(fileContents.find("<GameType>Man vs Man</GameType>"), std::string::npos);
    ASSERT_NE(fileContents.find("<Cell>X</Cell>"), std::string::npos);
    ASSERT_NE(fileContents.find("<Cell>O</Cell>"), std::string::npos);
}

TEST(GameStateTest, CreateGameStateXML_CreatesFile) {
    std::string filename = "new_game_state.xml";
    char firstPlayer = 'O';
    std::string gameMode = "AI vs Man";
    std::vector<std::vector<char>> board = { {'_', '_', '_'}, {'_', '_', '_'}, {'_', '_', '_'} };

    createGameStateXML(filename, firstPlayer, gameMode, board);

    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open());
    std::string line;
    std::getline(file, line);
    ASSERT_NE(line.find("<Player>O</Player>"), std::string::npos);
    ASSERT_NE(line.find("<GameType>AI vs Man</GameType>"), std::string::npos);
}

TEST(GameStateTest, SelectFirstPlayer_ValidChoice) {
    std::istringstream input("1\n");
    std::cin.rdbuf(input.rdbuf());
    char result = selectFirstPlayer();
    ASSERT_EQ(result, 'X');

    input.str("2\n");
    std::cin.rdbuf(input.rdbuf());
    result = selectFirstPlayer();
    ASSERT_EQ(result, 'O');

    input.str("3\n");
    std::cin.rdbuf(input.rdbuf());
    result = selectFirstPlayer();
    ASSERT_TRUE(result == 'X' || result == 'O');
}

TEST(GameStateTest, MakeMove_ValidMove) {
    std::vector<std::vector<char>> board(3, std::vector<char>(3, '_'));

    bool success = makeMove(board, 5, 'X');
    ASSERT_TRUE(success);
    ASSERT_EQ(board[1][1], 'X');

    success = makeMove(board, 5, 'O');
    ASSERT_FALSE(success);
}

TEST(GameStateTest, PrintBoard) {
    std::vector<std::vector<char>> board = { {'X', 'O', '_'}, {'_', '_', '_'}, {'_', '_', '_'} };
    ASSERT_NO_THROW(printBoard(board));
}

TEST(GameStateTest, ParseGameStateXML_ValidFile) {
    std::ofstream file("valid_game_state.xml");
    file << "<GameState><Player>X</Player>"
        << "<GameType>Man vs AI</GameType>"
        << "<Board><Row><Cell>X</Cell><Cell>O</Cell><Cell>_</Cell></Row>"
        << "<Row><Cell>_</Cell><Cell>_</Cell><Cell>_</Cell></Row>"
        << "<Row><Cell>_</Cell><Cell>_</Cell><Cell>_</Cell></Row></Board>"
        << "<Status>Start</Status></GameState>";
    file.close();

    char firstPlayer;
    std::string gameMode, gameStatus;
    std::vector<std::vector<char>> board(3, std::vector<char>(3, '_'));

    parseGameStateXML("valid_game_state.xml", firstPlayer, gameMode, board, gameStatus);

    ASSERT_EQ(firstPlayer, 'X');
    ASSERT_EQ(gameMode, "Man vs AI");
    ASSERT_EQ(gameStatus, "Start");
    ASSERT_EQ(board[0][0], 'X');
    ASSERT_EQ(board[0][1], 'O');
    ASSERT_EQ(board[0][2], '_');
}

TEST(GameStateTest, ParseGameStateXML_NonExistentFile) {
    char firstPlayer;
    std::string gameMode, gameStatus;
    std::vector<std::vector<char>> board(3, std::vector<char>(3, '_'));

    ASSERT_NO_THROW(parseGameStateXML("non_existent_file.xml", firstPlayer, gameMode, board, gameStatus));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
