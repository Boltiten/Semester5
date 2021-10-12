#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <functional>

using namespace std;

class ChessBoard
{
public:
    enum class Color
    {
        WHITE,
        BLACK
    };
    class Piece
    {
    public:
        Piece(Color color) : color(color) {}
        virtual ~Piece() {}

        int xPos, yPos;
        Color color;
        std::string color_string() const
        {
            if (color == Color::WHITE)
                return "white";
            else
                return "black";
        }
        string color_char() const
        {
            if (color == Color::WHITE)
                return "w";
            else
                return "b";
        }

        /// Return color and type of the chess piece
        virtual std::string type() const = 0;
        virtual std::string type_short() const = 0;

        /// Returns true if the given chess piece move is valid
        virtual bool valid_move(int from_x, int from_y, int to_x, int to_y) const = 0;
    };

    class King : public Piece
    {
    public:
        King(Color color) : Piece(color) {}

        /// Return color and type of the chess piece
        std::string type() const override
        {
            return "King" + Piece::color_string();
        }
        std::string type_short() const override
        {
            return "k" + Piece::color_char();
        }

        /// Returns true if the given chess piece move is valid
        bool valid_move(int from_x, int from_y, int to_x, int to_y) const override
        {
            if ((from_x == to_x - 1 || from_x == to_x + 1) || (from_y == to_y - 1 || from_y == to_y + 1))
            {
                return true;
            }
            return false;
        }
    };

    class Knight : public Piece
    {
    public:
        Knight(Color color) : Piece(color) {}

        /// Return color and type of the chess piece
        std::string type() const override
        {
            return "Type: Knight" + Piece::color_string();
        }
        std::string type_short() const override
        {
            return "n" + Piece::color_char();
        }

        /// Returns true if the given chess piece move is valid
        bool valid_move(int from_x, int from_y, int to_x, int to_y) const override
        {

            if (((from_x == to_x - 1 || from_x == to_x + 1) && (from_y == to_y - 2 || from_y == to_y + 2)) || ((from_x == to_x - 2 || from_x == to_x + 2) && (from_y == to_y - 1 || from_y == to_y + 1)))
            {
                return true;
            }
            return false;
        }
    };

    ChessBoard()
    {
        // Initialize the squares stored in 8 columns and 8 rows:
        squares.resize(8);
        for (auto &square_column : squares)
            square_column.resize(8);
    }
    

    /// 8x8 squares occupied by 1 or 0 chess pieces
    vector<vector<unique_ptr<Piece>>> squares;

    /// Move a chess piece if it is a valid move.
    /// Does not test for check or checkmate.
    bool move_piece(const std::string &from, const std::string &to)
    {
        int from_x = from[0] - 'a';
        int from_y = stoi(string() + from[1]) - 1;
        int to_x = to[0] - 'a';
        int to_y = stoi(string() + to[1]) - 1;

        auto &piece_from = squares[from_x][from_y];
        if (piece_from)
        {
            if (piece_from->valid_move(from_x, from_y, to_x, to_y))
            {
                auto &piece_to = squares[to_x][to_y];
                if (piece_to)
                {
                    if (piece_from->color != piece_to->color)
                    {
                        if (print_take_piece) print_take_piece(piece_to->type(), from, to);
                        if (auto king = dynamic_cast<King *>(piece_to.get())){
                            if (print_game_lost) print_game_lost (king->color_string());
                        }
                    }
                    else
                    {
                        // piece in the from square has the same color as the piece in the to square
                        if (print_invalid_move) print_invalid_move(piece_from->type(), from, to);
                        return false;
                    }
                }
                piece_to = move(piece_from);
                if (print_move) print_move(*piece_to, from, to);
                return true;
            }
            else
            {
                if (print_invalid_move) print_invalid_move(piece_from->type(), from, to);
                return false;
            }
        }
        else
        {
            if(print_no_piece_at_space)print_no_piece_at_space(from);
            return false;
        }
    }    
    function<void(const Piece &piece, const std::string &from, const std::string &to)> print_move;
    function<void(const std::string &color, const std::string &from, const std::string &to)> print_take_piece;
    function<void(const std::string &color)> print_game_lost;    
    function<void(const std::string &color, const std::string &from, const std::string &to)> print_invalid_move;
    function<void(const std::string &from)> print_no_piece_at_space;


    std::string printChessBoard()
    {
        std::string boardstate = "";
        cout << "Board state" << endl;
        vector<string> rows(8);
        int i = 0;
        for (auto &columns : squares)
        {
            for (auto &piece : columns)
            {
                if (piece == nullptr)
                {
                    rows[i] += " □ ";
                }
                else
                {
                    rows[i] += " ";
                    rows[i] += piece->type_short();
                }
                i += 1;
            }
            i = 0;
        }

        for (int i = rows.size() - 1; i >= 0; i--)
        {
            boardstate.append(rows[i]);
            boardstate.append("\n");
        }
        return boardstate;

        //omsorter til rekker
    }
    
};

class ChessBoardPrint
{
public:
    ChessBoardPrint(ChessBoard &board)
    {
        board.print_move = [&board](const ChessBoard::Piece &piece, const std::string &from, const std::string &to){
            cout << piece.type() << " is moving from " << from << " to " << to << endl;
            std::cout<<board.printChessBoard()<<std::endl;
        };
        board.print_take_piece = [&board](const std::string &color, const std::string &from, const std::string &to){
            cout << color << " is being removed from " << to << endl;
            std::cout<<board.printChessBoard()<<std::endl;
        };
        board.print_game_lost = [&board](const std::string &color){
            cout << color << " lost the game" << endl;
        };
        board.print_invalid_move = [&board](const std::string &color, const std::string &from, const std::string &to){
            cout << "can not move " << color << " from " << from << " to " << to << endl;
        };
        board.print_no_piece_at_space = [&board](const std::string &from){
            cout << "no piece at " << from << endl;
        };
    }
};

int main()
{
    ChessBoard board;
    ChessBoardPrint print(board);

    board.squares[4][0] = make_unique<ChessBoard::King>(ChessBoard::Color::WHITE);
    board.squares[1][0] = make_unique<ChessBoard::Knight>(ChessBoard::Color::WHITE);
    board.squares[6][0] = make_unique<ChessBoard::Knight>(ChessBoard::Color::WHITE);

    board.squares[4][7] = make_unique<ChessBoard::King>(ChessBoard::Color::BLACK);
    board.squares[1][7] = make_unique<ChessBoard::Knight>(ChessBoard::Color::BLACK);
    board.squares[6][7] = make_unique<ChessBoard::Knight>(ChessBoard::Color::BLACK);

    board.printChessBoard();

    cout << "Invalid moves:" << endl;
    board.move_piece("e3", "e2");
    board.move_piece("e1", "e3");
    board.move_piece("b1", "b2");
    cout << endl;

    cout << "A simulated game:" << endl;
    board.move_piece("e1", "e2");
    board.move_piece("g8", "h6");
    board.move_piece("b1", "c3");
    board.move_piece("h6", "g8");
    board.move_piece("c3", "d5");
    board.move_piece("g8", "h6");
    board.move_piece("d5", "f6");
    board.move_piece("h6", "g8");
    board.move_piece("f6", "e8");
}