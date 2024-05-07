# HEX - second project for Algorithms and data structures
Details about the game: https://en.wikipedia.org/wiki/Hex_(board_game)

## Input/Output
in the folder ,,exampleInputOutput" are example tests. Files contain: 1.input, 2.verified correct output and 3.my output (is also correct!:D ). 

## Build 
1. Go to folder with the project in terminal.
2. g++ *.cpp -o main \
   (In the third step change the number (21) with your specific number. Possible numbers to choose: {1,2,4,6,11,16,21}.  
4. ./main < exampleInputOutput/input/test21.in > exampleInputOutput/my\ output/output21.out
5. Use this website to compare my and correct output: https://www.diffchecker.com ( alternatively you can use command ,,diff" to compare outputs

## Problems to face
1. BOARD_SIZE - a number from the range <1;11> indicating the size of the board
2. PAWNS_NUMBER - a number from the range <0;121> indicating the number of pawns of both players on the board.
3. IS_BOARD_CORRECT - a YES/NO response indicating whether the state of the board is correct, in other words, whether the number of pawns of one player is appropriate relative to the number of pawns of the other player.
4. IS_GAME_OVER - a YES RED/YES BLUE/NO response indicating whether (and if so, which) player has ended the game, i.e., whether they have connected two edges of the board with an uninterrupted path of their color.
5. IS_BOARD_POSSIBLE - a YES/NO response indicating whether the state of the board is possible. This means that the board is correct and that achieving such a state did not result in overlooking an earlier win by one of the players.
6. CAN_RED_WIN_IN_N_MOVE_WITH_NAIVE_OPPONENT - a YES/NO response indicating whether one of the players can end the game in N (where N belongs to <1;2>) moves when playing against a naive opponent (making the worst possible moves for themselves). The number of moves N indicates the number of moves by the player for whom we are considering victory. Victory must occur in the Nth move, which means that the player must have the ability to make such a number of moves.
For example, if we are checking whether the red player can win in N = 2 moves and the current move belongs to the blue player, both players will make two moves. In the case where the current move belongs to the red player, the red player will make two moves and the blue player only one.
7. CAN_RED_WIN_IN_N_MOVE_WITH_PERFECT_OPPONENT - analogous case to the previous one, with the difference that the player checks whether they can end the game playing against a perfect opponent (making the best possible moves for themselves) in N (where N belongs to <1;2>) moves.
## Tests
<img width="417" alt="Screenshot 2024-05-01 at 11 57 44" src="https://github.com/HubGitPL/hex/assets/72828637/392b49e6-b30e-4089-8ace-66510654850d">
